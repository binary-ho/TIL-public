# Item 90. 직렬화된 인스턴스 대신 직렬화 프록시 사용을 검토하라
어떤 객체를 직렬화 하기로 결정한 순간, 

어떤 객체에 Serializable 구현하는 것은 사실 객체 생성의 또다른 방법을 제공하는 것이나 다름없다. <Br>
객체는 자연스럽게 여러 버그와 보안적인 문제가 생길 수 있다. <br>
이를 해결할 수 있는 방법 중 하나가 바로 **직렬화 프록시 패턴이다. (serialization proxy patter)** <br>


## 1. 직렬화 프록시 패턴
직렬화 프록시 패턴은 직렬화 하고자 하는 객체의 프록시 버전을 '내부에'만들어 내는 것이다. <br>
말 그대로 private 중첩 클래스를 만들어 내는데, 이 클래스가 바깥 클래스의 직렬화 프록시이다. <Br>
코드 먼저 보자. 

```java

public static final class Period implements Serializable {
    private final Date start;
    private final Date end;

    public Period(Date start, Date end) {
        this.start = start;
        this.end = end;
    }

    private static class SerializationProxy implements Serializable {
        private final Date start;
        private final Date end;

        SerializationProxy(Period period) {
            this.start = period.start;
            this.end = period.end;
        }

        private static final long serialVersionUID = 134134L; // 아무 값

        ... // 이후 완성
    }

    public Date getStart() {
        return start;
    }

    public Date getEnd() {
        return end;
    }
}
```
위는 직렬화 프록지의 미완성 버전이다. <Br>
일단 내부에 이너클래스를 만드는 모습을 보여주려고 가져왔다. <br>
위의 코드와 같이 직렬화 프록시 패턴은 <br>
1. 직렬화 하고자 하는 원본 클래스의 논리적 상태를 정밀하게 표현하는 private static 중첩 클래스를 만든다.
2. 바깥 클래스와 중첩 클래스 모두 `Serializable`를 구현한다.
3. 중첩 클래스의 생성자는 단 하나여야 한다.
4. 중첩 클래스의 생성자는 바깥 클래스를 매개변수로 받아 내부에 필드를 복사해낸다.


## 2. 프록시 패턴 완성 3 step
이제 생성자를 만들었으면 다음의 3가지 메서드를 만들어 줌으로써 프록시 패턴을 완성할 수 있다.
1. `writeReplace` 메서드
2. `readObject` 메서드
3. `readResolve` 메서드


### 2.1 writeReplace 메서드
```java
private Object writeReplace() {
  return new SerializationProxy(this);
}
```

writeReplace는 직렬화 시스템이 바깥 클래스의 인스턴스 대신에 SerializationProxy 인스턴스를 반환도록 돕는다. <br>
직렬화가 이뤄지기 전에 바깥 클래스의 인스턴스를 직렬화 프로시로 변환해 주는 것이다. <br>
이 writeReplace가 가로막고 있는 한 직렬화시스템은 바깥 클래스의 직렬화된 인스턴스를 생성해낼 수 없다. <br>

### 2.2 readObjcet

writeReplace의 노력에도 불구하고 의도적인 훼손을 위해 바깥 클래스 직렬화를 시도할 수 있다. <br>
이를 간단하게 막는 방법이 readObject의 구현이다.

```java
private Object readObjcet(ObjcetStream stream) throws InvalidObjectException {
  throws new InvalidObjectException("프록시 필요!!");
}
```

### 2.3 readResolve
마지막으로 추가해야 할 메서드는 readResolve이다. <Br>
readResolve 메서드는 직렬화 프록시 패턴에서 가장 아름다운 부분중 하나라고 할 수 있다. <br>
```java
private Object readResolve() {
  return new Period(start, end);
}
```
직렬화는 생성자를 이용하지 않고도 인스턴스를 만들어내는 아주 불량한 친구다. <Br>

하지만 readResolve로 역직렬화 인스턴스의 기존 생성 방식을 공유해주면 이런 불량한 짓을 하지 않아도 된다. <br>
또한 역직렬화 이후 다양한  검증 문제에서도 해결되고, 불변식 검사도 안 해줘도 된다. <br>
마치 방어적 복사와 같이 가짜 바이트 스트림 공격과 내부 필드 탈취 공격에서도 자유로워 진다. <br>
또 여러 직렬화 접근법과 달리 직렬화할 객체의 내부 필드들을 final로 만들 수 있기 때문에 <br>
우리가 그렇게 사랑하는 불변 객체를 깨뜨리지 않아도 되는 것이다!! <br> <br>

그러면서도 이 패턴은 readObject에서 방어적 복사를 수행하는 것보다 강렬한데 <br>
직렬화 프록시 패턴은 역직렬화 인스턴스와 원본의 직렬화 인스턴스의 클래스가 달라도 정상적으로 작동한다. <br>
우리가 가끔 사용하는 EnumSet 또한 그렇게 구성되어 있다. <br>

## 한계점
마지막으로 프록시 패턴의 적용이 어려운 두 가지 케이스와 단점 하나를 언급하고 마치겠다.
1. 클라이언트가 확장할 수 있는 클래스에는 적용할 수 없음.
2. 객체 생성 순환이 있는 경우 적용할 수 없음/
3. 방어적 복사 직렬화 보다 약 14% 정도 느림!


## Reference
- Effective Java <조슈아 블로크>  
