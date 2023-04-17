# [Nginx] Don't try this at home - "IF" is Evil

> **Nginx if is evil**  
> **Don't try this at home**  
> **You were warned**  

미국 공포 영상이나 위험한 과학 실험 영상의 썸네일이나 제목을 보면

위와 같은 문구가 작성 되어 있다.

위의 문구는 NGINX 공식 홈페이지의 어떤 문서의 예제 위에 적혀 있는 문구이다.

예제를 따라하지 말라고 경고하고 있다.

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FuiOo0%2FbtsaETD7Hlt%2FMILlu7Ea07jXVUaqMja8Rk%2Fimg.png)

Nginx를 사용하며 if를 사용할 일은 꽤 많다.

CORS 처리엔 필수적이고, 메서드나 소스에 따른 처리가 필요할 때가 있다.

그럼에도 Nginx if는 매우 매우 불친절하다. 

또 단순히 불친절 한줄만 알았는데, 악마적인 모습 또한 감추고 있다.

Nginx의 설정파일을 작성할 때 if를 사용하는 경우와

if의 불친절함, 그리고 Nginx의 if를 악마라고 부르는 이유를 살펴보자

## 1\. Nginx 설정파일과 IF

Nginx를 쓰다 보면 if를 쓸 일이 꼭 있다.

특정 포트, Source에서 온 요청들에 대해 따로 처리해줘야 하는 경우

if문을 통해 처리해줘야 한다

예를 들어 아래와 같은 코드를 보자

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fqg1qJ%2FbtsatWac9EZ%2FlzhEYzEfcKhaj9pQjlenb1%2Fimg.png)

위 코드는 Nginx 기본 설정 코드 중 CORS 처리를 위한 코드이다.

Preflight 요청은 OPTIONS 메서드로 날아오기 때문에

if문으로 요청이 OPTIONS인 경우 헤더에 Access-Control-Allow-Origin을 추가 해주는 코드이다.

현재 내가 운영중인 서비스인 [https://imhere.im](https://imhere.im) 에서 온 요청만을 허락하기 위한 코드이다.

이외에도 if를 쓸 일은 꽤 있다.

PORT 번호에 따라, SOURCE에 따라 다른 처리가 필요할 때가 있기 때문이다.

### 2\. Nginx If의 불친절함

문제는 Nginx의 if가 매우 불친절 하다는 점이다.

모르는 사람을 위해 불친절 하다는 이유를 알려주겠다.

아쉽게도 캡쳐가 없지만 무려 전부 겪은 if 관련 오류이다.

1\. Nginx 설정 파일에서 조건문은 location 블록 안에서만 사용 가능하다

2\. Nginx 설정 파일에서 조건문은 중첩이 불가능하다.

3\. Nginx 설정 파일에서 조건문은 else나 if else를 지원하지 않는다.

그러니까 무조건 location 블록 안에서만 사용 가능하고,

```
if (condition) {
	if (condition2) {
		if (condition3) {
        
			// ...
		}
	}
}
```

위와 같은 중첩이나 else if 사용도 불가능 하다는 것이다.

단지 아래와 같은 형태만 가능할 뿐이다.

```
if (condition1) { 
	
    // ...
} 

if (condition2) {
	
    // ...
}

if (condition3) {
	
    // ...
}
```

그래 불친절한건 불친절 한건데, 

사실 위와 같이 if를 연속으로 배치하면 어떻게든 다중 조건문을 처리할 수 있다.

(이에 대한 2가지 방법은 다른 글에서 소개하겠다.)

그런데 왜 악마라니 뭐니 하는 말이 나온걸까?

## 3\. Nginx if is evil - content handler, rewrite phase

**Nginx의 if는 우리가 아는 if와는 조금 다르게 작동한다.**

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FmRZeV%2FbtsaKy68sIJ%2FIBn0KUmd0ferB6kdMqPkQ0%2Fimg.png)

위와 같은 코드를 살펴보자. 

Case 1이라고 부르겠다.

location 블록 안이 보이는가?

set 지시어를 통해 a의 값을 32로 설정해 주었다.

이후 if문을 만나게 되고 a = 32이므로 a가 56으로 설정될 것이다.

그리고 if문을 빠져 나오면서 a = 76이 될 것이다.

실제로 nginx에 접속하면 프록시 패스로 인해 /76으로 이동하게 된다.

이런 proxy module의 프록시 패스와 같은 지시어를 content handler라고 부른다

그럼 위 코드에서 딱 1줄만 추가된 아래 경우를 보자.

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FebXFzj%2FbtsaEhkh6P5%2Fw4OAe2kJ26m8tUmL8HO7cK%2Fimg.png)

위 코드를 Case 2라고 부르겠다

if문 안의 echo 지시어가 추가 되었다.

echo의 결과는 어떨지 대답해보자.

56이라고 답했다면 틀렸다.

**정답은 76이다.**

이상하다!

문명 a가 32가 되고.. if문을 진입하여 56이 된 다음 echo 지시어를 만나게 됨은 분명하다.

그런데 왜 값이 76이 될까?

이런 이상한 동작 외에도 특이한 점을 먼저 한가지 말 하고 싶은데,

실제로 두 코드는 if문을 벗어나지 않는다.

그러니까 if문 블록을 벗어나지 않은 채로 요청 처리를 끝마친다.

대체 무슨 소리인가?

그럼 첫 번째 코드에서 proxy\_pass는 왜 실행 된것이며,

두 번째 코드에서 a는 76이 되는건가?

심지어 두 번째 코드에서 proxy\_pass는 작동하지 않는다!!

이런 요상한? 작동은 모르고 사용한다면 악마같이 작용할 수 있다. 

때문에 공식 페이지에서 if는 악마이며, 예제를 실행시키지도 말라고 한 것이다.

이제 if의 동작 과정과 HTTP 요청 처리 과정을 살펴보자.

## 4\. Nginx HTTP 요청 처리와 IF

### 4.1 Content Handler

Nginx에선 여러 모듈을 제공한다.

proxy\_pass 등의 proxy 관련 지시어를 제공하는 proxy 모듈

echo를 제공하는 echo모듈

로드밸런싱과 같은 다수 서버의 조절을 위한 기능을 제공하는 upstream 모듈 등

여러 모듈을 제공하고, 이들이 제공하는 지시어를 Content Handler라고 부른다.

Nginx는 if문 안에 Content Handler가 따로 없는 경우, 

if문 밖의 Content Handler를 상속 받는다!

![imgae](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FmRZeV%2FbtsaKy68sIJ%2FIBn0KUmd0ferB6kdMqPkQ0%2Fimg.png)

그러니까 위 코드에서 if문은 내부적으로 아무 Content handler가 없으므로, (set은 content handler가 아니다)

it문 밖의 proxy\_pass를 상속 받게 되고,

실제로는 if문 밖을 벗어나지 않고도 proxy\_pass가 이루어진다! 

혼란스럽다. 하지만 실제로 그렇게 작동한다.

위 사실을 그냥 받아들인다고 치더라도 다른 문제가 남아있다.

if문 밖을 벗어나지 않는다면,

위 코드에서 proxy\_pass는 왜 /76으로 되었고,

Case 2 코드에선 왜 echo의 결과가 76인가?

### 4.2 Rewrite Stage

Nginx가 HTTP 요청을 처리할 때 총 11개의 stage를 거친다. ([링크](https://gist.github.com/denji/9130d1c95e350c58bc50e4b3a9e29bf4))

이 중 REWRITE\_PHASE는 응답을 실제로 처리하는 CONTENT\_PHASE 전에 작동하는데,

Rewrite directive를 처리한다!

그러니까 set $a와 같이 변수의 값을 rewrite하는 처리를

실제 응답을 처리하기 한참 전에 처리한다는 것이다.

이 무슨 또 해괴한..

그러니까 아래 코드 Case 2는

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FebXFzj%2FbtsaEhkh6P5%2Fw4OAe2kJ26m8tUmL8HO7cK%2Fimg.png)

여러 흐름들이 실행되기 전에,

이미 a = 32, a = 56, a = 76이 먼저 작동한다는 것이다.

다만 if문을 들어가는 진행은 그대로 실행되기에,

a = 76인 상태에서 if문을 진입하게 되고,

echo의 결과는 76이 되는 것이다.

대체 이게 무슨..

그러니까 if의 동작 방식과 nginx의 http 요청 처리 단계를 모르고 있다면,

큰 실수를 할 수도 있는 것이다.

공식 문서에서 Don't try this at home!이라고 할 정도로 말이다!

if is evil이라는 표현이 꼭 if를 쓰지 말라는 표현은 아니다!

이러한 작동 방식들을 이해하고 조심해서 코드를 작성하라는 경고의 하나이다.

if문 안에 if 블록을 탈출하면서 계속 진행하는 break;를 사용하거나, 

아예 전체 진행을 끊는 return을 사용하면서 if를 잘 활용하자.

단, 두 지시어는 content handler가 아니기 때문에 if문 밖의 content handler를 상속 받을 수 있다는 점과

if문 내부에 있으면서 return과 break 이후에 있는 content handler 지시어들은 블록을 빠져 나오면서 실행될 수 있다는 점은 여전히 주의 하며 코드를 작성하면 되겠다.

#### Reference

\- [\[Nginx 공식문서\] If is Evil… when used in location context](https://www.nginx.com/resources/wiki/start/topics/depth/ifisevil/ "If is Evil… when used in location context")

\- [How nginx "location if" works](http://agentzh.blogspot.com/2011/03/how-nginx-location-if-works.html)

\- [NGINX actual HTTP Request processing flow is divided into 11 stages.](https://gist.github.com/denji/9130d1c95e350c58bc50e4b3a9e29bf4)
