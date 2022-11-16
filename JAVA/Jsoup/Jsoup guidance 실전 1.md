# Jsoup guidance for yoon yung babys
선 요약

1. 의존성 추가
1. html 소스를 String으로 가져온다.
2. html 소스 String을 `Jsoup.parse`를 통해 파싱.
3. 결과를 `org.jsoup.nodes`의 `Document`로 받음
4. `org.jsoup.nodes.Element`의 `select`메서드로 가져오고 싶은 클래스나 attribute를 가져올 수 있다.

굳이 굳이 라이브러리를 다 적는 이유는 Documet와 같은 경우 여러 라이브러리에서 지원하기 때문에, 헷갈리면 안 되기 때문이다. <br>
보여줄 예제는 html파싱으로 깃허브 커밋 이력 대충 가져오는 예제. (실제로는 github API쓰면 됨)

## 0. Jsoup이란?
정확히는 **스크래핑 툴로 웹 페이지 Html Source를 가져온다.** 이후 다양한 강력한 기능들로 파싱해서 사용할 수 있다.

|클래스|설명|
|:----:|:----:|
|Document|Jsoup으로 HTML을 긁어온 결과 그 자체, 전체 Source에 해당한다.|
|Element|Document의 HTML 요소로 Document의 부분으로 이해하면 된다. <br> 결국 파싱한 결과가 Element로 나타난다.|
|Elements| Element의 이터러블한 자료형. 주로 여러 Element들이 반환되는 메서드의 반환형임.|
|Response|Jsoup이 Document와 함께 가져오는 정보로, status 관련 내용이나 헤더 메시지 쿠키 등의 **해당 URL의 접속과 관련된 정보를 가져온다.**|

## 1. Dependency 추가 하기
`build.gradle` 안의 `dependencies` 부분에 아래와 같은 코드 추가
```java
// build.gradle 
dependencies {
  
  (... 생략)

  implementation 'org.jsoup:jsoup:1.15.3'
}
```
gradle 프로젝트의 경우고, maven의 경우 `pom.xml`의 dependencys에 아래 코드 넣어준다. <Br>
  
버전은 자유롭게 고쳐 써도 됨. `1.15.3`은 가장 최신이고 usage가 가장 많은 버전은 `1.13.1`
```java
<dependency>
    <groupId>org.jsoup</groupId>
    <artifactId>jsoup</artifactId>
    <version>1.13.1</version>
</dependency>
```
메이븐의 경우. 이런 dependency는 다들 알겠지만, mvnrepository에서 보면 됨. [mvnrepository 바로가기](https://mvnrepository.com/artifact/org.jsoup/jsoup/1.13.1)

## 2. getHtmlSource
입력으로 url 주소를 받아서 Html소스를 가져온다. <br>
페이지의 HTML 소스 전체를 스트링으로 받아오는 코드.
```java
private String getHtmlSource(String url) {
    try {
        URL targetUrl = new URL(url);
        BufferedReader reader = new BufferedReader(new InputStreamReader(targetUrl.openStream(), "UTF-8"));
        StringBuilder html = new StringBuilder();
        String current = "";
        while ((current = reader.readLine()) != null) {
            html.append(current);
        }
        reader.close();
        return html.toString();
    } catch (MalformedURLException e) {
        e.printStackTrace();
    } catch (IOException e) {
        e.printStackTrace();
    }
    return null;
}
```
## 3. getHTMLDocument
String HtmlSource를 받아 `Jsoup.parse()`를 통해 파싱한다.

```java
private Document getHTMLDocument(String userGitHubId) {
    String htmlSource = this.getHtmlSource("https://github.com/" + userGitHubId);
    return Jsoup.parse(htmlSource);
}
```
getHtmlSource로 깃허브 특정 유저의 dashboard html 소스를 가져오는 예시. getHtmlSource의 입력으로는 string으로 된 url을 바로 넣어주면 된다. <br>


윤영교수님 사이트는 이런식
```java
public Document getHTMLDocument() {
    String htmlSource = this.getHtmlSource("https://apl.hongik.ac.kr/members/current-and-former");
    return Jsoup.parse(htmlSource);
}
```

`Document`에 주의! `org.jsoup.nodes`의 것을 받아와야함.

<br> 
나중에 알게 된 사실인데, 다 필요 없고 바로 Document로 파싱하는 함수가 있음.
```java
  Document document = Jsoup.connect("https://apl.hongik.ac.kr/lecture/dbms").get();
```
위의 과정이 다 필요 없다..

## 4. 원하는 클래스나 attribute 가져오기

### 클래스로 태그 찾기
```java
private int getContributionCount(String userGitHubId, String dateString) {
    Document document = this.getHTMLDocument(userGitHubId);
    
    // 가져오고 싶은 클래스 이름
    String calenderClassString = ".ContributionCalendar-day";

    String rectDateString = "rect[data-date=" + dateString + "]";
    String dataCountAttrString = "data-count";

    Elements dayComponent = document.select(calenderClassString).select(rectDateString);
    String dayContributionString = dayComponent.attr(dataCountAttrString);
    return  Integer.parseInt(dayContributionString);
}
```
가져오고 싶은 태그에 클래스 attr가 잘 되어 있다면, `    String calenderClassString = ".ContributionCalendar-day";`와 같이 string으로 만들어둔다. <br> 클래스로 태그를 찾을 수 있다.

### 태그와 태그 안의 attribute value로 찾기

이후 `.ContributionCalendar-day` 안의 `rect`태그를 가져올 예정이다. 
```java
String rectDateString = "rect[data-date=" + dateString + "]";

(...생략)

Elements dayComponent = document.select(calenderClassString).select(rectDateString);
```
이 코드는 다음과 같이 동작한다. 
1. class value가 `.ContributionCalendar-day`인 태그를 찾는다.
2. 그 중 `rect`태그를 찾아 `data-date` attribute 값이 `dataString`과 딱 일치하는 것을 `Elements dayComponent`로 받는다.

여기서 `Elements`는 꼭 `org.jsoup.nodes.Element`의 것을 사용해야한다! <br> <br>


이렇게 특정 날짜의 커밋 데이터를 가져왔다. 이제 커밋 횟수 `data-count`를 가져오겠다.
```java
String dataCountAttrString = "data-count";

(...생략)

String dayContributionString = dayComponent.attr(dataCountAttrString);
```

아까 만든 Elements dayComponent에서 `attr()`를 통해 value를 string으로 가져오면 끝

```java
String rectDateString = "rect[data-date=" + dateString + "]";
String dataCountAttrString = "data-count";

Elements dayComponent = document.select(calenderClassString).select(rectDateString);
String dayContributionString = dayComponent.attr(dataCountAttrString);

return  Integer.parseInt(dayContributionString);
```

완성된 모습. 

<br>

![suc](https://user-images.githubusercontent.com/71186266/199424433-9091c074-5c97-4f48-9d7c-774f42131c1e.png)

성공
  
## 5. 실전에서는 어떻게 사용할까?
실전에서는 **클래스 이름을 쓸 수 없는 경우가 대부분이다.** 빌드 과정에서 자동 생성되는 경우가 있기 떄문.. <br>
그래서 내가 추천하고 싶은 방법은 역시 tag나, attribute와 예상 value를 찾는 것이다. <br>
  
예를 들어 깃허브의 잔디의 tag는 `<rect>`이고, attribute `day-count`가 존재한다. 이 값을 이용하는 것이 결국 실전 스크리핑의 현실적인 방법이다. <br>

**결국, 스크래핑 하는 정보가 담긴 부분의 tag나, attribute의 규칙만 파악하면 된다는 것!**
  
#### Text
각종 삽질을 통해 찾은 Text관련 메서드들..  결국 웹 페이지에서 어떤 정보를 나타낼 떄, Plain Text가 제목이나 세부 정보의 역할을 할 확률이 높다. <br>
결국 Text관련 함수가 실전에서는 중요해 보인다.

1. text() :star:
아주 강력한 메서드! element 내 Text 요소를 전부 털어온다! 결국 나타나는 정보를 털어오려면 `text()`가 필요하고 웬만한 웹 사이트는 이거 하나만 있어도 중요 정보를 다 가져올 수 있다.
```java
  private List<Example> parseExamples(List<Element> elements) {
      List<Example> examples = new ArrayList<>();
      elements.forEach(element -> {
          String[] fieldArray = element.text().split(",");
          Example example = new Example();
          example.setName(fieldArray[0].trim());
          example.setAge(fieldArray[1].trim());
          example.setEmail(fieldArray[2].trim());
          examples.add(student);
      });
      return examples;
  }
```
예시만 봐도 얼마나 강력한지 알 수 있다.

2. 내부적으로 특정 plain 텍스트를 가진 Element를 반환!
```java
  document.body().getElementsContainingOwnText("test");
  document.body().getElementsMatchingText("test"); 
```
