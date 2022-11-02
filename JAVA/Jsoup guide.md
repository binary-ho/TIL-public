# Jsoup guide for yoon yung babys
선 요약
0. 의존성 추가
1. html 소스를 String으로 가져온다.
2. Spring을 `Jsoup.parse`를 통해 파싱.
3. 결과를 `org.jsoup.nodes`의 `Document`로 받음
4. `org.jsoup.nodes.Element`의 `select`메서드로 가져오고 싶은 클래스나 attribute를 가져올 수 있다.

굳이 굳이 라이브러리를 다 적는 이유는 Documet와 같은 경우 여러 라이브러리에서 지원하기 때문에, 헷갈리면 안 되기 때문이다. <br>
보여줄 예제는 html파싱으로 깃허브 커밋 이력 대충 가져오는 예제. (실제로는 github API쓰면 됨)

## 1. Dependencie 추가 하기
`build.gradle` 안의 `dependencies` 부분에 아래와 같은 코드 추가
```java
// build.gradle 
dependencies {
  
  (... 생략)

  implementation 'org.jsoup:jsoup:1.15.3'
}
```
gradle 프로젝트의 경우고, maven의 경우 버전은 자유롭게 고쳐 써도 됨. `1.15.3`은 가장 최신이고 usage가 가장 많은 버전은 `1.13.1`

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
