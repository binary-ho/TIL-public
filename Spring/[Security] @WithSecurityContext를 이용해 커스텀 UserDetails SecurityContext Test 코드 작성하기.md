# [Security] @WithSecurityContext를 이용해 커스텀 UserDetails SecurityContext Test 코드 작성하기
선요약!

커스텀하게 UserDetails를 구현해서 사용중이라면,

SecurityContext의 인증된 유저 관련 테스트를 진행할 때 @WithMockUser를 사용할 수 없다.

몇 가지 대안 중 더 편리해 보이고 아주아주 유연한 처리가 가능한 @WithSecurityContext를 이용해 테스트 코드를 작성하는 법을 소개해본다.

## 1\. @WithMockUser 사용하기

보통 Spring Security의 Security Context에 로그인된 유저 정보를 이용한 테스트를 진행할 때,

간편하게 \`@WithMockUser\` 어노테이션을 이용할 수 있다.

내 프로젝트의 Authentication Helper 클래스는 아래와 같이 현재 로그인한 유저를 

Security Context에서 꺼내올 수 있는 메서드를 제공한다.

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fsb4Lj%2FbtsaJVf4eEq%2F6FBPL1FZAfr702DZFWv8dk%2Fimg.png)


이는 API 요청시 여러 검증 과정에서 사용하기 위해 구현해주었다.

UserDetails를 따로 구현하지 않는다면,

아래와 같은 @WithMockUser 어노테이션을 이용해 편하게 테스트 할 수 있다. 

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FeHputJ%2Fbtsakdpv8rv%2FzOz4t5DibRAiefSNGMkoe0%2Fimg.png)

어노테이션 안에 따로 프로퍼티를 지정해 주지 않으면,

기본적으로 username을 \`user\`로, password를 \`password\`로, 그리고 roles를 \`ROLE\_USER\`로 가진

UsernamePasswordAuthenticationToken 인증 객체가 생성되고, SecurityContext에 set 된다.

위에서 보인 바와 같이 username이나 role 또한 편하게 커스텀 할 수가 있어서 너무 편리하다.

하지만 프로젝트에서 @WithMockUser를 사용할 수 없는 문제가 발생했다.

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbBeGbk%2FbtsakiqySVR%2F4TCyfUJazD6Eoue5bkhiq0%2Fimg.png)

확인해 보니 ClassCastExection이 발생했는데,

발생 지점은 아래 코드의 return 부분이였다.

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fsb4Lj%2FbtsaJVf4eEq%2F6FBPL1FZAfr702DZFWv8dk%2Fimg.png)

UserDetails를 직접 구현해 직접 커스텀한 PrincipalDetails로 캐스팅 하는 과정에서 에러가 발생한 것이다.

@WithMockUser를 사용하여 만들어낸 유저는 org.springframework.security.core.userdetails.User 객체로 생성된다.

따라서 JWT 도입 등의 이유로 UserDetails를 직접 구현해서 사용중이라면 @WithMockUser 를 사용할 수 없다는 것이다.

## 2\. @WithUserDetails와 @WithSecurityContext  비교

이에 대한 대안으로 고려해볼 수 있는 방법은 두 가지가 있다.

1\. @WithUserDetails : 실제 유저 데이터를 사용하는 방식

2\. @WithSecurityContext : 직접 SecurityContext 를 생성하는 방식

1번의 @WithUserDetails는 내게 불편해 보였다.

1\. 실제 있는 유저로 테스트 한다는 것은 테스트 환경에서 미리 등급별 유저를 넣어 놓아야 한다는 것

2\. 등급별로 다른 테스트를 해야 할 때가 있을텐데 유저를 등급별로 저장해야 한다는 점

위 두가지 부분이 불편해 보였다.

특히 WithUserDetails는 직접 정확한 이름을 기입하여 유저를 특정해야 하는데,

실수 하기도 쉬워 보이고 여간 불편해 보이는 것이 아니였다.  

그리고 @WithSecurityContext가 가진 장점들과 유연함이 너무 편해 보였다.

그래서 나는 @WithSecurityContext를 사용하기로 결정했다.

## 3\. @WithSecurityContext 사용하기

 @WithSecurityContext는 **실제로 존재하지 않는 유저를 사용해** 아주 유연한 테스트가 가능하다

물론 @WithMockUser와 같이 **이름, 등급 등을 전부 커스텀 해서 사용할 수 있다.**

아래에 적겠지만, 정말 유연하게 다양한 처리가 가능하다.

테스트를 위해 직접 구현한 Mock 유저 클래스가 들어갈 수 있는

커스텀 SecurityContext를 만들어서 사용한다. 

이는 **WithSecurityContextFactory**를 직접 구현 함으로써 가능하다

### 3.1 Mock User 어노테이션 만들기

일단 커스텀 컨텍스트에 들어갈 유저 어노테이션을 만들어 보자.

내 프로그램에선 여러 이유로 Member라는 이름을 쓰므로,

MockMember로 이름을 지었다.

(실제 사용하는 GDSC 회원들이 맴버라는 용어를 쓴다, 예약어 피하기, 시큐리티의 User와 구분하고 싶어서 등등의 이유..) 

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbMLIP0%2FbtsaiaGCen8%2FnTBzGwVy5qsKwTa3KHbcuk%2Fimg.png)

위와 같이 구현해 주면 된다. 아주 쉽고 편리하다.

@WithSecurityContext 어노테이션은 interface WithSecurityContextFactory를 구현한 클래스를 지정해 줌으로써 사용할 수 있다. 해당 팩토리 클래스 안의 오버라이딩 된 **\`createSecurityContext()\`** 메서드를 호출해 SecurityContext를 만드는데 곧 구현하는 법을 설명하겠다.

일단은 비워 두거나 적절한 이름을 적어 두면 되겠다.

@WithSecurityContext를 통해 SecurityContext를 생성하므로,

이를 테스트 코드에서까지 사용하기 위해선 어노테이션 유지 정책을 Runtime으로 바꿔줘야 한다.

@Retention(RetentionPolicy.RUNTIME)를 통해 설정할 수 있다.

그리고 위와 같이 필드를 지정해줄 수 있다.

default를 통해 기본 값을 정해줄 수 있고, id의 경우엔 특수한 처리가 필요하다.

default로 지정된 값은 상수여야 하기 때문에 Long으로 선언하면 기본 값 설정이 어렵다.

그렇다고 매번 넣어 주기는 불편하니 일단 long으로 지정한 다음, WithSecurityContextFactory를 구현한 클래스에서 따로 처리해주겠다.

### 3.2 WithSecurityContextFactory 구현체

이제 WithSecurityContextFactory 구현체를 만들어보자

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fc9iQfW%2FbtsatUCqMKF%2FhtCVXsQuxp5idVGGIqmIMk%2Fimg.png)

위와 같이 WithSecurityContextFactory를 구현하는데,  앞서 만든 MockMember를 넣어 준다.

WithSecurityContextFactory<MockMember> 형태가 된다.

그리고 createSecurityContext를 Override 해준다.

createSecurityContext를 Override하면서 구현에 필요한 다양한 처리가 가능하다.

createSecurityContext의 입력으로 MockMember를 받아

내 프로젝트에서 맴버를 생성하는 정적 팩터리 메서드 Member.createMemeber를 호출했다.

각자 방법에 맞게 실제로 사용중인 유저 객체를 만들어 주면 되겠다.

그리고 DB에 저장하지 않고도 id를 발급 받기 위해 앞서 MockMember에서 넣어준 long id값을 호출해 대입해준다.

이런 자동 생성 값들은 위와 같이 처리해 주면 되겠다.

이후 사용중인 회원 객체를 이용해 UserDetails를 구현한 객체를 만든다.

나의 경우 PrincipalDetails이므로, 어노테이션을 통해 만든 Member 인스턴스를 이용해 만들어 줄 수 있었다.

이후 usernamePasswordAuthenticationToken을 이용해 토큰을 만들고

컨텍스트를 만들어 token을 set해준 다음 반환한다.

이렇게 하면 성공적으로 MockMember가 set되어 있는 Context가 생성된다.

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FJV5Gl%2FbtsaKw8nJZp%2Fm7J8SpmpxKK0uKbORc5II0%2Fimg.png)
  
위와 같이 편리하게 사용할 수 있다!

어노테이션을 구현하며 설정해둔 필드를 통해,

위 사진과 같은 편리한 필드값 변경이 가능하다. 

#### \+ 추가

스프링 공식 도큐먼트에 따르면 아래와 같이 실제로 있는 유저를 사용하는 구현도 가능하다고 한다.

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FQSIAJ%2FbtsaqPVIGMn%2FCtG4r7WwIoAiVi8trL6ZcK%2Fimg.png)
  
실제 있는 유저를 통해 테스트 해야해서,

@WithUserDetails 를 사용해야 하는 경우에도 @WithSecurityContext 를 사용할 수 있는 것이다.

@WithSecurityContext 가 얼마나 유연한지 알 수 있는 대목이다.

필요한 어떤 처리도 가능한 것 같다.

Reference

\- [스프링 공식 문서 - Testing Method Security](https://docs.spring.io/spring-security/reference/servlet/test/method.html#test-method-withsecuritycontext)

\- [\[Spring\] SecurityContext에 사용자 정보 넣어 테스트하기](https://sol-devlog.tistory.com/m/18)

\- [Test / Spring Security / 단위 테스트에 Security 추가하기](https://highright96.tistory.com/18)
