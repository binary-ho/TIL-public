# Graceful Shutdown
# 1. Tomcat

- JVM은 기본적으로 활성 스레드 갯수를 세고 있음
- 데몬 스레드 외의 모든 스레드가 종료되면 프로그램 종료
- SIGKILL → 바로 종료
- SIGTERM → Singnal + Terminate 종료신호 보냄 (종료 명령어는 더 알아봐야 할듯)
- 무한으로 돌면 어떡함?
    - Spring에서 Graceful Shutdown 설정할 때 무한루프 방지를 위해 시간 제한을 줄 수 있다.
        
        ```bash
        spring:
          lifecycle:
            timeout-per-shutdown-phase: 5s
        ```

<br>


## 1.1 Tomcat GracefulShutdown 과정

![image](https://github.com/user-attachments/assets/df5e07f1-a74f-4734-ac61-c08e29de41b4)


- WebServerManger가 GracefulShutdown 객체 가지고 있음. shutdowngracefully 호출
- WebServerGracefulShutdownLifecycle 에서도 호출함

```java
public class TomcatWebServer implements WebServer {

	private final Tomcat tomcat;

	private final GracefulShutdown gracefulShutdown;

	/**
	 * Initiates a graceful shutdown of the Tomcat web server. Handling of new requests is
	 * prevented and the given {@code callback} is invoked at the end of the attempt. The
	 * attempt can be explicitly ended by invoking {@link #stop}.
	 * <p>
	 * Once shutdown has been initiated Tomcat will reject any new connections. Requests
	 * on existing idle connections will also be rejected.
	 */
	@Override
	public void shutDownGracefully(GracefulShutdownCallback callback) {
		if (this.gracefulShutdown == null) {
			callback.shutdownComplete(GracefulShutdownResult.IMMEDIATE);
			return;
		}
		this.gracefulShutdown.shutDownGracefully(callback);
	}
```

<br>

- GracefullShutdown 객체의 함수를 호출한다.
- shutdown 시도

```java
	void shutDownGracefully(GracefulShutdownCallback callback) {
		logger.info("Commencing graceful shutdown. Waiting for active requests to complete");
		CountDownLatch shutdownUnderway = new CountDownLatch(1);
		new Thread(() -> doShutdown(callback, shutdownUnderway), "tomcat-shutdown").start();
		try {
			shutdownUnderway.await();
		}
		catch (InterruptedException ex) {
			Thread.currentThread().interrupt();
		}
	}
```

<br>

- doShutdown을 호출

1. 커넥터 리스트를 전부 가져온다.
2. 커넥터 전부 close
3. isActive && GracefulShutdown 객체 aborted false인 동안 대기한다.
	- 처리중인 비동기 요청이 있거나, Servlet이 처리중인 요청이 있으면 Active
4. shutdown 완료


```java
	private void doShutdown(GracefulShutdownCallback callback, CountDownLatch shutdownUnderway) {
		try {
			// getConnectors로 커넥터 리스트 가져온다.
			List<Connector> connectors = getConnectors();
			// 커넥터를 닫는다.
			connectors.forEach(this::close);
			shutdownUnderway.countDown();
			awaitInactiveOrAborted();
			if (this.aborted) {
				logger.info("Graceful shutdown aborted with one or more requests still active");
				callback.shutdownComplete(GracefulShutdownResult.REQUESTS_ACTIVE);
			}
			else {
				logger.info("Graceful shutdown complete");
				callback.shutdownComplete(GracefulShutdownResult.IDLE);
			}
		}
		finally {
			shutdownUnderway.countDown();
		}
	}
```

<br>

## 1.2 Connector "Close" 의미

- Connector Close 의미 연결은 유지하되, 새로운 요청을 수신 X

```java
	private void close(Connector connector) {
		connector.pause();
		connector.getProtocolHandler().closeServerSocketGraceful();
	}
	
	
// connector.pause()에서 호출하는 AbstractEndpoint.java의 pause: 새로운 연결을 accepting을 stop
  /**
 * Pause the endpoint, which will stop it accepting new connections and
 * unlock the acceptor.
 */
  public void pause() {
      if (running && !paused) {
          paused = true;
          releaseConnectionLatch();
          unlockAccept();
          getHandler().pause();
      }
  }

// ProtocolHandler.java의 closeServerSocketGraceful: 서버 소켓을 닫아 추가 연결 방지
  /**
 * Close the server socket (to prevent further connections) if the server socket was bound on {@link #start()}
 * (rather than on {@link #init()} but do not perform any further shutdown.
 */
void closeServerSocketGraceful();
```

<br>

## 1.3 awaitInactiveOrAborted

- awaitInactiveOrAborted: inactive나 aborted를 기다린다.
- aborted가 아니고, active인 동안 대기

```java
	private void awaitInactiveOrAborted() {
		try {
			for (Container host : this.tomcat.getEngine().findChildren()) {
				for (Container context : host.findChildren()) {
					while (!this.aborted && isActive(context)) {
						Thread.sleep(50);
					}
				}
			}
		}
		catch (InterruptedException ex) {
			Thread.currentThread().interrupt();
		}
	}
	
	
	// GracefultShutdown.java의 abort는 TomcatWebServer.java의 stop()에서 호출한다.
	void abort() {
		this.aborted = true;
	}
	
	// TomcatWebServer.java stop()
	@Override
	public void stop() throws WebServerException {
		synchronized (this.monitor) {
			boolean wasStarted = this.started;
			try {
				this.started = false;
				if (this.gracefulShutdown != null) {
					// 여기서 호출
					this.gracefulShutdown.abort();
				}
				removeServiceConnectors();
			}
			catch (Exception ex) {
				throw new WebServerException("Unable to stop embedded Tomcat", ex);
			}
			finally {
				if (wasStarted) {
					containerCounter.decrementAndGet();
				}
			}
		}
	}
```

<br>

## 1.4 Active 판단 기준은?

- `getInProgressAsyncCount()`: 처리중인 비동기 요청이 있으면 Active
- `getCountAllocated()` Servlet이 처리중인 요청이 있으면? Active

```java
	private boolean isActive(Container context) {
		try {
			if (((StandardContext) context).getInProgressAsyncCount() > 0) {
				return true;
			}
			for (Container wrapper : context.findChildren()) {
				if (((StandardWrapper) wrapper).getCountAllocated() > 0) {
					return true;
				}
			}
			return false;
		}
		catch (Exception ex) {
			throw new RuntimeException(ex);
		}
	}
```

<br>

## 1.5 요약

1. Tomcat에서 연결 스레드 세고 있음
2. WebServerManger나, WebServerGracefulShutdownLifecycle에서 `shutdowngracefully()` 호출로 시작
3. GracefullShutdown의 `shutDownGracefully()` 호출
4. Connector 리스트를 가져와 모든 커넥터 닫는다.
    - 닫는다는 의미: 연결은 유지하되, 새로운 요청을 수신하지 않음.
    - connector의 pause와 closeServerSocketGraceful 호출
5. 현재 연결된 종료를 기다린다.
    - GracefulShutdown 객체의 abort 대기
    - isActive 판단 기준
        - 처리중인 비동기 요청이 있으면 Active
        - Servlet이 처리중인 요청이 있으면 Active
        (Context Children 중 할당된 Container가 있으면 Active)

# 2. 백그라운드 수행 로직들은 어떻게 할 것인가?

- ThreadPoolExecutor 활용 로직이라면 테스크 Complete를 기다릴 수 있다.

```yaml
corePoolSize : 2
maxPoolSize : 64
queueCapacity : 500
threadNamePrefix : "async-executor-" 
rejectedExecutionHandler : ThreadPoolExecutor.CallerRunsPolicy()

# Graceful Shutdown 
waitForTasksToCompleteOnShutdown : true
awaitTerminationSeconds : 30
```

- `waitForTasksToCompleteOnShutdown=true` 로 가능
- `awaitTerminationSeconds` 로 Termination 시간 설정 가능한데,
기본값이 0이다.. 그래서 `waitForTasksToCompleteOnShutdown`만 설정하면 사실상 즉시종료
    
    [001프로젝트 / ThreadPoolTaskExecutor를 이용한 Spring에서 Graceful Shutdown 구현해 보기](https://ocblog.tistory.com/83)
    
    [ThreadPoolTaskExecutor의 waitForTasksToCompleteOnShutdown 속성 알아보기](https://sungjk.github.io/2023/05/22/spring-boot-graceful-shutdown.html)
    
- 옵션 정리글
    
    [ThreadPoolTaskExecutor 옵션 설명](https://velog.io/@bonjugi/ThreadPoolTaskExecutor-%EC%98%B5%EC%85%98-%EC%84%A4%EB%AA%85)
    

<br>

# 3. 실전 Case

## 3.1 컨슈머 Application 종료시

- 컨슈머 종료는 주의해야 한다.
- 소비중인 메시지를 처리하고 종료할 수 있다?
    - 커밋 시점에 따라 유실되는 메시지가 있을 수도 있다.
    - 커밋 시점을 잘? 조절하면 되지만 메시지 중복 문제가 있을 수 있다?
- 메시지를 모두 사용하고 종료하도록 커스텀
Java에서는 어떻게 할 수 있는지 알아봐야?

[알고도 놓치는 Graceful Shutdown](https://medium.com/@sudosubin/%EC%95%8C%EA%B3%A0%EB%8F%84-%EB%86%93%EC%B9%98%EB%8A%94-graceful-shutdown-6ba48ca75bec)

## 3.2 인프라 레벨 Graceful Shutdown

결국 쿠버든 도커든 Application에 Sigterm 잘 보내고, 제한 시간 관리하고, sigkill까지 잘 하면 된다.

- 아티클

[[Docker] Graceful Shutdown in Docker](https://ingnoh.tistory.com/39)

[Kubernetes Pod의 Graceful 한 종료](https://wlsdn3004.tistory.com/14#google_vignette)

## Reference

[SpringBoot Graceful-Shutdown 개념과 동작 원리](https://velog.io/@byeongju/SpringBoot%EC%9D%98-Graceful-Shutdown)

[tomcat architecture](https://kbss27.github.io/2017/11/16/tomcatarchitecture/)
