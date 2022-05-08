Markdown 문법
=============

# 1. Markdown 문법을 공부하는 이유
 매일 개발 공부를 하지만 공부한 내용들이 머릿속에서 금방 휘발되어 버리고 만다. 분명 공부량은 많은 것 같은데 남는 것은 적은 느낌을 받았다. 직접 풀은 문제인데 다시 풀려니 못 풀겠거나, 
분명 배운 내용인데 말 하지 못 하는 상황이 적지 않았다.   
 블로그에도 가끔 공부 내용을 정리 하긴 했지만, 정제된 지식만을 올리고 싶은 마음에 자꾸 비공개 글을 쓰거나, 완전한 글을 완성 시킬 시간이 부족하면 작성 자체를 포기하기도 하였다. 그래서 따로 공부한 내용들을 매일 편하게 정리할 곳이 필요했고, github에 정리하기로 하였다.   
 깃허브에 매일 공부한 내용들을 좀 더 보기 좋게 정리하기 위해 Markdown 문법에 대해 간단한 공부를 시작하기로 하였다. 작성은 Visual Studio Code에서 진행하였다.

# 2. Markdown 기초 문법
## 2.1 Headers
제목이나 글머리를 위한 문법. Notion에서 사용하던 것과 비슷하게 하면 된다.   

- 큰 제목: 문서 제목용
    ```
    This is an H1
    ==============    
    ```    
    This is an H1
    ======   

 아래에 =의 갯수를 꼭 맞출 필요는 없었다. 2개 3개만 적어도 헤더로 인식 되었다는 의미로 에디터에서 진한 글씨로 나타나는 것을 확인할 수 있었다.  


- 작은 제목: 문서 부제목용
    ```
    This is an H2
    ----------
    ```
    This is an H2
    -------

- 글머리: 1~6까지 지원함.
    ```
    # This is a H1
    ## This is a H2
    ### This is a H3
    #### This is a H4
    ##### This is a H5
    ###### This is a H6
    ```
    > # This is a H1
    > ## This is a H2
    > ### This is a H3
    > #### This is a H4
    > ##### This is a H5
    > ###### This is a H6

- 제목 이외에 큰 글씨를 쓸 때는 아무래도 #을 이용하는 것이 더 용이했다.

## 2.2 List
#### ● 숫자 목록(번호)
순서가 있는 목록은 숫자와 점을 이용한다. 숫자를 잘못 입력해도 내림차순으로 보이게 된다.
```
1. 첫번째
2. 두번째
3. 세번째
5. 다섯번째
4. 네번째
```

1. 첫번째
2. 두번째
3. 세번째
5. 다섯번째
4. 네번째


#### ● 숫자 없는 목록 (기호 `*`, `+`, `-` 이용)
```
* 별1
  * 별2
    * 별3

+ 플러스1
  + 플러스2
    + 플러스3

- 마이너스1
  - 마이너스2
    - 마이너스3

* 혼합1
  - 혼합2
    + 혼합3
      + 혼합4
```
* 별1
  * 별2
    * 별3

+ 플러스1
  + 플러스2
    + 플러스3

- 마이너스1
  - 마이너스2
    - 마이너스3

* 혼합1
  - 혼합2
    + 혼합3
      + 혼합4


## 2.3 Code
#### 2.3.1 들여쓰기
탭이나 4개의 공백(들여쓰기)를 만나면 들여쓰지 않은 행을 만날 때까지 병환된다. 한 줄의 띄어쓰기가 필요하다. 없을 경우 코드로 인식 불가.   
나에게는 불편하게 느껴졌다.
```
들여쓰지 않음 

    들여썼다.

들여쓰지 않음 
```
위 내용을 적용하면
****
들여쓰지 않음 

    들여썼다.

들여쓰지 않음 
*****
이렇게 된다.

#### 2.3.2 Code Block

- `<pre><code>{code}</code></pre>` 이용방식

```
<pre>
<code>
public class Main {
  public static void main(String[] args) {
    System.out.println("Hello World!");
  }
}
</code>
</pre>
```
위와 같이 작성한 경우
<pre>
<code>
public class Main {
  public static void main(String[] args) {
    System.out.println("Hello World!");
  }
}
</code>
</pre>
이렇게 나타나게 된다. 제일 확실해 보여서 좋다.   

- ` ``` ` 을 이용하는 방법.


<pre>
<code>
```
public class Main {
  public static void main(String[] args) {
    System.out.println("Hello World!");
  }
}
```
</code>
</pre>

위와 같이 작성하면,

```
public class Main {
  public static void main(String[] args) {
    System.out.println("Hello World!");
  }
}
```
이렇게 나타난다. 간편하긴 하지만 은근 사용이 어려워서 잘 쓰지 않을 것 같다.
` ``` ` 바로 뒤에 사용 언어를 적으면 문법 강조가 가능하다. 

<pre>
<code>
```java
public class Main {
  public static void main(String[] args) {
    System.out.println("Hello World!");
  }
}
```
</code>
</pre>

```java
public class Main {
  public static void main(String[] args) {
    System.out.println("Hello World!");
  }
}
```


## 2.4 수평선 `<hr/>`


`<hr/>`, `* * *`, `***`, `*****`, `- - -`,
  `---------------------------------------`


적용하면 전부 아래와 같이 나타난다
* * *

## 2.5 작은 박스 ` `
#### - ` 두개 사이에 아무거나 넣으면 작은 박스가 된다. 아무거나
```
`아무거나`
```
`아무거나`

## 2.6 Link

- 참조 링크
    ```
    [link keyword][id]

    [id]: URL "Optional Title here"
    ```

    ```
    <실제 코드>
    Link: [Google][googlelink]

    ( [googlelink]: https://google.com "Go google" )
    ```
    위에서 보인 것 처럼 한 줄의 공백이 필요함.

    Link: [Google][googlelink]

    [googlelink]: https://google.com "Go google"


- 외부 링크
`[Title](link)`
단순하게 Title 부분에 보일 타이틀을 넣고, link 부분에 링크 주소를 적으면 된다. **-> 이 방법이 제일 편한 것 같다.**
`ex) [Google](https://google.com, "google link")` 은 아래와 같이 나타난다.
Link: [Google](https://google.com, "google link")
- 자동 연결 `<>`
    ```
    일반적인 URL 혹은 이메일주소인 경우 그냥 <>으로 묶어주면 된다.

  * 외부링크: <http://google.com/>
  * 이메일링크: <address@example.com>
    ```

* 외부링크: <http://google.com/>
* 이메일링크: <dfghcvb11@naver.com>

## 2.7 Highlighting
```
* **볼드체 1**
* __볼드체 2__
* *이테릭 1*
* _이테릭 2_
* ~~취소선~~

```

> **볼드체 1**
 __볼드체 2__
 *이테릭 1*
 _이테릭 2_
> ~~취소선~~

__나는 볼드체를 자주 쓰는데, ~~별은 너무 자주 쓰여서 헷갈리니까 아래바 두개로 가두는 것이 편해보인다. 써 보니까 나름 편하다.~~__    
    -> 여러번 직접 써 보니 아래바는 글씨를 붙여 쓸 때 불편하다!    
    `__`로 가둔 이후 글씨를 붙여 쓰면 볼드체로 변하지 않는 것을 확인했다.. `**`이 더 낫다.

## 2.8 Image
```
![Alt text](/path/to/img.jpg)
![Alt text](/path/to/img.jpg "Optional title")
```
사용 예시

![Alt text](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FcIZNgv%2FbtraMqh9mCv%2FpZcKMalEyIVkrcbttmKWyK%2Fimg.jpg)

사이즈 조절 기능은 없기 때문에 ```<img width="" height=""></img>```를 이용해야 한다. 한번 크기를 조절해보겠다.

```
<img src="/path/to/img.jpg" width="450px" height="400px" title="px(픽셀) 크기 설정" alt="Jinho"></img><br/>
<img src="/path/to/img.jpg" width="40%" height="30%" title="px(픽셀) 크기 설정" alt="Jinho"></img>
```
<img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FcIZNgv%2FbtraMqh9mCv%2FpZcKMalEyIVkrcbttmKWyK%2Fimg.jpg" width="450px" height="400px" title="px(픽셀) 크기 설정" alt="Jinho"></img><br/>
<img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FcIZNgv%2FbtraMqh9mCv%2FpZcKMalEyIVkrcbttmKWyK%2Fimg.jpg" width="40%" height="30%" title="px(픽셀) 크기 설정" alt="Jinho"></img>

퍼센트로의 조절이 더욱 쉬워 보인다. 간단하게
```
<img src="/path/to/img.jpg" width="450px" height="400px"></img><br/>
```
이정도만 써 줘도 무방하다.

## 2.9 줄 띄우기
이걸 이제 알았네... 줄 띄우기 기능이 있다
```
<br/>
```

<br/>

# 4. 정리
markdown 문법을 좀 더 잘 활용하기 위한 기본 문법을 알아보았다.   
새로운 내용들은 여기에 계속해서 보충해 면 될 것 같다. 노션에서 이용하던 것과 똑같아서 그리 낯설지는 않았다.

## ○ 참고
[ihoneymon님의 how-to-write-by-markdown.md](https://gist.github.com/ihoneymon/652be052a0727ad59601#this-is-an-h1)
