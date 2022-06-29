# HTML FORM!
**사용자가 웹사이트로 정보를 보낼 수 있는 요소를 모두 폼이라고 부릅니다.** 

## 1. 폼 만들기 `<form>`
`<form [속성="속성값"]>여러 폼 요소</form>` 

|종류|설명|
|:----:|:----:|
|method|사용자가 입력한 정보를 서버쪽에 어떻게 넘길지를 결정 <br> - get: 길이 제한됨, 주소 표시줄에 입력 내용 드러남 <br> - post: 길이 제한 X, 입력 내용 안 드러남|
|name|js로 제어할 때 쓸 이름 지정|
|action|`<form>` 태그 안의 내용을 처리해줄 서버 프로그램 지정|
|target|action 속성에서 지정한 스크립트 파일을 다른 위치에서 열도록함|
|autocomplete|기본적으로 on 되어있으므로, 비번 같은 경우에는 "off"로 설정해줍니다.|

## 2. 폼 요소를 그룹으로 묶기 `<fieldset>`, `<legend>`
폼 안에서 구역을 나눌 때 `<fieldset>`을 사용합니다. 그리고 이름은 `<legend>`로 붙여줍니다

```html
// 기본 형태
<fieldset [속성="속성값"]> </fieldset>


// legend
<fieldset>
  <legend>그루비룸</legend>
</fieldset>
```
// 기본
<fieldset> </fieldset>
<br>
// legend
<fieldset>
  <legend>그루비룸</legend>
</fieldset>

## 3. 폼 요소에 레이블 붙이기 `<label>`
`<lable>` 태그는 `<input>` 태그와 같은 폼 요소에 레이블을 붙일 때 사용합니다. 
1. 태그 안에 폼 요소 넣기
2. `<lable>` 태그와 폼 요소를 따로 사용, `<lable>`의 **for** 속성과 폼 요소의 **id** 속성을 이용해 연결하기 (폼 요소의 id 속성값을 `<lable>`의 for에게 알려준다.)


```html
// 1. 태그 안에 폼 요소 넣기
<label> 레이블명 <input></label>
<label> 아이디<input type="text"></label>

// 2. 폼 요소의 id 속성값을 <label>의 for에게 알려주기
<label for="id명">레이블명<input id="id명"></label>

<label for="user-id">아이디</label>
<input type="text" id="user-id">

```
// 1. 태그 안에 폼 요소 넣기
<label> 레이블명 <input></label>
<label> 아이디<input type="text"></label>


// 2. 폼 요소의 id 속성값을 `<label>`의 for에게 알려주기
<label for="id명">레이블명<input id="id명"></label>

<label for="user-id">아이디</label>
<input type="text" id="user-id">


## 4. 사용자 입력 받기 `<input>`
로그인의 id칸, 검색창, 로그인 버튼 등 **사용자가 입력할 부분들은 주로 `<input>` 태그를 이용하고, 모두 모두 form입니다.** 


<label> 1. text, password, serch, url, email, tel -> <input type="text"></label>
<label> 2. checkbox <input type="checkbox"></label>
<label> 3. radio <input type="radio"></label>
<label> 4. number <input type="number"></label>
<label> 5. range <input type="range"></label>
<label> 6. date <input type="date"></label>
<label> 7. month <input type="month"></label>
<label> 8. week <input type="week"></label>
<label> 9. time <input type="time"></label>
<label> 10. datetime (국제표준시, 나머지는 전부 사용자 지역 기준) <input type="datetime"></label>
<label> 11. datetime-local <input type="datetime-local"></label>
<label> 12. submit <input type="submit"></label>
<label> 13. reset <input type="reset"></label>
<label> 14. image (그림 눌러서 submit) <input type="image"></label>
<label> 15. button <input type="button"></label>
<label> 16. file <input type="file"></label>
17. hidden - 사용자에게는 보이지 않지만 서버로 넘겨주는 값이 있는 필드를 만듬


## 5. 필드 타입별 추가 속성
바로 위에서 보여준 input의 다양한 타입별로 쓰이는 속성들을 정리
### 5.1 text, password - 텍스트와 비밀번호
password만 *이나, 다른걸로 입력 내용 가려주는 점이 다름 
##### [주요속성]
1. **size**: 텍스트나 비밀번호의 필드 길이 지정하기. 필드 길이이기 때문에 실제로 더 길어도 size만큼만 나오게 하는 것.
2. **value**: 텍스트 필드에 미리 적어 놓는 내용. password에서는 안 씀.
<label> ex) text <input type="text" value="value"></label>

3. **maxlength: 필드에 입력할 수 있는 최대 문자의 수 지정.** size와의 차이를 이해해라. size는 보여지는 길이고, maxlength는 적을 수 있는 실제 글자수다.

### 5.2 serch, url, email, tel - 다양한 용도에 맞게 입력해요!
HTML5 이전에는 입력한 값이 어떤 값인지, JS를 통해 직접 알아내야 했지만, 5에서 새로 도입됐다. 실제 지역마다 양식이 다른 **tel 외에는 자동으로 형식이 맞는지 확인해준다.** 여기까지만 있으면, 그저 그런 기능인데, 모바일 페이지에서 이 값들을 이용하면, 키보드도 각 값에 맞게 맞추어서 나오고, tel은 바로 전화를 걸 수도 있게 해준다. **모바일에서는 꽤나 좋은 기능**

### 5.3 checkbox, radio
- 여러개 중 하나 선택: **radio**
- 2개 이상 선택: **checkbox**

1. value: 선택한 버튼을 서버에 알릴때 넘길 값 지정. 필수 속성이며, 영문이거나 숫자임.
2. checked: 미리 체크해두고 싶을 때 쓰는 속성

```html
<fieldset>
  <legend>상품 선택</legend>
  <p><b>주문할 상품을 선택해 주세요.</b></p>
  <label><input type="checkbox" value="g_3">선물용 3kg</label>
  <label><input type="checkbox" value="g_5">선물용 5kg</label>
  <label><input type="checkbox" value="f_3">가정용 3kg</label>
  <label><input type="checkbox" value="f_5">가정용 5kg</label>

  <p><b>포장 선택</b></p>
  <label><input type="radio" name="gift" value="yes">선물 포장</label>
  <label><input type="radio" name="gift" value="no">선물 포장 안 함</label>
</fieldset>
```

<fieldset>
  <legend>상품 선택</legend>
  <p><b>주문할 상품을 선택해 주세요.</b></p>
  <label><input type="checkbox" value="g_3">선물용 3kg</label>
  <label><input type="checkbox" value="g_5">선물용 5kg</label>
  <label><input type="checkbox" value="f_3">가정용 3kg</label>
  <label><input type="checkbox" value="f_5">가정용 5kg</label>

  <p><b>포장 선택</b></p>
  <label><input type="radio" name="gift" value="yes">선물 포장</label>
  <label><input type="radio" name="gift" value="no">선물 포장 안 함</label>
</fieldset>

아래 있는 radio는 여러개 중 하나만 고를 수 있다. **그 포인트는 input 속성의 name에 있다.** <br> **radio는 name을 같게 해주면, 같은 이름끼리는 딱 하나밖에 고르지 못 한다.**

### 5.4 number, range
1. min, max: 최대-최소값 지정. **기본은 0, 100**
2. step: 숫자 간격 지정 가능. 기본 1
3. value: 필드 초깃값
### 5.5 data, month, week
### 5.6 time, datetime, datetime-local
### 5.7 submit, reset
전송 버튼입니다. submit은 폼에 입력한 정보를 서버로 전송합니다. **submit 버튼으로 전송된 정보는 `<form>`태그의 action 속성에서 지정한 폼 처리 프로그램에 넘겨집니다.** value 속성으로 버튼에 표시할 내용을 지정합니다.

```html
<div>
  <input type="submit" value="주문하기">
  <input type="reset" value="취소하기">
</div>
```

<div>
  <input type="submit" value="주문하기">
  <input type="reset" value="취소하기">
</div>

사용자가 submit 버튼을 누르면, 입력한 내용이 서버로 넘겨집니다. `<form>` 태그의 action에 적힌 order.php와 같은 링크에서 처리됩니다. (`<form>`태그에 action으로 연결된 링크) 취소하기는 폼에 입력한 내용을 모두 초기화 합니다. 

### 5.8 image (이미지 버튼)
```html
<input type="image" src="이미지 경로" alt="대체 택스트">
```
<input type="image" src="이미지 경로" alt="대체 택스트">

### 5.9 button
주로 버튼을 클릭해서 javascript를 실행할 때 사용합니다. value 속성으로 버튼에 표시할 내용을 지정합니다. 아래는 자바스크립트의 `window.open()` 함수를 실행하는 예시입니다.
```html
<form>
  <input type="button" value="공지 창 열기" onclick="window.open('notice.html')">
</form>
```
### 5.10 file
### 5.11 hidden
사용자에게 굳이 보여 줄 필요는 없지만, 관리자가 알아야 하는 정보는 히든 필드로 입력합니다. 그래서 이걸 어디에 쓰지? 이러한 입력 필드는 업데이트 되어야 하는 데이터베이스의 레코드를 저장하거나, 고유한 보안 토큰 등을 서버로 보낼 때 주로 사용됩니다.
```html
<input type="hidden" value="사이트를 통한 직접 로그인">
<label>아이디: <input type="text" id="user_id" size="10"></label>
<label>비밀번호: <input type="password" id="user_pw" size="10"></label>
<input type="submit" value="로그인">
```
<input type="hidden" value="사이트를 통한 직접 로그인">
<label>아이디: <input type="text" id="user_id" size="10"></label>
<label>비밀번호: <input type="password" id="user_pw" size="10"></label>
<input type="submit" value="로그인">


# 6. `<input>` 태그의 주요 속성
HTML5에서 폼 태그는 강력해졌습니다. <br>
그 강력하고 아름다운 기능들을 만나보자.
1. **autofocus**: 페이지를 불러오자마자 마스트 포인터를 표시한다. <br>
`<input type=텍스트-입력-필드 autofocus required>`
2. **placeholder**: 입력란에 힌트를 표시해줍니다.
3. **readonly**: 해당 필드를 읽기 전용으로 만들어줍니다.
4. **required**: 필수 입력 필드로 만들어줍니다.

# 7. 그 외의 태그
### 7.1 `<textarea>` 여러 줄을 입력해요.
- cols: 너비 지정
- rows: 세로 길이를 줄 단위로 지정
```html
<label for="memo">메모</label>
<textarea id="memo" cols="40" rows="4"></textarea>
```

<label for="memo">메모</label>
<textarea id="memo" cols="40" rows="4"></textarea>

### 7.2 드롭다운 `<select>`, `<option>`
- **select**: size, multiple 속성이 있다
- **option**: value, selected은 중요! <br>
value는 서버로 넘겨줄 값이고, selected는 기본으로 보일 항목임
```html
<label for="prod1">상품선택</label>
<select id="prod1">
  <option value="special_3" selected>선물용 3kg</option>
  <option value="special_10" selected>선물용 10kg</option>
  <option value="family_3" selected>가정용 3kg</option>
  <option value="family_10" selected>가정용 10kg</option>
</select>
```
<label for="prod1">상품선택</label>
<select id="prod1">
  <option value="special_3" selected>선물용 3kg</option>
  <option value="special_10">선물용 10kg</option>
  <option value="family_3">가정용 3kg</option>
  <option value="family_10">가정용 10kg</option>
</select>

### 7.3 데이터 목록 `<datalist>`, `<option>` 태그
텍스트 필드에 미리 만들어 놓은 값중에 선택을 가능하게 해줌.
```html
// 기본형
<input type="text" list="데이터 목록 id">
<datalist id="데이터 목록 id">
  <option value="서버로 넘길 값 1">선택 옵션 1</option>
  <option value="서버로 넘길 값 2">선택 옵션 2</option>
</datalist>

<label for="prod2">포장여부</label>
<input type="text" id="prod2" list="pack">
<datalist id="pack">
  <option value="package">선물 포장</option>
  <option value="no_package">포장 안 함</option>
</datalist>
```


### 7.4 Button 버튼 태그
button type은 진짜 그냥 버튼이다..
```html
<button type="submit">Submit</button>
<button type="reset">Reset</button>
<button type="button">Button</button>
```

<button type="submit">Submit</button>
<button type="reset">Reset</button>
<button type="button">Button</button>
