
# 8. CSS 박스
CSS 박스 모델은 **블록 레벨 요소**와 **인라인 레벨 요소**로 나뉩니다. 블록 레벨 요소는 요소가 한 줄 전체를 차지합니다. **즉, 요소의 넓이가 100%입니다.** 인라인 레벨 요소는 콘텐츠만큼만 영역을 차지합니다. 한 줄에 여러 요소를 넣을 수 있습니다. <br>
ex)
- 블록 레벨 요소: `<h1>` 시리즈, `<div>`, `<p>` 등
- 인라인 레벨 요소: `<span>`, `<img>`, `<strong>` 등이 있습니다.

### 1. 박스 모델 기본 구성
4가지 영역으로 콘텐츠가 둘러 쌓여 있다.
- `margin`: 여러 **박스 모델 사이의 여백**
- `border`: 박스의 테두리
- `padding`: **박스와 콘텐츠** 영역 사이의 여백
- 콘텐츠 영역: 가장 안쪽의 알맹이 영역
웹에서 아무 요소나 잡고 inspect를 눌러 computed 탭을 눌러보자. 각 영역이 어떻게 되어있는지 확인이 가능하다.
1. `width`, `height`: 기본 auto로 설정되어 있음. 콘텐츠 영역의 크기를 조절함.
2. `box-sizing`: 박스 모델의 크기를 어떻게 결정할지 선택한다. `content-box`가 기본으로 콘텐츠 영역만 너비값을 지정합니다. 옵션으로는 `border-box` 값이 있고, 테두리까지 포함해서 너비값을 지정합니다. **`border-box`로 설정해 두는 편이 요소의 크기를 계산하기 더 쉽겠죠?**
3. `box-shadow`: 박스에 그림자 추가하기

### 2. 박스 테두리 스타일
점선, 실선, 테두리 두께, 색상 등을 지정할 수 있습니다. <br>
**방향을 지정하는 순서가 있습니다. top 부터 시계 방향으로 진행됩니다.** <br> top -> right -> bottom -> left 순으로, 시계 방향으로 순서가 진행됩니다.


1. `border-style`: 기본이 none이기 때문에, 기본적으로 테두리가 보이지 않습니다. 속성값을 지정해주면 보입니다. hidden, solid, dotted, double, dashed, 입체적 표현으로는 groove, inset, outset, ridge 등이 있습니다.
2. `border-width`: 테두리 두께를 지정합니다. px단위로 입력할 수도 있고, **thin, medium, thick** 등의 예약어도 있습니다.
```css
// 다양한 표현법. 빈 곳은 마주 보는 곳과 똑같이 한다.
#box1 {border-width: 2px;}  /* 전체 지정 */
#box1 {border-width: thick thin;} /* 위 아래가 thick 나머지가 thin*/
#box1 {border-width: 10px 5px 5px 10px;} /* 4군데 순서대로 지정*/
```
3. `border-color`: 테두리 색 지정
4. `border`: 테두리 스타일, 두께, 색상을 한꺼번에 표현 가능.
```css
h1 {
  /* 아래쪽 테두리, 3px, 회색 실선 한 큐에 표현*/
  border-bottom: 3px solid rgb(75, 70, 70) 
}
```
5. `border-radius`: 테두리 둥글둥글하게 만들어주기. 너비의 반, 혹은 50%로 지정하면 원 형태의 이미지가 됩니다. <br> `border-top-left-radius`, `border-bottom-right-radius`와 같은 표현으로 각 꼭지점을 따로 지정해줄 수도 있습니다.


### 3. 여백 조절
박스 끼리의 여백인 **마진**, 테두리와 내용 사이의 여백 **패딩**을 설정하는 속성들입니다.
1. `margin`: 위의 예시들과 같이 그냥 쓰면 4방향 전부에 적용되고, `margin-top`, `margin-left`등과 같이 쓸 수도 있습니다.
2. **margin으로 컨텐츠 가운데 정렬하기**: `margin-right`, `margin-left`를 auto로 설정해주면, 웹 브라우저는 알아서 전체 화면 너비에서 요소의 너빗값을 뺀 나머지 영역을 좌우 마진으로 계산해줍니다. 가운데로 정렬해 준다는 뜻입니다.
```css
/* 전체 너비를 600px로 설정해 준 다음*/
/* 마진을 위 아래는 20px, left right는 auto로 주어서 가운데 정렬*/
#container {
  background-color: #fff,
  width: 600px;
  margin: 20px auto;
  padding: 20px;
}
```
3. **마진 중첩 문제**: 위 아래로 마진이 겹칠 때 나타나는 문제입니다. 이 경우 **더 큰 마진 쪽으로 겹쳐지게 됩니다.** 예를 들어, 박스끼리 60px정도 떨어지기를 기대하고 마진을 30px, 30px로 둔 경우, 그냥 위 아래 박스 간격이 30px로 맞춰집니다. 오른쪽 왼쪽에는 나타나지 않습니다. 마진 중첩을 고려한 설계가 필요합니다.
4. **`padding`: 콘텐츠와 테두리의 여백을 설정합니다.**


### 4. 웹 문서 레이아웃 만들기
#### 1. disply 속성
배치 방법을 결정합니다. 블록 레벨 요소와 인라인 레벨 요소를 서로 바꿔서 사용할 수 있습니다. 주로 문서의 네비게이션을 만들면서 메뉴를 가로로 배치할 때 많이 사용합니다. 이미지를 표 형태로 배치할 때도 사용합니다. 
|종류|설명|
|:----:|:----:|
|block|인라인 레벨 요소를 블록 레벨 요소로 만들기|
|inline|블록 레벨 요소를 인라인 레벨 요소로 만들기|
|inline-block|인라인 레벨 요소와 블록 레벨 요소의 속성을 모두 가짐.|
|none|해당 요소 화면에 표시하지 않기|

수평 네비게이션 만들기 예시
```css
<style>
  * { box-sizing: border-box; }
  nav ul { list-style: none; }
  nav ul li {
    display: inline-block;
    padding: 20px;
    margin: 0 20px;
    border: 1px solid #222;
  }
</style>
```
```html
<nav>
  <ul>
    <li>menu 1</li>
    <li>menu 2</li>
    <li>menu 3</li>
  </ul>
</nav>
```
<style>
  * { box-sizing: border-box; }
  nav ul { list-style: none; }
  nav ul li {
    display: inline-block;
    padding: 20px;
    margin: 0 20px;
    border: 1px solid #222;
  }
</style>
<nav>
  <ul>
    <li>menu 1</li>
    <li>menu 2</li>
    <li>menu 3</li>
  </ul>
</nav>

2. `float`: 왼쪽이나 오른쪽으로 배치함. float 속성은 웹 요소를 문서 위에 떠 있게 만들어 줄 수 있습니다. `left`, `right`로 왼쪽 구석이나 오른쪽 구석에 이미지를 배치하고, 이미지를 둘러싸도록 텍스트를 배치하고 싶을 때 베스트입니다. `margin-right`, `margin-left`와 함께 이용해서 이미지를 배치하고, 글을 쓰는 방식으로 아름답게 표현합니다. 기본 마진과 패딩이 없습니다.
3. `clear`: float를 해제합니다. float를 한번 적용하면 계속 float 상태가 유지되기 때문에, 이를 해제해줍니다. (left, right는 매번 적용되진 않음.)

#### 2단, 3단 레이아웃 예시
```css
<style>
  #container {
  	width: 1200px;
  	margin: 20px auto;
  }
  #header {
  	width: 100%;
  	height: 120px;
  	background-color: #acacac;
  }
  #sidebar {
  	width: 300px;
  	height: 600px;
  	background-color: #e9e9e9;
  	float: left;
  }
  #container {
  	width: 900px;
  	height: 600px;
  	background-color: #f7f7f7;
  	float: left;
  }
  #footer {
  	width: 100%;
  	height: 100px;
  	background-color: #888888;
  	clear: left;
  }
</style>
```
**side bar와 container를 봐라** float left를 두 번 넣어줬으므로, 전체 넓이를 둘이서 나눠 가지게 된다. 3단 레이아웃도 그냥 컨테이너와 푸터에 하나만 추가되면 되겠죠?
```css
#right-sidebar {
  ...
  float: left;
  ...
}
```


### 5. 웹 요소의 위치 정하기
`position`으로 원하는 위치에 자유롭게 넣어봐요. 실수하기 쉬우니 주의.
기본적으로는 문서의 흐름에 맞게 배치하는 `static`으로 설정이 되어 있습니다.

|종류|설명|
|:----:|:----:|
|static|흐름에 맞춰 배치|
|relative|위칫값을 지정할 수 있다는 점을 제외하면 static과 같음|
|absolute|**relative값을 사용한 상위 요소를 기준으로** 위치를 지정해 배치|
|fixed|**브라우저 창을 기준**으로 배치. 스크롤 해도 소용없어.|

**absolute 주의!** absolute는 부모 요소와 상위 요소 중에서 relative을 사용한 요소를 찾아서, 해당 요소를 기준으로 위치를 결정합니다. **absolute를 사용하려면 부모 요소는 relative로 설정 해두어야 원하는 대로의 배치가 가능합니다.** 아래의 예시 참고

### 배경 위에 글자 표시하기 예시
```css
#contents {
 background:url("../images/bg.jpg") no-repeat;
 background-size:cover;
 width:800px;
 height:500px;
 margin:0 auto;
 position:relative;
}
h1 { 
  color:#fff; 
  font-size:120px;
  text-shadow: 2px 3px 0 #000;      
  position:absolute;
  right:100px;
  bottom:100px;
}
```
부모 요소 - 그림을 relative, 아래 글씨를 absolute로 두었습니다. 그림 위에 글씨 표시가 가능합니다.
