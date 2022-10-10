# B. Lambda and interface (in Java 8)
## B1. 람다 도입 배경
1. 빅데이터의 중요성 증대
2. 병렬화 기술의 중요성 증대
3. 자바 8에서는 병렬화를 위한 컬렉션을 강화함.
4. 컬렉션을 더 효율적으로 사용하기 위해 스트림이 강화됨.
5. **이 스트림을 더 효율적으로 사용하기 위해 함수형 프로그래밍이 도입되었고, 함수형 프로그래밍을 위해 람다가 도입됨.**
7. 람다를 위해 인터페이스의 변화가 수반됨. 이를 함수형 인터페이스라고 부름


람다식은 위와 같은 배경으로 등장하였다. '따라서 B7의 컬렉션 스트림에서의 람다 사용이 중요할 듯 하다.' 나도 개인적으로 js 코드를 짜며 참 많이도 람다식을 사용하는데, 자바에서는 어떻게 되어있는지 제대로 공부해보자. 

## B.2 람?다
**람다란 코드 블록이다.** 람다는 아래와 같은 구조를 갖는다.
```java
(인자 목록) -> { 로직 }
```
예시는 아래와 같다.
```java
public static void main(String[] args) {
  Runnable runnable = () -> {
    System.out.prinln("Lambdai Lambdai Lambdaidam");
  }
}

OR

// 한 줄 일떄
public static void main(String[] args) {
  Runnable runnable = () -> System.out.prinln("Lambdai Lambdai Lambdaidam");
}
```
Runnable interface는 내부적으로 하나의 추상 메서드 `run()`을 갖는다. 그래서 위와 같은 구현은 run()을 구현한 것이 된다. 어차피 메서드가 단 하나여서 컴파일러가 헷갈릴 일은 없다.

## B.3 함수형 인터페이스
직전에 예시로서 등장한 `Runnable` interface는 `run()`이라는 추상 메서드 하나만 가지고 있다고 하였다. <br> 

이렇게 추상메서드를 하나만 갖는 인터페이스를 **자바 8 부터 함수형 인터페이스라고 한다.** <br> **이러한 함수형 인터페이스를 람다식으로 변경할 수 있다!!**


### 직접 함수형 인터페이스 선언해보기!
```java
@FunctionalInterface
interface MyFunctionalInterface {
  public abstract int runSomething(int cnt);
}
```
위와 같은 인터페이스가 있다. 단 하나의 추상 메서드를 가지고 있다. <br> 메서드 위의 `@FunctionalInterface` 어노테이션은 해당 함수가 함수형 인터페이스의 조건에 맞는지 확인해주는 어노테이션이다. 필수는 아니지만, 당연히 달아주는게 좋을 것 같다.

<br>

실제로 이용해보자.

```java
public static void main(String[] args) {
  // 기본
  MyFunctionalInterface test = (int a) -> { return a*a; };

  // 다양한 예시들
  // interface의 정의상 첫 인자는 int일 수 밖에 없어서 가능한 표현
  MyFunctionalInterface test = (a) -> { return a*a; };
  MyFunctionalInterface test = a -> { return a*a; };
  // 이 세미클론은 return이 아닌, 원래 코드 블럭의 것.
  MyFunctionalInterface test = a -> a*a;
}
```


## B.4 메서드 호출 인자로 람다 사용
내가 js에서 자주 쓰는 형태. 굳이 변수에 담아둘 필요가 없다. <br>
int 변수를 인자로 받는 메서드라면 아래와 같은 이용이 가능하다.
```java

public static void intMethod(MyFunctionalInterface test) {
  // 메서드 내용물
}

...

intMethod(a -> a * a);
```

## B.5 메서드 반환값으로 사용
```java
public static MyFunctionalInterface todo() {
  return num -> num * num;
}

...

MyFunctionalInterface test = todo();
test.runSomthing(3);
```


## B.6 자바 8 API의 함수형 인터페이스
```java
Runnable run = () -> System.out.println("hello");
Supplier<Integer> sup = () -> 3*3;
Consumer<Integer> con = num -> System.out.println(num);
Function<Integer, String> fun = num -> "input: " + num;
Predicate<Integer> pre = num -> num > 10;
UnaryOperator<Integer> uOp = num -> num*num;
```
자바 8 API에서는 여러가지 용도로 이용할 수 있는 함수형 인터페이스들을 제공한다. <br> 각 이름에 맞는 용도를 가지고 있고, 적절하게 사용하면 좋을 것 같다. 외울 필요는 없어 보이지만, 한번 각 인터페이스와 추상메서드를 통한 용도 파악은 도움이 될 것 같다.


| 함수형 인터페이스 |    추상메서드     |
| :---------------: | :---------------: |
|     Runnable      |    void run()     |
|    Supplier<T>    |      T get()      |
|    Consumer<T>    | void accept(T t)  |
|  Function<T, R>   |   R apply(T t)    |
|   Predicate<T>    | Boolean test(T t) |
| UnaryOperator<T>  |   T apply(T t)    |

추상 메서드 이름을 통해 그 용도를 추측할 수 있다. 이정도만 알면 될 것 같다. 자바에서는 무려 43가지 함수형 인터페이스를 제공한다고 하니, 역시 외울 필요가 없는 것 같다.

## B.7 컬렉션 스트림에서 람다 사용

결국 <br> 
**데이터!**를 제대로 다루기 위한 <br>
**컬렉션!**을 효율적으로 사용하기 위한 <br>
**스트림!**을 위한 <br> 
함수형 **프로그래밍!**을 위한 <br> 
것이 **람다!**이므로! <br> 
여기가 중요하겠다. <br>

<br>

그럼 스트림, 람다를 사용하면 뭐가 좋을까? <br> **함수형 프로그래밍의 장점인 선언적 프로그래밍을 활용할 수 있게 된다!** <br> **How가 아닌 What만을 지정한다!** <br>

무엇을 어떻게 해주세요가 아닌, 무엇을 줘!가 됩니다. 미성년자 출입 제한 코드의 리펙토링 과정을 봅시다.
```java
// 기존 방식
for (int i = 0; i < ages.length; i++) {
  if (ages[i] < 20) {
    System.out.format("Age %d!! Can't enter\n", ages[i]);
  }
}
```
```java
// 향상된 for 문
for (int age : ages) {
  if (age < 20) {
    System.out.format("Age %d!! Can't enter\n", age);
  }
}
```
대망의 스트림 + 람다
```java
Arrays.stream(ages)
    .filter(age -> age < 20)
    .forEach(age -> System.out.format("Age %d!!!!!!! Can't Enter!!!!\n", age));
```
위의 3줄을 보자. 정말 선언적이다.
1. 스트림을 얻기 위해 Arrays 클래스의 정적 메서드 stream() 사용
2. **20세 미만의 경우를 선별(filter)해줘.**
3. **선별된 요소들에게 저리 가라고 말 해줘.**

보면 알 수 있다 싶이, 마치 SQL문 처럼 **무엇을 원하는지만 요구했다!** 선언적 프로그래밍 요소 덕분에 의사소통 내용 자체가! 그대로 코드로 구현되었다!

## B.8 메서드 레퍼런스와 생성자 레퍼런스
람다식을 메서드 레퍼런스의 형식으로 바꿀 수 있다. 메서드 레퍼런스에는 3가지 유형이 있다.
1. 클래스::정적메서드
2. 클래스::인스턴스메서드
3. 인스턴스::인스턴스메서드

```java
Double[] nums = { ... };
// 기존 람다식
Arrays.stream(nums)
    .map(num -> Math.sqrt(num))
    .forEach(sqrtNum -> System.out.println(sqrtNum));

// 래퍼런스 형태
Arrays.stream(nums)
    .map(Math::sqrt)
    .forEach(System.out::println);
```

잘 보면, map안의 Math.sqrt()를 사용하는 부분은 **클래스::정적메서드**형식으로 바뀌었고, <br>
forEach를 쓰는 부분도 **인스턴스::인스턴스메서드**형식으로 바뀌었다. <br>

이렇게 바뀔 수 있는 이유는 어차피 인수가 명확하기 때문으로 추측된다. map의 결과는 어차피 컬렉션을 하나 하나 꺼내어 보는 형태일테니, squt에 인수로 들어가기 적합하고, forEach 또한 마찬가지이다. <br> 마지막으로 **클래스::인스턴스메서드**형태도 살펴보자.
```java
BiFunction<Integer, Integer, Integer> bip = (a, b) -> a.compareTo(b);
BiFunction<Integer, Integer, Integer> bip = Integer::compareTo;
```

#### 생성자 래퍼런스
생성자 레퍼런스로 함수형 인터페이스의 구현 객체를 만들 수 있다.
```java
// TestClass test = TestClass::new;
```
이건 안 된다. 생성자 레퍼런스의 결과로 생성되는 것은 클래스의 객체가 아니다. **생성자 레퍼런스로 만들어 지는 것은 함수형 인터페이스의 구현 객체이다.** 따라서 아래와 같은 이용이 적절하다.
```java
Supplier<TestClass> factory = TestClass::new;

TestClass test1 = factory.get();
TestClass test2 = factory.get();
```
물론 람다 표현도 가능
```java
Supplier<TestClass> factory = () -> new TestClass();
```

## B.9 인터페이스의 디폴트 메서드와 정적 메서드 in JAVA 8
디폴트 메서드는 - 구체 인터페이스 메서드이다. 이제 인터페이스도 몸체를 가진 인스턴스 메서드를 가질 수 있게 되었다.

```java
@FunctionalInterface
public interface MyFunctionalInterface {
  public static final int constant = 1;
  public abstract void abstractInstanceMethod();

  // 디폴트 메서드 - 구체 인스턴스 메서드
  public default void concreteInstanceMethod() {
      System.out.println("디폴트 메서드 - 구체 인스턴스 메서드");
  }

  // 정적 메서드 - 구체 정적 메서드
  public static void concreteStaticMethod() {
      System.out.println("정적 메서드 - 구체 정적 메서드");
  }
}

```

상상하는 것과 쓰임이 같다. <br>
디폴트 메서드는 아래와 같은 형태로 받으면, 따로 구현 없이 사용이 가능하다.
```java
@Override
public void concreteInstanceMethod() {
  MyFunctionalInterface.super.concreteInstanceMethod();
}
```
**당연히 위와 같은 오버라이드가 없어도 잘 작동한다. 그래서 default 메서드이다.** <br>

정적 메서드는 우리가 아는 클래스에서의 정적 메서드와 똑같이 작동한다.

<!-- 스트림과 병렬화, parallellStream() 공부하기 -->
