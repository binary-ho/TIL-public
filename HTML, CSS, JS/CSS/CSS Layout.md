# CSS Layout
## 1. Header & Navigation Bar
상단 메뉴 레이아웃. `<body>` 태그 안에 `<header>` 태그 만들고, `<nav>` 이용해서 네비게이션 바를 만들고, 안에 unordered list 맨들기. 
```html
<body>
  <div id="warp">
    <header>
      <a class="logo" href="#home">
      <img src="https://poiemaweb.com/img/logo.png" height="36px">
      </a>
      <nav>
        <ul class="nav-items">
          <li><a href="#home">Home3</a></li>
          <li><a href="#news">News</a></li>
          <li><a href="#contact">Contact</a></li>
          <li><a href="#about">About</a></li>
        </ul>
      </nav>
    </header>
    </div>
  </div>
</body>
```
CSS로 간지나게 바꿔준다.
```css
nav {
    float: right;
}
```
일단, `float`프로퍼티를 추가해서 navigation bar를 우측 정렬합니다.
```css
.logo {
    display: inline-block;
    height: 36px;
    margin: 12px 0 12px 25px;
}
.logo > img {height: 36px;}
```
logo 꾸며주기. 중요한건 logo image를 포함하는 a 태그의 height를 image와 같은 height로 맞춰주어야 합니다. a tag는 inline 요소이므로, margin을 정의하기 위해 `display: inline-block`을 설정해준 것입니다.

```css
.nav-items > li {
    display: inline-block;
}
.nav-items > li > a {
    line-height: 60px;
    padding: 0 30px;
    color: rgba(0, 0, 0, 0.4);
}
.nav-items > li > a:hover {
    color: rgba(0, 0, 0, 0.8);
}
```
1. 수직 정렬된 Nav 바를 수평 정렬하기: `<li>`는 block 요소이기 때문에, `display: inline-block`을 설정하여 inline 요소와 같이 가로로 정렬해 줍니다.
2. 수직 중앙 정렬해주기: `line-height`로 텍스트의 높이를 헤더 높이와 맞춰집니다. 그리고 텍스트 간의 간격을 적당하게 만들어 주기 위한, padding을 정의해 줍니다.
3. 마우스를 올렸을 때 텍스트 색상 변경을 위한 hover입니다.


## 2. Section & Aside
- **Section**: 콘텐츠의 영역
- **Aside**: 콘텐츠에 대한 Navigation item이나, 부가 정보 영역. 
- Section 영역은 다시 article 영역으로 구분할 수 있음. (큰 Section 틀 안에 여러개의 article 태그 넣기)
- 두 영역은 float 프로퍼티를 통해 수평 정렬하는 것이 국룰이다.
```html
<div id="content-wrap">
      <aside>
        <h1>Aside</h1>
        <ul>
          <li><a href="#" class="active">London</a></li>
          <li><a href="#">Paris</a></li>
          <li><a href="#">Tokyo</a></li>
          <li><a href="#">Newyork</a></li>
        </ul>
      </aside>
      <section>
        <article id="london">
          <h1>London</h1>
          <p>런던런던런던</p>
        </article>
        <article id="paris">
          <h1>Paris</h1>
          <p>패리스 인 더 레인 페리스 인 더 레인</p>
        </article>
        <article id="tokyo">
          <h1>토키요</h1>
          <p>근디와도쿄가?지금부터나쁜짓을할고고든</p>
        </article>
        <article id="newyork">
          <h1>NewYork</h1>
          <p>뉴요오오옥~ (뒤에 가사 모름)</p>
        </article>
      </section>
    </div>
```
```css
header {
    position: fixed;
    top: 0;
    ...
}
#warp {
    margin-top: 60px;
}
```
상단에 네이게이션 바를 고정해줍니다. 헤더 부분을 `fixed`로 만들어주고, 아래 내용물들이 헤더 안에 들어가지 않도록 헤더와 똑같은 높이만큼 `#warp`에 margin을 넣어준다.
```css 
/* clerfix */
#content-wrap:after {
    content: "";
    display: block;
    clear: both;
}
aside {
    /* float: left; */
    position: fixed;
    top: 60px;
    bottom: 0;
    width: 200px;
    padding-top: 25px;
    background-color: #333;
    /* fixed일 때는 %를 없애고 고정폭을 이용해야한다. */
    /* width: 20%; */
}
section {
  float: right;
  width: 80%;
}
```
이후, aside를 좌측에 정렬하고, 섹션을 우측에 정렬합니다.
```css
aside > ul {
    width: 200px;
}
aside > ul > li > a {
    display: block;
    color: #fff;
    padding: 10px 0 10px 20px;
}
aside > ul > li > a.active {
    background-color: #4CAF50; /* green */
}
aside > ul > li > a:hover:not(.active) {
    background-color: #555;
}
```
마우스로 눌렀을 때, 초록색으로 바꾸기, 마우스 올렸을 때 다른 색으로바꾸기..
```css
aside > h1 {
    padding: 20px 0 20px 20px;
    color: #fff;
}
section {
    float: right;
    /*width: 80%;*/
    /* aside width */
    margin-left: 200px;
}
article {
    margin: 10px;
    padding: 25px;
    background-color: white;
}
h1 { font-size: 1.8em; }
h1, h2, h3, h4, h5, h6, p {
    margin: 10px 5px;
}
```

## 3. footer
footer는 **absolute 프로퍼티**를 설정합니다. 고정되어 있을 필요가 있지만, 본문을 가리지 않아야 합니다. 그래서 fixed는 안 되고, 다른 요소가 먼저 위치를 점유하고 있어도 밀리지 않는 부유객체로 설정을 해 주어야 합니다.  (aside와 같은 요소들 보다는 위에 있어야하기 위함) 그래서 absolute를 씁니다.

```html
    </div>
    <footer> Copyright 어쩌고 저쩌고</footer>
</body>
```
맨 아래에 둡니다. div 아래 (당연)
```css
footer {
    position: absolute;
    height: 60px;
    width: 100%;
    padding: 0 25px;
    line-height: 60px;
    color: #8a8c8f;
    border-top: 1px solid #dee5e7;
    background-color: #f2f2f2;
}
```
부유객체를 만들기 위해 (본문은 안 가리는데, Aside 보다는 앞에 있어야함.) `position: absolute;`

# Reference
(https://poiemaweb.com/css3-layout)
