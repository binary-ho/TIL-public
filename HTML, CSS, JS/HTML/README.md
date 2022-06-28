# HTML
HyperText Markup Language. 에초에 하이퍼텍스트를 위한 언어이다! 처음에 만드신 분은 대학원생이셨는데, 기존의 인터넷에서는 논문들의 참조를 따라가기가 너무 어려웠다고 한다. <br> 예를 들어 참조한 논문 3개가 있으면, 따로 따로 또 검색해야하고.. 그 논문들에는 또 참조한 논문 5개가 있고.. <br>
이런 상황에서 바로바로 논문의 이름만 누르면 이동할 수 없을까? 해서 만들어진게 지금의 HyperLink 같은 것이고, 이것을 위한 언어가 바로 **HTML인 것이다.** 직역하면 하이퍼텍스트를 '표시하는' 랭귀지 정도가 되겠다. <br>
- 그래서 거 당최.. 기본 기능이 뭡니까?
- **웹 브라우저에 보여 줄 내용에 마크업하고 문서끼리 링크하는 것이 HTML의 기본 기능입니다.**


# 1. 기본 구조 알아보기
```html
<!DOCTYPE html>
<html lang="ko">
    <head>
        <meta charset="UTF-8">
        <title>HTML 기본 문서</title>
    </head>
<body>
        <h1>프런트엔드 웹 개발</h1>
        <hr>
        <p>HTML</p>
    </body>
</html>
```
평범한 HTML 파일이다. 항상 보았지만, 기본적인 구조도 모르고 사용해왔다. 이제부터 알아보자~ <br>
- `<!DOCTYPE html>`: **문서 유형 태그입니다.** 현재 문서가 HTML5 언어로 작성한 웹 문서라는 뜻입니다.
- `<html>~<html>`: 웹 문서의 시작과 끝을 나타내는 태그입니다. **웹 브라우저가 <html> 태그를 만나면 </html>까지 소스를 읽어 화면에 표시해줍니다.**
- `<head>~</head>`: **웹 브라우저가 웹 문서를 해석하는 데 필요한 정보를 입력하는 부분입니다.** (안 보이는 부분)
- `<body>~</body>`: **실제로 나타나는 내용입니다.** 대부분의 HTML 태그는 `<body>`안에 들어있습니다.

**핵심! `Head`는 브라우저가 웹 문서를 해석하는데 필요한 정보들을 입력하는 곳이고! <br> `Body`는 실제 화면에 나타내는 내용들을 입력하는 곳입니다!!! 악!!**

# 2. `<Head>` 태그
웹 브라우저에서는 보이지 않는 부분입니다.
### 2.1 `<meta>` in `<Head>` 
`<meta>`태그: 메타 정보를 표시합니다. 데이터에 대한 데이터이므로, 웹 문서와 관련된 다양한 정보를 지정합니다. 
```html
<!-- meta tag의 가장 중요한 역할! -->
<!-- 화면에 글자를 표시할 때 어떤 인코딩을 사용할지 지정합니다. -->
<meta charset="UTF-8"> 


<meta name="keywords" content="html의 구조">
<meta name="description" content="html의 구조를 알아봅시다">
<meta name="author" content="불꽃카리스마진호우">
```

### 2.2 `<title>`
Head에서 가장 중요한 태그입니다. 웹문서의 제목을 입력합니다. 크롬과 같은 브라우저에서 탭 이름으로도 이 제목이 쓰입니다.
```html
<title>HTML 기본 문서</title>
```

# 3. `<Body>`
1. `<p>`: paragraph (텍스트 단락)
2. `<a>`: anchor (앵커)


### 3.1 **시멘틱 태그** `<header>`, `<main>`, `<footer>`
웹 사이트는 헤더, 메인(본문), 푸터의 세가지 영역으로 나뉘어진다. 이런 **시멘틱 태그**를 이용하면
1. 웹 브라우저가 구조를 파악하기 쉬워짐.
2. 이를 통해 여러 기기의 다양한 화면에서 웹 문서를 표현하기가 쉬워짐
3. 검색시에도, main 부분에서만 검색이 일어나도록 도와줌.

### 3.2 `<div>`
시맨틱 태그가 나오기 이전에는 헤더, 내비게이션, 푸터 등을 구분할 때 `<div>`를 많이 썼다고 한다. 당연히 지금도 엄청 많이 쓰는데, id나 class 속성을 사용해서 문서 구조를 만들거나 스타일을 적용할 때 사용합니다. <br> **즉, 영역을 구별하거나, 스타일로 문자를 꾸밀 때 사용합니다.** ex) `<div id="header">`, `<div class="detail">`


# 4. 내용 입력하기
## 4.1 Text
1. 제목 `<h1>제목</h1>`
h1 부터 h6까지 있고 점점 작아진다. 꼭 `</h1>`과 같이 닫는 태그를 이용해 주어야 한다.
2. `<p> 내용 </p>`: 텍스트 단락
3. 텍스트 단락을 만들 때 `<br>` 두번 쓰면, CSS로 텍스트 단락 스타일을 적용할 때 문제가 생길 수 있다. 텍스트 단락을 만들 때는 앞으로 `<p>` 태그를 이용하자.
4. `<blockquote>인용문?</blcokquote>`: 단락 들여쓰기. 마치 인용문을 살짝 들여쓰는 것처럼, 해당 단락을 조금 들여씁니다.
5. 볼드체: `<strong>굵게 쓰기</strong>`, `<b> 굵게 쓰기 2</b>`: strong은 보통 경고사항 굵게 만들 때 쓰고, 그냥 글씨가 굵을 때는 `<b>`를 쓴다.
6. 기울이기: `<em></em>`, `<i></i>` (이탤릭)

## 4.2 List
크게 3가지 리스트가 있다. **ordered list, unordered list, description list**
#### 1. 순서 있는 목록 **ordered list `<ol>`, `<li>`** 
order list는 `<ol></ol>`를 써주고, 그 안에 항목들은 `<li></li>`와 같이 써준다.
```html
<ol>
    <li> 항목1 </li>
    <li> 항목2 </li>
</ol>
```
그럼 아래처럼 나온다.
<ol>
    <li> 항목 111 </li>
    <li> 항목 22222 </li>
</ol>

#### `<ol>`의 type, start 속성
- type: 순서를 1, 2, 3 말고 다른 타입으로 쓸 수 있게 해줌.
- start: 1부터 시작 말고 다른 것부터 시작할 수 있게 해줌.

```html
로마 대문자 I
<ol type="I" start="3">  
    <li> 로마 1 </li>
    <li> 로마 22 </li>
</ol>

알파벳 대문자 A
<ol type="A" start="21">  
    <li> 알파 1 </li>
    <li> 벳 2 </li>
</ol>
```

**로마 대문자 I**
<ol type="I" start="3">  
    <li> 로마 1 </li>
    <li> 로마 22 </li>
</ol>

**알파벳 대문자 A**
<ol type="A" start="21">  
    <li>알파 1 </li>
    <li>벳 2 </li>
</ol>

#### 2. 순서 없는 목록 unordered list `<ul>`, `<li>`
bullet으로 표시됨
```html
<ul>
    <li>아부징</li>
    <li>돌 굴러 가유~</li>
</ul>
```
<ul>
    <li>아부징</li>
    <li>돌 굴러 가유~</li>
</ul>

#### 3. 설명 목록 description list `<dl>, <dt>, <dd>`
설명목록이란, 이름과 값 형태로 된 목록을 말 합니다. (name, value) <br>
마치 사전에서 단어명과 설명이 있는 모습을 떠올리면 쉽게 이해할 수 있습니다. 
- `<dl>`: 설명 목록 시작 부분, 이 안에 다른 애들을 넣어줍니다.
- `<dt>`: 이름 부분을 지정해줍니다. 아마도 description title인듯.
- `<dd>`: 설명 부분입니다. 
예시를 보는게 빠를것 같습니다.
```html
// 정석
<dl>
    <dt>이름</dt>
    <dd>값 1</dd>
    <dd>값 2</dd>
</dl>

// 예시
<h3>사과 상품 구성</h3>
<dl>
    <dt>선물용 3kg</dt>
    <dd>소과 13~16과</dd>
    <dd>중과 10~12과</dd>
</dl>

<dl>
    <dt>선물용 5kg</dt>
    <dd>중과 15~19과</dd>
</dl>

```
[**정석**]
<dl>
    <dt>이름</dt>
    <dd>값 1</dd>
    <dd>값 2</dd>
</dl>

[**예시**]

<h3>사과 상품 구성</h3>
<dl>
    <dt>선물용 3kg</dt>
    <dd>소과 13~16과</dd>
    <dd>중과 10~12과</dd>
</dl>

<dl>
    <dt>선물용 5kg</dt>
    <dd>중과 15~19과</dd>
</dl>


## 4.3 표
1. 표 만들기: `<table>`, `<caption>`: table은 표를 만들고 caption은 제목을 지어준다.
2. 행 만들기: `<tr>` table row의 줄임말, 안에 셀들을 만들 때는 `<td>`를 써준다. (table detail인가?) 단, 제목으로 만들고 싶은 줄은 `<th>`를 쓰는데, 뭔가 제목의 header에서 따온 것 같다. 그냥 진하게 칠해줄 뿐이다
3. 표의 구조 지정: `<thead>`, `<tbody>`, `<tfoot>` 예를 들어 맨 위는 각 열의 제목, 맨 아래는 합계.. 이런 식으로 나타낼 때 도움이 된다. 걍 table.. head, body, foot이네.
4. 행이나 열을 합치는 rowspan, colspan 속성: 실제로는 셀을 합치는 행위이기 때문에, `<td>` 태그에서 일어난다.
5. 열 묶기 `<col>`, `<colgroup>` 


#### 1. 표 만들기 `<table>`, `<caption>` + 행 만들기 `<tr>`, `<td>`, `<th>`
```html
<table>
    <caption>안녕하세요 저는 표! 입니다.</caption>
    <tr>
        <th>1행 1열</th> -> 하나만 th로 해줘보자
        <td>1행 2열 입니다.</td>
    </tr>
    <tr>
        <td>2행에 1열</td>
        <td>2행 2열!</td>
    </tr>
</table>
```
<table>
    <caption>안녕하세요 저는 표! 입니다.</caption>
    <tr>
        <th>1행 1열</th>
        <td>1행 2열 입니다.</td>
    </tr>
    <tr>
        <td>2행에 1열</td>
        <td>2행 2열!</td>
    </tr>
</table>


#### 4. 행이나 열 합치기~ rowspan
만들 때 열 2칸짜리 행을 행을 만들어 줬다면, 다음 열 만들 때도 영향을 미쳐서 하나가 이미 만들어져있다. 예시를 보자.
```html
<table>
  <caption>선물용과 가정용 상품 구성</caption>
  <tr>
    <th>용도</th>
    <th>중량</th>
    <th>개수</th>
    <th>가격</th>
  </tr>
  <tr>
    <td rowspan="2">선물용</td>
    <td>3kg</td>
    <td>11~16과</td>
    <td>35,000원!</td>
  </tr>
  <tr>
    <td>5kg</td>
    <td>18~26과</td>
    <td>52,000원</td>
  </tr>
  <tr>
    <td rowspan="=2">가정용</td>
    <td>3kg</td>
    <td>11~16과</td>
    <td>30,000원</td>
  </tr>
  <tr>
    <td>5kg</td>
    <td>18~26과</td>
    <td>47,000원</td>
  </tr>
</table>
```

<table>
  <caption>선물용과 가정용 상품 구성</caption>
  <tr>
    <th>용도</th>
    <th>중량</th>
    <th>개수</th>
    <th>가격</th>
  </tr>
  <tr>
    <td rowspan="2">선물용</td>
    <td>3kg</td>
    <td>11~16과</td>
    <td>35,000원!</td>
  </tr>
  <tr>
    <td>5kg</td>
    <td>18~26과</td>
    <td>52,000원</td>
  </tr>
  <tr>
    <td rowspan="2">가정용</td>
    <td>3kg</td>
    <td>11~16과</td>
    <td>30,000원</td>
  </tr>
  <tr>
    <td>5kg</td>
    <td>18~26과</td>
    <td>47,000원</td>
  </tr>
</table>

#### 5. 열을 묶어주는 `<col>`, `<colgroup>` 태그
col 태그는 열을 1개만 지정할 때 쓰고, colgroup은 col을 2개 묶을 떄 씁니다. **반드시 table의 `<caption>` 태그 다음에 씁니다.** 그리고 이 colgroup으로 col들에게 스타일을 부여할 거면, **스타일이 부여되지 않은 col에도 그냥 빈 `<col>`을 써 줘야 합니다.** 순서대로 적용되기 떄문일 것입니다.
```html
<colgroup>
    <col>
</colgroup>
```
4번에서 쓴 예시에 아래 것을 추가해보겠습니다.
```html
<colgroup>
  <col style="background-color:#eee;">
  <col>
  <col span="2" style="width:2000px;">
</colgroup>
```
저기 저 2번째 줄 처럼 뭐 적용되는 스타일이 없어도, 일단 `<colgroup>` 써 줬으면 저렇게 지정 해주어야 하고, <br> 
저기 저 3번째 줄처럼 span="2"로 2열을 묶어서 스타일을 지정해줄 수 있단다!!!

<table>
  <caption>선물용과 가정용 상품 구성</caption>
  <colgroup>
  <col style="background-color:#eee;">
  <col>
  <col span="2" style="width:2000px;">
</colgroup>
  <tr>
    <th>용도</th>
    <th>중량</th>
    <th>개수</th>
    <th>가격</th>
  </tr>
  <tr>
    <td rowspan="2">선물용</td>
    <td>3kg</td>
    <td>11~16과</td>
    <td>35,000원!</td>
  </tr>
  <tr>
    <td>5kg</td>
    <td>18~26과</td>
    <td>52,000원</td>
  </tr>
  <tr>
    <td rowspan="2">가정용</td>
    <td>3kg</td>
    <td>11~16과</td>
    <td>30,000원</td>
  </tr>
  <tr>
    <td>5kg</td>
    <td>18~26과</td>
    <td>47,000원</td>
  </tr>
</table>

이쁘게 변했지요? 야호!
