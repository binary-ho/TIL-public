# Item 22. 인터페이스는 타입을 정의하는 용도로만 사용하라.
이 아이템에서는 인터페이스의 본래의 목적을 강조하고, 안티 패턴인 상수 인터페이스에 대한 대안에 대해 다룬다! 


## 1. 인터페이스란? (지후 걸프란?)
**클래스가 인터페이스를 구현한다는 것은 자신의 인스턴스로 무엇을 할 수 있는지를 클라이언트에게 알리는 것이다!** <br>
인터페이스는 자신을 구현한 클래스의 인스턴스를 참조할 수 있는 타입 역할을 한다. **인터페이스는 오직 이 용도로만 사용해야 한다...**


## 2. 나쁜 아이 상수 인터페이스
상수 인터페이스는 이 지침을 개무시한 **안티패턴으로,** **메서드 없이 static final 상수 필드로만 가득 찬 인터페이스를 말한다.** <br>
```java
public interface PhysicalConstants {
  // 아보가드로 수 (1/몰)
  static final double AVOGADROS_NUMBER   = 6.022_140_857e23;

  // 볼츠만 상수 (J/K)
  static final double BOLTZMANN_CONSTANT = 1.380_648_52e-23;

  // 전자 질량 (kg)
  static final double ELECTRON_MASS      = 9.109_383_56e-31;
}
```
아주 나쁜 아이다. 인터페이스를 잘못 이용한 대표적인 예로, **인터페이스의 내부 구현들을 클래스의 API로 노출하고 앉아 있는 것이다.** 의존성이 높아지고.. 사회가 무너지고.. 가정이 무너진다.. <br>
그 위대한 자바 플랫폼에도 있는 이 상수 인터페이스는 잘못된 예이므로 따라하면 안 된다!


## 3. 착한 아이 상수 유틸리티 클래스
여기 착한 아이 상수 유틸리티 클래스를 소개하겠다. <br>
그렇게 상수를 공개해서 쓰고 싶어? 그렇다면 착한 아이와 함께 하자. <br>
```java
public class PhysicalConstants {
  private PhysicalConstants() { }  // 인스턴스화 방지

  // 아보가드로 수 (1/몰)
  public static final double AVOGADROS_NUMBER = 6.022_140_857e23;

  // 볼츠만 상수 (J/K)
  public static final double BOLTZMANN_CONST  = 1.380_648_52e-23;

  // 전자 질량 (kg)
  public static final double ELECTRON_MASS    = 9.109_383_56e-31;
}
```
**아름답다! 최고다!!!!!!!!!!** <br>
private 생성자를 통해 인스턴스화를 막고, 전부 `public static final`로 선언해버리는 것이다. <br> <br>

사용할 때는 어떻게 할까? 꼭 클래스 이름까지 명시해 주는 것이 좋다. <br>
### `PhysicalConstants.AVOGADROS_NUMBER` 
이렇게 말이다! <br>


아니면, 정적 임포트를 통해서 상수의 이름만으로 사용할 수도 있다.
```java
import static 클래스_경로.PhysicalConstants.*;

public class Test {
  double atoms(double mols) {
    return AVOGADROS_NUMBER * mols;
  }
}
```
아주 멋들어졌다..  <br>

### 결론!
인터페이스는 오로지 타입을 정의하는 용도로만 사용해야 한다! <br>
상수 인터페이스는 안티 패턴이므로, 사용하지 말고 상수 유틸리티 클래스를 사용해라! 


## Reference
- Effective Java <조슈아 블로크>

