# Item 49. 매개변수가 유효한지 검사하라

메서드를 잘 만들었다면, 대부분의 에러는 잘못된 매개변수에서 올 가능성이 높다. <br>
예외는 빨리 찾아낼 수록 좋다. <br>
애초에 잘못된 값이 가공되고, 여기 저기 쓰이면서 점점 더 정체를 알 수 없는 쓰레기가 만들어진다. <br>
C라는 것이 잘못 되었대서 열심히 봤더니, B가 원인이였고, 실은 A가 원인이였다.. <br>
나도 자주 겪은 일이다. <br>
이런 식으로 추적해 나가는 일은 생각보다 괴롭고 어려운 일이다. <br>
그러기에 잘못된 값을 쓰고 있다면 최대한 빨리 알아야 한다. <br>

최고로 빠르게 찾아내는 방법은 물론 컴파일 에러다. <br>
가장 아름다운 에러지만, 매개변수로 컴파일 에러를 못 낼것 같다면, <Br>
몸체가 시작하기 전에 감지해 내는 것이 좋다 <Br>
그래서 권하길, **pulbic과 protected 메서드의 제약은 문서화 해야 하며, 몸체가 시작되기 전에 검사를 수행해야 한다. <Br> 또한 필히 발생하는 예외까지 문서화 해야 한다.** <br> <br>

```java
/**
* (현재 값 mod m) 값을 반환한다.
* 이 메서드는 항상 음이 아닌 BigInteger를 반환한다는 점에서
* remainder 메서드와 다르다.
* @param m 계수 (양수여야 한다.)
* @return 현재 값 mod m
* @throws ArithmeticException m이 0보다 작거나 같으면 발생한다.
*/
public BigInteger mod(BigInteger m) {
  if (m.signum() <= 0) {
    throw new ArithmeticException("계수 (m)는 양수여야 합니다. " + m); 
  }
}
```

위의 코드는 책에서 제시해준 best practice인것 같다. <br>
오며가며 위와 같은 형태를 몇번 봤던것 같은데, JavaDoc 형식의 tag들이라고 한다. <br>
JavaDoc 형식의 주석 작성에 대해 간단히만 알아보자.

## 1. JavaDoc
JavaDoc은 문서화를 위한 주석이다. <br>
뭐어?? 문서화를 위한 주석???????? <Br>
이라며 화낼 Java 큰 형님들의 분노가 벌써 눈에 선하다.. <br>
좋은 메서드는 그 자체로 바로 이해가 가야 한다. <Br>
바로 이해하기 어렵다면, 다시 명명하거나, 너무 많은 책임 때문일 수 있으므로 분리를 고려해야 한다는 숭고한 가르침을 잊고 주석을 달자는 것이 아니다. <br>
정말 필요한 곳에 달기 위해서 알아보자는 것이다. <Br>

주석을 다는 것은 어딘가 잘못되었다는 가르침은 자바 사용자들에게 엄청난 압박을 준다. <br>
하지만 현실은 당장 몇 개월 전에 본인이 짠 코드도 이해하기 힘든 경우가 더러 있다 <br>
하물며 남이 쓴 코드는 어떤가.. <br>
내가 참고한 블로그에선 여러 프로젝트의 레거시 코드들 중 어려운 코드를 발견하는 족족 JavaDoc을 작성했다고 한다. <Br>
그랬더니 반응도 좋았고, 대부분의 메서드를 3초 안에 파악할 수 있엇다고 한다. <br>
블로그 글의 필자는 수초 안에 간단히 파악할 수 있느냐를 기준으로 삼아 Doc을 작성한 것 같다 <Br>
내 눈엔 그리 나쁘지 않게 보였고, 배워두고 필요하면 사용할 가치가 충분히 있다고 느꼈다. <br>
그 쓰임과 활용을 한번 살펴보자. 

### 형식
**주석은 위에서 보인 예시와 같이 `구간 주석 -> /**/ 형태`로 달아야 한다.** <Br>

![badcomment](https://user-images.githubusercontent.com/71186266/221712407-b19e9bc0-8f2f-4b81-8435-19a62f9fde37.png)


<br>
위의 코드는 슬래쉬 두개 주석을 사용했다. 메서드에 마우스를 올린 경우 아무런 문구도 뜨지 않는다. <Br> 


![good commetn](https://user-images.githubusercontent.com/71186266/221712409-369b00aa-65dd-498f-9193-a268deae3cc0.png)

위와 같이 구간 주석을 사용하니, <br>
메서드에 마우스만 올려도 설명이 뜬다. <br>
이렇게 작성하면 메서드를 쓰는 사람이 도큐먼트까지 타고 들어가는 수고를 덜 수 있다. <Br>

그리고 다들 알겠지만, 대부분의 java 메서드에는 이런 주석이 기재되어 있다. <br>

이해하기 힘든 코드에선 충분히 도입을 고려해볼만 하다. 

### 잘 쓰는 법
1. **무엇을 리턴하는지는 명확해야 한다.** <br> 위와 같이 `@result`를 쓰던 말던 사실 상관 없다. <Br> 다만, **무엇을 받아 무엇을 반환하는가** 는 메서드를 쓰는 사람의 주 관심사이기 때문에 들어가 있으면 좋다. <br> 특히 `무엇을 리턴하는가?`는 항상 적혀 있는 것을 권한다. 
2. **가독성이 가장 중요하다. 애너테이션을 활용하자.** <br> 위의 사진과 같이 `@param`, `@result` 등의 파라미터들은 document 작성을 돕는다. <br> 사진과 같이 따로 분류되어 보이므로, 읽는 사람 입장에서 가독성이 너무 좋다. <br>

더욱 자세한 내용은 reference에 기재된 블로그를 참고하자. 필자의 경험과 함께 사용법과 좋은 예시를 기재한 너무나도 잘 쓰인 글이다. -> ([내가 Javadoc 작성을 선호하는 이유](https://johngrib.github.io/wiki/java/javadoc/#%EB%82%B4%EA%B0%80-javadoc-%EC%9E%91%EC%84%B1%EC%9D%84-%EC%84%A0%ED%98%B8%ED%95%98%EB%8A%94-%EC%9D%B4%EC%9C%A0)) <br> <br>

## 2. Java Object 검사 메서드들

Java Object의 검사 메서드들을 적극 활용해보자. <Br>
자바 7에 추가된 `requireNonNull`이나, 자바 9에서 추가된 `checkFromIndexSize`, `checkFromToIndex`, `checkIndex` 등을 사용하는 것이 좋다. <Br>

사용 예시를 보자.

```java
    public static void requireNonNullMethod(Integer input) {
        int value = Objects.requireNonNull(input, "hello i'm null");
        System.out.println(value);
    }
```
`Objects.requireNonNull` 검사는 T를 받아 T를 반환한다. <Br>
즉, 입력 값을 null 체크 한 뒤, null이 아니라면 그대로 돌려주는 방식이다. <Br>
null을 검사하려는 값과 두번째 파라미터로 message를 넣었는데 이를 통해 내가 원하는 메시지를 출력하게 할 수 있다. <Br>
위와 같은 메서드에 null을 넣어 보자. <br>
```java
Exception in thread "main" java.lang.NullPointerException: hello i'm null
	at java.base/java.util.Objects.requireNonNull(Objects.java:233)
	at com.company.Main.requireNonNullMethod(Main.java:14)
	at com.company.Main.main(Main.java:9)
```
message를 넣지 않으면 원래는 아래와 같은 에러 메시지가 나와야 한다. <br>

```java
Exception in thread "main" java.lang.NullPointerException
	at java.base/java.util.Objects.requireNonNull(Objects.java:208)
	at com.company.Main.requireNonNullMethod(Main.java:15)
	at com.company.Main.main(Main.java:9)
```

확실히 message가 있는 편이 더 명확하게 어디가 문제인지 빠르게 파악할 수 있다. <Br> <Br>

다음은 `checkFromIndexSize`를 사용해본 예시이다.

```java
    public static void checkIndexSizeMethod(int fromIndex, int size, List<Integer> list) {
        int fromIndexToo = Objects.checkFromIndexSize(fromIndex, size, list.size());
        System.out.println(fromIndexToo);
    }
```
만약 해당 fromIndex로 부터, 사이즈까지 sublist를 만들 수 있다면 fromIndex값을 반환 하고, <br>
불가능한 경우 예외를 출력한다.

```java
Exception in thread "main" java.lang.IndexOutOfBoundsException: Range [3, 3 + 5) out of bounds for length 5
	at java.base/jdk.internal.util.Preconditions.outOfBounds(Preconditions.java:64)
	at java.base/jdk.internal.util.Preconditions.outOfBoundsCheckFromIndexSize(Preconditions.java:82)
	at java.base/jdk.internal.util.Preconditions.checkFromIndexSize(Preconditions.java:361)
	at java.base/java.util.Objects.checkFromIndexSize(Objects.java:411)
	at com.company.Main.checkIndexSizeMethod(Main.java:14)
	at com.company.Main.main(Main.java:10)
```

명확하게 문제가 되는 지점을 찝어줘서 좋지만, <br>
사실 코드가 단순하다고는 못 느끼겠다. <Br>
인덱스만 확인할 때는 아래의 `checkIndex`가 좋아 보인다.

```java
  public static void checkIndexMethod(int index, List<Integer> list) {
      int safeIndex = Objects.checkIndex(index, list.size());
      int value = list.get(safeIndex);
      System.out.println(value);
  }
```

<br>

안전할 경우 반환값으로 인덱스를 반환해준다 <Br>
위와 같이 한번 거르는 용도로 보인다. <Br>
그냥 바로 `get` 안에 넣어서 사용하는 방식으로 써도 좋을것 같다. <br>
틀린 경우 `IndexOutOfBoundsException`를 반환한다.

```java
Exception in thread "main" java.lang.IndexOutOfBoundsException: Index 5 out of bounds for length 5
	at java.base/jdk.internal.util.Preconditions.outOfBounds(Preconditions.java:64)
	at java.base/jdk.internal.util.Preconditions.outOfBoundsCheckIndex(Preconditions.java:70)
	at java.base/jdk.internal.util.Preconditions.checkIndex(Preconditions.java:266)
	at java.base/java.util.Objects.checkIndex(Objects.java:359)
	at com.company.Main.checkIndexMethod(Main.java:19)
	at com.company.Main.main(Main.java:10)
```

<Br>

## 3. public이 아니라면 assert 문법을 활용하라
public이 아니라면, assert 문법으로 매개변수 유효성을 검증하는 것도 좋다. <Br>
쓰는 법은 `내 말이 무조건 맞아` 식이다.
```java
	public static void assertNotNullMethod(Integer input) {
		assert input != null;
		System.out.println(input);
	}
```
위와 같이 사용하면 된다. <br>
그러면 아래와 같은 `AssertionError` 에러를 만나볼 수 있다. <Br>
![assert arror](https://user-images.githubusercontent.com/71186266/221721209-bcd9f375-d002-48e9-ac35-c8d16b2dd6db.png)

<br>

저는 그냥 통과하는데요? ㅠㅠㅠ <br>
라고 하는 사람들을 위해 친절히 첨부한다. <br>
그냥 통과하는 이유는 VM option 설정을 안 해주어서 그렇다.


![vm option](https://user-images.githubusercontent.com/71186266/221721214-aa475b11-ee4b-406d-8682-4547da8873a0.png)

위의 1번을 누르면 `Edit Configuration`이 있다. <br>
그걸 누른 다음 2번의 VM Option에서 `-ea`를 추가 해주면 assert가 의도대로 작동한다. <br>
꿀팁이다. <br> <br>

가독성이 좋고, 조건문이 필요 없으며, `-ea`를 사용하지 않을 시 런타임에 성능 저하가 없다고 한다. <br>
사실 테스트 해보려면 `-ea`를 붙여야 해서 뭐가 그리 나은지는 잘 모르겠다.

## 4. 특히 생성자를 주의해라
생성자는 특히 주의해야 한다. <Br>
왜냐하면 **나중에 쓰려고 필드 값을 저장해 두는 대표적인 예시이기 때문이다.** <Br>
위에서 언급한, 발생 지점을 찾기 힘든 케이스 이므로, <BR>
**생성할 때 유효성 검사를 해라. 불변식을 어기는 객체 생성을 막아라.**

## Reference
- Effective Java <조슈아 블로크>
- [내가 Javadoc 작성을 선호하는 이유](https://johngrib.github.io/wiki/java/javadoc/#%EB%82%B4%EA%B0%80-javadoc-%EC%9E%91%EC%84%B1%EC%9D%84-%EC%84%A0%ED%98%B8%ED%95%98%EB%8A%94-%EC%9D%B4%EC%9C%A0)
