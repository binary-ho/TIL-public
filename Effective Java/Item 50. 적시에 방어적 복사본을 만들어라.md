# Item 50. 적시에 방어적 복사본을 만들어라
다른 클래스의 침투를 막아라! <br>
안전하지 않은 C와 C++를 피해 자바로 도망왔다고 하더라도, <br>
마법처럼 아무 노력 없이 안정성을 확보할 수 있는건 아니다. <br>
**우리는 클라이언트가 악마라고 가정해야 한다.** <br> 
클라이언트는 우리의 불변식을 깨트리기 위해 어떤 댓가도 치룰 수 있는 악마들이라고 가정하고, <Br> 
방어적으로 프로그래밍 해야 한다. <br>
그를 위해 **방어적 복사본을 만들어라..**


## 1. 문제상황

```java
public static final class Period {
    private final Date start;
    private final Date end;

    public Period(Date start, Date end) {
        this.start = start;
        this.end = end;
    }

    public Date getStart() {
        return start;
    }

    public Date getEnd() {
        return end;
    }
}
```
겉 보기엔 아주 순진무구해 보이는 불변 객체이다.. <Br>


```java
  public static void main(String[] args) {

      Date start = new Date();
      Date end = new Date();

      Period period = new Period(start, end);
      System.out.println(period);
      end.setYear(10);
      System.out.println(period);
  }
```

하지만 위와 같은 코드를 넣어보니.. <br>


`충격` `공포` 아래와 같은 결과가 나왔다. (가장 끝의 end 년도 를 봐라..) <Br>
```
Period{start=Tue Feb 28 10:00:56 KST 2023, end=Tue Feb 28 10:00:56 KST 2023}
Period{start=Tue Feb 28 10:00:56 KST 2023, end=Mon Feb 28 10:00:56 KST 1910}
```
Date는 가변 객체이다! <br>
일단 당연하게도 앞으로 Date 같은 구닥다리 객체는 쓰면 안 된다! <br>
`Instant`나 `LocalDateTime`, `ZonedDateTime`을 써라 <br>
이제 무서운 마음이 들 것이다. <Br>
앞으로 일일히 모든 객체의 불변성을 확인해야 하는가? <br>
그건 너무 끔찍한 일이다. <Br>
위와 같이 외부의 공격으로 부터 인스턴스 내부의 필드들을 보호하기 위해선 <br>
**생성자에서 받은 가변 매개변수들을 방어적으로 복사하고, 인스턴스 안에서 복사본을 사용하라.** <br>
그리고, **유효성 검증 이전에 일단 복사해라.** <br>

## 2. 방어적인 복사본
위의 Period 객체 생성자의 올바른 모습을 살펴보자.
```java
  public Period(Date start, Date end) {
      this.start = new Date(start.getTime());
      this.end = new Date(end.getTime());

      if (this.start.compareTo(this.end) > 0) {
        throw new IllegalArgumentException("시작 시간이 끝나는 시간 보다 늦다.");
      }
  }
```
1. 방어적 복사본 생성
2. 유효성 검증
3. 클론 메서드를 사용하지 않았다.
위와 같은 순서가 올바른 순서인 이유는, <br>
멀티 스레드 환경에서 유효성을 검사하고 객체가 만들어지는 그 짧은 순간에도, <Br> 
얼마든지 공격이 이루어질 수 있기 때문이다. 클라이언트를 아주 악독한 악마로 가정하는 것이다. <br>
망상이 아니고 아예 이런 공격의 용어도 있다. <br> 
이를 TOCTOU 공격이라고 하는데, time-of-check/time-of-use의 검사시점/사용시점 공격이라고 부른다. <br> <br>

### Date의 클론은 왜 안 썼나요?
**클론 메서드를 사용하지 않은 이유는 무엇일까?** <br>
Date가 final이 아니므로, clone이 Date의 clone이 아닐 수 있다. <br>
즉, **악마가 재정의한 하위 클래스 인스턴스를 내놓을 수도 있다.** <Br>
매개변수가 확장 가능한 타입이라면, clone을 사용하지 말라.


## 3. getter도 복사본을 내놓아라.
위의 예시에서 또 하나의 치명적 결함이 있는데, <br>
바로 `getter`이다. getter를 보면 객체를 바로 내놓고 있는데, <br>

```java
public static final class Period {
    private final Date start;
    private final Date end;

    ...

    public Date getStart() {
        return start;
    }

    public Date getEnd() {
        return end;
    }
}
```
<br>

**getter도 방어적 복사본을 내세워라!** <Br>
바로 이렇게

```java
public static final class Period {
    private final Date start;
    private final Date end;

    ...

    public Date getStart() {
        return new Date(start.getTime());
    }

    public Date getEnd() {
        return new Date(end.getTime());
    }
}
```
너무 좋다. <br>
이제 Period는 악의 무리에 현혹되지 않는 불변맨이 되었다. <br>
길이가 1 이상인 배열도 가변이기 때문에, 방어적 복사를 수행하자. <Br>
이런 지경이니, 항상 불변 객체들로 객체를 구성하는 것이 얼마나 중요한지 다시금 느껴지지 않는가? <br>
**클라이언트와 내가 서로 믿을 수 있는 상황이 아니라면, 항상 대비해야 한다.**


## Reference
- Effective Java <조슈아 블로크>
