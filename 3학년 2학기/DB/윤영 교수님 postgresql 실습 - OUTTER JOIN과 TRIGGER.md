# postgresql 실습 - OUTTER JOIN과 TRIGGER  
(윤영 교수님 database 수업의 실습입니다.)
## 1. OUTTER JOIN
Outter Join은 연관되지 않은 자료까지 모두 가져오는 join이다. <br>
기존의 JOIN 연산은 두 테이블간의 연관이 존재하는 정보들만 합쳐 가져오는 연산이였다. <br>
**OUTTER JOIN은 이와 달리, 결과가 없는 튜플들도 가져온다!** 이럴 경우 Projection을 건 컬럼 따라 비어있는 곳이 있을 수 밖에 없는데.. **OUTTER JOIN에선 그냥 가져온 다음 NULL을 보여준다.**  <br>


## 2. LEFT RIGHT FULL
OUTTER JOIN은 LEFT OUTTER JOIN, RIGHT OUTTER JOIN, FULL OUTTER JOIN의 3가지 종류가 있다. 그냥 간단하게, **LEFT JOIN, RIGHT JOIN, FULL JOIN로 부른다.** 
1. **LEFT JOIN:** **왼쪽에** 있는 데이터를 모두 가져옴. 오른쪽은 없는 경우 그냥 NULL 
2. **RIGHT JOIN:** **오른쪽에** 있는 데이터를 모두 가져옴. 왼쪽은 없는 경우 그냥 NULL 
3. **FULL JOIN:** **양쪽의 데이터를 모두 가져온다.** 없는 컬럼은 없는대로 그냥 NULL


## 3. 용례
```sql
SELECT canned_food.name, sum(can_rating.rating)
FROM canned_food
  LEFT JOIN (
    SELECT *
    FROM rating
    WHERE item_type = 'canned_food'
  ) can_rating
  ON canned_food.id = can_rating.item_id
GROUP BY canned_food.name;
```
1. 캔 음식을 이름별로 그룹 바이 (같은 이름끼리 묶음)
2. 이름과 받은 점수 합을 가져온다.
3. **FROM에 LEFT JOIN이 있다.** <br> `canned_food` 테이블과 `rating` 테이블을 LEFT JOIN하는데, `rating`에서 캔으로 된 음식만 가져온 다음, 조인하는데, **canned_food에서 canned_food.id와 can_rating.item_id가 같은 부분 튜플만 join된다.**
4. 일단 가져온 다음 엮어주는 것 

아래와 같은 결과가 도출된다. <br>

|       |    name     |  sum  |
| :---: | :---------: | :---: |
|   1   |   "삼치"    |   3   |
|   2   | "고추참치"  | null  |
|   3   |   "참치"    | null  |
|   4   |   "연어"    |  11   |
|   5   | "곰과 연어" |   1   |

rating 된 적 없는 고추참치와 참치는 null 값이 들어와 있다.

## 4. COALESCE
COALESCE는 NULL값의 처리를 위한 문법이다. <br>
위의 예시에서 `sum(can_rating.rating)`의 결과가 null인 경우가 참치와 고추참치로 두 경우가 있었는데, COALESCE를 사용하면 NULL일 경우 지정해둔 값으로 채울 수 있게 된다. <br>
`COALESCE(sum(can_rating.rating), 0)`
```sql
SELECT canned_food.name, COALESCE(sum(can_rating.rating), 0)
FROM canned_food
  LEFT JOIN (
    SELECT *
    FROM rating
    WHERE item_type = 'canned_food'
  ) can_rating
  ON canned_food.id = can_rating.item_id
GROUP BY canned_food.name;
```

그럼 아래와 같은 결과를 받아볼 수 있다. <br>

|       |    name     |  sum  |
| :---: | :---------: | :---: |
|   1   |   "삼치"    |   3   |
|   2   | "고추참치"  |   0   |
|   3   |   "참치"    |   0   |
|   4   |   "연어"    |  11   |
|   5   | "곰과 연어" |   1   |

## 5. OUTTER JOIN 실습 문제
### 1. 물건의 아이디와 타입을, 해당 물건들의 평균 평점과 함께 보여라
```sql
SELECT item_type, item_id, avg(rating.rating) AS rating
FROM rating
GROUP BY item_type, item_id;
```
## 2. 모든 상품의 평균 평점을 상품 이름, 종류와 함께 출력하시오

```sql
SELECT items.name, items.item_type, AVG(items.rating)
FROM
(SELECT d.name as name, rt.rating as rating, COALESCE(rt.item_type, 'drink') as item_type
 FROM drink d LEFT JOIN rating rt 
 ON d.id = rt.item_id AND rt.item_type = 'drink'
UNION
SELECT r.name as name, rt.rating as rating, COALESCE(rt.item_type, 'ramen') as item_type
 FROM ramen r LEFT JOIN rating rt 
 ON r.id = rt.item_id AND rt.item_type = 'ramen'
UNION
SELECT c.name as name, rt.rating as rating, COALESCE(rt.item_type, 'canned_food') as item_type
 FROM canned_food c LEFT JOIN rating rt 
 ON c.id = rt.item_id AND rt.item_type = 'canned_food') items
GROUP BY items.name, items.item_type;
```
위와 같은 쿼리는 아래와 같은 결과를 만들어 낸다.
|      name      |   item_type   | avg_rating |
| :------------: | :-----------: | :--------: |
|   "리얼짬뽕"   |    "ramen"    |   [null]   |
|   "무안단물"   |    "drink"    |   [null]   |
|   "순진맥주"   |    "drink"    |   [null]   |
| "에너지드링크" |    "drink"    |     1      |
|     "참치"     | "canned_food" |   [null]   |
|  "오렌지주스"  |    "drink"    |   [null]   |
|  "오랜지주스"  |    "drink"    |   [null]   |
|   "고추참치"   | "canned_food" |   [null]   |
|     "삼치"     | "canned_food" |     3      |
|  "고추짜장면"  |    "ramen"    |     2      |
|  "곰과 연어"   | "canned_food" |     1      |
|     "더맛"     |    "drink"    |     3      |
|  "겨울이라면"  |    "ramen"    |     2      |
|     "연어"     | "canned_food" |     2      |
|    "진라멘"    |    "ramen"    |     4      |
|   "추풍라면"   |    "ramen"    |     1      |


## 6. Trigger와 함수

트리거는 이름 그대로 어떤 '사건'이 일어났을 때, 자동으로 DB에서 이런 저런 처리를 해주는 기능이다. <br> 
나는 당연히 이런 부분들이 백엔드 단에서 이루어져야 한다고 생각했는데, DB단에서 하는게 편하면 그냥 그렇게 한다고 한다.  <br>

ex) 예시로 코드들을 보는 것이 빠르다. <br>
Trigger: 유튜브 구독 버튼을 누르는 경우, 구독자 정보 갱신 및 구독자 수 늘리기 <br>
구독자 정보가 갱신되면 구독자 수가 늘어나는 예시입니다. <br>

1. 테이블들
```sql
CREATE TABLE subs_table (
  subs_id INTEGER,
  subs_name VARCHAR(80)
);

CREATE TABLE num_subs (
  subs_num INTEGER
);
```

2. 구독자 수 설정
```sql
INSERT INTO num_subs VALUES(0);
```

3. **함수 만들고 트리거 달아주기**
```sql
CREATE FUNCTION inc()
RETURNS TRIGGER AS
$$BEGIN
UPDATE num_subs SET subs_num = subs_num + 1;
RETURN NULL;
END;$$
LANGUAGE PLpgSQL;

CREATE TRIGGER subs_insert AFTER INSERT ON subs_table
FOR EACH ROW EXECUTE PROCEDURE inc();
```

1. `inc()`라는 함수를 정의했습니다. 
2. TRIGGER를 리턴하는데, num_subs의 값을 ++ 해주는 트리거를 리턴합니다.
3. 트리거를 만듭니다. **지정한 table에서 INSERT가 일어나면 발동됩니다.**
4. **막 삽입된 열들에 대해 각각 inc를 실행합니다.**


이렇게 설정 해주면, 구독자 정보가 설정되면, 즉 **subs_table에 뭔가가 INSERT 되면, num_subs를 UPDATE합니다.** <br>
백엔드 단에서는 아마 구독자가 생기면 구독자 정보를 입력할 것입니다. 이에 맞춰 구독자 수를 늘려주는 연산이 DB에서 실행됩니다. <BR>
이는 생각해보면 매우 편리한 기능입니다. 어차피 백엔드 단에서도 구독자 수를 받아와서 1만큼 늘려줬을 텐데, 커넥션 없이 바로 구독자 수를 늘릴 수 있으니 아주 좋은 상황이라고 할 수 있습니다.

5. 잘 들어갔나 확인해봅시다
```sql
SELECT * FROM num_subs;
```

6. 기타 메서드
```sql
\du -> 모든 유저 보기
\dt -> 모든 테이블 보기
\df -> 모든 함수 보기
```
## Reference
- [장동호](https://github.com/jjddhh)
