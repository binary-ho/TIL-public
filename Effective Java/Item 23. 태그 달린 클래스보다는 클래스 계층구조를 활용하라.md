# Item 23. 태그 달린 클래스보다는 클래스 계층구조를 활용하라

## 1. 태그 달린 클래스
태그 달린 클래스 => 쓰레기 클래스. <br>
이런 형태의 클래스의 존재를 이 책을 읽으며 처음알았다. <br>
객체지향에 대한 책들을 먼저 접한 상황이라 그랬던것 같다. <Br>

'태그 달린 클래스'란 한 클래스가 어떤 기준을 통해 여러 클래스 처럼 동작하게 만든 클래스를 말하는 것 같다. <br>
예를 들어, '도형' 클래스가 있다고 할때, 생성자에 따라 어떨 때는 '사각형' 클래스로, 어떨 때는 '원' 클래스로 작동하는 기괴한 클래스를 태그 달린 클래스라고 한다. <br>
단점은 책을 보지 않고도 줄줄 외울 수 있지만, 책에 따르면, 상황에 따라 쓰이지도 않는 필드들과 로직등의 코드들이 잔뜩 있어 가독성도 나쁘고, 용량도 크게 처리하며, 컴파일러가 디버깅을 돕기도 힘들다. 엉뚱한 필드를 초기화 하고 있어도 컴파일러는 그 의도를 알 방도가 없다... <br>

## 2. Subtyping
자바와 같은 객체 지향 언어는 태그 달린 클래스를 사용할 필요가 없다. <br>
**타입 하나로 다양한 의미의 객체를 표현하기 위해 클래스 계층구조를 활용하는 서브타이핑을 사용하면 된다!** <br>
태그 달린 클래스는 클래스 계층구조를 어설프게 흉내낸 아류일 뿐이다! <br>
그냥... 이상하게 만들지 말고, <br>
일반화를 통해 상위 클래스를 만들고, 구체화된 형태의 클래스 여러개로 나누면 그만인 것이다.. <br>

## 3. Refactoring

쉬운 내용이지만, 구체적으로 태그 달린 클래스를 계층 구조를 활용해 리팩토링 하는 과정을 확인해 보자.

```java
class Figure {
    enum Shape { RECTANGLE, CIRCLE };

    // 태그 필드 - 현재 모양을 나타낸다.
    final Shape shape;

    // 다음 필드들은 모양이 사각형(RECTANGLE)일 때만 쓰인다.
    double length;
    double width;

    // 다음 필드는 모양이 원(CIRCLE)일 때만 쓰인다.
    double radius;

    // 원용 생성자
    Figure(double radius) {
        shape = Shape.CIRCLE;
        this.radius = radius;
    }

    // 사각형용 생성자
    Figure(double length, double width) {
        shape = Shape.RECTANGLE;
        this.length = length;
        this.width = width;
    }

    double area() {
        switch(shape) {
            case RECTANGLE:
                return length * width;
            case CIRCLE:
                return Math.PI * (radius * radius);
            default:
                throw new AssertionError(shape);
        }
    }
}
```
괴물같이 징그러운 클래스! <br>
한 클래스가 생성자에 따라, 상황에 따라 사각형으로, 원으로 활동하고 있다! <br>
한번 리팩토링 해보자. 
1. 루트가 될 추상 클래스를 정의한다 -> 일반화된 상위 클래스
2. **태그 값에 따라 동작이 달라지는 메서드들을 루트 클래스의 `추상 메서드`로 선언!:** 여기서는 `area()` 메서드가 shape에 따라 다르게 동작한다.
3. 태그 값에 상관 없이 동작이 같은 메서드들은 `일반 메서드`로 루트 클래스에 올린다. 여기서는 없다!
4. 공동으로 사용하는 데이터 필드들도 전부 루트 클래스로 올린다! 여기서는 없다
5. 이제, 의미 별로 (태그 별로) 루트 클래스를 확장한 구체 클래스들을 정의하며, 각각의 쓰임에 맞는 필드와 메서드들을 넣어주면 된다. 

<br>

위에서 보인 `Figure`는 계속 언급한대로 원과 사각형으로 나뉜다! <br>
일단 앙상해진 Figure을 보자.
```java
abstract class Figure {
    abstract double area();
}
```
태그에 따라 동작이 변하는 `area()`만이 추상 메서드로 남아 있다. <br>
```java
class Circle extends Figure {
    final double radius;

    Circle(double radius) { this.radius = radius; }

    @Override double area() { return Math.PI * (radius * radius); }
}
```
원의 모습, 원에 맞는 생성자 필드 등을 나누어 가졌고, area() 또한 원에 맞는 동작을 가진다. <br>
```java
class Rectangle extends Figure {
    final double length;
    final double width;

    Rectangle(double length, double width) {
        this.length = length;
        this.width  = width;
    }
    @Override double area() { return length * width; }
}
```
Rectangle의 모습, Rectangle에 맞는 생성자와 필드를 나누어 가졌고, area() 또한 Rectangle에 맞는 동작을 가진다. <br>
이렇게 리팩토링 해줌으로써 **태그 달린 클래스의 단점을 전부 날려버렸다.** <br>
쓸때없는 코드도 없고, 간결하고 명확한 코드가 되었다. 불안정한 case문도 지워버렸다. <br>
새로 클래스를 만들기도 편하다! <br>
정사각형을 만든다고 생각해보자. <br>
태그 달린 클래스에서는 또 의미도 파악하기 힘들고 (없고), 쓸대없는 필드나 생성자, 메서드 등을 추가했을 것이다. <br>
하지만 계층 구조에서는?

```java
class Square extends Rectangle {
    Square(double side) {
        super(side, side);
    }
}
```
너무너무 쉽다!! <Br>

### 요약
태그 달린 클래스를 써야만 하는 경우는 정말 거의 없다. <Br>
태그가 필요해진다면, 계층구조로 대체해버려라. 이미 그런 구조가 있다면 당장 고쳐라

## Reference
- Effective Java <조슈아 블로크>
