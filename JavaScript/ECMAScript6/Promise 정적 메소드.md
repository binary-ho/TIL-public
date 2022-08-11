# 프로미스 정적 메소드!
Promise는 주로 생성자 함수로 사용되지만 함수도 객체이므로, 메소드를 갖을 수 있다. Promise 객체는 4가지의 정적 메소드를 제공합니다.

## 1. `Promise.resolve/Promise.reject`
`Promise.resolve`와 `Promise.reject` 메소드는 존재하는 값을 Promise로 래핑하기 위해 사용하는 메소드입니다. <br> 아직은 그 용도를 이해하지 못 하고 있으나, 분명 `Promise.all()`과 같은 메소드를 활용할 때 처럼 억지로 Promise를 만들어 주어서 처리해 주어야 하는 일들에 쓰일 것 같습니다. <br> <br> 

정적 메소드 Promise.resolve 메소드는 인자로 전달된 값을 resolve 하는 Promise를, Promise.reject 메소드는 인자로 전달된 값을 reject하는 Promise를 생성합니다. <br> <br>

말이 좀 어려운데, `Promise.resolve()`를 걸어주면 해당 프로미스는 프로미스가 성공 했을 떄, 즉, `.then()`에서 `resolve()` 메소드의 인자로 전달된 값을 실행합니다. <br>
똑같이 Promise의 `.catch()`에서 `Promise.reject()`에 인자로 전달해준 값을 실행하게 됩니다. <br> <br>

그래도 좀 모호한데, 동작하는 모습을 보이겠습니다.
```js
// 아래 두 문장은 똑같은 동작을 합니다.
const resoloedPromise = Promise.resolve([1, 2, 3]);
const resolvedPromise = new Promise(resolve => resolve([1, 2, 3]));
resolvedPromise.then(console.log); // [1, 2, 3]


// 아래 두 문장은 똑같은 동작을 합니다.
const rejectPromise = Promise.reject(new Error('Error!'));
const rejectPromise = new Promise((resolve, reject) => reject(new Error('Error!')));
rejectPromise.catch(console.log);
```

## 2. `Promise.all()`
`Promise.all()` 메소드는 프로미스가 담겨있는 배열과 같은 이터러블을 인자로 받습니다! **그리고 전달받은 모든 프로미스를 병렬로 처리하고,** 모든 프로미스의 처리가 종료될 때까지 기다립니다. 그리고 그 모든 처리 결과를 resolve하는 새로운 프로미스를 반환합니다. (또는 rejcet)

```js
Promise.all([
  new Promise(resolve => setTimeout(() => resoleve(1), 100000))
  new Promise(resolve => setTimeout(() => resoleve(2), 10000))
  new Promise(resolve => setTimeout(() => resoleve(3), 1000))
]).then(console.log)  // [1, 2, 3]
  .catch(console.log);
```
위의 실행 결과 (.then()): `[1, 2, 3]`  <br>
- 첫 번째 프로미스는 100초 후 1을 resolve하여 처리 결과를 반환함
- 두 번째 프로미스는 10초 후 2를 resolve하여 처리 결과를 반환함
- 세 번째 프로미스는 1초 후 3을 resolve하여 처리 결과를 반환함

`Promise.all()` 메소드는 전달 받은 모든 프로미스를 병렬로 처리하게 되는데, 
1. **모든 처리가 종료될 때까지 기다린 다음 모든 처리 결과를 resolve 또는 rejcet 한다.** 모든 프로미스의 처리가 성공하면, **각각의 프로미스가 resolve한 처리 결과를 배열에 담아 resolve하는 새로운 프로미스를 반환한다.** 
2. **처리 순서가 보장된다.** 첫 번째 프로미스는 분명 가장 마지막에 처리되지만, `Promise.all()` 메소드가 반환하는 프로미스는 첫 번째 프로미스가 resolve한 처리 결과부터 **알아서 차례대로 배열에 담아 그 배열을 resolve 하는 새로운 프로미스를 반환한다.** 
3. 하나라도 프로미스 처리가 실패하면, **시간상 가장 먼저 실패한 프로미스**가 reject한 에러를 reject 하는 새로운 프로미스를 즉시 반환한다. 
4. `Promise.all()` 메소드는 전달 받은 이터러블의 요소가 프로미스가 아닌 경우, 아래와 같이 Promise.resolve 메소드를 통해 프로미스로 래핑된다.
```js
// 자동 래핑
Primise.all([1, 2, 3])  // => Promise.resolve(1), (2), (3)
  .then(console.log)
  .catch(console.log);
```

<br> **쓸만해 보이는 예제가 있어서 가져왔다.** github id로 github 사용자 이름을 취득하는 예제이다.

```js
const githubIds = ['jeresig', 'ahejlsberg', 'ungmo2'];

Promise.all(githubIds.map(id => fetch(`https://api.github.com/users/${id}`)))
  .then(responses => Promise.all(responses.map(res => res.json())))
  // [user, user, user] => Promise
  .then(users => users.map(user => user.name))
  // [ 'John Resig', 'Anders Hejlsberg', 'Ungmo Lee' ]
  .then(console.log)
  .catch(console.log);
```
`Promise.all()` 메소드의 첫 줄 fatch 함수가 반환한 3개의 프로미스의 배열은 병렬처리된다. `[Response, Response, Response] => Promise` <br> 모든 프로미스 처리가 성공하면, 첫 번째 `.then()`에서, 각각의 프로미스가 resolve한 3개의 Response 객체가 담긴 배열 (위에서 보인 배열)을 resolve하여 전달합니다. 이 때 json 메소드가 프로미스를 반환하므로 한번 더 `Promise.all()`을 호출합니다. 그러면 github로 부터 취득한 3개의 사용자 정보가 담긴 배열을 resolve 하는 프로미스를 반환합니다. <br> 두 번째 Promise then에는 3개의 사용자 정보 객체가 담긴 배열이 전달되게 됩니다. <br>

## 3. `Promise.race()`
`Promise.all()`이 병렬적으로 프로미스를 처리한다면, `race()`는 순서대로 **처리된 프로미스가 resolve한 결과를 resolve하는 식으로 작동한다.** 실패시에는 똑같이 가장 먼저 실패한 프로미스가 rejcet한 error를 reject한다.


## Reference
https://poiemaweb.com/es6-promise
