# Item 9. try-finally 보다는 try-with-resources를 사용하라

자바 라이브러리 자원들 중에는 `InputStream`, `OutputStream`, `java.sql.Connection`과 같이 `close` 메서드를 호출해 직접 닫아줘야 하는 자원이 많다! <br>
자원 닫기는 놓치기 쉽지만, 그 댓가는 쥐도 새도 모르게 성능을 떨어뜨리는 문제로 이어질 수 있다. <br>
이를 위한 기존의 finalizer는 예측할 수 없고, 위험할 수도 있어 사용하지 않는 편이 낫다. <br>
이에, `try-finally`가 자주 쓰였으나, 이또한 믿을만한 존재는 아니다. `try-with-resource`를 써라!


## 1. `try-finally`의 문제점
다음과 같은 코드를 보자.
```java
  static String firstLineOfFile(String path) throws IOException {
      BufferedReader br = new BufferedReader(new FileReader(path));
      try {
          return br.readLine();
      } finally {
          br.close();
      }
  }
```
`try-finally`의 문제는 try 구간 외에도 `br.close()`가 있는 **finally 구간에서도 에러가 발생할 수 있다는 점이다.**  <Br>
만약에 기기의 물리적 오류가 생긴 상황을 생각해보자. `br.readLine()`에서 에러가 발생할 것이다. **그리고 프로그래머가 확인하고 싶었던 것은 아마도 이쪽 try 쪽의 에러일 것이다.** <Br>

문제는 finally에서도 에러가 발생할 수 있다는 점인데, 기기의 물리적 오류가 발생한 만큼 **`br.close()` 부분에서도 에러가 발생할 수 있다!** <br>

이런 경우 **두번째 오류가 첫번째 오류를 집어삼켜 버려, 스택 추적 내역에 첫번째 오류는 남지 않게 된다!** <br>
완전히 망한 것이다. 내가 보고 싶은 오류를 보지 못하는 상황에 이른 것이다. 

## 2. `try-with-resource`!
위의 코드에 `try-with-resource`를 적용해보자.
```java
  static String firstLineOfFile(String path) throws IOException {
      try (BufferedReader br = new BufferedReader(
              new FileReader(path))) {
          return br.readLine();
      }
  }
```
읽기 쉬울 뿐만 아니라, 문제를 진단하기에도 아주 수월해 졌다. <br>
이제는 기존처럼 두 군데에서 모두 에러가 발생하는 경우 **주 관심사인 try에 대한 예외가 기록되고, 나머지는 숨겨진다!** <br>
그렇다고, close시의 에러를 아주 버리기 보다는, 숨겨졌다는 의미의 `suppressed` 꼬리표만 달고, 출력해준다. <br>
또한 자바 7의 `Throwable`의 `getSuppressed` 메서드를 이용하면 프로그램 코드에서 가져올 수도 있다. <br>

이 놀라운 `try-with-resource`는 **단지 `AutoCloseable`을 구현하면 사용 가능하다!** AutoCloseable은 close 메서드 하나만 덩그러니 정의한 void 반환 인터페이스다! <br> 
자바의 여러 라이브러리들은 이미 이를 구현하거나 확정해 두었다. <br>

여러모로 너무 좋다! 이 밖에도 다수의 예외를 처리할 때에도, 닫아야 하는 자원을 여러개 사용할 때에도 좋다. <br>

### 다수의 예외를 처리할 때
`try-with-resource`에서는 try문을 중첩할 필요 없이 **catch문을 통해 여러 예외를 처리해줄 수도 있다.**
```java
  static String firstLineOfFile(String path, String defaultVal) {
      try (BufferedReader br = new BufferedReader(
              new FileReader(path))) {
          return br.readLine();
      } catch (IOException e) {
          return defaultVal;
      }
  }
```
위와 같이 코드를 짜주면 되는데, catch문을 통해 파일을 열거나 데이터를 읽지 못했을 때 예외를 던지는 대신에 기본값 `defaultVal`를 반환하도록 짜준 코드이다! <Br>

정말 편리하면서도 강력하다.

### 닫아야 하는 자원을 여러개 사용할 때
```java
  static void copy(String src, String dst) throws IOException {
      InputStream in = new FileInputStream(src);
      try {
          OutputStream out = new FileOutputStream(dst);
          try {
              byte[] buf = new byte[BUFFER_SIZE];
              int n;
              while ((n = in.read(buf)) >= 0)
                  out.write(buf, 0, n);
          } finally {
              out.close();
          }
      } finally {
          in.close();
      }
  }
```
다음과 같이 close가 필요한 여러 자원을 사용하는 경우를 살펴보자. <Br>
중첩된 문법으로 머리가 어지럽다... 물론 finally에서도 에러가 터지는 문제가 있지만, 일단은 읽고 짜기가 너무 벅차다. <Br>

하지만 `try-with-resource`가 나선다면?

```java
  static void copy(String src, String dst) throws IOException {
      try (InputStream   in = new FileInputStream(src);
            OutputStream out = new FileOutputStream(dst)) {
          byte[] buf = new byte[BUFFER_SIZE];
          int n;
          while ((n = in.read(buf)) >= 0)
              out.write(buf, 0, n);
      }
  }
```
너무 아름답다.. <Br>
다수의 자원을 사용할 때도, 이렇게 우아하게 모두 닫아줄 수 있다. <br>

꼭 회수해야 하는 자원을 다룰 때에는 `try-finally` 말고 `try-with-resource`를 사용하자. 코드는 더 짧아지고, 더 분명해지며, 만들어 지는 예외 정보 또한 훨씬 유용하다! <Br>
예외는 없다! 닫아야 하는 자원을 사용하는 상황이라면 `try-with-resource`를 써라

## Reference
- Effective Java <조슈아 블로크>





