# PostgreSQL 실습 3편
이론적으로만 배운 인덱스, 트랜잭션, 권한 부여 등이 실제로 명령어를 통해 적용되는 과정을 확인해보자.

# 1. Index
PostgreSQL는 단순 B Tree를 사용한다. <br>
기본적으로 대부분의 DBMS는 따로 명시가 없으면 테이블들의 PK를 인덱싱 해둔다. <br>
그런데, 우리는 PK로만 튜플을 조회하지 않는다. 다양한 컬럼 들을 조합해서 사용하면서 조회한다. 이런 컬럼들에 대해 직접 인덱스를 지정해줄 수 있다. <br> <br>

PostgreSQL에서 지원하는 인덱스 중 유용한 두 가지 인덱스를 살펴보자.
1. **GIN (Generalized Inverted Index)** 
2. **Compound Column Index: 복합 컬럼 인덱스**


## 1.1 Generalized Inverted Index
GIN이 유용한 상황 <br>
책 제목과, 내용이라는 두개의 속성을 가진 테이블이 있다고 가정하자!
- 여러 책들 중에서 "학교"라는 단어가 포함된 책을 찾으려면 어떻게 해야할까?
 

만약 B+Tree 이용한다고 생각해보자. 제목을 찾는 상황에서는 아주 즐겁다! 하지만, 특정 "단어"를 "내용"에서 찾으려면, 정말 모든 "내용"을 다 뒤져 보아야 한다.. <br>
이는 당연히도 **학교라는 단어에 대한 인덱싱이 안 되어 있기 때문이다.**
- 혹은 어떤 단어를 포함한 책을 **모두** 찾는다면?

이 역시 끔찍한 일이다. 해당 단어에 대한 인덱싱이 안 되어 있기 떄문에 모두 뒤져봐야 한다.. <br> <br>

이는 **각 단어가 어떤 문서에 들어있는지 연결함으로써 해결할 수 있다.** 

(그림)

그림에서 a가 가리키는 노드엔 a라는 내용이 있는 책들이 들어있고, b가 카리키는 노드에는 b의 내용이 있는 책들이 들어 있다! <br>
인덱스를 중심으로 내용들을 분류하는 것이 아니라, 내용물들로 전체 내용을 분류해 버렸다. 
이렇게 분류 방식이 역으로 되어 있어서, **inverted index라고 부른다.** 
inverted index를 통해 내가 검색하길 원하는 요소들을 미리 어디에 들어가 있는지 인덱싱을 걸 수 있다. **요소 중심이 아닌 단어 중심 검색이 가능해진다.** <br>

## 1.2 단일 컬럼 인덱스
우리가 잘 아는 평소의 인덱스이다. <br>
예를 들어 점수 컬럼이 오름차순 정렬되도록 해주었다. <Br> 
이는 점수 범위 연산에도 유리하고, 편하다. <br>
그런데 여기 까다로운 요구를 주겠다. **전체 점수는 오름차순 정렬하되, 같은 점수를 가진 사람들의 이름은 내림차순으로 정렬해라.** <br>
이러한 요구는 단일 컬럼 상황에서, 별 수 없이 **같은 점수의 이름들을 일일이 비교하면서 내림차순 해줘야 한다...** <br> 이런 상황은 많다. 같은 성적에 대해서는 학번 내림차순을 해주세요 등.. 의외로 사용할 일이 많다. <br>

## 1.3 복합 컬럼 인덱스
복합 컬럼 인덱스는 여러 컬럼에 대해 

이러한 단일 인덱스의 단점을 해결하기 위해 다루는 인덱스.

ex1) 점수 2를 가진 홍길동 찾기

**더 포괄적이거나 중복값이 많은 인덱스로 먼저 걸러 주는 것이 조회 횟수를 줄이는 길이다!** <br>
예를 들어, 점수 2를 가진 사람은 이름이 홍길동인 사람 보다 훨신 많다고 해보자. **이런 경우에 점수 2를 먼저 가진 사람을 거른 다음,** 이름으로 거르라는 것이다.

## 1.4 인덱스 명령어 예시

1. **ramen의 name에 대해서 정렬 (기본 오름차순)**
```sql
CREATE INDEX name_idx ON ramen(name);
```

2. **ramen의 name에 대해서 내림차순 정렬**
```sql
CREATE INDEX name_idx ON ramen(name DESC);
```

3. **복합 컬럼 인덱스** <br> **item_type에 대해서는 오름차순으로, item_id는 내림차순으로 정렬한다.**
```sql
CREATE INDEX name_idx ON rating(item_type ASC, item_id DESC);
```

4. **유저의 name을 HASH해서 인덱싱 하기**
```sql
CREATE INDEX hash_idx ON users USING HASH(name);
```

## 1.5 GIN 인덱스 명령어 예시

1. content안의 단어들을 vector화 해줍니다 - 단어 토큰 생성
```sql
SELECT to_tsvector ('english', content) FROM boards;
```

2. vector화 된 단어들로 인덱싱을 해줍니다. 어떤 단어가 어디에 속해있는지 표시됩니다.
```sql
CREATE INDEX gin_idx ON boards USING GIN (to_tsvector('english', content));
```

content의 단어들을 벡터화 시킨다! 단어 토큰을 만든다! 이후, 단어 들이 어떤 content에 속해있는지 기록해준다. <Br>


3. **'time'이라는 단어가 들어 있는 content를 찾아 id와 title을 반환하기!!**
```sql
SELECT id, title
FROM boards
WHERE to_tsvector('english', content) @@ to_tsquery('time')
```

4. **측정 키워드:** `EXPLAIN` DB에게 해당 쿼리를 어떤 쿼리로, 어떤 속도로 처리할건지 설명하게 한다.. 
```sql
EXPLAIN SELECT * FROM public.accident
WHERE 발생일시 \< '2022-12-02' 
```
결과는 아래와 같이 나온다.
```
QUERY PLAN
index Scan using occurred_at_idx on accident (인덱스 탐색)
```
또는
```sql
Seq Scan on accident (순차 탐색)
```
위에서 언급한 인덱스를 통해 확인하겠다고 밝힌다. <br>

## 2. Transaction
POSTGRESQL의 Transaction은 **BEGIN;으로 시작해서 COMMIT;으로 끝난다!** <br>

```sql
BEGIN;
UPDATE customer
  SET phone_number = '010-1234-5678'
  WHERE name = '윤영'
SAVEPOINT savepoint1;
-- update membership logic
ROLLBACK TO savepoint1;
-- update address
COMMIT;
```

보다싶이 `BEGIN;`으로 시작해서 `COMMIT;`으로 끝난다. <br>

`SAVEPOINT`는 말 그대로 세이브 포인트를 남기는 것이다. 마치 게임 처럼 뭔가 잘못 되었을 때, 돌아갈 수 있는 포인트를 지정하는 것이다. <br> 
세이브 포인트 이후 membership을 업데이트 하는 로직이 있는데, 만약 이 부분에서 **에러가 생기면 savepoint1으로 돌아간다.** <Br>
이는 membership 로직 이후에 위치한 명령어 `ROLLBACK TO`를 통해 지정되었다. SAVEPOINT 덕분에, 힘들게 `BEGIN;`까지 갈 필요가 없다. <br>
성공적으로 마치면 주소를 업데이트 하고, `COMMIT;`을 통해 종료한다.


## 3. ROLE
PostgreSQL에서는 `ROLE`을 통해 사용자를 관리한다.
```sql
CREATE ROLE 롤이름;
DROP ROLE 롤이름;

-- 사용자 목록 보기
\du
```


1. 사용자 생성하기
```sql
CREATE user Jinho WITH PASSWORD 'binary-ho';
```

role이 없는 상태에서 user를 만들면, 진행이 안 된다. `\du`를 통해 확인해보면 아직 role이 없음을 알 수 있다. <br>

2. **ROLE 부여하기**
```sql
ALTER user Jinho WITH replication;
```
replication이라는 ROLE을 부여한 상황이다.

3. **특정 ROLE을 가진 사람에게 권한 부여하기**
```sql
GRANT SELECT ON boards TO replication
```
