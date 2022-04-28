Algorithm with Java
==

항상 C++만 이용하여 문제를 푸느라 Java로 알고리즘 문제를 푸는 법에는 매우 약하다.    
자바를 이용한 알고리즘 풀이에 익숙해지기 위해 만든 문서이다. 기본적인 문법들 중 PS와 관련 있는 요소들만 정리해보겠다.


### 1. 배열의 원소 String으로 출력하기
```Java
int[] arr = {1, 2, 3, 4, 5};
System.out.println(Arrays.toString(arr));
```
`Arrays.toString(arr)`를 이용한다. 그냥 toString()을 이용하면 배열의 주소 값을 출력하게 된다.
