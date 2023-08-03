# Item 78. 공유 중인 가변 데이터는 동기화해 사용하라
synchronized 키워드는 적용 범위에 따라 해당 메서드나 블록을 한번에 한 스레드씩 수행하는 것을 보장한다. <Br>

많은 프로그래머가 동기화에 대해 오해하는 부분이 있다. <br>
동기화는 단순히 한 스레드가 어떤 데이터를 변경중일때, 다른 스레드가 확인하는 것을 막는 정도로 생각한다. <br> 

하지만 동기화에는 중요한 기능이 하나 더 있는데, 동기화 없이는 한 스레드가 만든 변화를 다른 스레드에서 확인하지 못할 수도 있다. <br>
동기화는 
1. 일관성이 깨진 상태를 볼 수 없게 해야 하고,
2. **동기화된 메서드나 블록에 들어간 스레드가 같은 락의 보호하에 수행된 모든 이전 수정의 최종 결과를 보게 해야한다**

<br>

**그러니까 결국 최신 상태를 보여줘야 한다는 것이다.** <br>

## 1. VM 최적화와 동기화의 필요성
언어 명세상 long과 double 외의 변수를 읽고 쓰는 것은 원자적이라고 한다. <br> 
여러 스레드가 같은 변수를 동기화 없이 수정하는 중이여도, 
항상 어떤 스레드가 정상적으로 저장한 값을 온전히 읽어오는 것을 보장한다. <Br> <br>

오! long과 double 외의 변수는 읽고 쓸때 동기화 안 해야지~ 할 수도 있다. <Br>
하지만 이건 틀렸습니다~ <br>

**자바 언어 명세는 스레드가 필드를 읽을 때 항상 수정이 완전히 반영된 값을 얻는다고 보장하지만, <br> 한 스레드가 저장한 값이 다른 스레드에게 보이는가는 보장하지 않는다.**  <br>
먼 소리고...  <br>

공유중인 가변 데이터를 비록 원자적으로 읽고 쓸 수 있더라도, 동기화 해줘야 한다 <br>
JVM의 호이스팅은, 어떤 루프문 안에서 어떤 값에 대한 연산이 필요 없다고 예상되면, 루프문 밖으로 꺼낸다.
js의 호이스팅과는 많이 다르다.


<br>

예를 들어서 아래와 같은 코드를 보자. <br>
backgroundThread는 stopRequested 값을 확인하면서, false인 경우 계속 루프를 돈다. <Br>

```java
public class StopThread {
    private static boolean stopRequested;

    public static void main(String[] args)
            throws InterruptedException {
        Thread backgroundThread = new Thread(() -> {
            int i = 0;
            while (!stopRequested)
                i++;
        });
        backgroundThread.start();

        TimeUnit.SECONDS.sleep(1);
        stopRequested = true;
    }
}
```

main 메서드의 최하단에서 stopRequested를 true로 변경하면서, <br> 
backgroundThread가 while 루프를 탈출하는 것을 기대하고 있다. <br>
하지만, 실제로는 멈추지 않는다. <br>
앞서 언급한 JVM의 최적화 방식중 하나인 호이스팅 때문인데, while 루프 부분을 코드를 아래와 같이 변경시킨다.

```java
// 원래 코드
while(!stopRequest) {
  i++;
}

// 최적화한 코드
if (!stopRequested)
  while (true)
    i++;

```

쓰레드의 루프 내부에선 stopRequested를 변경시키는 부분이 없기 때문에,
사실상 stopRequested가 false면 무한으로 루프를 돌으라고 명령한 것으로 받아들이는 것이다. <Br>


출처 : https://zbvs.tistory.com/25

<br>


```java
public class StopThread {
    private static boolean stopRequested;

    private static synchronized void reqeuestStop() {
      stopRequested = true;
    }

    private static synchronized boolean getStopRequested() {
      return stopRequested;
    }

    public static void main(String[] args)
            throws InterruptedException {
        Thread backgroundThread = new Thread(() -> {
            int i = 0;
            while (!getStopRequested())
                i++;
        });
        backgroundThread.start();

        TimeUnit.SECONDS.sleep(1);
        reqeuestStop();
    }
}
```

<br>

쓰기 메서드와 읽기 메서드 둘 다 동기화 하는 것이 중요하다고 한다. <br>
쓰기와 읽기 모두가 동기화 되지 않으면 동작을 보장하지 못한다고 한다. <br>
물론 동작은 되는데 겉모습에 속으면 안 된다고 한다. <br>

## 2. volatile 한정자
위 코드에서 volatile을 사용하는 것도 좋은 방법이다. <Br>
volatile 한정자는 항상 메모리에 저장된 변수 값의 가장 최근에 기록된 값을 읽는 것을 보장한다.

```java
public class StopThread {
    private static volatile boolean stopRequested;

    public static void main(String[] args)
            throws InterruptedException {
        Thread backgroundThread = new Thread(() -> {
            int i = 0;
            while (!stopRequested)
                i++;
        });
        backgroundThread.start();

        TimeUnit.SECONDS.sleep(1);
        stopRequested = true;
    }
}
```

실제로 돌려보니 잘 동작했다. <br>

## 3. volatile은 무적이 아냐

volatile는 메모리에 기록된 최근 값을 읽는 것을 보장해주는 것은 맞다. <br>
그러나 활용시 실수할 수도 있는 부분이 있어, 주의를 요한다.

```java
private static volatile int nextSerialNumber = 0;

public static int generateSerialNumber() {
  return nextSerialNumber++;
}
```

return을 하는 부분에서 nextSerialNumber 값을 읽고 -> 1만큼 값을 올려 겹치는 시리얼 번호가 없도록 하는 프로그램이다. <br>
그런데 값을 읽는 순간, 그리고 값을 1만큼 올리기 "전에" 다른 스레드가 난입했다고 생각해보자. <br>
결국 같은 시리얼 값을 갖는 제품이 만들어진다. <br>
값을 읽고, 키우고, 저장하는 과정 자체가 보호받지 못해서 생기는 분제이다. <br>
**이렇게 프로그램이 잘못된 결과를 계산하는 오류를 안전 실패라고 부른다. (safety failure)** <br> <br>
문제를 해결하려면 그냥 generateSerialNumber 자체를 `synchronized`를 붙여 보호해 버리면 된다. <br>
물론 nextSerialNumber의 volatile은 필요 없어진다.

## 4. Atomic Type
`java.util.concurrent.atomic` 패키지의 AtomicLong, AtomicXXX 클래스는 락 없이도 스레드 안전한 프로그래밍을 지원해주는 클래스들이 담겨있다. <br>
volatile은 동기화의 두 효과 중 통신 쪽만 지원하지만, 이 패키지는 원자성까지 지원해준다. <Br>
그리고 성능도 위의 버전 보다 우수하다. 


```java
  private static final AtomicLong nextSerialNumber = new AtomicLong();

  public static long generateSerialNumber() {
      return nextSerialNumber.getAndIncrement();
  }
```


사실 가장 좋은 방법은 그냥 데이터를 공유해서 사용하지 않는 것이다. <br>
가변 데이터는 단일 스레드에서만 사용하자! 

## Reference
- Effective Java <조슈아 블로크>
