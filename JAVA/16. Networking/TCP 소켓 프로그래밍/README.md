# 2. 소켓 프로그래밍
소켓 프로그래밍은 소켓을 이용한 통신 프로그래밍을 뜻합니다. socket이란 프로세스간의 통신에 사용되는 양쪽 끝단(endpoint)를 의미합니다. 전기를 주고 받을 때는 양 끝단에 콘센트가 필요합니다. 이 소켓이 사전적으로는 콘센트의 의미를 가집니다. <br> <br>

쓰레드로 Sender와 Receiver를 나눈 케이스: TcpIpServerSeparate.java, TcpIpClinetSeparate.java <br>
단체 체팅방을 구현한 케이스: MultichatServer, MultichatClient 

### 2.1 TCP와 UDP
||TCP|UDP|
|:----:|:----:|:----:|
|연결방식|**connection-oriented** <br> - 연결 후 통신(전화기), 1:1통신방식|**connectionless-oriented** <br> - 연결없이 통신(소포), n:n 통신방식|
|특징|**byte-stream(데이터 경계 구분 X)**<br> 느리지만, 신뢰성 있는 전송|**datagram(데이터 경계 구분)** <br> 빠르지만, 신뢰성 없음|
|**관련 클래스**|1. Socket <br> 2. ServerSocket|1. DatagramSocket <br> 2. DatagramPacket <br> 3. MulticastSocket|



# 2.2 TCP소켓 프로그래밍

1. 서버 프로그램에서는 서버소켓을 통해, 서버 컴퓨터의 특정 포트에서 클라이언트의 연결요청을 처리할 준비를 함
2. 클라이언트 프로그램은 접속할 서버의 IP주소와 포트 정보를 가지고 소켓을 생성해서 서버에 연결을 요청한다.
3. 서버소켓은 클라이언트의 연결요청을 받으면, 서버에 새로운 소켓을 생성해서 클라이언트의 소켓과 연결되도록 한다.
4. 이제 클라이언트의 소켓과 새로 생성된 서버의 소켓은 서버소켓과 관계없이 일대일 통신을 한다.

**서버소켓은 포트와 결합(bind)되어 클라이언트의 연결 요청을 기다리고 있다가, 요청이 들어오면 새로 소켓을 만든다.** 서버 내의 소켓과 외부 소켓을 이어주는 전화교환기와 같은 역할을 하는 것이다. 서버소켓은 다른 소켓과 다르게, 한 포트를 독점한다. <br> <br>
소켓끼리의 통신에서 한 소켓의 출력 스트림은 상대 소켓의 입력 스트림과 연결되고, 입력 스트림은 상대 소켓의 출력 스트림과 연결된다. 이런식으로 교차 연결되어 데이터를 주고 받는다. <br> 너무 멋진 아이디어 <br>




# 1. 기본 송수신 상황


서버측 코드 
```java
public static void main(String[] main) {
        ServerSocket serverSocket = null;

        try {
            // 1. 서버소켓을 생성하여 7777번 포트와 결합 (bind) 시킨다.
            serverSocket = new ServerSocket(7777);
            System.out.println(getTime() + " 서버가 준비 되었습니다.");
        } catch (IOException e) { e.printStackTrace(); }

        while(true) {
            try {
                System.out.println(getTime() + " 연결요청을 기다립니다.");

                // 서버소켓은 클라이언트의 연결요청이 올 때까지 실행을 멈추고 계속 기다린다.
                // 2. 클라이언트의 연결요청이 오면 클라이언트 소켓과 통신할 새로운 서버측 소켓을 생성한다.
                Socket socket = null;
                if (serverSocket != null) {
                    socket = serverSocket.accept(); // 서버 소켓으로 연결 요청 받으면 새로운 서버측 소켓 생성
                }
                System.out.println(getTime() + socket.getInetAddress().toString() + " 로부터 연결요청이 들어왔습니다.");

                // 3. 소켓의 출력스트림을 얻은 다음 데이터 아웃풋 스트림에 넣어준다.
                OutputStream outputStream = socket.getOutputStream();
                DataOutputStream dataOutputStream = new DataOutputStream(outputStream);

                // 4. 원격 소켓 (remote socket)에 데이터를 보낸다
                dataOutputStream.writeUTF("[Notice] Test message1 from Server.");
                System.out.println(getTime() + " 데이터를 전송했습니다.");

                dataOutputStream.close();
                socket.close();
            } catch (IOException e) { e.printStackTrace(); }
        }
    }
```


클라이언트측 코드
```java
public static void main(String args[]) {
        try {
            String serverIp = "127.0.0.1";
            System.out.println("서버에 연결중입니다. 서버 IP: " + serverIp);
            // 1. 소캣을 생성하여 연결을 요청합니다.
            Socket socket = new Socket(serverIp, 7777);

            // 2. 소캣의 입력스트림을 얻는다.
            InputStream inputStream = socket.getInputStream();
            DataInputStream dataInputStream = new DataInputStream(inputStream);

            // 3. 소캣으로 부터 받은 데이터를 출력한다.
            System.out.println("서버로 부터 받은 메세지 : " + dataInputStream.readUTF());
            System.out.println("연결을 종료합니다.");

            dataInputStream.close();
            socket.close();

            System.out.println("연결을 종료하였습니다다.");

        } catch (ConnectException ce) {ce.printStackTrace();}
        catch (IOException ie) {ie.printStackTrace();}
        catch (Exception e) {e.printStackTrace();}
    }
```

- **getPort()**: 상대편 소켓이 사용하는 포트
- **getLocalPort():** 소켓 자신이 사용하는 포트
- **setSoTimeout(int timeout)** 을 이용해서 서버소켓의 대기시간을 지정할 수 있다.
- 서버에 접속하는 클라이언트의 수가 많을 때는 쓰레드를 이용해서 클라이언트의 요청을 병렬적으로 처리하는 것이 좋다. 그렇지 않으면 서버가 접속을 요청한 순서대로 처리하기 때문에 대기시간이 길어진다.
- 소켓으로 데이터를 송신하는 작업과 수신하는 작업을 별도의 쓰레드가 처리하도록 하여, 송수신이 동시에 이루어지도록 해줄 수 있다.

# 2. 여러 개의 쓰레드를 생성해서 요청을 처리하는 상황 

```java
public class TcpIpServerThread implements Runnable{
    ServerSocket serverSocket;
    Thread[] threadArr;

    public static void main(String args[]) {
        TcpIpServerThread server = new TcpIpServerThread(5);
        server.start();
    }

    public TcpIpServerThread(int num) {
        try {
            // 1. 서버 소켓을 생성하여 7777번 포트와 결함(bind) 한다.
            serverSocket = new ServerSocket(7777);
            System.out.println(getTime() + " 서버가 준비되었습니다.");

            threadArr = new Thread[num];
        } catch (IOException e) {e.printStackTrace();}
    }

    public void start() {
        for(int i = 0; i < threadArr.length; i++) {
            threadArr[i] = new Thread(this);
            threadArr[i].start();
        }
    }

    public void run() {
        while(true) {
            try {
                System.out.println(getTime() + "가 연결요청을 기다립니다.");

                // 1. 연결요청 받으면 소켓 생성
                Socket socket = serverSocket.accept();
                System.out.println(getTime() + socket.getInetAddress().toString() + "로부터 연결요청이 들어왔습니다.");

                // 2. 소켓의 출력 스트림 얻기
                OutputStream outputStream = socket.getOutputStream();
                DataOutputStream dataOutputStream = new DataOutputStream(outputStream);

                // 3. 원격 소켓(remote socket)에 데이터를 보낸다.
                dataOutputStream.writeUTF("[Notice] Test Message 1 from Server.");
                System.out.println(getTime() + " 데이터를 전송했습니다.");

                // 4. 스트림과 소켓 닫기
                dataOutputStream.close();
                socket.close();

            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }


    static String getTime() {
        String name = Thread.currentThread().getName();
        SimpleDateFormat simpleDateFormat = new SimpleDateFormat("[hh:mm:ss]");
        return simpleDateFormat.format(new Date()) + name;
    }
}

```
# 3. 쓰레드로 Sender와 Receiver를 분리해놓은 케이스

서버측
```java
public class TcpIpServerSeparate {
    public static void main(String args[]) {
        ServerSocket serverSocket = null;
        Socket socket = null;

        try {
            serverSocket = new ServerSocket(7777);
            System.out.println("server is ready");

            socket = serverSocket.accept();

            Sender sender = new Sender(socket);
            Receiver receiver = new Receiver(socket);

            sender.start();
            receiver.start();
        } catch (Exception e) {e.printStackTrace();}
    }
}

class Sender extends Thread {
    Socket socket;
    DataOutputStream dataOutputStream;
    String name;

    Sender(Socket socket) {
        this.socket = socket;
        try {
            dataOutputStream = new DataOutputStream(socket.getOutputStream());
            // 이름 자체에 괄호 넣어주자
            name = "[" + socket.getInetAddress() + ":" + socket.getPort() + "] ";
        } catch (Exception e) {}
    }

    public void run() {
        // sender이므로 계속해서 입력 받기
        Scanner scanner = new Scanner(System.in);
        while(dataOutputStream != null) {
            try {
                // output stream에 내가 적은 내용들을 태워서 보내기
                dataOutputStream.writeUTF(name + scanner.nextLine());
            } catch (IOException e) {}
        }
    }
}

class Receiver extends Thread {
    Socket socket;
    DataInputStream dataInputStream;

    Receiver(Socket socket) {
        this.socket = socket;
        try {
            dataInputStream = new DataInputStream(socket.getInputStream());
        } catch (IOException e) {}
    }

    public void run() {
        while (dataInputStream != null) {
            try {
                // 인풋 스트림에 도착해있는 내용들 읽어서 출력하기
                System.out.println(dataInputStream.readUTF());
            } catch (IOException e) {}
        }
    }
}
```

# 4. 멀티 채팅. 하나의 서버 여러 참여자
하나의 서버를 만들어둬서 열어두고, 참여자들을 받는 방식입니다.

서버측
```java
public class MultichatServer {
    // HashMap clients;
    ConcurrentHashMap clients;
    MultichatServer() {
        // 회원들을 담는 hashmap
        //clients = new HashMap();
        //Collections.synchronizedMap(clients);
        clients = new ConcurrentHashMap();
        // 이걸로 바꿔주자
    }

    public void start() {
        ServerSocket serverSocket = null;
        Socket socket = null;

        try {
            serverSocket = new ServerSocket(7777);
            System.out.println("server is ready");

            while (true) {
                // 소켓 실행되면
                socket = serverSocket.accept();
                System.out.println("[" + socket.getInetAddress() + ":" + socket.getPort() + "] is connected.");
                // 리시버 실행해준다.
                ServerReceiver thread = new ServerReceiver(socket);
                thread.start();
            }
        } catch (Exception e) {e.printStackTrace();}
    }

    // 메세지 돌리기
    void sendToAll(String msg) {
        Iterator itr = clients.keySet().iterator();
        while (itr.hasNext()) {
            try {
                // 각 클라이언트를 가져온다음 DataOutputStream으로 형변환 해준다. 왜 이게 가능한거지?
                DataOutputStream outputStream = (DataOutputStream) clients.get(itr.next());
                outputStream.writeUTF(msg);
            } catch (IOException ie) {ie.printStackTrace();}
        }
    }

    public static void main(String[] args) {
        new MultichatServer().start();
    }

    class ServerReceiver extends Thread {
        Socket socket;
        // 일종의 중계기 이기 때문에 둘 다 입력을 받아준다.
        DataInputStream inputStream;
        DataOutputStream outputStream;

        ServerReceiver(Socket socket) {
            this.socket = socket;
            try {
                inputStream = new DataInputStream(socket.getInputStream());
                outputStream = new DataOutputStream(socket.getOutputStream());
            } catch (IOException ie) {
                ie.printStackTrace();
            }
        }

        public void run() {
            String name = "";

            try {
                // 시작할 때 누구 입장하면 이거 출력하고 아래서 while로 계속 입력 받아.
                // 이래서 입장 할 때 이름을 보내는구나
                name = inputStream.readUTF();
                sendToAll("#" + name + " has entered.");

                // 이름과 아웃풋 스트림을 넣어줘야 나중에 sendToAll 때 쓸 수가 있다
                clients.put(name, outputStream);
                // clients.size();
                // inputStream으로 받은 것을 모두에게 돌린다.
                while (inputStream != null) {
                    sendToAll(inputStream.readUTF());
                }
            } catch (IOException ie) {ie.printStackTrace();}
            finally {
                // 나갈 때의 처리
                sendToAll("#" + name + " has left. [" + socket.getInetAddress() + ":" + socket.getPort() + "]");
                clients.remove(name);
            }
        }
    }
}
```

클라이언트측
```java
public class MultichatClient {

    // 사용할 이름을 main함수에서 받아온다
    public static void main(String[] args) {
        if(args.length != 1) {
            System.out.println("USAGE: java MultichatClient name");
            System.exit(0);
        }

        try {
            String serverIp = "127.0.0.1";
            Socket socket = new Socket(serverIp, 7777);
            System.out.println("server is ready");
            Thread sender = new Thread(new ClientSender(socket, args[0]));
            Thread receiver = new Thread(new ClientReceiver(socket));

            // 둘 다 필요
            sender.start();
            receiver.start();
        } catch (ConnectException ce) {ce.printStackTrace();}
        catch (Exception e) {}
    }

    static class ClientSender extends Thread {
        Socket socket;
        DataOutputStream outputStream;
        String name;

        ClientSender(Socket socket, String name) {
            this.socket = socket;
            try {
                outputStream = new DataOutputStream(socket.getOutputStream());
                this.name = name;
            } catch (Exception e) {}
        }

        public void run() {
            Scanner scanner = new Scanner(System.in);
            try {
                if(outputStream != null) {
                    // 시작 할 때 이름을 같이 보낸다
                    // 입장시 쓰임!
                    outputStream.writeUTF(name);
                }
                while (outputStream != null) {
                    outputStream.writeUTF("[" + name + "]" + scanner.nextLine());
                }
            } catch (IOException ie) {}
        }
    }

    static class ClientReceiver extends Thread {
        Socket socket;
        DataInputStream inputStream;

        ClientReceiver(Socket socket) {
            this.socket = socket;
            try {
                inputStream = new DataInputStream(socket.getInputStream());
            } catch (IOException ie) {}
        }

        public void run() {
            while (inputStream != null) {
                try {
                    System.out.println(inputStream.readUTF());
                } catch (IOException e) {}
            }
        }
    }
}
```
