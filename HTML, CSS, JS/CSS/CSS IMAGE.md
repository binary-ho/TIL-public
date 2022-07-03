# 9. 이미지와 그라데이션으로 배경 꾸미기
1. `background-color`: 배경에 색 넣기. **배경색은 상속되지 않는다**
2. `background-clip`: 배경색의 적용 범위를 조절한다.
```css
<style>
  #clip-border { background-clip: border-box; } /* 가장 외곽인 테두리까지 적용 (기본값) */
  #clip-padding { background-clip: padding-box; } /* 테두리를 뺀 패딩 범위까지 배경 지정 */
  #clip-content { background-clip: content-box; } /* 콘텐츠에만 배경 지정 */
</style>
```
3. **`background-image`: 배경 그림 넣기!!**
```css
{ bakcground-image: url('이미지 파일 경로') }
```
요소보다 이미지가 작으면, 바둑판처럼 무한으로 반복시켜버립니다. 무늬일 때는 편하겠네요.
4. **배경 이미지 반복 지정 `background-repeat`**:
- `repeat`: 기본, 가로 세로로 꽉 찰 때까지 반복
- `repeat-x`: 가로 반복
- `repeat-y`: 세로 반복
- `no-repeat`: 반복 X
5. `background-position`: **배경 이미지의 수평, 수직 위치 지정. 순서도 수평, 수직임.**
- background-position: <수평위치> <수직위치>
- 수평 위치: left | center | right | <백분율> | <길이 값>
- 수직 위치: top | center | bottom | <백분율> | <길이 값>
6. `background-origin`: **배경 이미지의 적용 범위를 조절합니다.** 패딩까지? 테두리 포함해서? 등의 적용 범위를 적용합니다. 
- `content-box`: **기본값! 박스 모델 내용 부분에만 이미지 표시**
- `padding-box`: 박스 모델에서 패딩까지 배경 이미지를 표시합니다.
- `border-box`: 박스 모델 테두리까지 배경 이미지 표시
7. `background-attachment`: **배경 이미지 고정.** 기본으로 `scroll`로 설정 되어있습니다. **`fixed`를 통해 배경 이미지를 고정시킬 수 있습니다.**
8. `background`: 또 모든 속성을 하나의 속성으로 묶을 수 있다.
9. `background-size`: 배경 화면 크기를 조절합니다. 배경을 가득 채울 때 많이 사용합니다.
- auto: 원래 이미지 크기 만큼 표시. 기본값
- contain: 요소 안에 배경이 다 들어올 수 있도록 확대-축소 합니다.
- cover: 배경 이미지로 요소를 모두 덮도록 이미지를 확대-축소합니다.
- `<크기>`: 이미지의 너비와 높이를 지정합니다. 값이 하나만 주어질 경우 너빗값으로 인식합니다. 
- `<백분율>`: 요소의 크기를 기준으로 백분율을 지정합니다. 

**bakcground 속성으로 아래와 같이 심플하게 나타내 주면 됩니다.**
```css
body {
    background: url('images/bg5.jpg') left top no-repeat fixed;
    background-size: cover;
  }
```

### 9.3 그라데이션
314p
1. 선형 그라데이션: `linear-gradient`
2. 원형 그라데이션: `radial-gradient`
3. 그라데이션 반복: `repeating-linear-gradient`, `repeating-radial-gradient`

