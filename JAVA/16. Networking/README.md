# 16 Networking
네트워킹이란 두 대 이상의 컴퓨터를 케이블로 연결하여 네트워크를 구성하는 것을 말합니다. 
#### 1.1 클라이언트와 서버
클라이언트와 서버는 컴퓨터간의 관계를 **역할**로 구분하는 개념입니다. **서버(server)는 서비스를 제공하는 컴퓨터라서 서버입니다.** 우리가 식당에 방문 했을 때, 음식을 전달해주는 행위를 **'serving'** 전달해 주시는 직원 분을 **'server'** 라고 부르는 것을 생각하면 편합니다. **클라이언트**는 서비스를 사용하는 컴퓨터를 부르는 용어 입니다. <br> <br>
주요 모델로는 서버기반 모델(server-based model)과 P2P 모델(peer-to-peer model)로 두 가지가 있습니다. 
- server-based model: 서버구축비용과 관리비용이 드는 대신 안정적이고 관리와 보안이 용이
- P2P model: 서버 구축 비용을 절감하고 자원의 활용을 극대화 할 수 있는 대신, 자원 관리가 어렵고, 보안에 취약합니다.

#### 1.2 IP주소
IP주소는 컴퓨터(host)를 구별하는데 사용되는 고유한 값으로, 인터넷에 연결된 모든 컴퓨터는 IP주소를 갖습니다. IP주소는 네트워크 주소와 호스트 주소로 나눌 수 있는데, **IP주소의 네트워크 주소가 같으면 두 호스트는 같은 네트워크에 포함되어 있다는 것입니다.**
<br>
서브넷 마스킹을 통해 네트워크 주소를 알아낼 수 있고, 나머지가 호스트 주소입니다. 호스트 주소는 2의 자릿수 제곱개 만큼을 할당해줄 수 있는데, 주의할 점은 한 네트워크에 포함된 호스트의 수를 셀 때, 꼭 숫자 2를 빼 주어야합니다. 왜냐하면 호스트 주소가 0인 것은 네트워크 자신을 나타내고, 255는 브로드캐스트 주소로 사용되기 때문에 2개를 빼 주어야 하는 것입니다.

#### 1.3 InetAddress
자바에서는 IP주소를 다루기 위한 클래스 InetAddress를 제공합니다. 다양한 메서드가정의되어있습니다. (책 949p) <br> <br>
하나의 도메인명(www.naver.com)에 여러 IP주소가 맵핑될 수도 있고, 또 그 반대의 경우도 가능하기 때문에 전자의 경우 getAllByName()을 통해 모든 IP주소를 얻을 수 있다. 그리고 getLocalHost()를 사용하면 호스트명과 IP주소를 알아낼 수 있다.


```java
InetAddress ip = null;
        InetAddress[] ipArr = null;

        try {
            ip = InetAddress.getByName("www.naver.com");
            System.out.println("get host name: " + ip.getHostName());
            System.out.println("getHostAddress: " + ip.getHostAddress());
            System.out.println("toString: " + ip.toString());

            byte[] ipAddr = ip.getAddress();
            System.out.println("getAddress(): " + Arrays.toString(ipAddr));

            String result = "";
            for(int i = 0; i < ipAddr.length; i++) {
                result += (ipAddr[i] < 0) ? ipAddr[i] + 256 : ipAddr[i];
                result += ".";
            }
            System.out.println("getAddress() + 256 :" + result);
            System.out.println();
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }

        try {
            ip = InetAddress.getLocalHost();
            System.out.println("getHostName() :" + ip.getHostName());
            System.out.println("getHostAddress() : " + ip.getHostAddress());
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }

        try {
            ipArr = InetAddress.getAllByName("www.naver.com");
            for(int i = 0; i < ipArr.length; i++) {
                System.out.println("ipArr[" + i + "] : " + ipArr[i]);
            }
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }
```

#### 1.4 URL(Uniform Resource Locator)
URL은 인터넷에 존재하는 여러 서버들이 제공하는 자원에 접근할 수 있는 주소를 표현하기 위한 것으로 아래와 같은 형태로 이루어져있습니다. <br> `http://www.codechobo.com:80/sample/hello.html?referer=codechobo#index1` <br> `프로토콜://호스트명:포트번호/경로명/파일명?쿼리스트링#참조`
1. 프로토콜: 자원에 접근하기 위해 서버와 통신하는데 사용되는 통신규약 (`http`)
2. **호스트명: 자원을 제공하는 서버의 이름** (`www.codechobo.com`)
3. 포트번호: 통신에 사용되는 서버 포트번호 (`80`)
4. 경로명: 접근하려는 자원이 저장된 서버상의 위치 (`/sample/`) 좀 헷갈릴 수 있는데, **호스트명/~/**이 두 개의 슬레쉬 사이가 경로명이라고 보면 될 것 같다
5. 파일명: 접근하려는 자원의 이름 (`hello.html`)
6. 쿼리: ?이후의 부분 (`refer=codechobo`)
7. 참조: #이후의 부분(`index1`)


```java
URL url = new URL("https://section.blog.naver.com/BlogHome.naver?directoryNo=0&currentPage=1&groupId=0");

        System.out.println(url);
        System.out.println("url.getAuthority(): " + url.getAuthority());    //section.blog.naver.com
        System.out.println("url.getContent(): " + url.getContent());    //sun.net.www.protocol.http.HttpURLConnection$HttpInputStream@cd3fee8
        System.out.println("url.getDefaultPort(): " + url.getDefaultPort());    //443
        System.out.println("url.getPort(): " + url.getPort());  //-1 기본값이 -1이던데 그걸 가져온듯함

        // 파일명을 반환한다는데 경로명 이후 전부인듯?
        System.out.println("url.getFile(): " + url.getFile());
        //BlogHome.naver?directoryNo=0&currentPage=1&groupId=0

        // getHost 호스트명 불러오기
        System.out.println("url.getHost(): " + url.getHost());
        // url.getHost(): section.blog.naver.com

        // getPath 경로명 가져오기
        System.out.println("url.getPath(): " + url.getPath());
        // url.getPath(): /BlogHome.naver

        System.out.println("url.getProtocol(): " + url.getProtocol());  // https
        System.out.println("url.getQuery(): " + url.getQuery());    // directoryNo=0&currentPage=1&groupId=0
        System.out.println("url.getRef(): " + url.getRef());    // null
        System.out.println("url.getUserInfo(): " + url.getUserInfo());  // null

        // url을 문자열로 반환
        System.out.println("url.toExternalForm(): " + url.toExternalForm());
        //  https://section.blog.naver.com/BlogHome.naver?directoryNo=0&currentPage=1&groupId=0

        // url을 uri로 반환
        System.out.println("url.toURI(): " + url.toURI());
        // https://section.blog.naver.com/BlogHome.naver?directoryNo=0&currentPage=1&groupId=0

```

#### 1.5 URLConnection
URLConnection을 통해 어플리케이션과 URL간 통신이 가능하다. URLConnection을 통해 사용해서 연결하고자 하는 자원에 접근하고 읽고 쓰기를 할 수 잇다. 정말 많은 메서드가 있고, 책 954p에서 확인이 가능하다.


# 2. 소켓 프로그래밍
![바로가기](https://github.com/binary-ho/TIL-public/tree/main/JAVA/16.%20Networking/TCP%20%EC%86%8C%EC%BC%93%20%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%B0%8D)
