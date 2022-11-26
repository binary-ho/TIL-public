# SQL Injection
우리는 다양한 상황에서 클라이언트를 통해 입력을 받는다. 
사용자가 아이디와 비밀번호를 입력 받으면 DB에 어떤 쿼리가 들어갈까? <br>
간단하게 아무 예시나 들어보자.
```sql
SELECT user FROM USER_TABLE WHERE id='아이디' AND password='비밀번호';
```
이 때, 비밀번호란에 장난을 쳐보자.. <br>
아래와 같은 문장을 넣어 보겠다.
```sql
' OR `1` = '1'; --
```
그럼 제시된 문장이 아래와 같이 바뀐다;
```sql
SELECT user FROM USER_TABLE WHERE id='아이디' AND password='비밀번호' OR `1` = '1'; --';
```
알다 싶이 OR 1 연산은 무조건 결과가 1이다. 따라서 유저 정보가 무조건 가져와 지고, 로그인에 성공하게 된다. <br>
(가장 뒤의 `--`는 DB에 맞는 주석문을 넣은 것이다!) <br>

더 끔찍한 장난도 있다 만약에.. 아래와 같은 문장이 들어간다면?
```sql
'; AND 1 = SLEEP(100000000); --
```
1억 초간 DB 서버가 Sleep된다; <br>
더 끔찍한 장난도 있다.
```sql
'; DROP TABLE USER_TAME; --
```
이제 이 SQL Injection의 무서움이 느껴질 것 같다. <br>

이렇게 SQL Injection은 아주 간단한 방법으로 회사 DB의 소중한 정보들이나, 개인 정보들을 모조리 훔치거나, 아예 다 부숴 버릴 수도 있다.. <br>
기본적인 CD 뿐만 아니라, DB에서 지원하는 다양한 메서드를 전부 호출해 버릴 수가 있다!!
**말 그대로 소중한 DBMS를 누가 마음대로 다룰 수 있게 되는 것이다!** <br>


## 방어 방식
이러한 SQL 인젝션은 간단하면서도 매우 강력하기 때문에, 스크립트 자체를 꽂아 버리는 XSS와 항상 경계의 대상이 되어 왔다. <br>
이에, 대부분의 상용 DB들은 escape 함수와 prepared statement를 제공한다. <br>
이들을 활용해서 프론트 - 백 - DB 모두의 힘을 모아 막는 것이 좋다
#### 1. **프론트(클라이언트)** 
기본적으로 injection에 쓰이는 특수 문자를 막는다! (상용 서비스들이 특수 문자를 쓰지 못 하게 했던 이유를 알게 되었다!)
#### 2. 백(서버) 
클라이언트에서 여러 방식으로 우회할 수 있으므로, 여기서도 최선을 다해 막는다. <br> 
1차 적으로 정규 표현식 등으로 막는다. **그리고 escape 함수만으로는 구멍이 있을 수 있으니, prepared statement를 사용하는 것이 최선이다!.** <br>
ORM을 쓰는 경우, 메서드의 형태로 쿼리를 받기 때문에 안전성이 높다! <br> 
ORM으로 내가 주로 사용하는 JPA에서는 감사하게도 입력들이 value로서 사용되기 때문에 injection이 불가능 하다고 한다. (할렐루야) <br>
**내부적으로 Prepared Statement처럼 동작하는데,** 
**입력 파라미터를 제외한 값들이 미리 parse 되어 컴파일 된다.** 그리고 입력 값들이 **바인딩되는데,** 이 덕분에 들어오는 값이 SQL 문법으로 취급되지 않는다. 단지 값과 같이 사용되기 때문에 타격을 줄 수 없다. <br>
예시와 함께 조금 더 자세히 살펴보자. 

## Prepared Statement
어떤 sql문이 있을 때, 
```sql
select count(*) as count from student where userid = ?
```
이 ? 부분에 입력으로 들어오는 값이 위치하게 된다. <br>

Prepared Statement는 이 `?`외의 부분을 미리 파싱해 두는 것이다. 이후 결과를 메모리에 저장해 둔다면, 입력이 100개든 1억개든, 미리 파싱해둔 결과를 재활용 해도 되니 얼마나 효율적인가? <br>
?에 들어올 입력들은 바인드 변수가 되어 매번 바인딩 될 뿐이다. <br>
바인딩 데이터는 SQL 문법으로 취급되지 않고, 내부 인터프리터나 컴파일 언어로 처리되어서 **SQL 문법적인 의미가 없다!!** <br>
그래서 바인딩 변수에 SQL 공격 쿼리를 입력할지라도 의미가 없는 것이다. <br>

JPA에서는 이런 Prepared Statement와 같은 동작을 기본적으로 채택했다! <br>
이와 비슷한 방식으로는 Query Dsl을 사용할 때와 같이, 쿼리 명령어 들을 메서드 방식으로 호출하는 것이다.  <br>
여기서도 파라미터 바인딩이 된다. 따라서 <br>
**JPA + Query DSL의 조합은 사용만으로 기본적인 인젝션 공격 방어가 된다!**

## Reference
- [SQL 주입 공격 실행 - Computerphile](https://www.youtube.com/watch?v=ciNHn38EyRc)
- [JPA 시큐어 코딩 - 공격 종류 및 해결방안 \<AndersonChoi>](https://blog.voidmainvoid.net/173)
- [Prepared Statement를 쓰면 SQL 인젝션 공격이 되지 않는 이유는? - 에스케이인포섹](https://blog.naver.com/skinfosec2000/220482240245)
