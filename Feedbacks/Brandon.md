# 김우근 선배님의 말씀..
빛으로 만들어진 남자 김우근 선배님의 피드백 정리. 정말 감사드립니다.
## 1. 주석
**주석은 정말 필요한 순간이 아니면, 가급적 달지 않는 것이 좋다.** 굳이 주석이 없어도 이해되는 것이 바로 잘 만들어진 코드입니다. <br>
예를 들어, setApplicationDestinationPrefixes는 이름 만으로도
"api의 prefixes를 설정한다"라는 의미를 파악 할 수 있습니다. 차라리 **주석이 필요하다면, 깃 커밋 내역에 달아 두는 것이 좋습니다.**

#### 번외
굳이 주석이 필요한 상황은 메소드 분할을 통해서 해결할 수도 있음.
```java
// 원래 코드
public class WebsocketConfig implements WebSocketMessageBrokerConfigurer {
  @Override
  public void configureMessageBroker(MessageBrokerRegistry registry) {
      registry.setApplicationDestinationPrefixes("/app");
  }
}

// 선배님이 보여주신 예시
public class WebsocketConfig implements WebSocketMessageBrokerConfigurer {
  @Override
  public void configureMessageBroker(MessageBrokerRegistry registry) {
      setPrefixServerToClientForMessage(registry, "/app");
  }
   
  private void setPrefixServerToClientForMessage(MessageBrokerRegistry registry, String prefix) {
      registry.setApplicationDestinationPrefixes(prefix);
  }
}
```
# 2. 축약어
모든 식별자는 축약하지 않습니다. 쓸 때는 당연히 알지만, 나중에는 무조건 헷갈리게 되어 있습니다. <br>
예를 들어 `ws`라고만 써 두면, `web socket`인지, `web service`인지 나중에 헷갈릴 수가 있습니다.
