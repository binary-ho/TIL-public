Chapter 1. Layout 요약
========


### 1.1 layout_width, layout_height
- wrap_content: 뷰에 들어있는 내용물의 크기에 자동 맞춤.
- match parent: 뷰를 담고 있는 뷰 그룹의 여유 공간 채움.
- 숫자: 숫자로 크기 지정. dp나 px의 단위가 반드시 있어야함.


### 1.2 크기 표시 단위
- dp, dip (density independent pixel): **뷰의 크기를 조절 할 때 많이 씀. 화면 크기가 달라져도 비율 맞춰줌!** 160dpi기준을 알아서 비율 맞춰줌
- sp, sip (scale independent pixel): 얘도 비슷한데 얘는 텍스트 뷰나, 텍스트 크기용임. 사용자 단말기에서의 글꼴이나 폰트 변화에 맞춰 크기 바꿔줌.

 
### 1.3 resource 이름 규칙.
뭐 예를 들어 app/src/main/res/drawable 폴더에 이미지를 넣는다 할 때도, 
소문자, 숫자, _기호만 들어갈 수 있음. 첫 글자는 숫자가 될 수 없음. 이미지도! 안 돼. 걍 파일 전부 안 돼 ㅇㅋ? 심지어 확장자도 소문자여야함.
배경으로서 불러 올 때의 예시: android:background="@drawable/house" 이런식. 확장자 이름은 빼.
<br/>

### 1.4 레이아웃 종류
    
![image](https://user-images.githubusercontent.com/71186266/167997951-62fdd61c-4e8f-4866-8531-b998776e90e7.png)
<br/>

### 1.5 레이아웃 필수 속성 - 레이아웃은 필수 속성이 있음.
예를 들어 리니어 레이아웃은 한 쪽 방향으로만 뷰가 쌓이므로, 어느 방향으로 배치할 것인지를 지정하는 orientation 속성이 필수임. 다른 애들은 layout_width, height등이 필요.
파라미터도 설정 해 줘라 parms → width, height 정해주는 거
<br/>

### 1.6 색: ARGB로 표현, 실제 표현은 #AARRGGBB식으로 표현한다.
진한 빨강은 #ffff0000 그린은 #ff00ff00 이런식 반투명 빨강은 #88ff0000이겠지?
<br/>

### 1.7 앱 메인 화면인 MainActivity.java는 자동으로 만들어지고, 이는 AndroidManifest.xml 안에 자동으로 등록됨. 그러니까 메인을 바꿔주고 싶으면, manifests폴더 뒤져서 코드 수정해주면 됨.
<br/>

### 1.8 Layout 만드는 Code
**오브젝트가 수십 수백개가 될 때는 xml로 힘들게 만들기 보다는 java로 코드를 짜 주는게 좋다!     
[Layout Code 바로 가기](https://github.com/binary-ho/TIL-public/blob/main/Android/%5B%EC%B1%85%5D%20Do%20it%20%EC%95%88%EB%93%9C%EB%A1%9C%EC%9D%B4%EB%93%9C%20%EC%95%B1%20%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%B0%8D/1.%20Layout/Layout%20Code.md) -> 여러번 읽어 보자.**


### 1.9 Margin과 Padding
Margin - 위젯 Cell 테두리와 View 사이,
Padding - View 테두리와 content 사이 거리

![image](https://user-images.githubusercontent.com/71186266/167998793-76ac1673-772d-4581-9aec-1683c50f7f33.png)


### 1.10 [Frame Layout](https://github.com/binary-ho/TIL-public/blob/main/Android/%5B%EC%B1%85%5D%20Do%20it%20%EC%95%88%EB%93%9C%EB%A1%9C%EC%9D%B4%EB%93%9C%20%EC%95%B1%20%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%B0%8D/1.%20Layout/Frame%20View.md)

    
### 1.11 [ScrollView](https://github.com/binary-ho/TIL-public/blob/main/Android/%5B%EC%B1%85%5D%20Do%20it%20%EC%95%88%EB%93%9C%EB%A1%9C%EC%9D%B4%EB%93%9C%20%EC%95%B1%20%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%B0%8D/1.%20Layout/Scroll%20View.md)  -> 파라미터를 항상 설정 해줘야함에 주의할 것.
