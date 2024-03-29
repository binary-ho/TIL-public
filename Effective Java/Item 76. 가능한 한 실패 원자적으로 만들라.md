# Item 76. 가능한 한 실패 원자적으로 만들라

**호출된 메서드가 실패하더라도 객체는 메서드 호출 전 상태를 유지해야 한다.** <Br>
그러니까 예외가 발생하기 전과 후의 객체 상태를 같게 두자는 이야기이다. <br>
장점은 다음과 같다
1. 실패 이후에도 같은 상태를 유지하고 있다면, 그 객체를 정상적으로 다시 사용할 수 있다.
2. 예외가 검사 예외였다면, 호출자가 오류 상태를 복구하기 더욱 수월하다.

<br>

**이러한 특성을 실패 원자적, failure-atomic이라고 한다.** <Br>

**메서드 명세에 기술된 예외라면 항상 실패 원자성을 갖는게 기본 원칙이다** <Br>
이게 안 된다면 최소한 실패시의 객체 상태를 API 설명에 명시하기라도 해야한다. <br>
물론 지키지 않고 있는 API가 많으니 다른 API가 실패 원자적이지 않다고 해서 <br>
나도 안 지켜도 되지 않을까? 하면 안 된다.

## 실패 원자적 메서드
실패 원자적 메서드는 어떻게 만들면 될까? <Br>

1. 객체를 불변 객체로 설계하기
2. 작업 전 매개변수 유효성 검사
3. 커맨드를 실패 가능성 코드 뒤에 배치하기
4. 방어적 복사본을 적극 활용하기
5. 실패를 가로채서 복구하는 코드 작성하기

<br>

이런 다양한 방법들이 존재한다. 찬찬히 살펴보자 <br>
### 1. 객체를 불변 객체로 설계하기
당연하지만 애초에 객체가 불변 객체이면 변할 수가 없다. <Br>
태생적으로 불변인데 뭐 어쩔건가. <Br>
불변 객체의 경우 값이 변화할 때 새로운 객체를 만들곤 한다. <Br>
당연히 새로운 객체가 만들어지진 않지만 상태도 변하지 않는다. <Br>
**실패 원자성을 지키는 가장 쉬운 방법이다.**


### 2. 작업 전 매개변수 유효성 검사
객체의 내부 상태를 변경하기 전에 <br>
그냥 예외 발생 가능성을 많이 거두어 내자는 방식이다. <Br>
빈틈이 많아 보이는 방법이지만 효과적이다.


### 3. 커맨드를 실패 가능성 코드 뒤에 배치하기

2번과 취지는 비슷하다. <br>
애초에 문제가 발생할 수도 있는 코드를 앞에 두어서, <Br>
전부 통과한 다음 상태를 바꾸자는 것이다. <br>
이것도 모든 문제 발생 가능성을 인지하고 있어야 한다는 점에서 <br>
조금 불완전해 보이는 것은 사실이다. <br>
더욱 탄탄한 방법들을 살펴보자.

### 4. 방어적 복사본을 적극 활용하기

작업 자체를 객체로 하지 않고, **임시 복사본을 사용하는 것이다.** <Br>
그 다음 작업이 성공하면 조작한 복사본을 기존 객체와 교체하는 것이다. <br>
확실히 실패하더라도 안전하게 기존 상태 객체를 받아볼 수 있는 좋은 방법 같다. <Br>
기존 2번 3번 보다는 더 안전해 보인다 <br>
복사본을 만들어야 한다는 코스트 정도만 인지하고 있으면 될 것 같다. <br>


### 5. 실패를 가로채서 복구하는 코드 작성하기
작업 도중 발생하는 실패를 `try-catch` 와 같은 문법을 이용하여 <br>
낚아챈 다음 따로 처리해주는 것이다. <br>
자주 쓰이는 방식은 아니다.


## 언제나 트레이드 오프

이렇게 실패 원자성을 만드는 여러가지 방법을 알아 보았다. <Br>
안전해 보이는 방법도 있었고, <Br>
좀 빈틈있어 보이는 방법도 있었는데 <br>


**결국 진짜 중요한건 트래이드오프다.** <br>
실패 원자성은 일반적으로는 권해진다. <Br>
하지만 항상 달성할 수도 없는 문제이고, <Br> 
복구 연산 비용이 너무 크고 복잡하다면 안 하는게 나을 수도 있다. <br>
그래도 가슴 한켠에 실패 원자성을 담아두고, 유심히 관찰 해야한다 <br>
문제를 파악할 수 있다면, 꽁짜 실패 원자성이 보일 때도 있기 때문이다. <br> <br>



## Reference
- Effective Java <조슈아 블로크>
