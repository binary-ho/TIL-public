# Docker Container와 가상화 - Docker Container의 이해
도커 컨테이너는 프로세스를 격리해서 사용하는 공간이라고 했는데, 이게 무슨 의미일까? 또 기존의 가상화 기술에 비해 어떤 이점이 있는걸까? <br>

## 1. OS 가상화 기술
가상화 기술이 나오기 전, 한대의 서버는 하나의 용도로만 사용할 수 있었다. 하나의 서버에 하나의 OS, 그리고 하나의 프로그램.. <br>
분명 안정적이지만, 남는 서버 공간은 그대로 방치되기 때문에 비효율적인 사용이라고 할 수 있다. <br>

이후 'OS 가상화' 기술이 등장하게 되었다. 논리적으로 공간을 분할하여 Virtual Machine이라는 독립된 가상 환경을 만들어 냈다. VM은 말 그대로 가상의 기계로, 컴퓨터 안의 논리적인 가상 컴퓨터라고 생각하면 된다. 그리고 VM엔 가상화 된 OS가 있다. <br>
하이퍼-바이저는 호스트 시스템에서 다수의 게스트 OS를 구동할 수 있게 해주는 소프트웨어이다. 호스트 시스템은 별게 아니고 가상화 기술이 올라간 기반 시스템이다. 이를테면 VM을 돌리고 있는 우리의 컴퓨터를 가리킨다. <br> 
하이퍼 바이저 기반 가상화 기술로 여러 게스트 OS를 만들어내고, 하드웨어를 가상화 할 수 있게 되었다. 하이퍼 바이저는 하드웨어와 각각의 VM을 모니터링 하는 중간관리자이다.

![하이퍼바이저](https://user-images.githubusercontent.com/71186266/210130200-b64284c0-6fd4-4341-b5bc-4059620f7bac.png)

이런 모습..

## 2. 컨테이너 가상화 기술
이러한 하이퍼-바이저 기반 가상화 기술을 토대로, **컨테이너 가상화 기술이 만들어졌다.** <br>

![contanier](https://user-images.githubusercontent.com/71186266/210130201-162915fd-02e9-4b1a-8c28-b14734c25dd7.png)

위와 같이 꽤나 유사한 구조를 띄고 있는 것을 알 수 있다. 차이점은 VM과 도커 컨테이너 안을 들여다 보면 알 수 있는데, VM 안에는 Guset OS가 있지만, **컨테이너 방식에는 Guest OS가 없다.** <br>

**컨테이너들은 하나의 OS를 공유한다!** VM은 어플리케이션 실행을 위해 VM을 띄우고, 자원을 할당하고, 게스트 OS를 부팅하는 등 복잡한 과정이 필요하다. **하지만, 컨테이너 방식에서는 그냥 이미지만 배포하면 되기 때문에, 훨씬 가벼울 수 밖에 없다.** <br>

## 3. 컨테이너의 자원 공유
![container 2](https://user-images.githubusercontent.com/71186266/210130203-8e9e9c4c-2600-4ae5-9e90-d61f08a987bc.png)

도커 컨테이너들은 호스트 OS의 커널을 공유한다. 그림처럼 컨테이너라는 논리적으로 격리된 공간이 있고, 호스트 OS의 커널이나 컴퓨터의 자원들을 프로세스에서 필요한 만큼 사용하는 것이다. 예를 들어 우리 집이 층도 많고 넓어서, 한 층을 빌려주는 것이다. 건물이나 전기, 수도 같은 자원이나 시스템을 공유하는 것이다. (적절한 예시인지는 모르겠다.) <br> 

![contanier 4](https://user-images.githubusercontent.com/71186266/210130348-2d1a29c8-55e0-4e32-8ca7-edd65464afed.png)

컨테이너를 좀 더 자세히 본 그림인데, 위의 그림과 같이 하나의 커널을 공유하고, 해당 컨테이너의 프로세스를 작동시키는데 필요한 양 만큼의 하드디스크, RAM, CPU, 네트워크 등을 나누어 주는 것이다! (너무 신기) <br>

## 4. 컨테이너 격리 기술 - Linux
어떻게 컨테이너를 격리시킬까?   <br>
리눅스의 control groups - Cgroup과 namespaces에 의해 격리된다. <br>

C Group은 CPU나 메모리, Network Bandwith, HD I/O 등 프로세스 그룹의 시스템 리소스 사용량을 관리해주는 기능이다. 어떤 프로세스의 사용량이 커졌을 때 CPU와 메모리의 사용을 제한하는 기능이다. <br>
그리고 namespace는 하나의 시스템에서 프로세스를 격리시킬 수 있는 가상화 기술로, 격리된 환경을 제공하는 경량 프로세스 가상화 기술이다. (더 찾아보자.) <br>
두 리눅스 커널 기능들을 통해 컨테이너와 호스트에서 실행되는 다른 프로세스들 사이에 벽을 만들 수 있다. <br>

그런데 이상하다. 나는 분명 Window 환경에서 Docker를 사용하고 있는데, 그럼 Window OS가 공유되는 것인가? 그럼 리눅스 커널 기능들은 어떻게 사용할 수 있는건가? 도커는 내가 현재 사용중인 Windows에서 돌아가는 것이 아니다! <br>
**도커 컨테이너는 리눅스 VM에서 돌아간다.**

![container 3](https://user-images.githubusercontent.com/71186266/210130204-26c7b190-6670-4c1d-92b2-3c5126984707.png)

위의 그림처럼 리눅스 VM이 있고, 그 안의 리눅스 OS가 호스트 OS가 되는 것이다. 도커는 이렇게 리눅스 VM 위에서 동작하게 된다. <br>
**도커는 리눅스 VM 위에서 작동하는 덕분에, <br> 위에서 언급한 리눅스의 리소스 제한 기능과 프로세스 격리 기능들을 활용해서 성공적으로 컨테이너를 격리시킬 수 있게 되었다!**

## Reference
- [따라하며 배우는 도커와 CI환경](https://www.inflearn.com/course/%EB%94%B0%EB%9D%BC%ED%95%98%EB%A9%B0-%EB%B0%B0%EC%9A%B0%EB%8A%94-%EB%8F%84%EC%BB%A4-ci/dashboard)
