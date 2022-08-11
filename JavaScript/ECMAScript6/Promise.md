# Promise - ES6
Promise is "Return type of functions which does asynchronous task" -> 비동기적으로 작동하는 함수들은 프로미스 타입 객체를 반환합니다. **비동기 처리, 작동방식을 통일하기 위해 나온 표준 인터페이스가 Promise입니다.** <br>

특별히 새로운 것은 아닙니다. 어떤 비동기함수가 있을 때, 성공했을 때와, 실패했을 때 호출되는 콜백 함수가 있다고 해봅시다. **이 두 함수를 모두 가지고 있는 객체가 Promise 객체가 되겠습니다.** 원래는 콜백함수들을 받는 형태가 보통인데, Promise로 감싸주기만 하면 됩니다. 아래에 예시를 보이겠습니다.

```js
function doSomthingAsync(onSuccess, onError) {
  // call onSuccess() or onError()
}

// Promise 적용 - 불필요한 매개함수 없고, 반환 타입이 통일됨
function doSomthingAsync() {
  return new Promise(
    function(resolve, reject) {
      // do somthing
      if(success) { resolve(); }
      else { reject(); }
    }
  );
}
```
프로미스 인스턴스는 `then`과 `catch` 함수를 지원합니다. `then`은 성공 했을 때, `catch`는 실패 했을 때 실행할 함수를 전달해줍니다. 
```js
function doSomethingAsync() {
  return new Promise( ... );
}

// p is instance of Promise
const p = doSomethingAsync();

// 체이닝 한 모습 
p.then(onSuccess)
 .catch(onError);
```
마지막은 체이닝을 한 모습입니다. 기존의 지옥 같은 콜백함수 문제점(?)들을 해결 하기 위해 저런 식으로 체이닝을 했었습니다. 하지만 지금은 더 나은 방법인 `async/await` 방식이 권장된다고 합니다.

<br> <br>
프로미스 체이닝은 아래와 같이도 가능합니다.

```js
promiseObject()
  .then(foo())
  .then(foo2())
  .then(foo3())
  .catch(console.error);
```

## `async/await`
Promise를 더 편하게 쓸 수 있는 방법입니다. 단순해 보이는 기능이지만, Promise를 주류로 만들어준 1등 공신이 바로 `async/await`입니다. 꼭 Promise를 써야만 `async/await`를 이용할 수 있기 때문입니다. 이게 왜 좋은걸까요? **바로 비동기적인 코드를 동기적으로 보이게 만들어주기 때문입니다.** 기존의 Promise를 적용한 코드는 아래와 같았습니다.
```js
function test() {
  fetch("https://api.testdomain.com")
  .then(response => {
    // do something success
  })
  .catch(error => {
    // handle error
  }
  );
}
```
여기에 `async` 키워드를 앞에 붙여주면, `then`은 `await` 키워드가 대신해주고, `catch`는 다른 언어의 예외 처리 구문인 `try/catch`와 같은 꼴로 처리해줄 수 있습니다.
```js
async function test2() {
  try {
    const response = await fetch("...url...");
    // do something
  } catch (error) {
    // handle error
  }
}
```

그래서 왜 좋냐.. 체이닝 방식은 내부에서 사용한 식별자들의 스코프가 좁기 때문에, 안정성이 높습니다. `async/await`은 안정성이 낮은 대신에, 보통 사람들이 많이 사용하는 명령형 프로그래밍 방식과 동기화 작업이 유사합니다.

### 비동기 함수를 동기적으로..!
```js
function wait(duration) {
  return new Promise(resolve => {
    setTimeout(resolve, duration);
  });
}

async function run() {
  // do something
  await wait(1000);
  // do something
}

```
wait 함수는 setTimeout 함수를 Promise로 감싸서 실제 사용할 때 동기함수처럼 이용 가능하도록 도와줍니다. 원래 Promise를 지원하지 않는 비동기 함수를 Promise함수로 바꿔줍니다. run은 async/await 문법을 활용해서 간편하게 일정 시간동안 다음 코드 실행을 멈춰줍니다!! <br> 
비동기함수 setTimeout의 콜백함수에 프로미스의 resolve 함수를 넣어줘서, 대기시간이 지났을 때 resolve 함수를 호출하도록 처리하였습니다. **비동기 작업을 논리적인 동기 작업처럼 만들어주기 편합니다.**
```html
<div class='root'></div>
```
```js
function show() {
  return new Promise(resolve => {
    const popup = document.createElement('div');
    const ok = document.createElement('button');
    popup.appendChild(ok);

    document
      .querySelector('div.root')
      .appendChild(popup);
    
    ok.addEventListener('click', () => {
      resolve();
      popup.remove();
    });
  });
}

async function run() {
  // do something
  await show();
  // do something
}
run();
```

## Reference
https://poiemaweb.com/es6-promise
