# 아이템 3. private 생성자나 열거타입으로 싱글턴임을 보증하라.

클래스를 싱글턴으로 만드는 방식은 보통 두 가지이다. 
두 방식 모두 클라이언트에서 함부로 생성자를 호출할 수 없도록, 생성자를 private로 감춰둔다. <br>
찬진이는 아예 호출시 예외를 발생하도록 처리하기도 했다. <br>
그리고 `유일한` 인스턴스에 접근할 수 있는 수단을 제공해주는데, **Public Static 맴버를 하나 만들어둔다.** <br>
그 public static 맴버를 무엇으로 줄 지에 따라 두가지 방법으로 나누어 볼 수 있다.

## 1. 맴버가 final 필드인 방식
```java
public class Elvis {
    public static final Elvis INSTANCE = new Elvis();

    private Elvis() { }

    public void leaveTheBuilding() { ... }
}
```
클래스 첫 줄을 보자. **`private`생성자는 public static final 필드인 `Elvis.INSTANCE`를 초기화 할때 딱 한번만 호출된다.** <br>
**다른 생성자가 없으므로,** 클래스가 초기화될 때 만들어진 인스턴스가 **전체 시스템에서 하나뿐임이 보장된다!** <br>

예외가 발생할 수 있는 경우도 있는데, private 생성자를 호출할 수도 있다고 한다. <br>
이에 대비해 private 생성자에 호출시 예외가 발생하도록 처리해줄 수 있다. <br>

**장점**
1. 해당 클래스가 싱글턴임이 API에 아주 명백히 드러난다! <br> public static 필드가 final이니, 절대 다른 객체를 참조할 수가 없다!!
2. 간결하다

## 2. 정적 팩터리 메서드를 public static 맴버로 제공
```java
public class Elvis {
    private static final Elvis INSTANCE = new Elvis();
    private Elvis() { }
    public static Elvis getInstance() { return INSTANCE; }

    public void leaveTheBuilding() { ... }
}
```

정적 팩터리 메서드가 제공됐다. <br>
`Elvis.getInstance`는 항상 같은 객체의 참조를 반환하므로, Elvis의 제 2의 인스턴스란 결코 만들어지지 않는다! <br> (단, 여기서도 1번과 같이 예외가 발생할 수 있다.)

**장점**
1. API를 바꾸지 않고도, 싱글턴이 아니게 바꿀 수 있다! 
2. 정적 팩터리를 `제네릭 싱글턴 팩터리`로 만들 수 있다. (아이템 30이라고 한다.)
3. 정적 팩터리의 메서드 참조를 Supplier로 사용할 수 있다. <br> getInstace의 반환을 그냥 Elvis가 아니라, `Supplier<Elvis>`로 사용하면 그만이다!

## 3. 직렬화 문제
위 두가지 방식으로 만든 싱글턴 클래스를 직렬화 하려면, 평소처럼 단순히 `Serializable`을 구현하는 것으로는 모자라다. <br>
직렬화된 인스턴스를 역직렬화할 떄마다 새로운 인스턴스가 만들어질 수 있다. <br>
이를 해결하려면
**모든 인스턴스를 transient이라고 선언하고 readResolve 메서드를 제공해야 한다** (아이템 89) <br>

```java
/*  */
private Object readResolve() {
  return INSTANCE;
}
```
이런 `가짜`가 탄생되는 현상을 막으려면 위와 같은 `readResolve` 메서드를 추가해야 한다. <br>
위의 코드는 진짜 Elvis를 반환하고 가짜 Elvis는 가비지 컬렉터에 맡기는 코드이다. <br>
위와 같은 코드를 통해 싱글턴을 보장할 수 있다.

## 4. 원소가 하나인 Enum 타입을 선언하는 방식
```java
public enum Elvis {
    INSTANCE;

    public void leaveTheBuilding() { ... }
}
```
싱글턴을 만드는 세번째 방법이다! <br>
**원소가 하나인 Enum 타입을 선언하는 것이다.** <br>
public 필드 방식과 유사하지만, 더 간결하고 직렬화 하기가 쉽고, 위의 2 방법에서 발생하는 예외를 막아준다. <br>
좀 부자연스러워 보이지만, **대부분의 상호아에서는 원소가 하나뿐인 열거 타입이 싱글턴을 만드는 가장 좋은 방법이라고 한다.** <br>
단, 상속 문제로, 만드려는 싱글턴이 Enum 외의 클래스를 상속해야 한다면 사용할 수 없다.



## Reference
- Effective Java <조슈아 블로크>



