# [Spring] Spring WebSocket과 STOPM (1)
## 1. Spring WebSocket이란?
방식 3개
1. 폴링: 일정 주기를 두고 데이터를 받아 옴.
2. Server-Sent-Events: 서버의 갱신이 감지될 때마다 받아 옴.
3. Spring WebSocket: 실시간으로 교환함

## 2. 의존성 추가
Gradle dependencies에 `org.springframework.spring-boot-starter-websocket`을 추가해 줌으로서, 의존성을 추가해줄 수 있다. <br> <br>

## 3. 핸들러와 설정 파일 만들기
이후, `TextWebSocketHandler`를 상속받은 `WebSocketHandler` 클래스를 정의합니다. 그리고 WebSocketConfigurer 인터페이스를 구현한 `WebSocketConfiguration` 클래스를 작성합니다.

```java
@Configuration
@EnableWebSocket
public class WebsocketConfig implements WebSocketMessageBrokerConfigurer {

  @Override
  public void registerStompEndpoints(WebSocketHandlerRegistry registry) {
    registry
    .addHandler(signalingSocketHandler(), "/room")
    .setAllowedOrigin("*");
  }

  @Bean
  public WebSocketHandler signalingSocketHandler() {
    return new WebSocketHandler();
  }
}
```
- `@EnableWebSocket`: 웹소켓 서버를 사용하도록 한다.
- `url:port/room`
- `setAllowedOrigin("*")`: 클라이언트에서 웹소켓 서버에 요청 시 모든 요청 수용 (CORS) -> 실제 서비스에서는 상황에 맞게 처리해야합니다.
- `WebSocketHandler`: WebSocketHandler 클래스를 웹소켓 핸들러로 정의합니다.


## 4. Handler와 End Point가 뭔가요?




### Reference
- https://brunch.co.kr/@springboot/695#
- https://blog.naver.com/ghdalswl77/222401162545
