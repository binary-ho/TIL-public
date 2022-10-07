# Template Callback Pattern in Spring
**템플릿 콜백 패턴은 전략을 익명 내부 클래스로 구현한 전략패턴이다.** <br>

템플릿 콜백 패턴은 전략 패턴의 변형으로, 스프링 3대 프로그래밍 모델 중 하나인 DI에서 사용하는 특별한 형태의 전략 패턴이다. <br> 템플릿 콜백 패턴과 전략 패턴은 **전략을 익명 내부 클래스를 사용하는 점이 다르다.** 

<br>

결합도가 조금 증가하지만, 전략마다 팩토리 객체를 일일이 만들 필요가 없다. 유연하게 내부 구현체만 바꿔주면 로직 가능하다. 외부에서 어떤 전략을 사용하는지 감추고, 중요한 부분에만 집중할 수 있습니다. <br>

스프링은 `Template Callback Pattern`을 DI에 적극 활용하고 있기 때문에, 스프링을 제대로 이해하고 활용하려면, 전략 패턴과 템플릿 콜백 패턴을 잘 알고 있어야한다. <br>

대표적인 예시로는 JdbcTemplate, RestTemplate, TransactionTemplate, RedisTemplate 등이 있는데, 몇 가지 코드를 직접 뜯어서 살펴보며 분석해보겠다. <br> <br>

설명에 앞서, 책에서 사용하는 용어인 컨텍스트와 전략은 Template Callback Pattern에서 각각 템플릿, 콜백에 대응한다! 그리고, **꼭 익명 내부 클래스로 구현할 필요는 없다!** 이것 때문에 여기 저기 물어보고 다녔다 ㅡㅡ

## 1. JdbcTemplate

<!-- 안녕하십니까 선생님들.. 궁금한 점이 있어 질문드립니다.

제가 지금 보고 있는 책에서는 Template Callback Pattern을 "전략을 익명 내부 클래스로 구현한 전략패턴이다"라고 소개하고 있습니다.

그리고 이 패턴을 스프링에서 이를 DI에 적극 활용중이라고 하기에 궁금해서 찾아보니, JdbcTemplate에서 사용중이라고 하기에 코드를 뜯어 보았습니다.

찾아보니 JdbcTemplate의 excute 메서드에서 StatementCallback<T>을(전략) 받고 있었습니다. 그래서 실제 사용된 부분을 찾아보니, query라는 메서드에서 return으로  StatementCallback<T>을 구현한 "로컬 이너 클래스"의 객체를 넣어주고 있었습니다.

Q1. 이런 형태도 템플릿 콜백 패턴이라고 볼 수 있나요? 
Q2. 맞다면, 템플릿 콜백 패턴을 구현 할 때, 전략을 꼭 익명 클래스가 아닌 형태로 짜도 되는걸까요? -->



Template Callback Pattern에서의 전략은 콜백에 대응한다. 정확히는 이 콜백 인터페이스의 구현 클래스의 객체가 전략으로서 들어간다! <br>
예시로 JdbcTemplate에서 제일 그럴싸 해보이는 StatementCallback 인터페이스를 살펴 보았다. sql state를 처리하기 위해 있는 인터페이스이다.

```java
@FunctionalInterface
public interface StatementCallback<T> {
  @Nullable
	T doInStatement(Statement stmt) throws SQLException, DataAccessException;
}
```

해당 인터페이스 객체를 입력으로 받는 메서드를 찾아 보았다. <br> 

execute 메서드는 StatementCallback의 구현체를 입력으로 받는다. execute 메서드가 바로 **컨텍스트에 해당한다.**

![executeWithRed](https://user-images.githubusercontent.com/71186266/194120589-f27acfa0-f7a2-4a98-b5d5-640554afebfa.png)

그럼 이 excute 메서드에 어떻게 구현체가 들어오는지 찾기 위해, execute를 호출하는 함수들을 찾아 보았다. 

![QueryStatementCallbackWithRedBox](https://user-images.githubusercontent.com/71186266/194120585-fcdd0b55-4810-4ec1-83a8-f2c8bdff13b2.png)

query 함수는 내부적으로 StatementCallback 인터페이스를 구현한 local inner class QueryStatementCallback을 정의하고, return에서 QueryStatementCallback의 구현체를 넣어서 execute를 호출한다. 그러면 query가 일종의 클라이언트에 해당한다. 

## 2. RedisTemplate

전략으로 쓰이는 콜백 메서드 하나를 잡았다.
```java
public interface RedisCallback<T> {
	@Nullable
	T doInRedis(RedisConnection connection) throws DataAccessException;
}
```
이를 입력으로 받는 컨텍스트 - excute 메서드 발견
![redis excute](https://user-images.githubusercontent.com/71186266/194262293-db2c3298-41f2-4fa1-abf3-0e25cb1055c1.png)

그리고 excute를 호출하는 클라이언트 입니다.
![redis ramda](https://user-images.githubusercontent.com/71186266/194262298-8e963e24-9959-4bbb-8a60-41a868ce68ab.png)

추가
![redis start](https://user-images.githubusercontent.com/71186266/194267082-af27ed89-a19a-489c-809e-825b53fca8b2.png)
