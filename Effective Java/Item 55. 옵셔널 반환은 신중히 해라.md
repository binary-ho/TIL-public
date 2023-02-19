# Item 55. 옵셔널 반환은 신중히 해라.

## Optional의 등장
`Optional<T>`은 원소를 최대 1개 가질 수 있는 불변 컬렉션으로, T 타입 참조를 하나 담거나, 비워둘 수 있다. <Br>
진짜로 컬렉션은 구현했다는 것은 아니고, 원칙적으로는 그렇다. <Br> <br>

`Optional`은 자바 8에서 추가된 null을 다루는 새로운 선택지로, 어떤 T 타입 객체를 반환하는 메서드에 대해, <Br>
반환할 객체가 null이 아닌 경우 `Optional<T>`에 객체의 참조를 담아 반환하고, null인 경우 비워둔 채로 반환한다. <br>
자바 8 이전엔 어떤 메서드의 반환 값이 null일 가능성이 있다면, <Br> 
그냥 null을 반환하거나, 조건문 등으로 열심히 처리해서 예외를 던져야 했다. <Br> <br>

이 두 방법은 모두 구리다! <Br>
왜냐하면 '예외'는 정말로 예외적인 상황에서만 던져야 하는 것이고, 예외 생성 비용은 결코 가볍지 않다. <Br>
또한 null을 그대로 반환하는 방식은 당연히 위험하다. <br>
실수로 놓쳐버리는 순간 null을 만든 곳과 아주 동떨어진 곳에서 에러를 발견하게 될 수도 있다. <br>
원인을 찾기가 아주 힘들어지는 것이다. <Br>
이런 상황을 위해 구현된 `Optional<T>`! 일종의 '통'이라고 생각하면 될 것 같다. <Br>
반환값을 그냥 주는 것이 아니라 박스에 담아 주는 것이다. <BR>
보통은 T를 반환해야 하지만, 가끔 아무것도 반환해야 하지 않을 때는, 반환형을 `Optional<T>`로 할것. <br>
이는 예외를 던지는 메서드보다 유연하며, null을 반환하는 메서드보다 오류 가능성이 적다. <Br> 
예를 들어 아래 코드를 리팩토링 해보자.
```java
pubic static <E extends Comparable<E>> E max(Collection<E> collection) {
  if (collection.isEmpty()) {
    throw new IllegalArgumentException("빈 컬렉션");
  }

  E result = null;
  for (E e : collection) {
    if (result == null || e.comparTo(result) > 0) {
      result = Objects.requireNonNull(e);
    }
  }

  return result;
}
```
위 메서드는 null을 반환하는 것이 무서워 인자인 collection이 비어있는 경우 `IllegalArgumentException`를 던지고 있다. <Br>
위 메서드를 리팩토링 해보자. 기존 반환값인 `E` 대신 `Optional<E>`을 반환하도록 바꿔 보겠다. <br>

```java
pubic static <E extends Comparable<E>> Optional<E> max(Collection<E> collection) {
  if (collection.isEmpty()) {
    return Optional.empty();
  }

  E result = null;
  for (E e : collection) {
    if (result == null || e.comparTo(result) > 0) {
      result = Objects.requireNonNull(e);
    }
  }

  return Optional.of(result);
}
```
쉽게 리팩토링 했다. <br>
주의할 점은 `Optional.of(null)`과 같은 코드는 작성하면 안 된다는 것이다. <Br>
넣는 경우 NullPointerException을 던진다. <br>
null 값도 허용하는 옵셔널을 만들려면 `Optional.ofNullable(value)`와 같이 코드를 짜면 되는데, 그럼 아래와 같은 구현도 가능할 것이다.

```java
pubic static <E extends Comparable<E>> Optional<E> max(Collection<E> collection) {
  E result = null;
  for (E e : collection) {
    if (result == null || e.comparTo(result) > 0) {
      result = Objects.requireNonNull(e);
    }
  }

  return Optional.ofNullable(result);
}
```


## Optional 사용 기준
Optional 반환 기준은 **반환값이 Null일 수도 있다는 것을 클라잉너트 사용자에게 알려주느냐다.** <Br>
클라이언트에게 반환값이 Null일 수 있음을 알릴 필요가 있을 떄 사용한다. <br>
그럼 클라이언트에선 미리 대비할 수 있게 된다. <br>


## 활용과 예시
Optional에 넣을 값이 없을 때, 클라이언트가 Optional에서 값을 꺼내는 과정에서 null 대신 내가 지정한 조취를 취하도록 할 수 있다. 
```java
String lastWordInLexicon = max(words).get();

// 없는 경우의 대처
String lastWordInLexicon = max(words).orElse("단어가 없습니다.");
String lastWordInLexicon = max(words).orElseThrow(TemperTantumException::new);
```
위와 같이 `"단어가 없습니다."`와 같은 기본값을 정해둘 수도 있고, 예외를 던지도록 할 수도 있다. <br>
혹은 `.orElseGet()`을 사용할 수도 있다. <Br>
`.orElseGet()`은 기본값을 설정하는 비용이 커서 부담될 때 사용하면 좋은데, <Br>
`Supplier<T>`를 인수로 받아, 값이 처음 필요할 때만 생성하므로 초기 설정 비용이 낮다. <Br> <Br>


### Optional 고급 메서드
이 밖에도 `isPresent`, `filter`, `map`, `flatMap` 등의 메서드가 있다. <br>
`isPresent`는 말 그대로 옵셔널이 채워져 있는지 확인하여 채워져 있다면 true를 반환한다. <BR>
`isPresent`는 언급한 다른 3가지 메서드로 대체하기 쉬우므로, 나머지 3개를 우선적으로 적용하는 편이 낫다. <Br>
예를 들어
```java
Optional<ProcessHandle> parentProcess = ph.parent();

System.out.println("부모의 PID : " + (parentProcess.isPressent() ? 
    String.valueOf(parentProcess.get().pid()) : "N/A"));
```
위와 같은 코드가 있다. <br>
삼항 연산자를 통해 `parentProcess`라는 Optional이 비어있는 경우 "N/A"를 반환하고, 비어있지 않은 경우엔 pid를 가져온다. <Br>

위 코드의 isPresent를 map으로 대체해보자.
```java
System.out.println("부모의 PID : " + ph.parent().map(h -> String.valueOf(h.pid())).orElse("N/A"));
```
무슨 일이 일어났는가? <Br>
map으로 반환값이 Optional인 `parent()`를 순회하며, 값이 있는 경우 pid를 반환하고, 없는 경우 "N/A"를 반환한다. <Br>
어차피 값을 1개 밖에 못 가지지만 원칙적으로 컬렉션 취급이므로.. 순회?한다. <br> <br>
 
### Optional과 스트림
Optional을 사용할 때, `Stream<\Optional<\T>>`로 Optional들을 받아 내어, 오직 채워진 옵셔널 값들에서만 값을 뽑아 Stream<T>에 거네 처리하는 경우는 흔하다. <Br>
이를 `filter`와 `map`을 통해 구현해보면,
```java
streamOptionals
  .filter(Optional::isPresent)
  .map(Optional::get)
```  
위와 같이 구현할 수 있겠다. <Br>
isPresent가 true인 경우만 남겨 get하는 것이다. <br>

자바 9 부터는 Optional 자체에 `stream()` 메서드가 추가되었다. `flatMap`과 함께 사용하면, <br>
이는 옵셔널에 값이 있으면, 아예 원소를 담은 스트림으로 준다. (없는 경우엔 빈 스트림.)
```java
streamOfOptionals
  .flatMap(Optional::stream)
```
위와 같이 나타낼 수 있다.

## Optional을 사용할 때 주의할 점
이렇게 편리한 Optional도 주의할 점들이 있다.
### 1. Optional은 오직 메서드 반환값에만 사용하라
즉, 메소드 매개변수, 맵의 키, 인스턴스 필드로 쓰면 안 된다. <br>
맵 안에 어떤 키가 있는지 확인할 때, 만약 키가 Optional로 되어 있다면? -> 일을 두번 하는 꼴이며 혼한스럽다. <br>

### 2. Optional을 리턴하는 메소드에서 null을 리턴하지 말자. 
-> 그럴거면 왜 Optional을 쓰는가?

### 3. Optional로 감싸선 안 되는 것들이 있다. 
Collection, Map, Stream Array, Optional은 Opiontal로 감싸지 말라
차라리 빈 컬렉션으로 반환하는 편이 낫다. 어차피 빈 자료구조들은 각자 비어있는 상태를 확인할 수 있는데, <Br>
굳이 굳이 Optional로 감싼다면 일을 두번 하는것 아닌가?
### 4. 프리미티브 타입용 Optional은 따로 있으므로, 그들을 사용하라
ex) OptionalInt, OptionalLong 등등 <br>
애초에 기본 타입은 옵셔널에 넣으며 박싱이 일어나기 때문에 무거워진다.
### 5. 성능이 중요한 곳에선 부적절하다.
Optional도 객체는 객체이다. 즉, 새로 할당하고 초기화도 해줘야 하며 사용할 때, 이런 저런 메서드를 통해 사용해야 하기 때문이다.

## Reference
- Effective Java <조슈아 블로크>
