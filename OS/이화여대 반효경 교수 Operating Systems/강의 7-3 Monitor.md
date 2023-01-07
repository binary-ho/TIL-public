# Monitor
Monitor는 사용자에게 편리한 동시성 문제 해결을 위해 도입됐다. <Br>
Semaphore을 이용한 동시성 해결은 여러 단점들이 있었지만, '너무 어렵다'는 단점이 있었다. <Br>
그냥 주의하면 되는 것이 아닐까 싶지만, 그렇지 않다. 세마포어는 아주 조금의 실수로 모든 시스템에 치명적인 영향이 미칠 수도 있다. Mutual Exclusion이 깨지는 것을 넘어 DeadLock에 걸릴 수도 있다. <Br>
이 '어렵다'는 단점을 해결하기 위해 그냥 사용하지 않기로 했다. correctness의 입증이 어렵다거나, 자발적 협력이 필요하다는 점 외의 단점들을 해결하면서, 훨씬 사용이 쉬운 Monitor가 도입됐다. <br>
이를 Monitor라고 부른다. <br> <br>

모니터는 공유 자원 관리를 프로그래밍 언어 차원에서 지원해 주는 기능으로, <br>
**오직 모니터에서 정의된 프로시저들을 통해서만 공유 자원을 접근할 수 있게 한다** <BR>
모니터 안에 공유 자원들과 공유 자원들에 접근하는 프로시저들을 정의해둔 다음, **공유 자원들을 접근하기 위해선 내부 프로서저를 이용해야만 하게 하는 것이다.** <bR>
그리고 모니터는 내부적으로, 알아서 프로시저들이 동시에 실행되는 것을 막아준다. <BR>
프로그래머는 이제 힘들여 락을 걸어가며 동시성을 걱정할 필요가 없다. 그냥 Monitor를 믿고 코드를 짜면 되는 것이다.

### Condition Variable
Moniter에서 Mutual Conclusion을 위해 사용한다. 편한 동기화를 위해 도입한 변수 <br>
Condition Variable은 `wait()`와 `signal()` 연산에 의해서만 접근 가능하도록 되어 있다. <br>

- `x.wait()`을 invoke한 프로세스는 다른 프로세스가 `x.signal()`을 invoke 하기 전까지 suspend 된다.
- `x.signal()`은 정확히 하나의 suspend된 프로세스를 resume한다. 말이 어려운데, 자는 프로세스를 깨우는 것이다. <Br> Suspend된 프로세스가 없다면, 아무 일도 일어나지 않는다. <Br> 이 아무 일도 일어나지 않는다는 생각보다 프로그래머를 아주 편하게 해주는 기능이다. 어떤 예외 문제가 발생할 걱정 없이 `signal()`을 호출해버리면 되는 것이기 때문이다.


# 1. Bounded Buffer Problem

이제 모니터를 이용한 Classic Synchronization 문제들의 개선을 살펴보자.

```cpp
monitor bounded_buffer
{
  int buffer[N];

  /* condition variable들은 값을 가지지 않는다. 
  그냥 자신의 큐에 프로세스들을 줄줄이 매달아 둔다.
  이들을 sleep 시키거나 queue에서 깨우는 역할을 한다.*/
  condition full, empty;

  void produce (int x)
  {
    if (there is no empty buffer)
      empty.wait();
    
    add x to an empty buffer!
    full.signal();
  }

  void consume (int *x)
  {
    if (there is no full buffer)
      full.wait();
    
    remove an item from buffer and store it to *x
    empty.signal();
  }
}
```
이제 모니터를 통해 힘들게 lock variable등을 사용할 필요가 없다. 그냥 메서드들을 호출하기만 하면 된다.


# 2. Dining Philosophers Problem
이번엔 식사하는 철학자 문제를 개선한 부분이다.

```cpp
monitor dining_philosopher
{
  enum { thinking, hungry, eating } state[5];
  condition self[5];

  void pickup(int i) {
    state[i] = hungry;
    test(i);
    if (state[i] != eating) {
      self[i].wait();
    }
  }

  void putdown(int i) {
    state[i] = thinking;
    /* 양쪽 검사한다. */
    test((i + 4) % 5);
    test((i + 1) % 5);
  }

  void test(int i) {
    if ( state[(i + 4) % 5] != eating 
    && state[i] == hungry
    && state[(i + 1) % 5] != eating) {
      state[i] = eating;
      self[i].signal();
    }
  }

  void init() {
    for (int i = 0; i < 5; i++) {
      state[i] = thinking;
    }
  }
}
```

모니터 프로시저 준비를 끝냈으니, 호출한다.
```cpp
Each Philosopher
{
  pickup(i);
  eat();
  putdown(i);
  think();
} while(1);
```

## Reference
- [반효경 교수 OS 강의](http://www.kocw.net/home/search/kemView.do?kemId=1046323)
