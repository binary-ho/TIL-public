# 스프링 부트 테스트

## 1. 테스트용 인메모리 DB 띄우는 법
스프링 부트를 통해 메모리 DB로 테스트를 해볼 수 있다.
![h2 in memory ver](https://user-images.githubusercontent.com/71186266/200557849-80e3107d-c75d-4111-af9a-7fd36058ca16.png)

더 좋은 방법도 있다, 별도의 설정이 없으면 알아서 메모리로 돌린다;

```py
spring:
#  datasource:
#    url: jdbc:h2:mem:test
#    username: sa
#    password:
#    driver-class-name: org.h2.Driver
#
#
#  jpa:
#    hibernate:
#      ddl-auto: create  # app 실행 시점에 entity 전부 지우고 다시 만들기
#    properties:
#      hibernate:
##        show_sql: true -> 여기는 system out으로 보임
#        format_sql: true

logging:
  level:
    org.hibernate.SQL: debug
    org.hibernate.type: trace # 쿼리 추적 기능
```
이렇게 하면 알아서 인메모리로 돌아간다! 물론 `application.yml`가 테스트 폴더에 들어가 있어야 함.. <br> 

어찌 됐던 테스트는 따로 돌리는 것이 좋으니까!

## 2. 예외 작성하기
```java
public class NotEnoughStockException extends RuntimeException {

    public NotEnoughStockException() {
        super();
    }

    public NotEnoughStockException(String message) {
        super(message);
    }

    public NotEnoughStockException(String message, Throwable cause) {
        super(message, cause);
    }

    public NotEnoughStockException(Throwable cause) {
        super(cause);
    }

}
```

## 2. `Ctrl + Alt + M`의 마법
이걸 여기에 적는게 맞는지는 모르겠지만, 테스트시 반복되는 코드를 줄일 때 너무 유용했다. <Br>
메서드 생성 단축키!
```java
Member member = new Member();
member.setName("진호");
member.setAddress(new Address("서울", "마포 어드메", "777-777"));
em.persist(member);
```
이 부분을 드래그 한 다음 `Ctrl + Alt + M` 입력. <br>

```java
Member member = createMember();
```
짜잔!

## 3. `@RunWith(SpringRunner.class)`
JUnit과 Spring을 연결해주는 어노테이션

## 4. `@SpringBootTest`
스프링 컨테이너 안에서 테스트 시작. <br> 
AutoWired와 같은 스프링 기능들이 정상적으로 작동하도록 도와준다.

## 5. `@Transactional`
트랜잭션을 걸고 테스트를 진행한다. 기본적으로 테스트가 끝나면 롤백한다. (리드 온리 내용 추가..)
