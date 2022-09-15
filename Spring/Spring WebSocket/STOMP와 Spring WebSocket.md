# STOMP와 Spring WebSocket
Spring STOMP는 Simple Text Oriented Messageing Protocol sub과 pub으로 나뉘어서, pub/sub의 발행/구독 아키텍쳐로 실행된다. <br> 
pub이 글을 쓰면 알아서 sub중인 사용자들에게 메세지를 전달해준다. WebSocket Handler를 따로 구현해줄 필요 없이 `@MessageingMapping`과 같은 어노태이션을 이용하여
메세지 발행시 엔드포인트를 별도로 분리하여 관리하게 해준다.

```java
@Configuration
@EnableWebSocketMessageBroker
public class WebsocketConfig implements WebSocketMessageBrokerConfigurer {

    @Override
    public void configureMessageBroker(MessageBrokerRegistry registry) {
        // 서버에서 클라이언트로 부터 메세지를 전달받을 api의 prefixes를 설정한다.
        // pub의 역할
        registry.setApplicationDestinationPrefixes("/app");

        // enable Simple Broker -
        // 메모리 기반 메세지 브로커가 해당 api를 구독하고 있는 클라이언트에게
        // 메세지를 전달한다.
        // sub의 역할 - destination의 prefix가 chatroom이 될 것이다.
        registry.enableSimpleBroker("/chatroom", "/user");
    }


    // 클라이언트에서 WebSocket을 연결할 api를 설정한다.
    @Override
    public void registerStompEndpoints(StompEndpointRegistry registry) {
        // path for all out website connection
        // so, here i'm just giving it as 'ws'
        // 웹소켓 서버 엔드포인트를 설정한다.
        registry.addEndpoint("/ws").setAllowedOriginPatterns("*").withSockJS();
    }
}

```

## 참조
정말 정말 멋진 글을 보았다.
https://brunch.co.kr/@springboot/695#
