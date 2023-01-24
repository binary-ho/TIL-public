# Covariant Return Type 공변 반환 타입
자바의 공변 반환 타이핑은 상속 관계 클래스의 `is a` 관계를 이용해 반환 타입에 대해 공변성을 지원해주는 기능이다. <br> 
무슨 말이냐면, 부모 클래스를 반환하는 메서드를 자식 클래스에서 Override한다면, 반환 값을 자식 클래스로 바꿔줄 수 있다. <br>
즉, **부모 클래스의 반환 타입은 자식 클래스의 타입으로 변경이 가능하다** <br>
바로 예시로 확인하자. 
```java
public class Animal {

    public Animal test() {
        return new Animal();
    }
}
```
위와 같이 부모 타입을 반환하는 클래스가 있을 때,

```java
public class Dog extends Animal {

    @Override
    public Animal test() {
        return this;
    }
}
```
이렇게 똑같이 부모 타입을 반환해도 되지만,

```java
public class Dog extends Animal {

    @Override
    public Dog test() {
        return this;
    }
}
```
**이렇게 자신을 반환하도록 바꿔줄 수 있다!** <br>

이렇게만 보면 뭐 신기하긴 한데 어쩌라고? 할 수 있겠지만, Object에서 제공하는 clone과 유용한 메서드들을 재정의 할때, 굳이 부모 타입으로 반환해줄 필요 없다. 

## Reference
- [손너잘 블로그 - 공변 반환 타이핑](https://bperhaps.tistory.com/entry/%EA%B3%B5%EB%B3%80%EB%B0%98%ED%99%98-%ED%83%80%EC%9D%B4%ED%95%91)
- [인쥭 블로그 - 공변 반환 타입(covariant return type)](https://ingnoh.tistory.com/153?category=1195061)
