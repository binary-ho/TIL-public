# Message Broker

simple broker는 클라이언트에서 전달 받은 subscription을 메모리에 저장하고 연결된 client에게 메시지를 보내는 역할을 한다. <br> <br>
stomp broker relay는 Spring MessageHandler로 메시지를 message broker에게 전달하는 역할을 한다. 
그렇게 하기 위해 tcp 연결이 성립되고 나면 모든 메시지는 broker에게 전달하고 다시 broker에게 전달받은 메시지를  WebSocket session을 통해서 클라이언트에게 보낸다. <br> 
**이 작업을 relay라고 하고 broker <-> messageHandler <-> clinet 양방향으로 진행된다.**

https://wedul.site/693

1. enable Simple Broker()는 메모리 기반 메세지 브로커가 해당 api를 구독하고 있는 클라이언트에게 메세지를 전달한다.
2. setApplicationDestinationPrefixes()는 서버에서 클라이언트로 부터 메세지를 전달받을 api의 prefixes를 설정한다.
3. addEndpoint: 엔드포인트를 설정한다.

이 문서는 여기까지만 읽고 [[여기]](https://github.com/binary-ho/spring-study/blob/main/study/STOMP%EC%99%80%20Spring%20WebSocket.md)로 넘어가면 된다

```java
@Configuration
@EnableWebSocketMessageBroker
public class WebsocketConfig implements WebSocketMessageBrokerConfigurer {

    @Override
    public void configureMessageBroker(MessageBrokerRegistry registry) {
        // 서버에서 클라이언트로 부터 메세지를 전달받을 api의 prefixes를 설정한다.
        registry.setApplicationDestinationPrefixes("/app");

        // enable Simple Broker
        // 메모리 기반 메세지 브로커가 해당 api를 구독하고 있는 클라이언트에게
        // 메세지를 전달한다.
        registry.enableSimpleBroker("/chatroom", "/user");
    }


    // 클라이언트에서 WebSocket을 연결할 api를 설정한다.
    @Override
    public void registerStompEndpoints(StompEndpointRegistry registry) {
        // path for all out website connection
        // so, here i'm just giving it as 'ws'
        // 엔드포인트를 설정한다.
        registry.addEndpoint("/ws").setAllowedOriginPatterns("*").withSockJS();
    }
}
```



https://asfirstalways.tistory.com/359
