# Item 13. clone 재정의는 주의해서 진행하라
Cloneable의 확장은 웬만하면 지양하는게 좋다. 여러 관점에서 봤을 때 웬만하면 재정의하지 않는 것이 좋고, <br> 
원칙은 - **복제 기능은 생성자와 팩터리를 이용하는것이 최고다!** <br>
유일하게 **배열, 배열만이 clone 메서드 방식이 깔끔하게 들어 맞는 예외일 뿐, 원칙적으로는 clone을 쓰지 않는다.** <br>

이 장에서는 그런 Cloneable을 인터페이스가 확장했을 때 몰고 오는 다양한 문제를 살펴보고 생성자와 팩터리 사용을 권한다. <br>
그래서 나는 글의 앞에 먼저 권장되는 방식 먼저 보이고, 단점을 설명하고자 한다.

# 1. 복사 생성자와 복사 팩터리를 사용하라!
꼭 Cloneable을 구현해야 하는 경우는 드물다. Cloneable을 이미 구현한 클래스를 확장한다면 필요하지만, 아닌 경우 **복사 생성자와 복사 팩터리를 사용해라!** <br>

복사 생성자는 아래와 같이 구현하면 된다.
```java
class Student
{
    private String name;
    private int age;
    private Set<String> subjects;
 
    public Student(String name, int age, Set<String> subjects)
    {
        this.name = name;
        this.age = age;
        this.subjects = subjects;
    }
 
    /* 복사 생성자 */
    public Student(Student student)
    {
        this.name = student.name;
        this.age = student.age;

        /* 깊은 복사 */
        this.subjects = new HashSet<>(student.subjects);
    }

    ...
}
```
이렇게 단순하게 자신과 같은 클래스의 인스턴스를 인수로 받아 생성하는 생성자를 말한다. <br>

복사 팩터리는 복사 생성자를 모방한 정적 팩터리다.
```java
class Student
{
    private String name;
    private int age;
    private Set<String> subjects;

    public Student(String name, int age, Set<String> subjects)
    {
        this.name = name;
        this.age = age;
        this.subjects = subjects;
    }

    // 복사 생성자
    private Student(Student student)
    {
        this.name = student.name;
        this.age = student.age;
        this.subjects = new HashSet<>(student.subjects); 
    }

    // 팩토리 복사
    public static Student newInstance(Student student) {
        return new Student(student);
    }
}
```
심플하다. 어떻게 구현하든, 자신과 같은 클래스를 가진 인스턴스를 받아 복사해주면 된다. <br>

이렇게 복사 생성자나 팩터리를 사용하면 여러 장점이 있다.
1. **해당 클래스가 구현한 인터페이스 타입의 인스턴스를 인수로 받을 수 있다.** <br> ex) 대부분의 범용 컬렉션 구현체는 Collection이나 Map 타입을 받는 생성자를 제공한다. 이를 '변환 생성자' 혹은 '변환 팩터리'라고 부른다. <br> **원본의 구현 타입에 얽매이지 않고, 복제본의 타입을 직접 선택할 수 있다.**

2. 언어 모순적이고 위험한 객체 생성 메커니즘을 사용하지 않는다.
3. 엉성하게 문서화된 규약에 기대지 않는다.
4. 정상적인 final 필드 용법과도 충돌하지 않는다.
5. 불필요한 검사 예외를 던지지 않고 형변환이 필요 없다


이렇게나 장점이 많으니 안 쓸 이유가 없다 <br>
그리고 장점 2 ~ 5에서 언급된 부분들은 Cloneable 방식의 단점이다. <br>

# 2. Cloneable/clone 구현하기
Cloneable은 특이하다. 보통 인터페이스를 구현한다는 것은 해당 클래스가 그 인터페이스에서 정의한 기능을 제공한다고 선언하는 행위인데, Cloneable의 경우에는 상위 클래스에 정의된 protected clone의 동작 방식을 '변경'한다. <br>
**드물게 Cloneable을 구현해야 하는 경우가 있다.** 그런 경우 어떻게 구현해야 할지 한번 살펴보자........ <br>
일단, 명세에서 이야기하진 않지만, 실무에서 상대방은 `Cloneable을 구현한 클래스는 clone 메서드를 public으로 제공하며, 복제가 이루어지길` 기대한다. <br>

이런 기대를 만족시키려면 그 클래스와 모든 상위 클래스는 복잡하고, 강제할 수 없고, 허술하게 기술된 프로토콜을 지켜야 한다. 그 결과 깨지기 쉽고, 위험하고, 모순적인 매커니즘이 탄생한다. 생성자를 호출하지 않고도 객체를 생성할 수 있게 된다.


```
이 객체의 복사본을 생성해 반환한다. '복사'의 정확한 뜻은 그 객체를 구현한 클래스에 따라 다를 수 있다. 일반적인 의도는 다음과 같다. 어떤 객체 x에 대해 다음 식들은 참이다.

1. x.clone() != x
2. x.clone().getClass() == x.getClass()
하지만, 이상의 요구를 반드시 만족해야 하는 것은 아니다 (허술)

한편 다음 식도 일반적으로 참이다. 허나 필수는 아니다.

1. x.clone().equals(x)
관례상 이 메서드가 반환하는 객체는 super.clone()을 호출해 얻어야 한다. 이 클래스와 모든 상위 클래스가 이 관례를 따른다면, 아래 식은 참이다.

x.clone().getClass() == x.getClass()
```

clone을 구현한 어떤 클래스의 하위 클래스가 super.clone을 호출한다고 생각해보자. 그러면 하위 클래스는 상위 클래스를 받게 되므로, clone이 제대로 동작하지 않는 일이 벌어진다. <br>
그래서 clone 메서드를 가진 상위 클래스를 상속해 Cloneable을 구현하고 싶다고 생각해보자. 얕은 복사만 가능한 경우, 그냥 아래 처럼 해줄 수 있다.

```java
public final class PhoneNumber implements Cloneable {

    ...

    @Override public PhoneNumber clone() {
        try {
            return (PhoneNumber) super.clone();
        } catch (CloneNotSupportedException e) {
            throw new AssertionError();  // 일어날 수 없는 일이다.
        }
    }
}
```

Cloneable을 구현한 다음, clone을 구현했다. 사용자가 따로 형변환 할 필요 없게 위처럼 하위 타입으로 형변환 해주자. <br>
PhoneNumber의 Cloneable을 구현했으므로 에러가 터지지 않을 것임을 알지만, 적어 줘야 한다.

## 3. 가변 객체 참조 Clone
위의 상황은 얕은 복사면 되는 상황이였다. 이젠 가변 객체를 참조하는 경우를 살펴보자. <br>

```java
public class Stack implements Cloneable {
    private Object[] elements;
    private int size = 0;
    private static final int DEFAULT_INITIAL_CAPACITY = 16;

    public Stack() {
        this.elements = new Object[DEFAULT_INITIAL_CAPACITY];
    }

    ...

}
```
우리가 잘 아는 Stack을 Java로 구현한 것이다. 위의 코드에서 기본 clone을 쓰면 어떻게 될까? <br>
`private Object[] elements`가 문제가 된다. 다 복사한 다음, 같은 배열을 참조하는 객체를 만들어 낼것이다! <Br>
**그러니까 의도와 달리 같은 elements를 공유하는 Stack이 만들어질 것이다.** <br>

이를 고쳐주기 위해선, clone에서 따로 재귀적으로 배열을 clone해줄 필요가 있다.
```java
  @Override public Stack clone() {
      try {
          Stack result = (Stack) super.clone();
          result.elements = elements.clone();
          return result;
      } catch (CloneNotSupportedException e) {
          throw new AssertionError();
      }
  }
```
이렇게 말이다! 배열에서 clone을 호출해줬다. <br>
#### 배열을 복제할 때는 배열의 clone 메서드를 사용하라고 권장한다.
#### 사실 배열은 clone 기능을 제대로 사용하는 유일한 예이다.

한편, 배열이 final이였다면, 이런 동작은 불가능하다. 그렇다고 final을 풀자니, **Cloneable은 사실상 가변 객체를 참조하는 필드는 final로 선언하라는 일반 용법과 충돌한다!** <br> <br>
아주 끔찍하다. <br>
또 연결 리스트를 복사해야 하는 경우에는 위의 방법이 먹히지 않는다. 당연한 것이 시작지점만을 복사할 것이기 때문이다. <Br>
그래서 연결리스트를 사용해야 하는 경우엔 아주 힘든 방식을 통해 전체를 deep copy하는 구현을 해내야한다. <br>

## 4. 결론!
자... 결론은.. <br>
1. Cloneable을 구현하는 모든 클래스는 clone을 재정의 해야 한다.
2. 이때, 접근 제한자는 public으로, 반환 타임은 클래스 자신으로 **형변환** 한다.
3. 먼저, super.clone을 호출한 후, 필요한 필들르 전부 적절하게 수정한다. <br> 즉, 가변 객체나 객체 내부의 깊은 구조까지 전부 고려해서 복사해주어야 한다.


이렇게 해야할까..? 너무 힘들다. <br>
Cloneable을 구현한 클래스를 확장한다면 어쩔 수 없이 clone이 작동하도록 구현해야겠지만, 아니라면 그냥 **복사 생성자와 복사 팩터리를 써라..**




## Reference
- Effective Java <조슈아 블로크>

