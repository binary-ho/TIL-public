## Mutual Exclusion을 제공하는 Mechanism
## 1. Mutual Exclusion
Mutual Exclusion은 Progress, Bounded Waiting과 함께 동기화를 제공하기 위한 조건들이다. 특히 Mutual Exclusion와 Progress는 필수라고 할 수 있다. <br>

하나의 프로세스 혹은 쓰레드가 Critical Section에 진입해 있다면, 다른 프로세스들은 공유 리소스가 존재하는 코드 영역인 Critical Section에 진입할 수 없어야 한다! 동기화의 최소 조건이라고 할 수 있다. 이것이 Mutual Exclusion이다. <br>

## 2. Mutual Exclusion을 제공하는 Mechanism
:x:는 실패한 방법!
## 2.1 Disabling Interrupts :x: :star:
한 process가 critical region에 있는 동안 context switching으로 인한 다른 process의 진입을 막기 위해, <br>
clock으로 부터 **Interrupts가 걸리지 않게 하는 것. 원천 봉쇄!**  <Br>
**당연히 문제가 된다. user가 interrupts를 제어한다? 절대 안 되는 일..** 버리는 방법!

## 2.2 Lock Variables :x:
**Lock 걸어버리는 방법. 실패한 알고리즘!** <br>
critical resgion에 들어가고 싶니? 변수 하나를 두고 0이면 1로 바꾸고 들어가렴~ 그리고 1이면 잠시 기다리렴~ <br>
-> 실패한 알고리즘! <br>
### Lock Variable 예외 케이스
1. A라는 Process가 변수 값이 0인 것을 확인하려고 막 들어가려는 찰나!! 
2. Process Switch가 일어남.. <br>
3. A는 다녀와서 들어가야지~ 상태이고, 새로 등장한 B가 들어가면서 변수 값을 1로 바꿈!!
4. B가 Critical Region에서 나오기 전에 또 Process Switch 발생!
5. A는 변수 값을 0으로 알고 있기에, 그냥 들어가버린다!
6. 망했습니다! 

## 2.3 Strict Alternation (엄격한 교대) :star: 
**Busy Wating과 Spin Lock 사용!** <br> 

#### 2.3.1 Busy Wating -> 무한 루프 :star:
보통은 while로 구현된 빈 루프를 무한으로 돌면서 입장을 위한 변수 상태를 계속 확인한다! <br> 단순한 일에 CPU Time을 낭비하는 것이기 때문에 아주 아주 잠깐 기다릴 것으로 예상될 때만 사용! (쓰지마)

#### 2.3.2 Spin Lock
**Busy Wating에 사용되는 Lock이다.** Lock Variable이랑 약간 비슷한데, 2개의 프로세스가 각각 0과 1을 자기 차례로 보고, 번갈아 사용한다. <br> A가 0일 때 진입한다면, B는 계속 기다리고, A가 다 쓰고 1로 바꿔주면, B가 들어가고 다시 A는 기다리는 식으로 Spin한다..

#### 2.3.3 엄근진 교대의 장단점!
장점
- 모든 race condition 방지!

단점
- **process가 critical region에 있지 않은 process에게 block될 수 있는데,** 이건 금기. noncritical_region에 있는 process가 상대 프로세스를 막는 꼴이 될 수 있다.
- **한 프로세스가 다른 프로세스에 비해 훨신 느리다면, 이런 식으로 번갈아 수행되는 알고리즘은 좋지 않다.**


## 2.4 Peterson's :star::star:
**얘도 Busy Waiting!** <br>

```c
#define FALSE 0
#define TRUE 1
#define N 2

int turn;
int interested[N];

void enter_region(int process)
{
  int other;

  other = 1 - process;
  interested[process] = TRUE;
  turn = process;
  while (turn == process && interested[other] == TRUE)
}

void leave_region(int process)
{
  interested[process] = FALSE;
}
```

두 프로세스가 같은 program을 사용한다. <br>

- other은 그냥 나머지 다른 하나의 프로세스를 가르키기 위해 있다.
- turn 변수를 공유하는데, 누구 차례인지를 표시. 내 차례야! 하고 선언하는 것과 같다.
- interested는 현재 region 진입에 관심 있는 process 번호다. 

내 차례여도 상대방이 관심이 있으면, 들어가지 못 한다. 내가 관심이 있어도! 둘 다 관심이 있는 상황이여도, trun을 공유하기 때문에 둘 중 하나는 들어갈 수가 있다!

- 시나리오를 한번 따져보면 좋긴 할 듯. 0 process와 1 process가 있다고 가정하고 따져보면 좋다.


## 2.5 TSL instruction (Busy Wating) :star::star:
**얘도 Busy Waiting을 사용한다.** <br> TSL RX, LOCK (Test and Set Lock)! <br>
메모리에 있는 lock 변수 값을 register RX에 넣고, lock 변수에는 nonzero 값을 넣어준다. 두 동작은 항상 동시에 일어난다!
```
enter_region:
  TSL REGISTER, LOCK          | Lock 값을 register에 복사한다. 그리고 lock을 1로 설정한다.
  CMP REGISTER, #0            | Lock이 zero인지 확인
  JNE enter_region            | zero가 아니면, lock이 set 된 것으로, 무한 루프..
  RET                         | return to caller; critical region entered

leave_region:
  MOVE LOCK, #0               | store a '0' in lock
  RET                         | return to caller
```

Sleep And WakeUp.. <br>

**Busy Wating의 단점**
- CPU Time 낭비
- **높은 priority의 process가 계속해서 busy waiting 중이면, <br> 다른 process들은 아무것도 못 하고, 계속 busy waiting**

### 생산자-소비자 문제
- 정해진 사이즈의 buffer가 존재한다
- **생산자:** buffer가 꽉 차면 소비자가 buffer에 있는 item 중 적어도 하나를 꺼내가지 않는 이상 sleep
- **소비자:** buffer에 내용물이 없으면, 생산자가 item을 적어도 하나 더 생산하지 않는 이상 sleep 

```c
#define N 100
int count = 0;

void producer(void)
{
  int item;

  while (TRUE) {
    item = produce_item();
    if (count == N) sleep();
    insert_item(item);
    count = count + 1;
    if (count == 1) wakeup(consumer);
  }
}
```
