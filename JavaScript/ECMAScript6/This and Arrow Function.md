# ES6 This and arrow Function
호출 방식에 따라 동적으로 달라지는 `This` Java의 `This`와는 조금 다르기 때문에 주의해야한다. This는 매우 헷갈려 보일 수 있지만, 사실 통일된 규칙을 갖는다. 이를 이해하는 것이 중요하다. 전역 객체 개념 알아야함

## 일반 함수 정의
1. 객체에 소속되지 않은 함수 안에서: this === window
2. 객체에 소속된 메소드 안에서: this === 객체 <br> **이 둘은 사실 같은 결과이다.** 왜냐하면 전역 변수나 전역 객체는 window가 앞에 생략 되어있는 것이나 마찬가지이다. 그래서 1번의 함수를 호출 할 떄, `func()`로 호출했지만 사실 앞에 `window`가 생략된 것으로 실제로는 `window.func()`이 호출된 것과 같은 동작을 보이는 것이다.
3. 생성자 안에서 this: 어떤 함수가 생성자로 쓰인다면, this는 생성될 객체를 가르킨다. (함수의 경우엔 당연히 window) 
4. apply와 this: 어떤 객체와, 객체에 속한 메소드를 주인-노예 관계라고 부릅니다 (master-slave). apply를 통해 어던 **함수**를 특정 객체에 속하게 만들어 줄 수 있습니다. 예를 들어 그냥 함수 `func`에서 this를 호출하면 `window`를 호출하겠지만, **`func.apply(object)`와 같이 호출하면, this는 object를 가르키게 됩니다.**

결국, 
- **생성자 함수, 객체 메소드: 자기 주인 객체 가르킴.**
- **나머지 모든 함수 (내부함수, 콜백함수 포함)**: 전역 객체 가르킴.

### this 예제
다른 개념과 달리 좀 헷갈릴 수 있으니, 특별히 예제 첨부
```js
function Prefixer(prefix) {
  this.prefix = prefix;
}
Prefixer.prototype.prefixArray = function (arr) {
  // (A)
  return arr.map(function (x) {
    return this.prefix + ' ' + x; // (B)
  });
};
var pre = new Prefixer('Hi');
console.log(pre.prefixArray(['Lee', 'Kim']));
```
1. **(A)지점:** A지점의 this는 생성자 함수 Prefixer가 생성한 객체인 pre를 가르킨다.
2. **(B)지점**: B지점의 this는 pre였으면 좋겠지만, 전역객체 `window`를 가르킨다.

#### B지점 this가 객체를 가르켰으면 좋겠습니다!
3가지 방법을 봅시다.
1. **that으로 A지점에서 this 가로채기.**
```js
Prefixer.prototype.prefixArray = function (arr) {
  var that = this;  // this: Prefixer 생성자 함수의 인스턴스
  return arr.map(function (x) {
    return that.prefix + ' ' + x;
  });
};
```
위와 같이, A지점에서는 this가 객체를 가르키는 점을 이용하여, 미리 that이라는 이름으로 저장해 둡니다.
2. **map 이용, 생성자 함수의 인스턴스 사용하기.**
```js
Prefixer.prototype.prefixArray = function (arr) {
  return arr.map(function (x) {
    return this.prefix + ' ' + x;
  }, this); // this: Prefixer 생성자 함수의 인스턴스
};
```
크게 와닿지는 않는 형식 (그냥 아직 arr, map을 안 배워서 그런듯)
3. `Funtion.prototype.bind()`로 this 바인딩
```js
Prefixer.prototype.prefixArray = function (arr) {
  return arr.map(function (x) {
    return this.prefix + ' ' + x;
  }.bind(this)); // this: Prefixer 생성자 함수의 인스턴스
};
```

## this in arrow Function
화살표 함수에서의 this는 다르다. 일반 함수에서의 this는 호출 방식에 따라 바인딩할 객체가 동적으로 결정됩니다. 하지만, **화살표 함수에서는 함수를 선언할 때 this에 바인딩할 객체가 정적으로 결정됩니다!** <br> **화살표 함수의 this는 언제나 상위 스코프의 this를 가르킵니다.** 이거 완전히 달달하기 때문에 위의 3번 솔루션의 Syntactic Sugar라고 부릅니다.
```js
Prefixer.prototype.prefixArray = function (arr) {
  // this는 상위 스코프인 prefixArray 메소드 내의 this를 가리킨다.
  return arr.map(x => `${this.prefix}  ${x}`);
};
```
그럼 화살표 함수만 쓰면 되겠네! 정적인 this를 제공하면 프로그래머가 헷갈릴 일이 없겠네!
# 2. Arrow Function
화살표 함수의 Lexical this 덕분에, **화살표 함수는 콜백 함수로 사용하기 편리**하지만, 사용하는 것이 오히려 혼란을 야기하는 경우도 있습니다.
1. **메소드 금지**: 메소드로 정의한 화살표 함수 내부의 this는 아쉽게도 window를 가리킨다. 축약 메소드 표현을 사용하여 객체를 가리켜라.
```js
const person = {
  name: 'Lee',
  sayHi() { // === sayHi: function() {
    console.log(`Hi ${this.name}`);
  }
};

```
2. **생성자 함수 금지:** 화살표 함수는 생성자 함수로 사용할 수 없습니다. 생성자 함수는 `prototype` 프로퍼티가 가르키는 프로토타입 객체의 constructor를 통해 객체를 생성합니다. **그런데, 화살표 함수는 `prototype` 프로퍼티를 가지고 있지 않으므로, 생성자 함수로서의 사용이 불가능합니다.**
```js
const foo = new Foo(); // 불가능합니다!
```
3. **`prototype`에 메소드 할당할 때 사용 금지.**: 이 또한 window를 가르키는 문제 때문에 불가능합니다.
4. **`addEventListener`의 콜백함수:** 콜백함수로 쓰면 좋다고 했는데, 이 경우에는 안 됩니다. 이 때도 this가 상위 컨택스트인 전역 객체 window를 가르키게 됩니다.

