# Item 5. 자원을 직접 명시하지 말고 의존 객체 주입을 사용하라

의존하는 자원이 있는 경우, 직접 자원을 명시하면 의존성이 너무 높아진다. <br>
해당 객체에서 직접 자원을 `new Object()`와 같은 방식으로 직접 의존을 형성하면, 유연한 대처가 어렵다. <br>

타이어의 종류는 수십가지이다. 그런데 한 종류의 타이어에 직접 의존해 버리면, 다른 타이어들을 사용하려 할 때, 많은 코드 변경이 있을 수 있다. <br>
그 타이어에 특화된 코드가 형성되어 있기 때문이다. <br>

의존성을 낮추고, 응집도를 높히기 위해선 **의존 객체를 주입해야 한다.**

```java
public class SpellChecker {
  private final Lexicon dictionary;

  public SpellChecker(Lexicon dictionary) {
    this.dictionary = Objects.requireNonNull(dictionary);
  }

  public boolean isVaild(String word) { ... }
}
```
자원인 dictionary를 생성자를 통해 주입받으면, Lexicon을 구현한, 다양한 dictionary를 얼마든지 이용할 수 있게 된다.

### 팩터리 주입 변형
위의 변형으로 자원 팩터리를 주입 받을 수도 있다. <br>
팩터리 메서드 패턴을 구현한 팩터리를 주입 받아, 특정 타입의 인스턴스를 만들어낸다. <br>

```java
Mosaic create(Supplier<? extends Tile> tileFactory) { ... }
```
위의 코드는 그 예시로, 타일을 상속한 클래스를 찍어내는 팩토리를 전달받은 것이다. <br>

### 결론
클래스가 내부적으로 하나 이상의 자원에 의존하고, 그 자원이 클래스 동작에 영향을 준다면, 싱글턴과 정적 유틸리티 클래스는 사용하지 않는 것이 좋다. <br>
그리고 이 자원들을 클래스가 직접 만들게 해서도 안 된다. <br>
대신에 필요한 자원이나 자원을 만들어내는 팩터리를 생성자를 통해 넘겨 받아라. <br> 
의존 객체 주입이라 하는 이런 기법은 클래스의 유연성, 재사용성, 테스트 용이성을 많이 개선해준다.


## Reference
- Effective Java <조슈아 블로크>
