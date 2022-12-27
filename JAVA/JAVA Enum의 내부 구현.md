# JAVA Enum 내부 구현 
## Java Enum의 정체
java 열거형은 내부적으로 상수 하나 하나가 객체로 표현 되어있다. <Br>
예를 들어
```java
enum Direction { EAST, SOUTH, WEST, NORTH }
```
위의 열거형 상수 EAST, SOUTH, WEST, NORTH는 모두 Direction 객체이다. <br>

위의 한 문장을 클래스로 정의하자면 아래와 같다. 
```java
class Direction {
  static final Direction EAST = new Direction("EAST");
  static final Direction EAST = new Direction("SOUTH");
  static final Direction EAST = new Direction("WEST");
  static final Direction EAST = new Direction("NORTH");
  
  private String name;
  private Direction(String name) {
    this.name = name;
  }
}
```

위 클래스의 static 상수 EAST, SOUTH, WEST, NORTH 값은 사실 **객체의 주소이다.** <br>
**이 값들은 바뀌지 않는 값이므로 enum에서 빠른 동등 비교 연산인 `==` 연산을 지원하는 것이다.** <br> **이런 내부 구현 덕분에 자바 Enum은 typesafe enum이다.**<br>

전부 객체로 취급되는 점 덕분에 Enum의 다양한 연산들을 사용 가능한 것이고, 비교 연산자는 사용이 어려운 것이다. 대신 `comapreTo()`를 사용해야 한다.

## java.lang.Enum
모든 열거형들의 조상은 java.lang.Enum 클래스이다. <br> 
Enum 클래스의 메서드는 아래와 같다. 
1. `Class<E> getDeclaringClass()`: 열거형의 Class 객체를 반환한다.
2. `String name`: 열거형 상수의 이름을 문자열로 반환한다.
3. `int ordinal()`: 열거형 상수가 정의된 순서를 반환한다. 0부터 시작한다.
4. `T valueOf(Class<T> enumType, String name)`: 지정된 열거형에서 name과 일치하는 열거형 상수를 반환한다.

## 열거형에 맴버를 추가할 수 있다.
열거형의 상수들이 내부 구현상 객체이기 때문에 아래와 같이 인스턴스 변수와 생성자를 추가해줌으로써, 열거형의 숫자를 마음대로 지정해줄 수 있다.

```java
enum Direction {
  EAST(1), SOUTH(5), WEST(-1), NORTH(10);

  private final int value;
  Direction(int value) { this.value = value; }
  public int getValue() { return value; }
}
```
value는 상수를 저장하기 위한 변수임으로 `final`을 붙여줬다. <br>
필요에 따라 여러 값을 추가해주거나, 추상 메서드를 선언하여 강제로 구현하게 해서 상황에 따라 다른 상수를 반환하도록 할 수도 있다.

## Java Enum의 장점

자바의 열거형은 아래와 같은 2가지 장점이 있다.
1. **typesafe enum**
2. 열거형 상수의 값이 바뀌더라도 다시 컴파일 할 필요 없다.

```java
class Card {
  static final int CLOVER = 0;
  static final int HEART = 1;
  static final int DIAMOND = 2;
  static final int SPADE = 3;
  
  static final int TWO = 0;
  static final int THREE = 1;
  static final int FOUR = 2;

  final int kind;
  final int num;
}
```

```java
class Card {
  enum Kind { CLOVER, HEART, DIAMOND, SPADE }
  enum Value { TWO, THREE, FOUR }
  
  final Kind kind;
  final Value value;
}
```

자바의 열거형은 C언어의 것보다 더욱 향상되어, **열거형의 값뿐만 아니라, 타입도 관리하기 때문에,** 보다 논리적인 오류를 줄일 수 있다. <br>

이러한 자바의 열거형을 `typesafe enum`이라고 부른다. <Br>
실제 값이 같더라도, 타입이 다르면 컴파일 에러를 발생시킨다. <br>

예를 들어 아래의 코드는 false를 반환한다.
```java
if (Card.Kind.CLOVER == Card.Value.TWO)
```

## Reference
- 자바의 정석 <남궁 성>
