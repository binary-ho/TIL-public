# firebase 쿼리 개선 경험
firebase db의 쿼리에 대해 학습한 다음, 현재 일하고 있는 학습 플랫폼 MANEE에서 사용하고 있는 쿼리를 개선해 보았다. <br>
쿼리 개선이라고 하니 매우 거창해 보이는데, 전혀 아니다. 마땅히 처음 부터 이렇게 작성했어야 하는 것을 이제서야 고친 것이다. <br>

## 1. 이번달에 공부한 적 있는 학생을 가져오는 메서드
이번달에 공부한 적이 있는 학생을 가져오는 메서드는 매달 순공부 시간의 랭킹을 보여주는 페이지에서 사용하는 메서드이다. <br>
기존 로직은 아래와 같은 순서로 흘러갔다
1. user의 공부 내용들이 기록되는 DB에서 전체 유저를 가져온다.
2. for문을 통해 모든 유저를 순회하며, 이번 달에 공부 시간이 있는 사람만 모은다.
3. 높은 순으로 정렬한다.
4. 유저 정보 DB를 전부 떼어온다.
5. 공부 시간이 있는 유저의 유저 정보를 보여준다.

<br>

아래는 기존의 로직 중 1, 2번에 해당하는 내용들이다.
```js
return this.app.database().ref(`유저공부정보`).once('value').then(snap => {
  let user_array = [];
  if (snap && snap.val()) {
    const 유저공부정보 = snap.val();
    Object.keys(유저공부정보).forEach(uid => {
      const 유저의이번달공부시간 = _.has(유저공부정보, [uid, '공부시간', '월별공부시간', monthTimestamp, '공부시간'])
        ? 유저공부정보[uid].공부시간.월별 공부 시간[monthTimestamp].공부시간 : 0;
      if (유저의이번달공부시간 !== 0) user_array.push({ uid: uid, 유저의이번달공부시간: 유저의이번달공부시간 });
    })
  }
```

유저의 공부 정보가 저장된 DB에서 유저 전체를 가져와서 순회한다. 유저가 적을 때는 문제 없지만, 많을 수록 느려지는 것이 당연하다.

### 개선
```js
const query = this.app.database()
      .ref(`유저공부정보`)
      .orderByChild(`공부시간/월별공부시간/${monthTimestamp}/공부시간`)
      .startAt(0);
    return query.once('value').then(snap => {
      const userArray = [];
      if (snap && snap.val()) {
        const 유저공부정보 = snap.val();
        Object.keys(유저공부정보).forEach(uid => {
          const 유저의이번달공부시간 = 유저공부정보[uid].공부시간.월별공부시간[monthTimestamp].공부시간;
          userArray.push({ uid, 유저의이번달공부시간: 유저의이번달공부시간 });
        });
      }
```
orderByChild를 통해 `유저 공부 정보` key의 value 중 `공부시간/월별공부시간/${monthTimestamp}/공부시간`를 key로 갖는 value를 가져올 수 있다. <br>
orderByChild는 친절하게도 해당 경로(value)가 없는 key는(user는) 탐색하지 않는다. <br>
startAt 0를 통해 0이상인 사람들만 가져올 수 있다. <br>
2번에서 발생하는 for문을 통한 유저 전체 순회를 성공적으로 없앨 수 있었다. <br>

### 추가로 개선해야 할점
firebase 쿼리는 value나 key를 정렬된 상태로도 가져올 수 있다. <br>
그러나 이 메서드 OrderByValue는 OrderByChild와는 함께 사용할 수 없다고 한다. <Br>
Firebase query에서 OrderBy는 중복될 수 없다고 한다. <br>
그래도 
1. 정렬된 상태로 유저 정보 가져오기
2. **join을 통해 유저 정보 전체를 가져오지 않도록 개선하기**

위와 같이 2가지 개선이 필요하다. <br>
firebase 공식 영상해서는 join 구현에 대한 가이드를 제공한다. <br>
하지만 내가 제대로 이해하지 못 한 것인지, 어째 매번 필요할 때마다 query를 날리는 것처럼 보인다. [영상](https://www.youtube.com/watch?v=Idu9EJPSxiY&t=1s) <br>
쿼리를 여러번 날리는 것은 미친짓이기 때문에 더 공부할 필요가 있다. <br>

추가적인 개선과 join도 빨리 도입해 보아야겠다.


## 2. 추천인의 UID를 가져오는 메서드
두 번째 개선은 추천인의 UID를 가져오는 메서드에 적용되었다. <br>
회원가입시 유저가 추천 코드를 입력하면, DB에서 해당 추천코드를 소유하고 있는 유저를 찾아내는 쿼리이다. <br>
기존에는 이 쿼리 또한 유저 전체를 가져와서 순회했다. <br>
```js
추천인아이디가져오기 = functions.https.onCall((초대코드, context) => {
  return this.app.database().ref('유저초대').once('value').then(snap => {
    const 유저초대 = snap.val();
    for (const uid of Object.keys(유저초대)) {
      if (유저초대[uid]['초대코드'] === 초대코드) {
        return uid;
      }
    }
    return null;
  });
});
```

### 개선

```js
추천인아이디가져오기 = functions.https.onCall((입력초대코드, context) => {
  return this.app.database().ref('유저초대')
    .orderByChild('초대코드').equalTo(입력초대코드)
    .once('value').then(snap => {
      return (snap && snap.val()) ? Object.keys(snap.val())[0] : null;
    });
});
```

훨신 낫다. <br>
`orderByChild`와 `equalTo`를 활용해 정확히 그 초대코드를 가진 유저만 한번에 가져온다! <br>
별것 아닌것 같지만, 여기서도 유저 전체를 가져와서 순회하는 for문이 사라진 만큼 O(N) 시간을 상수시간으로 줄일 수 있었다. 
