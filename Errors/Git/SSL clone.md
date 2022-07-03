# SSH 방식으로 Repository를 clone하는 과정에서 많은 에러가 발생했다. <br>
BitBucket에서 private repository를 SSH 방식으로 clone해오는 과정에서 많은 에러가 발생했다. <br>
계속해서 **Permission deny** 에러가 발생했는데, 공부해본 결과 대략 두 가지의 이유로 발생하는 문제였다.
1. clone 해오는 BitBucket 사이트에 내 public SSH key가 제대로 등록이 되어있지 않다.
2. 로컬머신의 private key를 관리하는 SSH Agent가 load된 SSH key identity file (private key를 저장한 file)을 가지고 있지 않은 경우
첫 번째는 아주 초보적인 단계기 때문에 언급하지 않겠다. (그냥 로컬에서 제대로 키를 만들고, 잘 등록해주기만 하면 된다.) <br>
두 번째는 처음에 이해도 잘 가지 않았는데, 내 로컬 머신의 private key를 관리하는 어떤 Agent가 있고, 해당 에이전트가 내가 생성한 SSH 키 파일을 가지고 있지 않다는 것이 요다. 
(Agent란 웹 요청을 만들어주는 클라이언트 어플리케이션) <br> <br>

해결 방법은 SSH-Agent를 킨 다음. ssh add 명령어를 이용해 해당 파일의 존재를 알려주기만 하면 된다. <br> 
정리하고 보니 너무 허무하지만, 사장님과 개발 팀장님 앞에서 빠르게 해결하려다 보니, 꽤나 머리아픈 일이였다. <br>
자세한 설명은 아래 블로그에서 볼 수 있다. 정말 많은 블로그를 참고했지만 아래의 블로그에서 제시한 방법이 먹혀들었다. 무한한 감사를 보낸다..

https://beagle-dev.tistory.com/185
