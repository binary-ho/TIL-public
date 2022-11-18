# firebase query advance
우리 회사는 Firebase를 쓴다. 이렇게 말 하면 웹, 모바일 프론트팀 학우들은 사용해 보았기에, 그리고 백엔드 학우들은 사파의 흑마술로 여겨 표정이 굳어 버린다. 
<br>

불친절한 도큐먼트에 삽질을 너무나도 많이 해봐서 나도 아주 아주 불만이 많지만 빠르게 서비스를 구축하기에는 이만한게 없다. 강력한 인증 기능 부터 DB기능까지.. <br>

어차피 NoSQL 이기도 하고, 몽고 디비처럼 강력한 쿼리를 제공하는 것도 아니니.. 대충 쿼리 메서드를 사용해왔다. <br>

어느날 쿼리 메서드를 복잡하게 사용할 일이 있어서 여러가지 고민을 하던 중이였다. <br>
알고 보니 firebase 쿼리도 join이 가능했다! 기쁘기 보다는 황당했다. 우리 회사 내에서도 이런 쿼리는 못 봤었기 때문이다. 그리고 join을 알아낸 김에 더 찾아보니, where 등도 제공했었다. <Br>
그걸 이제야 알게된 바보 같은 나.. 지금이라도 정신차리기 위해 각종 쿼리에 대해 공부한 내용을 정리하고, 직접 리펙토링을 진행해보겠다. <br>

나도 사실은 앞으로 firebase를 사용할 일이 얼마나 있을까 더는 공부하고 싶지 않지만, 미우던 이쁘던 현재 사용중인 기술이므로, 최대한 잘 쓰기 위해 노력하는 것이 올바른 개발자의 자세라고 생각하기 때문에 한번 공부해봤다.

## 1. 기본 쿼리 구조
파이어베이스 쿼리는 두 단계로 나뉘어져 있다.
```js
dbReference.orderFunction().queryFuntion();
```
## 1. `orderFunction()`: 순서를 정함. 
표현이 모호한데, 값을 비교해서 가져오는 기준을 key로 할건지 value로 할것인지를 정하는 부분이라고 생각하면 된다. <br>
보통 key로 가져올 때는 key의 값을 통해 가져온다기 보다는 페이징등을 위해 사용한다.
예를 들면, 아래 코드는 10개의 자료를 가져오는 쿼리를 작성해준다.
```js
dbRef.orderByKey.limitToFirst(10);
```

현재 사용 가능한 orderFunction에는 3가지 종류가 있다. 
1. `orderByKey()`
2. `orderByChild('child_property')`: 이걸 자주 사용. `WHERE` 같은 부분, 뒤에 쿼리 펑션을 붙여주면 완성
3. `orderByValue()`: 모든 child가 value를 기준으로 order됨



## 2. `queryFuntion()`
더욱 세세한 제한을 위한 기능이다. 몇 개의 예시를 보겠다.
### 2.1 `limitToFirst`, `limitToLast`
그냥 제한용 함수

```SQL
SELECT *
FROM Events
WHERE Name == "Jinho's Chicken Party"
LIMIT 1;
```

```js
const query = db.child('events')
                .orderByChild('name')
                .equalTo(`Jinho's Chicken Party`)
                .limitToFirst(1);
```

### 2.2 `equalTo('child_key')`
**활용도가 높다! value의 equal 체크용 메서드** <br> where 문을 변환하는 과정을 살펴보자.
```sql
SELECT *
FROM Users
WHERE Email = 'jinho@email.com';
```
```js
const query = reference.child('users')
                      .orderByChild('email')
                      .equalTo('jinho@email.com');
```
간단하게 변환이 가능하다!

### 2.3 `startAt('value')`, `endAt('value')`
나는 이 두 function이 웬지 쓸모없게 느껴졌었다. 값을 제한해주는건 좋은데 지금 일 하는 곳에서는 크게 필요가 없었으니까.. <br> 
그런데 더 찾아보니 **이 기능을 활용하면 와일드카드를 구현하는 치팅이 가능하다!** <br>
Like문을 쓰는 상황에서 와일드카드는 너무나도 유용하다! 그런데 firebase에서는 와일드카드를 제공하지 않는다. 위 두 쿼리를 통해 구현 가능하니 한번 살펴보자.

```SQL
SELECT *
FROM Users
WHERE Name LIKE 'D%';
```
위와 같은 쿼리는 아래와 같이 나타낼 수 있다.

```js
const query = reference.child('users')
                      .orderByChild('name')
                      .startAt('D')
                      .endAt('D\uf8ff');
```
`\uf8ff`는 유니코드의 가장 마지막 포인트다. 따라서   `D` ~ `D\uf8ff`는 `D%`와 같은 효과를 내는 것이다!



## 3. join 연산
아래와 같은 Json 형식의 데이터가 있다
```json
{
  "user": {
    "1": {
      "name": "Jinho",
      "bio": "hihihihihi"
    },
    "2": {
      "name": "Dongho",
      "bio": "hi there"
    },
    ...
  }
  "events": {
    "fm": {
      "name": "Chicken Party",
      "date": "2211182000"
    }
  }
  "eventAttendess": {
    "fm": {
      "1": "Jinho",
      "2": "Dongho",
      ...
    }
  }
}
```
최상위 키는 `users`, `events`, `eventAttendess`
users의 key는 숫자로 이루어져 있다. events와 eventAttendess의 키는 같고, eventAttendess의 events정보 안에는 참여자의 정보가 user key로 들어가 있다.

```js
const rootReference = firebase.database().ref();
const attendees = db.child('eventAttendess/fm');

let handles = [];
attendees.on('child_added', snap => {

  let userReference = db.child('users/' + snap.key);
  userReference.once('value').then(userSnap => {

  });
});
```
다음과 같은 쿼리를 통해 `eventAttendess/fm`의 key값을 받아와서 `users/`뒤에 붙여준 다음 가져오는 느낌이다. <br>
이런 쿼리를 통해 firebase에서도 join연산을 구현할 수 있다.

## Reference
- [Wildcard query on Firebase?](https://stackoverflow.com/questions/36365157/wildcard-query-on-firebase)
- [Firebase Database Query 101 - Firebase Database for SQL Developers](https://www.youtube.com/watch?v=3WTQZV5-roY&list=PLl-K7zZEsYLlP-k-RKFa7RyNPa9_wCH2s&index=4)
- [Converting common SQL queries from Firebase databases - Firebase databases for SQL developers](https://www.youtube.com/watch?v=sKFLI5FOOHs&list=PLl-K7zZEsYLlP-k-RKFa7RyNPa9_wCH2s&index=5)
- [How to Use JOIN in a Firebase Database - A Firebase Database for SQL Developers](https://www.youtube.com/watch?v=Idu9EJPSxiY&list=PLl-K7zZEsYLlP-k-RKFa7RyNPa9_wCH2s&index=6)
