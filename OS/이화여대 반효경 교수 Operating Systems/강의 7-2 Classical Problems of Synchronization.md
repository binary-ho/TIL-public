# Process Synchronization 2
# Classical Problems of Synchronization
고전적인 3가지 Synchronization 문제를 살펴보자.
1. **Bounded-Buffer Problem (Producer-Consumer Problem)**
2. **Readers and Writers Problem**
3. **Dining-Philosophers Problem**

### `wait()`는 `P`에, `signal()`은 `V`에 해당한다!

# 1. Bounded-Buffer Problem 
유한 버퍼 문제는 버퍼의 크기가 유한한 상황에서의 문제이다. (생산자-소비자 문제.) <br>

// 그림
Producer는 빈 버퍼가 있으면 해당 버퍼를 사용해 데이터를 **입력하거나** 조작하는 존재이고, Consumer는 꽉찬 버퍼가 있다면 데이터를 **꺼내고** buffer를 조작하는 존재이다. <br> 
하나는 넣고 하나는 꺼낸다. 하나는 데이터를 생산하고, 하나는 데이터를 소비한다. 그래서 생산자-소비자 문제이다. <br>


### 나도 이거 먹을래
하나의 버퍼를 공유하므로, 생산자 둘이 비어있는 버퍼 하나에 접근해 해당 버퍼를 둘이서 쓰거나, 소비자 둘이 차있는 버퍼 하나에 접근해 해당 데이터를 둘 다 소비하려 할 수도 있다. <Br>
그래서 각 생산자나 소비자는 자신의 역할을 행하기 전에 **먼저 Lock을 건다.** <br>
각 화살표는 한 칸씩 화살표를 이동하며 원형 버퍼를 사용한다. <br>

### 꽉차거나 텅 비거나
**두 번째 문제로는** 버퍼가 꽉찼는데 생산자가 새로 데이터를 만들어 넣고 싶거나, 버퍼가 전부 비어있는데 소비자가 소비를 희망할 때이다. <Br>

생산자와 소비자는 이런 상황에서, 기다릴 줄 알아야한다. <br>


### 어떻게 해결할까
생산자-소비자 문제를 해결하기 위해서는 아래의 두 가지 조취가 필요하다. -> 화살표 이후엔 이를 해결하기 위해 도입된 **세마포어 변수의** 이름을 적었다. 
1. 한 버퍼에 동시에 여러 프로세스가 접근하는 것을 막기 위해 전체 버퍼 풀에 락을 걸 수 있어야 한다. -> `mutex`
2. 꽉 차거나 텅 빈 상황에 대한 대처가 가능해야 한다. -> `full`, `empty`

두 가지 모두 반영된 수도 코드를 확인해보자. <br>
(강의에서 보다 더 깔끔한 코드를 보이고 싶어서 친구 블로그에서 훔쳐왔다. 하단 출처 기재함.)
```cpp
int N; 
semaphore mutex = 1; 
semaphore empty = N; 
semaphore full = 0; 
```

일단 3가지 세마포어 변수를 도입했다. N이 총 버퍼의 갯수일 때, 
1. `mutex`: 버퍼 풀에 한번에 접근 가능한 프로세스의 갯수 -> 1이다! 한번에 하나만 접근해라. 전체 락을 걸기 위한 변수.
2. `empty`: 비어 있는 버퍼의 수를 나타낸다. 초기엔 당연히 N개가 비어 있다.
3. `full`: 꽉 찬 버퍼의 수를 나타낸다. 초기엔 0개가 차 있다.


### 생산자 코드
```cpp
do {
  
  ...
  
  wait(empty); /* 빈 버퍼 갯수가 0개라면 대기 */
  wait(mutex); /* 들어가면서 버퍼 풀에 접근 가능한 프로세스 수를 1 감소 */
  
  /* 로직 */

  signal(mutex); /* 나오면서 접근 가능 프로세스 1 증가 */
  signal(full); /* 꽉 찬 버퍼 수 1 증가 */

} while(1);
```
생산자 코드는 위와 같이 구성 되어있다. <br>
버퍼 풀에 **비어있는 버퍼가 없거나,** mutex가 0이라면 대기한다. <br>
그리고 들어가면서 empty와 mutex값을 1 감소시킨다. <Br>
들어가서 할 일을 마치고 나올 때 다시 mutex 값을 1 늘린다. <Br>
그리고 **꽉 찬 버퍼수를** 1만큼 늘린다. <br>

**값을 확인하는 로직은 항상 변수가 0인지 아닌지를 확인한다.** <Br>
무슨 말이냐면, full이 N개인 경우도 물론 꽉찬 경우이지만, 그렇게 확인하지 않고 **empty가 0인지 아닌지를 확인한다. - 비어있는 버퍼 수를 확인하는 셈** <br>
이렇게 구현하면 N값을 계속 확인할 필요가 없으니, 일종의 최적화로 생각된다.

### 소비자 코드

```cpp
do {

  wait(full); /* 찬 버퍼 갯수가 0개라면 대기 */
  wait(mutex); /* 들어가며 버퍼 풀 접근가능 프로세스 수 1 감소 */

  /* 로직 */

  signal(mutex); /* 나오면서 버퍼 풀에 접근가능한 프로세스 수를 1 증가 */
  signal(empty); /* 빈 버퍼 수 1 증가 */

  ...

} while(1);
```
생산자 코드와 반대의 역할 <br>
역시나 **꽉차 있는 버퍼 갯수가 0개거나,** mutex가 0이라면 대기 <br>
들어가며 full과 mutex값 1 감소 <Br>
할 일을 마치고 나오면서 mutex 값을 1 늘림! <Br>
그리고 **비어있는 버퍼 수** 1만큼 늘린다. <br>
역시나 초반 비교는 0인지를 확인한다. <br>


# 2. Readers and Writers Problem
주로 DB에서 발생하는 문제로, 한 Process가 DB에 Write 중일 때, 다른 프로세스가 접근할 수 없게 해주는 것이다! (read는 동시에 여럿이 접근해도 무관)


### 2.1 공유 자원
1. DB 자체
2. `readcount`: **현재 DB에 접근 중인 Reader의 수**


### 2.2 솔루션!
1. **Writer가 접근 권한이 없는 상태에서는 모든 대기중인 Reader들의 접근을 허용한다!**
2. **Writer는 대기 중인 Reader가 없을 때만 접근이 허용된다!**
3. Writer가 접근 중이라면 Reader들은 접근이 금지된다. 빠져나간 이후에나 접근이 허용된다.
4. 기본적으로 읽을 때도 락은 걸어야 한다

### 2.3 Semaphore - Synchronization variables
1. `mutex`: readcount 접근에 대해 mutual exclusion을 보장
2. `db`: Writer에서는 Writer끼리의 접근을, Reader는 Writer의 접근을 막기 위해 사용. Writer는 대기중이거나, 사용중인 Reader가 없을 때만 접근이 가능한데, db 변수가 그 역할을 해주는 것이다.

### 2.4 구현

```
int readcount = 0;
DB 자체;
semaphore mutex = 1, db = 1;
```

### Writer
```cpp
do{

  ...

  wait(db); /* 들어가며 락을 건다. writer끼리의 상호 배제를 위함*/
  
  /* 쓰기 작업 */
  
  signal(db); /* 나오면서 락을 푼다 */
  
  ...

}while(1);
```
설명은 주석과 같다. writer들 끼리의 상호 배제를 신경써서 `db` 변수만 사용한다.
### Reader
```cpp
do {
  /* readcount 또한 상호 배제가 필요함! 
    이를 위한 wait와 signal */
  wait(mutex); 
  readcount++;

  /* 1만 체크하는 이유는 최초로 진입하게 된 Reader가 
    다른 Reader들을 대신해서 -> 이제 Reader차례다! 하고
    Writer의 접근을 막는 것. */
  if(readcount == 1) wait(db); 
  
  signal(mutex); /* readcount 변수에 대한 상호 배제 해제 */

  /* read from the shared data */

  wait(mutex); 
  readcount--;

  /* 마지막 Reader가 문 닫고 나오면서
    이제 우리 다 썼다~ 표시 */
  if(readcount == 0) signal(db); 
  signal(mutex); 

  /* do other things */

} while(1);
```
설명은 주석과 같다. <br> 
`readcount` 변수를 위한 상호 배제는 `mutex`변수로, <br> 
그리고 Reader들이 사용 중일 때 Writer의 접근을 막기 위해 시작할 때는 `readcount == 1`에서, <br>
 나올 때는 `readcount == 0`에서 `db` 변수를 조작한다!

### 2.5 Writer의 Starvation 발생 가능성!
Reader들은 얌체같이 자기 차례가 되면, 전부 나갈 때까지 락을 걸어 놓는다! <br>
1000개의 Reader가 들어가서 읽다가 이제 1명이 남았는데, 999명의 Reader가 또 들어온다면? 이런 상황이 계속 반복된다면?? <br>
**Writer는 지나치게 오래 기다리는 Starvation 문제를 겪게 될 수도 있다!** <br>
신호등이 없는 횡단보도를 생각하면 된다.. <br>
여러 방법들이 있다. 너무 늦게 들어온 Reader는 기회를 주지 않는다던지, 아니면 초반에 들어온 세트들이 한번 지나가면 Writer한테 기회를 한번 준 다던지 여러 방법을 생각해볼 수 있겠다.


# 3. Dining-Philosophers Problem
식사하는 철학자 문제. <br>

// 그림

그림과 같이 철학자들이 둘러 앉아 있다. <br>
철학자는 2가지 행동만을 할 수 있다.
1. 생각하기
2. 밥 먹기 (생각하다 배고파짐)

밥을 먹기 위해선 왼쪽 포크와 오른쪽 포크를 잡고 밥을 먹는다! <br>
철학자들은 각자 생각하는 시간이나, 밥을 먹는 시간이 제각이고, 양 옆의 포크는 공유되는 자원이기 때문에, **까딱하면 계속 굶는 철학자가 생기거나,** **최악의 경우 전체 철학자가 한쪽 포크를 든 채로 영영 기다릴 수가 있는 것이다!!** (DeadLock) <br>

## 3.1 구현 1

```cpp
semaphore fork[5]; /* 값은 전부 1 */

do {
  P(fork[i]);
  P(fork[(i + 1) % 5]);
  
  ...
  eat();
  ...
  
  V(fork[i]);
  V(fork[(i + 1) % 5]);

  ...
  think();
  ...

} while(1);
```
위 코드는 데드락이 발생할 수 있는 코드이다. <br>
첫 줄의 i번째 포크를 모두가 동시에 잡는다면??? **영락없이 모두 두번째 포크를 잡지 못 하게 된다...** (DeadLock 발생!!)

## 3.2 식사하는 철학자 해결법
1. 4명의 철학자만이 동시에 앉을 수 있게 한다! 
2. 포크 2개를 모두 잡을 수 있을 때만 잡는 것을 시도하게 한다!
3. 비대칭 전략 - 짝수 철학자는 왼쪽, 홀수 철학자는 오른쪽 포크 먼저 잡는다.

1, 2번 중 하나만 구현만 해도 DeadLock이 발생되지 않는다.

## 3.3 포크 2개를 전부 잡을 수 있을 때 잡는 전략
```cpp
/* 다섯 철학자의 상태를 3가지 상태로 표현 */
enum { thingking, hungry, eating } state[5];  
semaphore self[5] = 0;
semaphore mutex = 1;
```
```cpp
void putdown(int i) {
  P(mutex);
  state[i] = thingking;
  
  /* 자신이 포크를 들면서 양쪽의 철학자중 최소 한명은 대기하고 있다. 
  이를 챙겨주는 부분 */
  test((i + 4) % 5);
  test((i + 1) % 5);
  V(mutex);
}
```

```cpp
void pickup(int i) {
  P(mutex);
  state[i] = hungry;
  test(i);
  V(mutex);
  P(self[i]);
}
```
```cpp
/* 왼쪽 철학자 오른쪽 철학자 모두 eating 상태가 아니고 && 나도 배고플 때 먹는다! */
void test(int i) {
  if (state[(i + 4) % 5] != eating && state[i] == hungry
  && state[(i + 1) % 5] != eating) {
    
    state[i] = eating;
    V(self[i]);
  }
}
```
본 코드
```cpp
do {
  pickup(i);
  eat();
  putdown(i);
  think();
} while(1);
```

너무나도 코드가 복잡하다! 이는 세마포어의 고질적인 문제점이다!

# 4. Semaphore의 어려움
고전적인 3가지 문제의 해결을 세마포어를 사용해 시도했다. <Br>
다 괜찮은 방법들이지만 Semaphore의 치명적인 단점들이 존재한다.
1. 코드를 짜는 것이 너무 어렵다 -> **한번의 실수가 모든 시스템에 치명적인 영향이 미친다**
2. correctness의 입증이 어렵다
3. 자발적 협력이 필요하다. (voluntary cooperation)

순서가 조금만 바뀌어도 Mutual exclusion이 깨지거나, DeadLock에 걸려버린다.. <br>
이를 해결하기 위해, 좀 더 쉽게 코드를 짤 수 있는 방안이 제공되었는데! <br>
**이를 Moniter라고 부른다.** 
  
# 5. 모니터
모니터는 공유 자원 관리는 프로그래밍 언어 차원에서 지원해 주는 기능으로, <br>
오직 모니터에서 정의된 프로시저들을 통해서만 공유 자원을 접근할 수 있게 한다 <BR>
모니터 안에 공유 자원들과 공유 자원들에 접근하는 프로시저들을 정의해둔 다음, 공유 자원들을 접근하기 위해선 내부 프로서저를 이용해야만 하게 하는 것이다. <bR>
그리고 모니터는 내부적으로, 프로시저들이 동시에 실행되는 것을 막는다 <BR>
모니터는 자체적으로 동시 접근들을 전부 막기 때문에, 프로그래머는 이제 힘들여 락을 걸 필요가 없다!

### Condition Variable
Moniter에서 Mutual Conclusion을 위해 사용한다. 편한 동기화를 위해 도입한 변수 <br>
Condition Variable은 `wait()`와 `signal()` 연산에 의해서만 접근 가능하도록 되어 있다. <br>
  
  
모니터의 도입으로 이제 동기화 문제의 해결이 더 쉬워졌다. 더 자세한 내용과 구체적인 코드 레벨 개선은 다음 문서에서 설명한다. 

## Reference
- [반효경 교수 OS 강의]
- [Witch-Work 블로그 - 공룡책 7단원 정리](https://www.witch.work/os-6/#1-%EC%9C%A0%ED%95%9C-%EB%B2%84%ED%8D%BC-%EB%AC%B8%EC%A0%9C)
