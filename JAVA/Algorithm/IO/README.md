Input & Output (Algorithm with Java)
==

답답해서 내가 쓴다.

나 같이 Java외의 언어로 PS를 해오던 사람을 위해 PS 입출력을 위한 Java 문법들을 정리한 페이지이다. 내가 자료를 못 찾는건지 관련 자료가 거의 없거나, 있더라도 설명이 부실했다. 답답해서 내가 쓴다.

# 1. 입력 받기
입력을 받는 데에는 여러가지 방법이 있다. Consol을 이용한 방법 Scanner를 이용한 방법 BufferedReader을 이용한 방법. 등 여러가지가 있다. **우리는 그 중 BufferedReader**를 이용할 것이다. BufferedReader는 Input Stream의 버퍼로, 버퍼를 이용해서 입출력의 효율을 높일 수 있도록 해주는 역할을 한다. 그냥 스트림을 쓰는 것 보다 확연히 빠른 속도를 보인다. 자바에 도입된 순서로 따지자면, 사실 **Scanner**가 더욱 늦게 도입되었다. Scanner가 더 좋은거 아니냐? 하면 더 좋은게 맞다. 동기화를 사용하지 않고, 더 작고 가벼운 버퍼를 이용하며, 버퍼드리더는 String 밖에 받지 못 하는데 다양한 자료형을 받을 수 있다. 또한 i18n l10의 도입으로 현지화도 좋고, regular expression 덕에 "12,345"와 같은 문장도 12345로 인식해낼 수 있다. <U>**하지만 느리다**</U>.    
    
어느 정도냐면, 알고리즘 문제에서는 충분히 차이를 만들 만큼 느리다. 단지 그 하나의 이유 때문에 우리는 **BufferedReader**를 이용할 것이다. **알고리즘은 속도가 생명이니까.**    

## 1.1 결론은 BufferedReader + InputStreamReader
결론은 **BufferedReader** 쓰면 된다는 것이데 이렇게 쓴다.
```Java
BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
br.readLine();
```

하나씩 설명하겠다.
- BufferedReader: 버퍼를 이용해 입출력의 효율을 높인다.
- InputStreamReader: 바이트 기반 스트림을 문자기반 스트림으로 연결시켜준다.
- InputStreamReader을 이용하여 BufferedReader와 InputStream인 System.in을 연결해 주었다.    

이렇게 해준 다음 readLine()을 통해 한 줄씩 읽어 오는 것이 좋다. BufferedReader의 next()는 개행문자를 빼고 읽어 오는데, 알고리즘 문제 입력의 대부분은 개행문자가 포함 되어있어서 헷갈리게 된다. 차라리 한 줄 씩 읽어온 다음, 파싱해서 쓰는게 낫다.

## 1.2 파싱! StringTokenizer, parseInt

StringTokenizer는 문자열을 기준에 따라 잘라서 작은 토큰으로 만들어 주는 것이다. 이는 StringTokenizer(String str, String delim, boolean returnDelims) 로 이루어져 있다.
- String str: 자를 문자열
- String delim: 잘라 낼 기준 문자열. 문자열의 요소 하나 하나가 자르는 기준이 된다. -> 비워둘 시 공백
- boolean returnDelims: true일 시 delim또한 토큰으로 만듦. 비워두면 false.

아래와 같이 사용한다
```Java
StringTokenizer st = new StringTokenizer(str, ",");
// 토큰 나눠짐, 접근 방법
while(st.hasMoreTokens()) {
    System.out.println(st.nextToken());
}

// 위의 BufferedReader와 조합하자면
st = new StringTokenizer(br.readLine());
```

숫자의 경우 BufferedReader의 readLine()을 통해 입력을 읽어준 다음 파싱해서 쓴다.    
String의 상태이므로 parseInt등을 쓰면 되겠다.
```Java
// BufferedReader와 사용한 버젼
int N = Integer.parseInt(br.readLine());

// 토크나이저와 사용한 버젼
int curNum = Integer.parseInt(st.nextToken());
```
그냥 똑같다.
