
# AWS 인스턴스 만들기
AWS 인스턴스를 만들며 중요했던 것들을 기록합니다.
## 1. 보안 그룹 규칙!
매우 중요한 부분이다. 내 서버를 다른 사람이 쓸 수 있으면 어떻게 될까? 어떻게 되긴 나의 작은 서버에서 바로 신나게 코인을 채굴할 것이다. <br>
1. **SSH 유형 포트 22**: AWS EC2에 터미널로 접속할 때를 이야기함. pem키가 없으면 접속이 안 되니 소스를 전체 오픈으로 설정으로 하는 경우가 있는데, 그런 식으로 해두면 실수로 pem 키가 노출되는 경우 서버에서 가상화폐가 채굴되는 등의 끔찍한 일이 벌어질 수가 있다!! 그러니까 소스를 내 IP로 해두고 (접속한 장소의 IP 자동 지정) - 집 외의 다른 장소에서 접속할 때는, 해당 장소의 IP를 다시 SSH 규칙에 추가하는 것이 안전하다.
2. **사용자 지정 TCP 8080포트**: 내 스프링 프로젝트 기본 포트를 설정해준 것이다. 소스를 전체 오픈으로 해 두었는데 `0.0.0.0/0`, `::/0` 8080 포트를 여는 것은 위험한 일이 아니라 괜찮다.

## 2. 키 페어 생성
키 페어를 생성합니다. 일종의 마스터키이기 때문에, 절대 노출해서는 안 됩니다. RSA와 ED25519 방식이 있고, 후자가 훨씬 나은 방식입니다만. 처음 만들어 보는 것이기 때문에 RSA를 선택해보겠습니다.


## 3. 인스턴스 고정 IP 할당
**인스턴스도 결국 하나의 서버입니다.** 때문에 IP가 존재하는데, 인스턴스를 생성할 때 뿐만 아니라, 돈을 아끼기 위해 중지하고 다시 시작하는 경우에도 새 IP가 할당됩니다. 매번 접속 IP가 변경되면 굉장히 번거로우니, 고정 IP를 할당하는 것이 편합니다.

### 3.1 EIP 할당
AWS의 고정 IP를 Elastic IP라고 부릅니다. `탄력적 IP` 메뉴에서 주소 할당 이후, 내 인스턴스랑 연결해 주면 됩니다. <br> <br>

주의 할 점이 하나 있습니다. Elastic IP는 할당 이후, 인스턴스와 연결해주지 않을 경우 비용이 발생합니다. 그래서, Elastic IP가 두개일 경우를 조심해야합니다. EIP를 새로 하나 만들어서 기존 EIP가 연결되어 있는 인스턴스에 이어주는 경우 기존의 EIP가 붕 뜨게 되겠지요? 이런 경우 남게된 EIP에 요금이 부과될 수 있습니다.


## 4. 접속
Windows에서는 그냥 SSH로 접속하기에는 불편함이 많습니다. 그래서 **putty**와 **puttygen**을 이용하겠습니다. putty는 평소에도 학교 리눅스 서버에 접속했던 클라이언트입니다. putty는 기본적으로 pem 키 사용이 불가능합니다. pem키를 ppk 파일로 변환해 주어야 접속이 가능한데, 이를 도와주는 것이 **puttygen**클라이언트 입니다.

<br> <br>

1. puttygen을 실행해서 import key로 pem 파일을 엽니다. 
2. 이후 save private key를 눌러 ppk 파일을 생성합니다.
3. putty 클라이언트를 실행합니다. ec2 아마존 리눅스의 경우 Host Name이 `ec2-user`입니다. Host Name에 `ec2-user@${EIP}`를 입력해줍니다. ${EIP} 라고 적은 부분은 실제로 이렇게 쓰라는 것이 아니라 Elastic IP를 적는 것입니다.
4. 포트엔 SSH 포트인 22를 적어 주고, Connection type를 SSH로 체크해줍니다.
5. Connection-SSH-Auth 탭에서 Private key file를 등록하는 곳에 puttygen을 통해 만든 ppk 파일을 넣어줍니다.
6. Session 탭으로 돌아가서 Saved Sessions를 눌러 설정들을 저장해줍니다.
7. SSH 접속 완료

![ssh connection complete](https://user-images.githubusercontent.com/71186266/187028256-9538d332-9c77-48dd-8992-774dcfc76d01.png)


## 5. 초기 설정
아마존 리눅스 1 서버를 받은 다음 스프링 부트 + 톰캣 웹 어플리케이션 서버를 이용하기 위해 필수로 해야하는 설정들이 있습니다.
1. Java 설치
2. 타임존 변경하기: 기본으로 미국 시간대로 설정 되어있습니다.
3. 호스트네임 변경하기: 서버 별명을 설정합니다. IP만으로는 여러 서버가 있을 때 식별하기가 어렵기 때문에 필수로 등록해야합니다.


#### 5.1 java 설치
1. 설치: `sudo yum install -y java-1.8.0-openjdk-devel.x86_64`
2. 인스턴스 Java 버전 8로 변경하기: `sudo /usr/sbin/alternatives --config java`

#### 5.2 타임존 한국으로 변경하기
1. `sudo rm /etc/localtime`
2. `sudo ln -s /usr/share/zoneinfo/Asia/Seoul /etc/localtime`
3. `date` 명령어로 KST로 시간대가 바뀐 것을 확인하기.

#### 5.3 Host Name 변경하기
1. ~~`sudo vim /etc/sysconfig/network`~~ -> Linux 1에서나 쓰던 방법! 2 부터는 아래 방법으로 고친다.
2. `sudo hostnamectl set-hostname ${ 원하는 호스트 이름 }`
4. 호스트 주소 검색용으로 쓰이는 ect/hosts에 변경된 hostname 등록하기 `sudo vim /etc/hosts`
5. `127.0.0.1` 에 위에서 등록한 이름 **추가하기!** -> `127.0.0.1`가 이미 있다! 무시하고 새로 한 줄 만들어주기.
6. `sudo reboot`로 리부트 해서 확인


## 6. github에서 EC2로 코드 받아오기
### 6.1 깃허브 설치하기
1. `sudo yum install git`
2. 프로젝트 받아올 디렉토리를 만듭니다. `mkdir ~/app && mkdir ~/app/step1` 이런 식으로..
3. 디렉토리로 이동 한다음 git clone 해줍니다.
`git clone ${ 프로젝트 레포지토리 HTTPS 주소 }`

