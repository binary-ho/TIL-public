# Item 83. 지연 초기화는 신중히 사용해라 
지연 초기화는 왜 사용하는걸까? <br>
**클래스의 사용 빈도에 비해 초기화 성능이 너~~~무 높은 필드가 있는 경우, 우리는 지연 초기화를 고려해볼 수 있다.** <br>
하지만 이 상황은 매우 한정되어 있다. <br>
1. 인스턴스 초기화 비용은 줄지만 지연 초기화를 걸은 필드에 접근하는 비용은 커진다
2. 수많은 최적화와 마찬가지로 지연 초기화가 실제로는 성능을 느려지게 할 수도 있다

그래서 지연 초기화와 관련된 가장 중요한 원칙은 **'필요할 때까진 적용하지 마라'** 가 되겠다 <br>
그리고 적용하더라도 꼭 성능을 따져 보아야 한다 <br>
책에선 그냥 이렇게 말 한다 <br>
**대부분의 상황에서 지연 초기화 보다 그냥 일반적인 초기화가 낫다!** <br> <br>


### 그래도 적용해야 한다면
올바르게 지연 초기화를 해줘야 한다 <br>
아래의 법칙을 따라야 한다
1. `인스턴스 필드` : 이중검사 관용구를 사용하라
2. `정적 필드` : 지연 초기화 홀더 클래스 관용구를 사용하라
3. `반복해서 초기화 해도 괜찮은 경우` : 단일검사 관용구를 고려해라


## 멀티 스레드환경에서의 인스턴스 필드 지연 초기화

지연 초기화는 멀티 스레드 환경에서 더 까다롭다 <br>
지연 초기화 하는 필드를 두 스레드가 공유하는 상황을 생각해보자 <br>
제대로 된 동기화를 적용하지 않는 경우 심각할 버그로 이어질 것이다 <br>
일반적인 인스턴스 필드 초기화의 모습은 아래와 같다

```java
private final FieldType field = computeFieldValue();
```

지연 초기화로 인해 초기화 순환성이 깨질 것 같다면 synchronized를 사용하라.

```java
private FieldType field;
private synchronized FieldType getField() {
  if (field == null) {
    field = computeFieldValue();
  }
  return field;
}
```


## 정적 필드 지연 초기화
정적 필드를 성능 때문에 지연 초기화 해야 하는 경우 <br>
지연 초기화 홀더 클래스 관용구를 사용하라 <br>
지연 초기화 홀더 클래슨느 처음 쓰일 때 초기화되는 특성을 활용한 관용구이다


```java
private static class FieldHolder {
  static final FieldType field = computeFieldValue();
} 

private static FieldType getField() {
  return FieldHolder.field;
}
```

`getField()`라는 메서드가 처음 호출될 때 <br>
홀더 클래스의 fiedls가 처음으로 읽혀진다 <br>
이때서야 클래스의 초기화가 이루어 지는 점을 이용하는 것이다. <br>
중간에 동기화 과정이 있는가? <br>
없다. 때문에 성능적으로도 우수한 멋진 관용구다 <Br>


## 이중 검사 관용구
만약 성능 때문에 인스턴스 필드를 지연 초기화 하는 경우 <br>
이중검사 관용구를 사용할 수 있다 <br>
```java
private volatile FieldType field;

private FieldType getField() {
  FieldType result = field;

  // 첫 검사
  if (result != null) {
    return result;
  }

  // 두번째 검사
  synchronized (this) {
    if (field == null) {
      field = computeFieldValue();
      return field;
    }
  }
}
```

필드의 값을 두번 검사하는 방식이다 <Br>
첫 번째는 동기화 없이 검사한 다음 <br>
아직도 동기화 되지 않았다면 두 번째엔 동기화 하여 검사한다 <Br>
두번의 검사 이후에도 필드가 초기화 되지 않은 경우에만 필드를 초기화 한다. <br>

`volatile`을 사용한 이유는 필드 초기화 이후 동기화를 따로 진행하지 않기 위해서이다 <Br>
result 지역 변수는 필드가 이미 초기화된 경우에 다시 초기화를 시도하지 않도록 도와준다 (저자의 컴퓨터에선 1.4배의 성능 상승이 있었다고 한다) <br>
이런 이중검사는 좋은 방법이지만 정적 필드에선 홀더 클래스 방식이 더 낫다

## 단일검사 관용구

만약 인스턴스 필드를 반복해서 초기화 해도 상관 없는 경우 **두번째 검사를 생략한 단일검사 관용구를 고려해라**

```java
private volatile FieldType field;

private FieldType getField() {
  FieldType result = field;

  // 첫 검사
  if (result == null) {
    field = result = computeFieldValue();
  }
  return result;
}
```

만약 모든 스레드가 필드 값을 다시 계산해도 상관 없고, <BR>
필드 타입이 기본타입이며, long과 double이 아닌 경우volatile을 제거해도 된다고 한다. <Br>
이를 짜릿한 단일 검사라고 부른다고 한다 (빠르지만 거의 쓰지 않음)
  
 ## Reference
- Effective Java <조슈아 블로크>
