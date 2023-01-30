# Item 25. 톱레벨 클래스는 한 파일에 하나만 담으라

한 파일에 클래스를 하나만 두라는 이야기다. (중첩 클래스 제외) <Br>
소스 파일 하나에 톱레벨 클래스를 여러개 선언하더라도 컴파일상 문제는 없다고 한다. <br>
하지만, 
이런 경우에 단순히 컴파일러에 소스 파일을 건네는 순서에 따라, 클래스 중복 정의를 감지할 수도, 못할 수도 있는 어처구니 없는 상황이 발생할 수도 있다. <br>

**소스 파일 건내는 순서에 따라 동작이 달라진다.** <br>

### 예시

예를 들어 이런 상황이 발생할 수 있다.
```java
public class Main {
  public static void main(String[] args) {
    System.out.println(A.NAME + B.NAME);
  }
}
```

위의 A, B 클래스가 `A.java`라는 파일 하나에 정의되어 있다고 생각해보자.

```java
// A.java 파일
class A {
  static final String NAME = "진호";
}

class B {
  static final String NAME = "짱";
}
```

main을 실행하면 `진호짱`을 출력한다. <Br>
그리고 우연....히 `B.java` 파일을 만들었는데 정말 정말 우연히 아래와 같이 생겼다.
```java
// B.java 파일
class A {
  static final String NAME = "진짜 바보는";
}

class B {
  static final String NAME = "이진호야";
}
```

운이 좋아서 `javac Main.java B.java` 명령어로 컴파일 한다면, `Main`의 `println`의 괄호 안에서 `A.NAME` 먼저 만나기 때문에, `A.java`를 찾아본다. <br>
그 덕분에 컴파일러는 클래스 중복 정의를 알아차리게 될 것이다! <br> <br>
**하지만 재수가 없어서 `javac Main.java`나 `javac Main.java A.java` 명령어로 컴파일 한다면, `진호짱`을 출력한다.** <br>
**그리고 `javac B.java Main.java`로 컴파일 하면 `진짜 바보는 이진호야`를 출력해버린다!** <br>
**컴파일 할때 어느 소스 파일을 먼저 건내느냐에 따라 동작이 달라졌다!!** <br> <br>

이런 문제의 해결책은 아주 간단하다. **단순히 하나의 파일에 하나의 톱레밸 클래스를 두면 된다.** <br>
굳이 여러개를 구도 싶다면 정적 맴버 클래스 등의 이너 클래스 형태가 되어야 한다. <br>


굳이 이렇게 만들 필요도 없고, 효용도 없다. 개성을 발휘하는 방법으로 한 파일에 톱레벨 클래스를 여럿 만드는 방법은 좋은 방법이 아니다.

## Reference
- Effective Java <조슈아 블로크>
