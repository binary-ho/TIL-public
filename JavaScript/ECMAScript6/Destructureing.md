# Destructuring
말 그대로 구조화된 객체나 배열을 비구조화(파괴)하여 개별적인 변수에 할당하는 것입니다.
### 1. Array Destructuring
배열의 요소를 인덱스 기준으로 쉽게 추출하여 할당합니다.
```js
let x, y, z;
[x, y, z] = [1, 2, 3];
// 위의 구문과 동치
let [x, y, z] = [1, 2, 3];

const arr = [1, 2, 3];
const [one, two, three] = arr;

// 기본값도 가능
[x, y, z = 3] = [1, 2];

// spread 문법도 가능
[x, ...y] = [1, 2, 3];
```
다양한 표현이 가능하다. 예를 들어, Date 객체에서 년도, 월, 일을 추출할 때도 쓴다.
```js
// Tue May 21 2019 22:19:42 GMT+0900 (한국 표준시)
const today = new Date(); 

// "2019-05-21"
const formattedDate = today.toISOString().substring(0, 10); 

// [ '2019', '05', '21' ]
const [year, month, day] = formattedDate.split('-');
```
### 2. Object Destructuring
객체 디스트럭쳐링으로 객체의 프로퍼티들을 변수에 할당해줄 수 있습니다. 아래는 기존의 방식입니다.
```js
// ES5
var obj = { firstName: 'Ungmo', lastName: 'Lee' };
var firstName = obj.firstName;
var lastName  = obj.lastName;
```
더욱 간편해진 ES6 방식을 만나보세요!
```js
const obj = { firstName: 'Ungmo', lastName: 'Lee' };
const { lastName, firstName } = obj;
```
배열 디스트럭쳐링과 다르게, 순서는 의미가 없다. 이름이 중요하다. **그리고 할당 연산자 왼편에는 객체 형태의 변수 리스트가 와야 한다.** <br>
아래와 같은 방식도 가능하다.

```js
const { prop1: p1, prop2: p2 } = { prop1: 'a', prop2: 'b' };

// 축약하면?
const { prop1, prop2 } = { prop1: 'a', prop2: 'b' };

// 역시 기본값 설정도 가능!
onst { prop1, prop2, prop3 = 'c' } = { prop1: 'a', prop2: 'b' };
```
객체에서 프로퍼티 키로 필요한 프로퍼티 값을 추출 할 떄 씁니다.(당연) <br> <br>

응용해서 내게 필요한 프로퍼티를 가진 요소만 뽑아 올 때는 아래와 같이 표현해줍니다.
```js
const todos = [
  { id: 1, content: 'HTML', completed: true },
  { id: 2, content: 'CSS', completed: false },
  { id: 3, content: 'JS', completed: false }
];

// [ {id: 1, content: 'HTML', completed: true} ]
const completedTodos = todos.filter(({ completed }) => completed);

// [ {id: 2, ...}, {id: 3 ...} ]
const completedTodos = todos.filter(({ completed }) => 
  completed === false
);
```
