# 13 병열 프로그래밍과 병렬 처리
## 13.1 병렬 처리 소개
- **다수 프로세서 -> 여러 프로그램**
- **다수 프로세서 -> 한 프로그램의 분할된 부분들 동시 처리**

## 13.1.1 Flynn의 분류
1. SISD
2. SIMD: GPU, 행렬곱, 벡터곱
3. MISD
4. MIMD: 진정한 parallel processing programing
**-> 병렬 처리 컴퓨터는 SIMD, MIMD, 결국 mulit-data**

## 자료 공유 방식
- 공유 메모리 구조(shared-memory architecture): 큰 거 하나를 공유하자!
- 분산 메모리 구조(distributed-memory architecture): 프로세스마다 데이터를 주자.


## 13.2 병렬 처리와 프로그램 언어
<**주요 키워드**>
- Shared resource
- Synchronization
- Critical section
- Mutual exclusion
**shared resource를 동시에 접근하면 망가지겠지? <U>critical section!</U>** <br>
**야, 한 번에 한 명만 접근해라, <U>mutual exclusion!</U>** 결국 synchronization 기법이 중요<br>
- Process Terminate: 정해진 시간 안에 critical region 실행을 끝내라.
- Process Fair Scheduling: 한정된 시간 안에 critical region에 들어가라

### 병렬 처리를 위한 단위의 세 가지 선택 기법
- 입상(granularity) 크기에 따른 분류!
1. **명령어 수준**의 병렬성 -> fine grain
2. **프로시저 수준**의 병렬성 -> medium grain (명령어로 동기화)
3. **프로그램 수준**의 병렬성 -> course grain (자신의 사본 생성 MPMD - fork in unix)
- 작음: 입상 프로세스 생성 **유지 -> 오버헤드**
- 큰 덩이: 병렬성 부여 기회가 소멸됨

### 병행 언어가 필요한 것들
1. 병렬로 실행될 수 있는 **코드 묶음 지정** - task, process 등
2. 프로세스 실행 시작 기술 (여기서 부터 정렬해라!)
3. 공유 자료 상호 배제(Mutual Exclusion)
4. 동기화 수단 제공
5. 프로세스에 우선순위 부여 가능
6. 프로세스 지연시키기 (기다렷!)


# 13.3 Semaphor
**Semaphor**: 여러 task에서 이용할 수 있지만, 한 번에 하나의 task에서만 사용해야 하는 resource에 대한 엑세스를 제어하기 위한 자료구조. **공유되는 자원에 제한된 개수의 프로세스나 스레드만 접근할 수 있도록 만들기 위해 도입된 개념. Mutual Exclusion을 위해 도입되었다고 볼 수 있다.**

```c++
wait(s): if s == 1 then s := 0
        else 프로세스 P는 대기큐에 들어가 대기
signal(s): if(queue != empty) then 대기중인 프로세스는 critical section 실행 준비
            else s := 1
```
- **s == 1임을 두 프로세스가 동시에 확인하면, 두 프로세스가 동시에 진입하는 문제가 생긴다. 그런 문제를 방지하기 위해 wait는 반드시 atomic 해야한다.** (세마포어느느 atomic operation의 성질을 가져야 한다.)

## 13.3.1 Counting Semaphore
shared resource가 많을 때는 어떻게 해야할까? <br>
-> 트랜잭션 같은 개념 Down, Up primitive를 도입한다!
**Down mutex: 공유자원 하나 내놔라.** (프로세스가 공유자원을 하나 이용하고자 할 때 호출)
**Up mutex: 프로세스가 공유자원 이용을 끝냈을 떄 사용**
```c++
int mutex = 5;
// Down mutex -> 하나 쓴다.
if (mutex == 0)
    then -> 대기 큐에 P push!
    else mutex := mutex - 1 (하나 까고 들어가라. 나 쓴다잉~)

// Up mutex -> 잘 썼다. 간다.
if(대기큐.empty)
    then mutex := mutex + 1 (돌려줄게)
    else 큐에 대기중이였단 다른 프로세스에게 자원 활용 허락하고 critical section 실행
```
