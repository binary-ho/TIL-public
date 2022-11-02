# Lombok 사용시 주의점

## 1. `@Getter`, `@Setter`
이 두 메서드를 다 붙이면, 사실상 public 메서드나 다름없다. <br>
특히 `@Setter`는 값이나 의존성의 변경이 매우 적은 spring 객체의 특성상 꼭 필요한 경우가 아니면 절대 선언하지 마씨오.

## 2. `@AllArgsConstructor`, `@RequriedArgsConstructor`
`@AllArgsConstructor`은 모든 필드가 포함된 생성자를 만들어낸다. <br>

가장 편리한 annotation 중 하나라고 생각한다. 하지만 lombok이 생성자를 자동으로 만들어 줄 때, 파라미터를 받는 부분을 필드가 선언되어 있는 순서대로 만들어 주는데, 이 점에 유의해야한다. <br>
같은 `String`으로 선언된 필드들이 있다고 해보자.

```java
public class Message {
    private String senderName;
    private String receiverName;
    private String message;
    private String date;
    private Status status;
    private String avatarColor;

    public Message(String senderName, String receiverName, String message, String date, Status status, String avatarColor) {
        this.senderName = senderName;
        this.receiverName = receiverName;
        this.message = message;
        this.date = date;
        this.status = status;
        this.avatarColor = avatarColor;
    }
}
```
문제의 Message.. <br>
이런 메세지를 어디선가 생성자로 호출하고 있다고 생각했을 때, 사용자는 당연히  senderName, receiverName, message, date.. 순서로 값을 대입할 것이다. <br>

그런데 실수로 아래와 같이 순서가 뒤죽박죽 되었다고 생각해보자.

```java
public class Message {
    private String date;
    private Status status;
    private String receiverName;
    private String message;
    private String avatarColor;
    private String senderName;

    public Message(String date, Status status, String receiverName, String message, String avatarColor, String senderName) {
        this.date = date;
        this.status = status;
        this.receiverName = receiverName;
        this.message = message;
        this.avatarColor = avatarColor;
        this.senderName = senderName;
    }
}
```
lombok은 자연스럽게, 순서가 바뀐 생성자를 만들겠지만, **내가 호출하고 있는 부분까지 IDE Refactor가 알아서 바꿔주지는 않는다.** <br> 
이미 나는 어딘가에서 원래의 순서대로 쓰고 있었기 때문에 친구에게 `바보멍청이`라고 보냈다가 내 닉네임이 바보 멍청이가 되어버리는 바보 멍청이 같은 일이 벌어질 수도 있다. <br>

이런 문제는 초기화 되지 않은 final 필드나, `@NonNull`과 같은 제약조건이 설정 되어있는 모든 필드를 생성하는 `@RequriedArgsConstructor`에서도 발생할 수 있다.

## 3. `@NoArgsConstructor`
파라미터가 없는 생성자를 생성한다. 문제는 final 필드가 있는데도 그냥 만들어 준다는 것이다. 물론 이 부분은 `@NoArgsConstructor(force=true)`과 같이 옵션을 통해 해결이 가능하다. <br>

`@NonNull`과 같은 조건에서도 그냥 생성해버리는데, 추후 초기화 이전까지는 널 체크가 이루어지지 않는다.

## 4. `@EqualsAndHashCode`
equals 메소드와 hashcode 메소드를 생성한다. 필드 값이 바뀌면, 롬복은 알아서 다른 해쉬코드를 만들어 준다. <br>
그런데, 만약 이미 이 해쉬코드를 key로 다른 자료구조에 저장했다면 무슨 일이 일어날까? <br>

해당 자료구조는 영영 찾지 못 하게 되어 버린다... ㅠㅠ

## 5. `@Data`
`@Data` 마법사다 내부적으로 `@Getter `, `@Setter`, `@ToString `부터, `@RequiredArgsConstructor`, `@EqualsAndHashCode`까지 모두 포함한다. 참 편리한 마법사다. <br> 
미친 마법사 <br>
`@Data = @RequiredArgsConstructor + @Getter + @Setter + @ToString + @EqualsAndHashCode` 이므로, 안의 모든 애노테이션의 단점을 모두 포함한다.


## Reference
- https://velog.io/@rosa/Lombok-%EC%A7%80%EC%96%91%ED%95%B4%EC%95%BC-%ED%95%A0-annotation
