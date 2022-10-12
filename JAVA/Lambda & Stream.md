# 1. Lambda Expression
## 1.1 람다 도입 배경
람다의 도입으로 **자바는 더 이상 예전의 자바가 아니게 되었다고 한다.** <br>
자바는 람다식의 도입으로 인해, **객체지향언어인 동시에 함수형 언어가 되었다.** 람다식은 왜 도입되었을까?

1. 빅데이터의 중요성 증대
2. 병렬화 기술의 중요성 증대
3. 자바 8에서는 병렬화를 위한 **컬렉션을 강화**함.
4. 컬렉션을 더 효율적으로 사용하기 위해 **스트림이 강화**됨.
5. 이 스트림을 더 효율적으로 사용하기 위해 **함수형 프로그래밍이 도입**되었고, **함수형 프로그래밍을 위해 람다**가 도입됨.
7. 람다를 위해 인터페이스의 변화가 수반됨. 이를 함수형 인터페이스라고 부름


람다식은 위와 같은 배경으로 등장하였다. 

## 1.2 람?다
**람다식은 메서드를 <U>하나의 식으로</U> 표현한 것이다.** **람다란 코드 블록이다.** <br> 람다식을 적용하면 메서드의 **이름과 반환값이 없어진다.** 그래서 람다를 익명함수라고도 부르는 것이다. 람다는 아래와 같은 구조를 갖는다.

```java
(인자 목록) -> { 로직 }
```

그 예시는 아래와 같다.
```java
int max(int a, int b) {
  return a > b ? a : b;
}
```
위와 같은 메서드를 람다를 통해 아래와 같이 나타낼 수가 있다.
```java
(int a, int b) -> {
  return a > b ? a : n;
}
```
로직이 한 줄이고, 반환값이 있는 메서드이므로 아래와 같이 return과 중괄호를 한번에 없앨 수 있다.
```java
(int a, int b) ->  a > b ? a: n
```
return을 남기는 경우 중괄호를 없앨 수 없다.
<br>
연산결과가 자동으로 반환값이 된다. 문장이 아니라, 식이므로, 끝에 `;`이 붙지 않는다. <br>
여기서 또 있다. 매개변수 타입이 추론 가능하다면, 아래와 같은 생략도 가능하다.
```java
(a, b) ->  a > b ? a: n
```

매개변수가 하나이면 이런 것도 가능하다
```java
(a) -> a * a

a -> a * a
```
배리에이션을 자세히 아는게 중요해 보이지는 않는다. 어차피 필요할 때 구글링 하거나, 인텔리제이에서 알아서 도와줄 것이기 때문이다. 쓰다 보면 손에 익을 것이다. <br> <br>

기존의 메서드는 클래스에 포함되어야 하기 때문에, 여러 귀찮은 제약들이 많았다. 정의하려머느 클래스도 만들어야 하고, static이 아닌 경우 객체도 만들어야 호출 가능하고, 정말 귀찮았다! 이런 귀찮음을 해결해 주는 것이 바로 람다식! <br> 게다가, 람다식은 매개변수로 전달 되는 것도 가능하고, 결과로 반환될 수도 있다. 이로인해 마치, **메서드를 변수처럼 다루는 것이 가능해진 것이다.**

## 1.3 함수형 인터페이스
람다식은 내부적으로 어떻게 작동하는 것일까? 기존의 탄탄한 자바 세계에 큰 영향을 미치지 않고, 어떻게 람다식을 도입했을까? <br>

람다식은 일종의 메서드처럼 표현했고, 나도 그렇게 생각했다. 람다식의 실체는 메서드가 아닌, **익명 클래스의 객체이다.**

```java
(int a, int b) -> a > b ? a : b;
```
위와 같은 람다식은 실제로는 아래와 같다.
```java
new Objcet() {
  int max(int a, int b) {
    return a > b ? a : b;
  }
}
```
max는 그냥 붙인 이름이다. 람다식은 익명 클래스의 객체이다. <br>
#### 직접 함수형 인터페이스 선언해보겠다!
인터페이스에 단 하나의 추상 메서드만을 갖도록 만들면 된다. 인터페이스 위에 `@FunctionalInterface`를 붙이면, 올바르게 함수형 인터페이스를 정의하였는지 체크해준다.
```java
@FunctionalInterface
public interface TestFunctionalInterface {
    public abstract int max(int a, int b);
}
```
**람다식은 익명 클래스의 객체**이므로, 아래 두 표현은 같은 표현이다.
```java
MyFunctionalInterface test = new MyFunctionalInterface() {
  @Override
  public int max(int a, int b) {
    return a > b ? a : b;
  }
};
MyFunctionalInterface test1 = (int a, int b) -> a > b ? a : b;
```

람다는 이런 식으로 만들어졌다. 하나의 메서드가 선언된 인터페이스를 정의해서 람다식을 다루는 것은 기존의 자바의 규칙들을 어기지 않으면서도 자연스럽다. 이렇게 자바는 기존의 것들에 최대한 적은 영향을 주면서 람다식을 구현해냈다. <br> <br>


## 1.4 함수형 인터페이스 타입의 매개변수와 반환 타입
**람다식은 참조변수로 다룰 수 있다.** <br>

이는 람다식을 주고 받을 수 있다는 것을 의미한다. 람다식을 통해 마치 변수처럼 메서드를 주고 받는 것이 가능하다는 것이다.  <br>

람다식은 매개변수로 지정할 수 있고, 반환 타입이 함수형 인터페이스라면, 함수형 인터페이스의 추상형 메서드와 동등한 람다식을 가리키는 참조변수를 반환하거나, 람다식을 집접 반환할 수 있다. <br>

사실 람다식의 본질은 객체이기 때문에, 사실은 객체를 주고 받는 것이라서 근본적으로 달라진 것은 없지만, 더 간결하고 이해하기 쉽다는 점이 장점이겠다. <br>

```java
@FunctionalInterface
public interface TestFunctionalInterface {
    void run();
}
```
```java
// 이런 메서드가 있을 수 있다.
// TestFunctionalInterface 참조 변수로 받으면, 람다함수 참조 변수가 된다.
static TestFunctionalInterface getFuction() {
  return () -> System.out.println("Run~");
}
```

```java
// 인수로 넣기 가능
static void execute(TestFunctionalInterface test) {
  test.run();
}

public static void main(String[] args) {
  execute(() -> System.out.println("런~"));
// 런이라고 바로 출력된다.

  // 함수형 인터페이스 참조 변수로 받을 수도 있다.
  TestFunctionalInterface test = () -> System.out.println("무야호~");
}
```

## 1.5 람다식의 타입과 형변환
바로 위에서 함수형 인터페이스의 참조변수로 람다식을 참조할 수가 있었다. <br> **그렇다면, 람다식의 타입이 함수형 인터페이스의 타입과 일치하는가?** <br>
```java
TestFunctionalInterface test = () -> System.out.println("무야호~");
```
위와 같이 받아냈으니, 오른쪽 람다식의 타입은 TestFunctionalInterface일까? <br>

람다식의 타입? 또 무슨 소린가 싶지만, 람다식은 익명 객체이고, 익명 객체는 타입이 없다. 정확히는 타입은 있지만, 컴파일러가 임의로 이름을 정하기 때문에 알 수가 없다. 그래서 사실은 
묵시적으로 `(TestFunctionalInterface)`가 붙어 형변환이 이루어 지는 것이다. <br>

특이하게도 Object로의 형변환은 안 된다. 함수형 인터페이스로의 형변환이 허락되고, 굳이 Objcet 만들려면 함수형 인터페이스로 바꾼 다음 Object로 바꿔주면 또 된다. <br> <br>

**그래서 결론은 무슨 타입인데;** <br> **컴파일러는** 람다식의 타입을 외부클래스의 이름을 이용해서 만든다. (익명 객체의 타입을 만들 때 처럼) <br>

일반적인 익명 객체는 `외부클래스$번호`와 같은 타입을 갖고, 람다식은 `외부클래스이름$$Lambda$번호`와 같은 형식을 갖는다.

![람다 타입](https://user-images.githubusercontent.com/71186266/195284245-f0b8b1b3-5874-4661-a10f-b200e02f1492.png)


## 1.6 외부 변수를 참조하는 람다식
람다식은 익명 객체이므로, 참조하는 지역변수를 final로 만든다. 즉, 상수로 간주되게 만든다. <br> assignMe를 참조하는 순간, 다른 곳에서 이를 변경하는 것을 허용하지 않는다.
![람다 변수 참조 1](https://user-images.githubusercontent.com/71186266/195290184-fd370ce2-2128-49e6-ad09-8035e8cbe9b2.png)
평화롭다.
![람다 변수 참조 2](https://user-images.githubusercontent.com/71186266/195290190-6293319f-cc93-4667-b584-32e39b953720.png)
역시 평화롭다.
![람다 변수 참조 3](https://user-images.githubusercontent.com/71186266/195290194-e788b62a-e5b4-4e93-951e-cece08f0a3e2.png)
에러 발생
 
<br>
그리고 외부 지역변수와 같은 이름의 람다식 매개변수는 허용되지 않는다.

## 1.7 java.util.function 패키지
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

<!-- ## 1.8 컬렉션 프레임워크와 함수형 인터페이스? 디폴트 메서드
컬렉션 프레임워크의 인터페이스에 다수의 디폴트 메서드가 추가되었다. 그 중의 일부는 인터페이스를 사용한다.

 -->

함수형 인터페이스들의 다양한 사용법은 생략하겠다. 나중에 작성 한번 해보자.

## 1.8 Method Reference

람다식이 하나의 메서드만을 호출하는 경우, 메서드 레퍼런스의 형식으로 바꿀 수 있다. 메서드 레퍼런스에는 3가지 유형이 있다.
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

## 1.9 생성자도 Method Reference해버리자
생성자를 호출하는 람다식도 메서드 참조로 변환할 수 있다. WOW <br>

```java
Supplier<TestClass> factory = () -> new TestClass();
Supplier<TestClass> factory = TestClass::new;

// 매개 변수 여러개인 경우
Function<Integer, TestClass> factory1 = (elem) -> new TestClass(elem);
Function<Integer, TestClass> factory1 = TestClass::new;


BiFunction<Integer, String, TestClass> factory2 = (elem, elem2) -> new TestClass(elem, elem2);
BiFunction<Integer, String, TestClass> factory2 = TestClass::new;

// 배열
Function<Integer, int[]> factory3 = (x) -> new int[x];
Function<Integer, int[]> factory3 = int[]::new;
```
매개 변수가 있는 생성자라면, 그에 맞는걸로 해주면 된다. 물론 배열도 된다.


# 2 스트림 (stream)
스트림이란 앞서 언급한 것 처럼! 빅 데이터의 중요성이 증대되면서, 병렬화 기술을 이용한 컬렉션 사용의 효율을 높이기 위해 등장했다. <br>

기존의 for 문이나, Iterator을 이용한 탐색은 길고 알아보기도 힘들었고, 재사용성도 떨어졌으며, 소스별로 다루는 방식이 달라 여간 불편한 것이 아니였다. <br>

Iterator 있잖아요? 컬렉션을 위한 인터페이스 Iterator가 물론 있지만, 컬렉션 클래스는 중복 정의 메서드가 너무 많았다.. 예를 들어 List는 Collections.sort()로 정렬하고, 배열은 Arrays.sort()로 정렬하고, 더 편리한 새로운 추상화가 필요했다.. <br>  <br>
그래서 나온 것이 **스트림이다.** 데이터 소스들을 아름답게 추상화 하였고, 이를 통해 재사용성이 높아졌다. <br>
스트림을 통한 리펙토링 과정을 맛보자면..
```java
String[] strArr = { "aaa", "bbb", "ccc" };
List<String> strList Arrays.asList(strArr);
```
위와 같은 배열과 리스트에 대해, 아래와 같이 간단하게 모든 원소를 출력해낼 수 있다.
```java
Stream<String> stream1 = strList.stream();
Stream<String> stream2 = Arrays.stream(strArr);

stream1.sorted().forEach(System.out::println);
stream2.sorted().forEach(System.out::println);
```
람다 메서드 인터페이스까지 함꼐 적용된 모습이다.. 진짜 스트림과 람다는 전설이다.. <br>
우리가 자주 사용하는 forEach가 스트림 최종연산으로 쓰였다. 메서드를 받아서, 해당 메서드를 원소 하나 하나에 적용시켜준다. <br> 이 밖에도 통계를 낸다던지, 그룹을 지어준다던지의 다양한 기능을 제공한다. <br> <br>


대충 맛 봤으니, 스트림의 대표 성질들에 대해 알아보자.
### 2.1 스트림은 데이터 소스를 변경하지 않는다.
스트림은, 데이터 소스로 부터 데이터를 **읽어오기만 한다.** 그 소스를 변경하지 않는다.
### 2.2 스트림은 일회용이다.
스트림은 Iterator와 같이 **일회용이다.** 스트림을 한번 사용하고 나면, 재사용이 불가능하다.
```java
stream1.sorted().forEach(System.out::println);
int size = stream1.count(); -> 불가능!
```
### 2.3 스트림은 작업을 내부 반복으로 처리한다!
스트림이 간결할 수 있었던 비결 중의 하나가 `내부 반복`이다. 반복문을 메서드 내부에 숨김으로써, 간결함을 가질 수 있었다. -> forEach가 그 예시이다.

## 2.4 스트림의 연산
스트림의 강점 중 하나로, **스트림은 연산 결과를 스트림으로 반환한다.** <br>
정확히는 연산을 **중간 연산**과 **최종 연산**으로 나누었는데, <br>
**중간연산은 스트림을 반환하므로, 연속적으로 스트림 연산을 계속해서 적용할 수가 있다.** <Br>
**최종 연산**은 반환값이 스트림이 아니고, 스트림을 소모한다. 따라서 단 한번만 호출이 가능하고, 최종 연산의 호출로 스트림은 닫히게 된다.
```java
stream.distinct().limit(5).sorted().forEach(System.out::println);
```
## 2.5 스트림 지연연산!
**스트림은 게으르다.** <br>

스트림의 연산에서 중요한 점이 있는데, 그것은 **최종연산이 수행되기 전에는 중간 연산이 수행되지 않는 다는 점이다.** 책에는 이렇게 적혀있다. 하지만 나는 **결과가 필요하기 전까지는 연산을 수행하지 않는다.**가 더 적절하다고 생각한다. <br> <br>

**스트림의 Lazy 연산에 대해 알아보자.** <br> 분명 대부분의 연산에서는 Eager(즉시) 연산이 속도 면에서 유리하다. 작업의 결과가, 즉시 다음 작업의 인풋으로 쓰이는 스트림과 같은 연산이라면 그 차이가 더 클 것이다. 그 뿐인가? 지연 연산은 스트림 문장 전체를 인식하고 시작하기 때문에, 추가 오버헤드가 발생한다. <br> 하지만, 스트림에서는 Lazy한 연산을 수행한다. **이는 스트림이 거대한 컬렉션을 다루는 것을 고려해서 최적화 하였기 떄문이다.**
그리고 무한한 원소를 가진 무한 스트림의 활용 또한 고려하였기 때문이다. 
<br> 

이를 위해 스트림에서는 **루프 퓨전**과 **쇼트 서킷**을 제공한다.

## 2.5.1 스트림 루프 퓨전
이름이 참 멋있다. 스트림 루프 퓨전이 무엇일까? 아래와 같은 스트림 연산이 있다. <br>
```java
static class Data {
  private final int value;
  public Data(int value) { this.value = value; }
  @Override public String toString() { return " -> " + value; }
}
```
```java
Stream.of(new Data(1), new Data(20), new Data(300))
    .peek(System.out::println)
    .peek(System.out::println)
    .forEach(System.out::println);
```
- of는 입력으로 배열을 받아 스트림으로 만듦
- peek은 forEach의 중간 연산 버젼
- forEach는 forEach

이것의 결과는 어떻게 나올까?
```
-> 1
-> 20
-> 300
-> 1
-> 20
-> 300
-> 1
-> 20
-> 300
```
아래와 같은 출력을 기대할 것이다. 이것이 eager한 연산이다. <br> 
하지만 실제로는 아래와 같이 나와버린다..
![loop fusion 1](https://user-images.githubusercontent.com/71186266/195332635-a5a6db27-3922-4ab0-8c0c-e636ef0449a4.png)


이게 뭘까.. <br> 
아아.. 이것은 **루프 퓨전이라는 것이다..** <br>
예시로 보인 스트림을 for문으로 나타내면 아래와 같은 동작을 해버린다..

```java
for (Data data : datas) { 
  System.out.println(data); // 첫 번째 peek
  System.out.println(data); // 두 번째 peek
  System.out.println(data); // forEach
}
```
이렇게 루프를 엮어주는 루프 퓨전이 일어나면, 자료구조에서 원소들에 접근하는 횟수가 확 줄어든다! <br> eager한 연산으로는 분명 9번의 원소 접근이 필요한 일을 단 3번으로 줄인 것. 거대한 자료구조일 수록, 접근 횟수는 더 더욱 줄어든다. 참 신기하다! <br> <br> 이러한 루프퓨전이 항상 일어나는 것은 아니다. 중간 처리 결과가 필요한 경우에는 루프퓨전이 일어나지 않게 된다. <br> 그것이 무슨 말인고 하니, `sort`를 생각해보자. 정렬 연산은 분명히 모든 원소를 가지고 있어야 가능하다! 아래와 같은 예시를 보자. 
```java
Stream.of(new Data(1), new Data(20), new Data(300))
    .peek(System.out::println)
    .peek(System.out::println)
    .sorted(Comparator.comparing(Data::getValue))
    .peek(System.out::println)
    .peek(System.out::println)
    .forEach(System.out::println);
```
- value를 확인하는 getValue를 Data에 추가로 정의해줬다.
- sorted는 값을 꺼내어 비교해준다.

위와 같은 예시가 있을 때, 2번째 peek까지는 루프 퓨전이 일어난다. 그 결과를 한대 모아 sorted해준 다음, 그 아래의 peek과 forEach에서는 루프 퓨전이 다시 일어나는 것이다. <br>

## 2.5.2 스트림 쇼트 서킷
쇼트 서킷은 우리가 조건문에서 많이 접해봤을 것이다. 전류가 흐르는 서킷에 쇼트를 걸 듯, 연산을 중간에 끊어주는 행위를 말 한다. <br>
이미 알겠지만, `if(A == 1 && B == 2 && C == 3)`이 있을 떄, A가 1이 아니라면, 그 뒤는 볼 필요 없기 때문에 연산이 진행되지 않는다. 이것이 쇼트 서킷이다. <br> <br>

이와 같은 행위가 스트림에서도 `limit()`연산을 통해 지원된다. 스트림은 빅 데이터를 다루기 위해 도입되었다. 그리고 무한한 원소를 갖는 무한 스트림을 이용할 때도 더러 있다. 따라서 이런 쇼트 서킷 연산은 꼭 필요했다. 예를 들어 배열 중 가장 큰 수 5개만 정렬하고 싶다고 가정하자.

```java
Stream.generate(() -> new RandomInt())
    .limit(100) 
    .sorted(Comparator.comparingInt(Data::getValue)) 
    .collect(Collectors.toList());
```
위의 코드는 랜덤 Int 무한으로 발생하는 무한 스트림을 만든 다음 100개만을 받아서 끊어준 다음 정렬한다. 무한하게 int가 만들어지지만 `limit()`을 통해 필요한 만큼만 자를 수 있다. 이것이 스트림에서 지원하는 최적화 도구 **쇼트 서킷이다.** <br> 가장 간단한 예를 보인거라 별로 와닿지 않을 수 있다. <br> 

`limit()`은 순서에 유의해야한다. 위의 순서가 바뀐다면?
```java
Stream.generate(() -> new RandomInt())
    .sorted(Comparator.comparingInt(Data::getValue)) 
    .limit(100) 
    .collect(Collectors.toList());
```
sorted는 루프 퓨전이 일어나지 않기 때문에, 연산은 영원히 끝나지 않는다.. 

## 2.6 병렬 스트림!
여러 장점들이 있지만, 가장 처음 언급했듯 스트림은 빅 데이터를 위해 만들어졌고, 병렬처리를 쉽게 할 수 있게 해준다. <br>

자바에서 병렬처리에 사용하는 fork&join 프레임워크를 내부적으로 이용하여, 연산을 병렬로 수행해준다. <br> **어떻게? `parallel()` 하나만 붙여주면 끝!**

```java
int sum = arrayStream.parallel()
                  .mapToInt(s -> s.length())
                  .sum();
```
`parallel()`은 새로운 스트림을 생성하는 것이 아니라, 스트림의 속성을 변경해주면서 쉽게 병렬화를 지원한다. 기본적으로 스트림은 스트림이 아니고, 병렬화를 취소해주고 싶으면 `sequential()`을 붙여주면 된다. 


# 2.7 스트림을 위한 람다! 선언적 프로그래밍!

결국 <br> 
**데이터!**를 제대로 다루기 위한 <br>
**컬렉션!**을 효율적으로 사용하기 위한 <br>
**스트림!**을 위한 <br> 
함수형 **프로그래밍!**을 위한 <br> 
것이 **람다!**임.

<br>

그럼 스트림, 람다를 사용하면 뭐가 좋을까? <br> 정말 여러가지 장점을 보았지만, **함수형 프로그래밍의 장점인 선언적 프로그래밍을 활용할 수 있게 된다!** <br> **How가 아닌 What만을 지정한다!** <br>

`무엇을 어떻게 해주세요~`가 아닌, `무엇을 줘!`가 됩니다. <br> 
술집 출입 제한 코드의 리펙토링 과정을 봅시다.
```java
// 기존 방식
for (int i = 0; i < ages.length; i++) {
  if (ages[i] < 20) {
    System.out.format("Age %d! Can't enter\n", ages[i]);
  }
}
```
향상된 for 문
```java
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

보면 알 수 있다 싶이, 마치 SQL문 처럼 **무엇을 원하는지만 요구했다!** 
`기존의 ages 배열을 하나하나 순회하면서, 그 value가 20 미만일 경우 뭐를 출력해주세요.. 보다 직관적이고 깔끔하다` <br>

선언적 프로그래밍 요소 덕분에 의사소통 내용 자체가! 그대로 코드로 구현되었다!


### Reference
- [bugoverdose님 블로그](https://bugoverdose.github.io/development/stream-lazy-evaluation/)
- 자바의 정석 2권 <남궁민 저>
- <!-- https://developer-joe.tistory.com/197 -->

