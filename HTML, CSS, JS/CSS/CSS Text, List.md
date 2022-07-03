# 2. CSS 텍스트 스타일
너무 내용이 많기 때문에, 모두 기록하고 암기하려고 하기 보다는 중요한 것만 적기로 하겠습니다.

### 2.1 글꼴
1. **font-family**: 글꼴을 설정해줍니다. **사용자 시스템의 글꼴을 이용합니다.** 사용자의 시스템에 해당 글꼴이 설치되어있지 않을 수도 있기 때문에, `,`를 간격으로 여러가지 글꼴을 설정해 두는 편입니다.
2. **font-size**: 폰트 사이즈입니다. `px`, `pt` 등의 절대 단위로 지정할 수 있습니다만, **모바일 기기까지 고려함이 필수기 때문에, 상대 단위인 `em`이나, `rem`을 많이 쓰는 편입니다.** 1em은 16px, 12pt입니다.
3. **font-style**: 이탤릭체로 표시 italic
4. **font-weight**: 글자 굵기 지정 

### 2.2 웹 폰트
font-family 속성으로 글꼴을 지정하면, 사용자 시스템의 글꼴을 사용하기 때문에, 문제가 될 수 있습니다. **이럴때 사용하는 것이 web font입니다.** 일단 사용자의 로컬에 해당 글꼴이 있는지 확인하고, 직접 다운 받아 만들어줍니다. 아래의 'Ostrich'라는 웹 폰트 적용 예시를 참고합니다.  TTF 포맷은 WOFF 포맷 보다 용량이 크기 때문에 가장 나중에 확인합니다.
```css
<style>
  @font-face {
    font-family: 'Ostrich'
    src: local('Ostrich Sans'),
    url('fonts/ostrich-sans-bold.woff') format('woff'),
    url('fonts/ostrich-sans-bold.ttf') format('truetype'),
    url('fonts/ostrich-sans-bold.svg') format('svg');
  }
  .wfont {
    font-family: 'Ostrich', sans-serif; /* 웹 폰트 지정 */
  }
  p {
    font-size: 30px;
  }
</style>
```

`@font-face`부분에서 웹 폰트를 만들어 줍니다. `font-family`를 통해 폰트의 이름을 정해주고, 일단 로컬에 있는지 부터 확인해줍니아. 없다면 용량이 작은 woff부터 시작해서 확인 작업을 합니다.

### 구글 폰트 사용하기
1. fonts.google.com에서 폰트 찾기.
2. `+Seclect this style` 버튼을 누르기
3. `@import`를 클릭하여 속성 보기.
4. 속성 내의 `@import url`어쩌고를 `<style>`태그 바로 아래에 붙여넣고, 
5. `font-family` 부분은 해당 웹 폰트를 사용할 요소에 붙여 넣습니다.  
```css
<style>
  @import url('https://fonts.googleapis.com/css2?family=Nanum+Pen+Script&dis-play=swap'); /* 4번 내용 */

  h1 {
    font-size: 60px;
    font-weight: bold;
    font-family: 'Nanum Pen Script', cursive; /* 5번 내용 */
  }
</style>
```

### 2.3 텍스트
1. `color`: 글자색
2. `<text-align>`: 텍스트 정렬 **left, right 대신 start, end를 써야 한다.**
3. `line-height`: 줄 간격 조절하기, 단위를 안 붙이면 글자 크기의 배수로 띄어지고, 백분율도 비슷하게 글자 크기를 기준으로 계산합니다.
4. `text-decoration`: 텍스트에 줄긋기. **"text-decoration:underline"**, **"text-decoration:overline"**, **"text-decoration:line-through"**
5. `text-shadow`: 텍스트에 그림자를 줍니다. 제목에 살짝 줍시다.
6. `text-transform`: 텍스트의 대소 문자를 변환한다.
7. `letter-spacing`: 글자와 글자 사이 간격 조절
8. `word-spacing`: 단어와 단어 사이의 간격 조절

### 2.4 리스트
1. **불릿 모양과 번호 스타일을 지정하는** `list-style-type`: 이거 좋아 정말 좋아. 불릿의 모양들을 조절할 수 있습니다. 그리고 순서 목록을 숫자로 할지, 알파벳으로 할지 등을 지정할 수 있습니다. `none`으로 작성하면 없앨 수도 있습니다.
2. `list-style-image`: 불릿 대신 이미지를 사용합니다. 작으면 좋습니다. (당연)
3. `list-style-position`: 목록 들여쓰기. 기본값은 `outside`입니다. `inside`로 지정해주면 들여씁니다.
```css
.inside {list-style-position: inside;}
```
4. `list-style`: 목록 속성 한꺼번에 표시하기 위에서 언급한 모든 속성들을 그냥 여기에 다 넣으면 알아서 처리해줍니다.

### 2.5 표
1. `caption-side`: 표의 제목의 위치를 옮깁니다.
2. `border`: 표에 테두리 그리기
3. `border-spacting`: 셀 사이의 여백 지정
4. `border-collapse`: 표와 셀의 테두리를 합쳐줍니다.
