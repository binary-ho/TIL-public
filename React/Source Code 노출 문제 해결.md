# 프로젝트 전체 Source Code 노출 문제
현재 우리 서비스에서 소스코드가 노출되는 문제를 발견했다. <br>
아래 그림과 같이 적나라하게 전체 프로젝트의 소스 코드가 공개되었다. <br>
GET의 Response로 전체 소스코드가 날아오는 것으로 확인되었다. <Br>

![source 노출](https://user-images.githubusercontent.com/71186266/219049523-9a43239b-55a2-4a38-a2a1-ee27b85a785a.png)

보다 싶이 심각하다. 그냥 프로젝트 전체가 강제로 오픈 소스가 되었다.

## 코드 난독화
처음엔 키워드를 잘못 잡고, 난독화에 대해 알아보았다. <BR>
소스 코드 난독화는 개발자 도구 `Elments` 탭에 날아오는 정적 파일을 난독화 하는 것이다. <Br>

![elemets 탭](https://user-images.githubusercontent.com/71186266/219049166-e74da37f-cda4-4c96-9dbb-77bbd04e95a0.png)

위와 같이 그대로 보이는 정적 파일이 노출되기 싫은 경우 여러 도구를 통해 태그나 내용물을 알아보기 힘든
텍스트 들로 바꾸는 난독화를 진행할 수 있다. <br>

![난독화](https://user-images.githubusercontent.com/71186266/219049154-0a08d6ba-5082-4330-aea3-6f216efab5e7.png)
(출처 최하단 블로그) <br>

스크래핑이나 크롤링도 막을 수 있어 보인다. <br> <br>

그런데 네이버나 깃허브 등의 메이저한 사이트들을 찾아보니, 딱히 정적파일 난독화를 하지 않는 것으로 보여, <Br>
우리도 불필요하다고 판단했다. <Br>
혹시나 정적파일에 중요한 데이터가 노출되는 경우 시도해 볼 수 있으나,
1. 작정하면 난독화 해제가 가능하다
2. 중요한 파일은 `.env` 파일 등을 통해 주입 받는 편이 낫다
위의 2가지 이유로, 그냥 난독화는 하지 않기로 했다.

## Source Map
구글링 키워드를 잡기 어려웠는데, 결국 소스 코드 노출 문제의 원인을 찾아냈다. <br> 
원인은 React가 빌드 과정에서 원활한 디버깅을 위해 
소스 코드의 래퍼런스인 'Source Map'을 만들기 때문이라고 한다. <br>
이게 원활한 디버깅에 어떻게 도움이 되냐면, Console에서 오류 발생시 
어떤 파일의 몇 번째 줄에서 발생했는지 보통 표시되는데, <Br>
Source Map이 있는 경우 그 부분을 눌러 바로 이동할 수 있는 것이다. <Br>
그래서 브라우저 상에서도 오류 위치를 바로 확인할 수 있는 것이다. <Br>
신경 써줘서 고마워 React야! 하지만 너무나도 필요 없다. <Br>
그냥 IDE나 편집기를 보면 되는 문제이고, 오히려 코드가 노출되니 너무 위험하다. <Br> <br>


## 해결법
이 source map의 생성을 막으려면 GENERATE_SOURCEMAP 설정을 FALSE 로 바꾸면 된다.
가장 간단한 방법은 2가지로, 위 내용을 `.env` 파일에 추가하여 받아오는 방법과 <br> 
package.json 빌드 스크립트에 추가하는 방식이 있다. <br>
이미 `.env` 파일이 있는 서비스에서는 주로 env 파일에 추가하는 것 같고, <br>
package.json 에 추가하는 방식은 OS에 따라 스크립트가 달라질 수 있어서 너무 귀찮아 보였다. <br>
그래서 `.env`파일에 `GENERATE_SOURCEMAP=FALSE` 한 줄을 추가하는 방법을 택했다.. <br>


## 공유 파일 관리
예전에 후배가 질문한게 있어 문서의 목적과 맞지 않지만 첨언한다. <br>
이런 `.env` 파일 등 중요한 내용이 있는 파일은 당연히 `.gitignore`에 추가해야 한다. <br>
그 다음 팀에 따라 Github를 사용하는 팀은 Github Actions의 Secret으로, <br>
우리 팀 처럼 BitBucket을 사용하는 경우 `Downloads` 탭을 이용하여 관리하면 된다. 

## Reference
- [개발자 도구에서 React의 소스 코드 숨기기 [3가지 방법]](https://geekconfig.com/tutorial/hide-reacts-source-code-in-developer-tools-3-ways#:~:text=1.%20.env%20%ED%8C%8C%EC%9D%BC%EC%9D%84%20%ED%86%B5%ED%95%B4&text=env%20%ED%8C%8C%EC%9D%BC%EC%9D%84%20%EC%83%9D%EC%84%B1%ED%95%A9%EB%8B%88%EB%8B%A4,%ED%8C%8C%EC%9D%BC%20%EC%83%9D%EC%84%B1%EC%9D%84%20%EB%B0%A9%EC%A7%80%ED%95%A9%EB%8B%88%EB%8B%A4)
- [React build 시 sourcemap 제거하기](https://velog.io/@racoon/React-build-%EC%8B%9C-sourcemap-%EC%A0%9C%EA%B1%B0%ED%95%98%EA%B8%B0)
- [react jscrambler로 코드 난독화 하기](https://bekusib.tistory.com/140)
