Algorithm with Java
==

항상 C++만 이용하여 PS를 하느라 Java를 이용한 알고리즘 문제를 풀이에는 매우 약하다.    
이 문서는 자바를 이용한 알고리즘 풀이에 익숙해지기 위해 만들었다. 기본적인 문법들 중 PS와 관련 있는 요소들만 아주 기본적인 것들까지 전부 정리해보겠다.


### 1. 배열의 원소 String으로 출력하기
```Java
int[] arr = {1, 2, 3, 4, 5};
System.out.println(Arrays.toString(arr));
```
`Arrays.toString(arr)`를 이용한다. 그냥 toString()을 이용하면 배열의 주소 값을 출력하게 된다.

결과: `[1, 2, 3, 4, 5]`

### 2. String 내용을 int로 불러오기
```Java
String str = "1234";
int num = Integer.parseInt(str);
```

결과: `1234`
다른 자료형들도 동일한 방식으로 파싱이 가능하다.


### 3. 다차원 배열의 length
배열의 length는 원소의 수 이다. 다차원 배열의 length는 어떨까?
```java
int[][] arr = new int[5][3];
```
위와 같은 배열이 있을 때, `arr.length`의 값은 무었일까?
답: 5
__다차원 배열은 배열의 각 원소가 또 배열을 가지는 식이다.__ (배열의 배열)
__arr가 참조하는 배열의 원소의 수는 5이므로, `arr.length`의 결과는 5가 된다.__
당연하지만 `arr[0].length`의 결과는 3이다.

### 4. Vector는 이제 없는거지? Vector -> ArrayList
**`Vector` 대신 `ArrayList`를 써라!** `Vector는` 호환상 명목상으로 남아 있는 거고, `ArrayList`가 대체할 수 있다.    
`Vector`를 개선하기 위해 만든 것이 `ArrayList!`    다만 C++과는 달리 `vector[idx]` 와 같은 get과 set은 어렵다. get(), set() 메소드를 이용하여야 한다.
