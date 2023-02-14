# Item 36. 비트 필드 대신 EnumSet을 사용하라
열거 값들이 집합으로 쓰일 때가 있다. <br>
예를 들어, 글씨를 쓸 때 I have a **볼드체,** i have a *이테릭,* I have a ~~취소선~~ <br>
Ah! ***~~볼드이테릭취소선~~*** <br>
이런 식으로 여러 효과를 한 문장에 넣을 수가 있다. <br>

이렇게 열거 값들이 집합으로 사용되는 경우, 아래와 같이 비트 시프트를 통해 한 칸씩 할당하여 사용하곤 했다.

```java
public class Text {
  public static final int STYLE_BOLD = 1 << 0;
  public static final int STYLE_ITALIC = 1 << 1;
  public static final int STYLE_UNDERLINE = 1 << 2;
  public static final int STYLE_STRICKETHROUGH = 1 << 3;

  public void applyStyles(int styles) {
    /* 여기서 styles 값은
    여러개의 STYLE 상수들을 OR한 결과이다. */
    ...
  }
}
```
예를 들어 볼드체와 이테릭을 동시에 적용하면 `styles = STYLE_BOLDE | STYLE_ITALIC = 3`이 되는 방식이다 <br>

손 아프게 열심히 설명했지만, 이런 styles와 같은 집합을 **비트 필드** 라고 부르고, 구닥다리 기법이라고 한다. <br>

이런 방식은 그저 정수를 열거한 상수의 단점을 그대로 안고 있다. <br> 
1. 숫자 그대로 사용하는 것이라 컴파일시 값이 클라이언트 파일에 그대로 새겨진다. <br> -> 상수 값이 바뀌면 다시 컴파일 해야 한다. 
2. 상수 그룹을 순회할 방법이 마땅하지 않다. 갯수를 파악하는 것 부터 어렵다.
3. 값을 하드코딩 해야한다.
4. 그냥 '숫자' 여서 의미 파악이 어렵다.

예를 들어 위의 글씨채 예시에서 `5` -> 무슨 의미인가? `BOLD | UNDERLINE`이다. `6`은? 머릿 속에서 OR 값을 생각해야한다. 숫자가 커지면 더 문제다. 100101010110001 이면 어쩔 것인가? <br>
숫자만 보고 의미를 파악하기 쉽지 않다는 것이다. <Br>
그리고 필드 크기를 미리 예측해야 한다. <br>
만약에.. 만약에 상수들 갯수가 31개를 넘긴다면? 비트 필드는 int가 아닌 long이 될 것이다! <br>

이걸 미리 예측하고 사용해야 하고, 열거할 상수가 늘어나게 되면 뜯어 고쳐야 할 수도 있는 것이다. <br>


## EnumSet
열거형식으로 쓰려니 너무 단점이 많다 <br>
그냥 EnumSet을 써라. <br>
EnumSet 클래스는 열거 타입 상수의 값으로 구성된 집합을 효과적으로 표현해준다. <br>
Set 인터페이스를 완벽히 구현했으며, 타입 안전하고, 다른 어떤 Set 구현체와도 함께 사용할 수 있다. <br>
**그러면서도 내부 구현은 비트 벡터로 되어 있어, 비트 필드에 비견되는 성능을 갖고 있다.** Set하나를 보통 long 변수 하나로 표현한다. <br>
비트 필드의 장점은 취하고, 단점은 대부분 보완한 아주 좋은 방법이다. <br>

앞의 예시를 고쳐보자
```java
public class Text {
  pulbic enum Style { BOLD, ITALIC, UNDERLINE, STRIKETHROUGH }

  public void applyStyles(Set<Style> styles) {
    /* 어떤 Set을 넘겨도 좋다!! */
    
    ...

  }
}
```

이뻐 죽겠다! <br>
위 `applyStyles` 메서드에 EnumSet 인스턴스를 건네어 보자 
```java
text.applyStyles(EnumSet.of(Style.BOLD, Style.ITALIC));
```

마음이 아주 편안하지 않는가? <br>

**앞으로 상수들을 열거하여 집합처럼 사용해야 할 때는 비트 필드를 쓰지 말고 그냥 EnumSet을 쓰면 된다.**

## Reference
- Effective Java <조슈아 블로크>
