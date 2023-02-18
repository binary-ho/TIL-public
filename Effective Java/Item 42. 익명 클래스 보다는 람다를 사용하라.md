# Item 42. 익명 클래스 보다는 람다를 사용하라
자바에서 함수 타입을 표현할 때는 주로 익명 클래스를 이용한다. <br>
함수의 타입 표현을 위한 인스턴스를 함수 객체라고 부르는데, <br>
예전엔 주로 인터페이스를 통해 만들었으나, 요새는 익명 클래스를 통해 만든다. <br> 

```java
Collections.sort(words, new Comparator<String>() {
  public int compare(String s1, String s2) {
    return Integer.compare(s1.length(), s2.length());
  }
});
```
위 코드는 문자열을 길이순으로 정렬하는 코드이다. <br>
정렬을 위한 비교 함수로 익명 클래스를 사용했다. <br>

익명 클래스는 [전략 패턴](https://github.com/binary-ho/TIL-public/blob/main/gdsc/backend/%EC%8A%A4%ED%94%84%EB%A7%81%20%EC%9E%85%EB%AC%B8%EC%9D%84%20%EC%9C%84%ED%95%9C%20%EC%9E%90%EB%B0%94%20%EA%B0%9D%EC%B2%B4%20%EC%A7%80%ED%96%A5%EC%9D%98%20%EC%9B%90%EB%A6%AC%EC%99%80%20%EC%9D%B4%ED%95%B4/Strategy%20Pattern.md)이나 [템플릭 콜백 패턴](https://github.com/binary-ho/TIL-public/blob/main/gdsc/backend/Template%20Callback%20Pattern%20in%20Spring.md)에서 사용하기 좋았다. <br> (내가 쓴 글들이니 참고바란다.) <br>

하지만 위와 같은 코드는 너무 길기 때문에, 함수형 프로그래밍에 적합하지 않다. <br>
그래서 자바 8에 와서야 다시 추상 메서드 하나짜리 인터페이스가 인정 받게 되었다. <br>
자바 8에서 이런 함수형 인터페이스를 람다식을 사용해 만들 수 있게 되었다. <br>


## Hello Lambda
람다는 함수나 익명 클래스와 개념은 비슷하지만, 코드는 훨씬 간결하다. <br>
앞서 보인 코드를 아래와 같이 간결하게 바꿀 수가 있다.
```java
Collections.sort(word,
  (s1, s2) -> Integer.compare(s1.length(), s2.length()));
```
여기서 람다의 타입은 Comparator<String>, 
매개변수 s1, s2의 타입은 String, 그리고 반환값의 타입은 int이다. <br>
하지만 그 어디에도 적혀 있지 않다. <br>
컴파일러가 문맥을 통해 타입을 추론한 것이다. <br>
정말 똑똑하다. 하지만 가끔 직접 타입을 결정하지 못할 때는, <br>
프로그래머가 컴파일러에게 속삭여줄 필요는 있다. <br>
타입을 명시해야 확실히 코드가 더 명확해 질 때를 제외하고는 매개변수 타입을 생략하라. <br>
컴파일러가 오류를 내뿜으며 도와달라 요청할 때만 타입을 명시하면 된다. <br>

## Lambda Magic
람다를 통해 복잡한 코드를 간략하게 바꿔보겠다. <br>
아래는 Enum 타입 Operation의 예시이다. <br>
```java
public enum Operation {
    PLUS("+") {
        public double apply(double x, double y) { return x + y; }
    },
    MINUS("-") {
        public double apply(double x, double y) { return x - y; }
    },
    TIMES("*") {
        public double apply(double x, double y) { return x * y; }
    },
    DIVIDE("/") {
        public double apply(double x, double y) { return x / y; }
    };

    private final String symbol;

    Operation(String symbol) { this.symbol = symbol; }

    public abstract double apply(double x, double y);
}
```

apply 메서드들의 동작은 상수마다 (연산자 마다) 다른데, 이를 클래스 몸체를 이용해 어렵게 구현하고 있다. <br>

이제 람다를 적용해보자.
```java
public enum Operation {
    PLUS  ("+", (x, y) -> x + y),
    MINUS ("-", (x, y) -> x - y),
    TIMES ("*", (x, y) -> x * y),
    DIVIDE("/", (x, y) -> x / y);

    private final String symbol;
    private final DoubleBinaryOperator op;

    Operation(String symbol, DoubleBinaryOperator op) {
        this.symbol = symbol;
        this.op = op;
    }

    public double apply(double x, double y) {
        return op.applyAsDouble(x, y);
    }

}
```
아름답다. <Br>
상수별로 더럽게 클래스 몸체를 구현하지 않고, 인스턴스 필드를 두었다. <br>

## 주의할 점과 팁

람다의 아름다운 맛을 보았다고 해서 전부 람다화 시켜버리면 안 된다. <br>
람다는 컴파일러만 타입을 추론 시키는게 아니고, 읽는 사람도 내용을 추론해야 한다. <br> 

이름도 없고, 문서화도 안 되어 있으며, 동작이 명확하지 않아 보인다. <Br>
람다는 한 줄일때 쓰는 것이 좋고, 길어야 3줄 안에 끝나는 것이 좋다. <br> <br>
또, 람다를 적용하지 못 하는 곳들도 있다. <br>
1. 추상 클래스의 인스턴스를 만들 때 
2. 추상 메서드가 여러 개인 인터페이스의 인스턴스를 만들 때
익명 클래스를 써야 한다 <br> <br>
람다는 자신도 참조할 수 없어서 특이하게도 this를 호출하면 바깥 인스턴스를 가리킨다. <br>
그리고 직렬화 형태가 가상머신 별로 다를 수가 있어서, 직렬화하지 말아야 한다. <br>

추가적인 팁은 내가 쓴 글을 첨부할테니, 읽으면 좋을것 같다. <br>
[람다와 인터페이스에 관한 글이다. 왜 나왔고, 어떻게 쓰는 건지 구체적으로 알아보자.](https://github.com/binary-ho/TIL-public/blob/main/gdsc/backend/%EC%8A%A4%ED%94%84%EB%A7%81%20%EC%9E%85%EB%AC%B8%EC%9D%84%20%EC%9C%84%ED%95%9C%20%EC%9E%90%EB%B0%94%20%EA%B0%9D%EC%B2%B4%20%EC%A7%80%ED%96%A5%EC%9D%98%20%EC%9B%90%EB%A6%AC%EC%99%80%20%EC%9D%B4%ED%95%B4/B.%20Lambda%20and%20Interface%20in%20Java%208.md)


## Reference
- Effective Java <조슈아 블로크>
