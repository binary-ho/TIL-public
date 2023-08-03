# Item 80. 스레드보다는 실행자, 태스크, 스트림을 애용해라


## 1. 실행자와 태스크
`java.util.concurrent` 패키지의 ExecutorService를 사용하면, <br> 
클라이언트가 요청한 작업을 백그라운드 스레드에 위임해 비동기적으로 작업을 처리하는 작업 큐를 손쉽게 구현할 수 있다. <br> <br>

다양한 사용법과 주석들 달아 놓았다.
```java
    private static final ExecutorService executor = Executors.newSingleThreadExecutor();
    private static final AtomicInteger atomicInteger = new AtomicInteger();
    private static final Runnable task = atomicInteger::getAndIncrement;

    private static final Callable<Integer> task2 = atomicInteger::getAndIncrement;
    private static final List<Callable<Integer>> tasks = List.of(task2);


    public static void main(String[] args) {

        // 1. 실행자에 실행할 작업 넘기는 방법
        executor.execute(task);

        // 2. 실행자를 종료하는 방법
        // 작업이 실패해도 VM 자체가 종료되지 않는다.
        executor.shutdown();

        // 3. 특정 태스크가 완료되기를 기다리는 get 메서드
        try {
            executor.submit(task).get();
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }

        // 4. 태스크 모음 중 아무거나 한가지 혹은 모든 태스크가 완료되기를 기다린다.
        try {
            executor.invokeAny(tasks);  // 아무거나 하나 완료 기다림
            executor.invokeAll(tasks);  // 모든 태스크 완료 대기
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }

        // 5. 실행자 서비스가 종료하기를 기다린다.
        try {
            executor.awaitTermination(3L, TimeUnit.SECONDS);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // 6. 완료된 태스크들의 결과를 차례대로 받는 ExecutorCompletionService
        ExecutorCompletionService<Integer> executorCompletionService = new ExecutorCompletionService<>(executor);

        // 테스크 전달
        executorCompletionService.submit(() -> 10);

        // 작업 결과 받아오기기
        try {
            Future<Integer> future = executorCompletionService.take();
            Integer integer = future.get();
            System.out.println(integer);
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }

        // 7. 태스크를 특정 시간에 혹은 주기적으로 실행하게 한다.
        ScheduledThreadPoolExecutor scheduledThreadPoolExecutor = new ScheduledThreadPoolExecutor(20);
        scheduledThreadPoolExecutor.execute(task);

        // 딜레이와 함께 작업 예약하기
        scheduledThreadPoolExecutor.schedule(
            () -> System.out.println("Task1 executed"), 1, TimeUnit.SECONDS);

        // FixedRate로 반복 작업 예약
        scheduledThreadPoolExecutor.scheduleAtFixedRate(
            () -> System.out.println("Task2 executed"), 0, 2, TimeUnit.SECONDS);

        // 딜레이와 함꼐 반복 잡업 예약
        scheduledThreadPoolExecutor.scheduleWithFixedDelay(
            () -> System.out.println("Task3 executed"), 0, 3, TimeUnit.SECONDS);
    }

```



큐를 둘 이상의 스레드가 처리하도록 만들고 싶다면 다른 정적 팩터리를 이용해 다른 종류의 실행자 서비스를 생성하면 된다. (스레드 풀) 스레드 풀의 스레드 개수는 고정할 수도, 늘어나거나 줄어들도록 만들 수도 있다.

우리에게 필요한 실행자 대부분은 `java.util.concurrent.Exectors`의 정적 팩터리를 통해 생성할 수 있다.


## 작은 서버
작은 프로그램이나 가벼운 서버라면, 요청 태스크들이 큐에 쌓이지 않고, 즉시 스레드에 위임되어 실행되는 `Execturors.newCachedThreadPool`이 일반적으로 좋다. (`CachedThreadPool`) 가용 스레드가 없다면 새로 하나를 생성한다. <br>
무거운 프로덕션 서버에는 적합하지 않다. CPU 이용률이 100%까지 치닫게 될 수도 있다. <br>
좀만 무거워도 스레드 갯수를 고정하는 것이 좋다. <br>
-> `ThreadPoolExecutor`를 직접 사용하는 편이 낫다.

## 작업큐, 실행자, Task 
작업 큐를 손수 만드는 일은 삼가는 것이 좋다. <br>
일반적으로 스레드를 직접 다루는 일도 삼가는 것이 좋다. <br>
보통은 스레드를 직접 다루면, 작업단위와 수행 메커니즘 역할을 모두 수행하게 된다. <Br>
반면, 실행자 프레임워크에서는 작업단위와 실행 메커니즘이 분리된다! <br>
작업 단위를 나타내는 핵심 추상 개념이 태스크다.

1. Runnable
2. Callable : Runnable과 비슷하지만 값을 반환하고 임의의 예외를 던질 수 있다.


그리고 이런 태스크를 수행하는 일반적인 매커니즘이 바로 실행자 서비스이다. <br>
태스크 수행을 실행자 서비스에 맡기면 원하는 태스크 수행 정책을 선택할 수 있고, 생각이 바뀌면 언제든 변경할 수 있다. <br>

핵심은 컬랙션 프레임워크가 데이터 모음을 담당하듯이 실행자 프레임워크가 작업 수행을 담당해준다는 것이다. <br>

자바 7 부터 실행자 프레임워크는 포크-조인 태스크를 지원하도록 확장되었다. <br>
포크-조인 태스크는 포크-조인 풀이라는 특별한 실행자 서비스가 실행해준다. <br>
포크-조인 태스크 `ForkJoinTask`의 인스턴스는 작은 하위 태스크로 나뉠 수 있고, `ForkJoinPool`을 구성하는 스레드들이 이 태스크들을 처리하며, 일을 먼저 끝낸 태스크들은 다른 스레드의 남은 태스크를 가져와 대신 처리할 수도 있다. <br>
이렇게 모든 스레드를 바쁘게 돌려 CPU를 최대한 활용한다. <br>
높은 처리량과 낮은 지연시간을 달성한다. <br>
포크-조인 태스크를 직접 작성하고 튜닝하기는 어렵지만, 포크-조인 풀을 이용해 만든 병렬 스트림(아이템 48)을 이용하면 적은 노력으로 그 이점을 얻을 수 있다. <br>
물론 포크-조인에 적합한 형태의 작업이여야 한다.

## Reference
- Effective Java <조슈아 블로크>

