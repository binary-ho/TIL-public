# Prompt와 뒤로가기 제어

Prompt는 react-router-dom 의 API로 저희가 자주 사용하는 history와 함께 v6 부터는 지원이 종료된 API입니다.

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/2500c59e-2d0f-40c4-9309-d349c161971d/Untitled.png)

when의 값이 ture일 때, 뒤로가기가 눌리는 경우 페이지 이동을 막습니다. 

단순히 뒤로가기를 막으며, 페이지 이동을 막는 것은 아닙니다.

이후 massage에 있는 내용을 실행합니다.

message의 결과가 true일 경우 페이지가 이동되고, false일 경우 현재 페이지에 그대로 있습니다.

# handlePrompt

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/005c7420-6cbc-4622-a38f-f9ed2133ade9/Untitled.png)

handlePrompt를 이용해 모달을 켜 주고, false를 반환합니다.

모달에서 누르는 버튼에 따라 뒤로가기 여부를 결정할 예정이므로

일단 false를 반환하도록 해 주었습니다.

# ConfirmButtonModal

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/7e342b77-5dff-4ea7-8cac-7b8380ae00e7/Untitled.png)

모달에 예 버튼을 눌렀을 때와 아니오 버튼을 눌렀을 때 실행할 내용들을 넣어줄 수 있습니다.

(메서드로 뺐으면 더 이뻤겠네요.)

그림에선 Yes를 누르는 경우 모달창을 끌 뿐만 아니라, isBlocking 값도 false로 만들어줍니다.

만약 isBlocking 값을 true로 남겨두는 경우 페이지가 이동되지 않으며, 모달 창이 계속 다시 뜹니다.

이후 history.back();을 이용하여 여기서 직접 이전 페이지로 보내줍니다.

No 버튼을 누르는 경우 단순히 모달만을 종료합니다.

# ConfirmButtonModal

![prompt 구현.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/9ecfa7eb-d094-4c48-b982-5327e373cb4f/prompt_%EA%B5%AC%ED%98%84.png)

ConfirmButtonModal은 위와 같이 예 아니오 버튼이 있는 모달입니다.

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/49c7904e-2bae-4637-ae55-45d0b906b331/Untitled.png)

위와 같이 내부적으로 handleClickYesButton과 handleClickNoButton을 받아 

예 버튼을 눌렀을 때와, 아니오 버튼을 눌렀을 때 일어날 일을 정해줄 수 있습니다.
