# Java 실행 명령어와 cannot find symbol 에러
java 파일을 컴파일하고 실행할 때, `java Main.java`와 같은 명령어로 실행할 수 있습니다. 그런데 이번에 자바 공부를 하며 파일을 실행시키는 과정에서 아래와 같은 `error: cannot find symbol`에러를 마주했습니다.



![java symbol](https://user-images.githubusercontent.com/71186266/175859367-e414c37b-8c56-4ff8-bf00-ef2789b839d6.png)

아마도 실행시킨 파일인 `TcpIpClientSeparate.java`에서 이용한 Sender Receiver class가 같은 패키지 내의 `TcpIpServerSeparate.java`라는 다른 파일에 선언 되어 있는데, 이걸 불러오지 못 해서 발생하는 문제인 것 같습니다. <br> 
해당 에러를 해결한 내용들을 공유하기 위해 글을 써 본다. 다른 이유로 해당 에러를 마주한 사람은 굳이 읽을 필요가 없습니다.
<br>

## error: cannot find symbol
첫 번째로 해당 에러가 왜 발생하는지를 알아보았다. 일단 에러가 발생하면, 당연히 첫 번째로는 에러 문구를 읽어보고, 왜 발생한 에러인지 부터 파악해야합니다.
<br><br>
이 에러를 가장 많이 마주하는 이유는 단순히 타이핑 오류라고 합니다. 단순히 이름을 잘못 적은 경우에 많이 마주하는 에러라고 하는데.. 사실 IDE가 너무나도 잘 되어있는 지금 애노테이션 없이 오버라이딩을 하는 경우가 아니라면 오타로 인해 해당 오류를 마주하는 사람은 없을 것 같습니다..
<br><br>
아마도 저와 같은 이유로 해당 에러를 마주하는 사람이 많을 것 같은데 **서로 연관된 파일들을 각각 실행해버린 상황**에서 해당 에러를 마주하는 것이 대부분일 것이라고 생각합니다. 

<br> <br>

제가 실행시킨 `TcpIpClientSeparate.java`의 Sender와 Receiver 클래스는 파일 `TcpIpServerSeparate.java`에 선언되어 있습니다. `java`명령어는 **단순 실행 명령어입니다.** 프로젝트를 통으로 빌드하는게 아니고 파일 하나만 실행한다면, 당연히 같은 패키지 내에 있다고 해서 단순 실행 명령어가 알아서 연관 파일들까지 전부 실행 시키지는 않는 것입니다. 그래서 **class 파일을 만들어 주는 컴파일 명령어인 `javac`를 사용해 보았습니다.**

<br> <br>
`javac`명령어로 두 파일을 함께 컴파일 해준다면, 서로 연관을 지어줄 수 있다. 아래 사진의 가장 아래쪽 명령어와 같이 입력 해주면 됩니다.

![화면 캡처 2022-06-26 090844](https://user-images.githubusercontent.com/71186266/175861789-ba9fa74e-2a2a-459f-ae0d-6aa29f903e58.png)

**`javac TcpIpClientSeparate.java TcpIpServerSeparate.java`을 입력해서 성공적으로 두 파일을 함께 클래스 파일로 컴파일 해줄 수 있었습니다.** 아까 발생했던 cannot find symbol error는 이제 발생하지 않았습니다. <br> 바로 위의 `javac TcpIpClientSeparate.java` 명령어는 따로 컴파일 하면 안 된다는 것을 보여주기 위해 함께 캡쳐해 보았습니다. **연관된 파일들을 모두 함께 컴파일 해주는 것이 포인트입니다.**


## 클래스 파일 실행
이제 클래스 파일을 실행해 봅시다. 보통의 1개 파일짜리 클래스 파일이라면, `java TcpIpClientSeparate`와 같이 실행하면 되겠지만, **패키지 내의 여러 파일들을 연관시켜 컴파일 해주는 경우에는 다릅니다.** 실행 방법을 한줄 요약하면, `명령어 실행 경로에서 패키지 외부까지 나가서 패키지 이름과 함께 실행한다.`입니다. 위의 그림을 다시 보면, 명령어를 입력하는 경로에 패키지명인 `com.company`가 포함되어 있습니다.

![화면 캡처 2022-06-26 090844](https://user-images.githubusercontent.com/71186266/175861789-ba9fa74e-2a2a-459f-ae0d-6aa29f903e58.png)

위의 그림과 같은 위치에서 실행하려고 시도하면 계속해서 실패하게 됩니다.
![class 파일 실행 위치](https://user-images.githubusercontent.com/71186266/175863960-55962f74-ca00-44d8-bc51-a30d0baa7fc0.png)

바로 위의 그림에서 첫 번째, 두 번째 명령어와 같이 말이죠.. <br>

이 밖으로 나와야 하기 때문에, `cd ..`을 두 번 입력해서 나와줍니다. 이후 **패키지 명을 포함해서 실행해줍니다.** 위의 그림의 맨 아래 명령어와 같이 `java com.company.TcpIpServerSeparate` 명령어를 입력해 주는 것입니다. 그러면 아래와 같이 정상적으로 실행이 가능합니다.

![done](https://user-images.githubusercontent.com/71186266/175864149-7eb7c0ec-d58b-4ec8-9e24-895e33d6ed0a.png)

지금까지 연관된 자바 파일들을 cannot symbol error 없이 컴파일 하고 실행하는 방법을 소개하였습니다. 읽어주셔서 감사합니다. 

## 참고
https://kirkim.github.io/java/2021/05/12/java_compile.html
https://velog.io/@solar/Java-%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8-%ED%84%B0%EB%AF%B8%EB%84%90%EC%97%90%EC%84%9C-javac%EB%A1%9C-%EC%BB%B4%ED%8C%8C%EC%9D%BC-%ED%9B%84-%EC%8B%A4%ED%96%89-%EA%B3%BC%EC%A0%95%EC%97%90%EC%84%9C-%EB%B0%9C%EC%83%9D%ED%95%9C-%EC%98%A4%EB%A5%98-%ED%95%B4%EA%B2%B0
https://zincod.tistory.com/139
