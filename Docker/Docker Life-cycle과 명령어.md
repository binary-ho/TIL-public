# 도커의 생명주기와 명령어
도커의 생명주기는 생성, 시작, 실행, 중지, 삭제로 이루어져있다. <br>
평범한 생명주기를 가지고 있고, 명령어와 생명주기의 관계는 아래 그림과 같다.

![docker lifecycle](https://user-images.githubusercontent.com/71186266/210172381-6ea0f72a-83b5-486d-8d71-50ebee66754c.png)


## 1. 컨테이너의 생성
## `docker create`, `docker start`
`docker run`은 `docker create <이미지>`와 `docker start <컨테이너 아이디/이름>`의 두개로 나뉘어진다. 

두 명령어의 차이를 이해하기 위해선, 이미지를 통해 컨테이너가 만들어지는 과정을 알아야 한다. (따로 글도 있다.) 컨테이너는 아래와 같은 2가지 과정을 통해 생성되는데 <br>
1. 도커 이미지에 있는 파일 스냅샷을 하드디스크에 옮긴다.
2. 이미지가 가진 실행 명령어를 실행한다.

두 명령어는 정확히 두 과정과 매칭된다. <br>
`docker create <이미지 이름>`은 도커 이미지의 파일 스냅샷을 컨테이너 하드디스크에 적재한다. <Br>
`docker start <컨테이너 아이디/이름>` 실행 명령어를 컨테이너에서 실행시킨다. <Br>

![docker start](https://user-images.githubusercontent.com/71186266/210172923-64b00a91-8904-453f-8da7-943c28431f28.png)

`docker create`의 결과로 해당 컨테이너의 id값 전체가 출력되었다. 이 id 값의 일부를 이용해 `-a` 옵션과 함께 `docker start`명령어를 수행할 수 있다. `-a`의 a는 `attach`를 의미한다.


## 2. 컨테이너 중지
## `docker stop` `docker kill`
컨테이너를 중지하는 명령어에는 `docker stop`과 `docker kill`이 있다. <br>

`docker stop <컨테이너 아이디/이름>`은 Gracefully 하게 중지 시킨다. 아주 '자비롭게' **그동안 하던 작업들을 완료한 다음 컨테이너를 중지한다.** <br>
`docker kill <컨테이너 아이디/이름>`은 stop과 달리 **그 자리에서 전부 중지 시켜버린다.** <br>

컨테이너가 중지되기 위해선 Container의 Main Process에 `SIGKILL`이라는 명령어가 날아가야 한다. <br>
`docker kill`의 경우 이 `SIGKILL`이 바로 날아가게 되는데, <br>
`docker stop`의 경우엔 `SIGTERM`이라는 term이 잠깐 생긴다. 이 term은 `Grace Period`라 불리는 정리 기간인데, 이 기간동안 작업들을 중지시킨 다음 `SIGKILL`이 날아간다. 

## 3. 컨테이너 삭제
## `docker rm <컨테이너 아이디/이름>`
**중지된 컨테이너만 삭제할 수 있다.** 일단 컨테이너를 중지한 다음, rm 명령어를 통해서 컨테이너를 삭제할 수 있다. <br>
컨테이너 삭제 명령어에는 아래와 같이 많은 종류가 있다. 
1. `docker rm <컨테이너 이름>`: **지정된 컨테이너 삭제**
2. `docker rm 'docker ps -a -q'`: **모든 컨테이너 삭제**
3. `docker rmi <Image id>`: 도커 **이미지를 삭제한다.**
4. `docker system prune`: **실행 상태가 아닌 컨테이너, 이미지, 네트워크를 한번에 모두 삭제한다! 편리!**


## Reference
- [따라하며 배우는 도커와 CI환경](https://www.inflearn.com/course/%EB%94%B0%EB%9D%BC%ED%95%98%EB%A9%B0-%EB%B0%B0%EC%9A%B0%EB%8A%94-%EB%8F%84%EC%BB%A4-ci/dashboard)
