# What is "Callback"
in other words "called at the back" of the other function.
다른 말로 바꿔 말해서, Callback은 called at the back 을 의미한다!

## 그럼 콜백함수는?
**함수에 파라미터로 들어가는 함수. 코드를 순차적으로 실행하고 싶을 때 씁니다.** addEventListener나, setTimeout에 파라미터로 넣으면, 순차적으로 실행됩니다. 
```js
document.querySelector('.button').addEventListener('click', 함수명);
setTimeout(function () {

}, 1000);
```

### 어떻게 코드를 짜야 할까?
1. 파라미터를 함수로 받는 상황
```js
function first(parameter) {
  parameter();
}

first(function() { ... });
```

2. first, second 함수가 순차적으로 작동하길 원하는 상황
```js
function first(parameter) {
  console.log('first');
  parameter();
}
function second() {
  console.log('second');
}
// 순차적으로 실행되길 원합니다.
first(second);
```
순차적으로 무언가가 동작하길 바랄 때 굳이 callback 함수를 사용해야 하는 이유가 있을까? 그냥 순차적으로 쓰면? -> **단순히 순차적으로 쓰면, 혹시 모를 비동기적 실행에 의해 순서가 꼬일 수도 있다.** 
이에 대한 대비가 어렵기 때문에, 차라리 이렇게 콜백함수를 쓰는 편이 안전하다. 순차적 실행을 보장하기 때문. <br> 
예를 들어 db에서 데이터를 순서대로 뽑아야 할 때, 콜백 함수를 이용하는 것이 안전합니다. 코드는 좀 더럽겠지만 어쩔 수 없습니다. (프로미스나 에이싱크도 가능)
