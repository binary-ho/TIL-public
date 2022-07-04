# What is "Callback"
in other words "called at the back" of the other function.
다른 말로 바꿔 말해서, Callback은 called at the back 을 의미한다!


# RESTful
Representational State Transfer
1. **URI는 Resource 중심**
2. 자원에 대한 행위는 **HTTP Method**로 표현


### REST API
REST API는 자원(Resource), 행위(Verb), 표현(Representations)의 3가지 요소로 구성된다.
|구성 요소|내용|표현 방법|
|:---:|:---:|:---:|
|**Resource**|자원|HTTP URI|
|**Verb**|자원에 대한 행위|HTTP Method|
|**Representations**|자원에 대한 행위의 내용|HTTP Message Pay Load|


# Ajax 통신


# JSON
JSON 으로 데이터를 주고 받음. Ajax 통신을 위해 html, css, js 파일을 주고 받는 것이 아니라 **데이터를 교환**하기 위한 규칙, 데이터 포맷을 말 하는 것<br>
- 객체 -> JSON: 직렬화 `JSON.stringify(object);`
- JSON -> 객체: 역직렬화(Deserializing), `JSON.parse(object);`

# XMLHttpRequest
브라우저는 XMLHttpRequest 객체를 이용하여 Ajax Request를 생성하고 전송하고 처리합니다.
```js
XMLHttpRequest.open(method, url[, async])
```


|매개변수	|설명|
|:---:|:---:|
|method	|HTTP method (“GET”, “POST”, “PUT”, “DELETE” 등)|
|url	|요청을 보낼 URL|
|async	|비동기 조작 여부. 옵션으로 default는 true이며 비동기 방식으로 동작함|

# DOM
Document Object Model

## HTMLCollection
반환 값이 HTMLCollection인 경우에는 유의. 이는 유사배열로, 변화가 바로 반영되는 객체이다. 이를 live하다고 표현한다. 마치 vector에서 erase할 때 처럼, 변화가 바로 반영되기 때문에, 길이가 계속해서 변해버릴 수가 있기 떄문에 반복문을 통해 어떤 처리를 할 때는 항상 유의해야한다. 
1. **역순으로 접근하기**: 계속 변화가 일어나서, 유사배열 안의 원소들이 갑자기 사라지거나 할 수 있는데, 그래도 문제가 발생하지 않도록 **인덱스 역순 부터 접근하는 방식이다.**
2. **배열로 변경하기**: 권장하는 방법임
```js
const elems = document.getElementsByClassName('red');

// 유사 배열 객체인 HTMLCollection을 배열로 변환한다.
// 배열로 변환된 HTMLCollection은 더 이상 live하지 않다.
console.log([...elems]); // [li#one.red, li#two.red, li#three.red]

[...elems].forEach(elem => elem.className = 'blue');
```
3. 애초에 NodeList로 받기 `querySelectorAll`
```js
// querySelectorAll는 Nodelist(non-live)를 반환한다. IE8+
const elems = document.querySelectorAll('.red');
[...elems].forEach(elem => elem.className = 'blue');
```


# 

1. 모든 수를 실수 처리함.
2. string은 작은 따옴표로 나타내라.
3. 문자열은 변경이 불가능하다. 새로운 문자열을 메모리에 생성하고 할당할 뿐. 그냥 새로운 문자열을 가르킬 뿐이다.
4. 문자열은 유사배열이라 인덱스 접근이 가능하다. 이 경우 인덱스로 일부 문자를 변경해도 반영이 되지 않는다. 또한 에러도 뜨지 않는다.
5. 문자열은 더하기 연산도 먹한다. 새로 할당하는 것이지만.
6. **비어있는 문자열**, `null`, `undefined`, 0은 `false`로 간주됨.
7. `undefined`는 선언 이후 값을 할당하지 않은 변수! 실제로 개발자가 `undefined`을 할당해 주는 것은 원래 취지와 혼동될 가능성이 있으므로, 사용하면 안 된다.. 대신 `null`을 써라
8. `null`은 `Null`, `NULL`과는 다르다 소문자 주의.
9. `typeof`연산자로 null 값을 연산하면 null이 아닌 object가 나옵니다. (설계상 오류) **따라서 `null` 타입인지 확인 할 때는 typeof 연산자가 아닌 일치연산자 `===` null을 이용해야한다.**
10. 변수의 중복 선언이 가능. 값을 덮어 쓴다. 위험한듯 하다. 문법적으로는 허용되지만, 사용하지 않는 것이 좋다.
11. 호이스팅(Hoisting)에 대한 이해 필요. **마치 모든 선언문이 해당 Scope의 선두로 옮겨진 것처럼 동작하는 특성.** 모든 선언문은 선언되기 이전에 참조가 가능하다. 단, 선언만 옮겨가는 것이기 때문에, 할당문 이전까지는 값을 참조해도 `undefine`을 반환하게 된다. 실제 코드레벨에서 옮겨간다기 보다는, **변수 객체가 미리 등록되고, undefined로 초기화 되는 것이다.**

### 12. **var 키워드로 선언된 변수의 문제점**
`var` 키워드는 다른 C-family 언어와는 달리 **함수 레벨 스코프**를 가지고 있습니다. (C-family는 보통 블록 레벨 스코프)  ES6 전에는 이 `var`이 유일한 변수 선언 키워드이기 때문에, 많은 문제가 있었고, 이는 명백한 **설계 오류**입니다. 
1. 함수 레벨 스코프
- 전역 변수 남발
- for loop 초기화 식에서 사용한 변수를 외부 또는 전역에서도 참조가 가능함
2. var 키워드 생략 허용 - 의도치 않게 변수가 전역화됨.
3. 중복 선언 허용 - 의도하지 않게 변수값을 변경하는 일이 발생함.
4. 변수 Hoisting - 변수를 선언하기 전에 참조가 가능함

이를 위한 해결방법으로 ES6에서 `let`과 `const`가 도입 되었습니다.

### 블록 레벨 스코프 변수 `let`
1. 블록 레벨 스코프를 따릅니다.
2. 변수를 중복 선언 할 수 없습니다.
3. Hoisting은 비슷합니다. **하지만, let 키워드로 선언된 변수는 선언문 이전에 참조시 참조에러(ReferenceError)가 발생합니다.** let 키워드로 선언된 변수는 **스코프의 시작에서 변수의 선언까지 일시적으로 사각지대에 빠지기 때문입니다.** (Temporal Dead Zone; TDZ) .`var`는 그냥 `undefine`이 떴던 것과는 대조적입니다. <br> <br> 이는 호이스팅 방식의 차이에서 오게 되는데, 호이스팅은 선언 단계 -> 초기화 단계 -> 할당 단계의 세 단계로 나누어집니다. **실행 컨텍스트**의 변수 객체에 변수를 등록하고(선언) -> 이를 위한 공간을 할당하고(초기화) -> 실제로 값을 할당합니다.(할당) <br> `var`은 선언과정과 초기화 과정이 동시에 일어나기 때문에, (`undefine` 으로) 값을 참조해도 오류가 뜨지 않았던 것이고, `let`은 실제 배정문 까지는 초기화를 하지 않기 때문에 참조시 오류가 발생했던 것입니다. 그런데 이런 식이면 호이스팅이 없는 것과는 뭐가 다른걸까요? <br> <br> 
```js
let foo = 1; // 전역 변수
{
  console.log(foo); // ReferenceError: foo is not defined
  let foo = 2; // 지역 변수
}
```
위와 같은 예제에서 foo는 원래대로라면 블록 밖의 foo를 참조해야 하지만, 이 경우에는 블록 안의 foo를 참조하여 참조에러가 발생됩니다.  <br> **`let`의 호이스팅은 블록의 맨 위로 선언문을 옮긴 것과 같게 이루어진다고 이해하면 될 것 같습니다.**
4. 자유변수?, 클로저
5. 전역 객체와 `let`: `var`로 전역 변수를 만들면 전역 객체의 프로퍼티가 된다. **`let`키워드로 선언된 변수를 전역 변수로 사용하는 경우에는 `let` 전역 변수는 전역 객체의 프로퍼티가 아닙니다.** <br> <br> 
```js
var foo = 123; // 1. var 전역변수
console.log(window.foo); // 123
```
```js
let foo = 123; // 2. let 전역변수
console.log(window.foo); // undefined
```
Browser-side의 전역 객체 `window`와 Server-side 전역 객체 `global` 객체를 이용한 접근입니다. 1번과 같은 접근은 가능한데, 2번과 같은 접근은 불가능합니다. **`let` 전역변수는 보이지 않는 개념적인 블록 내에 존재하게 됩니다.**

### 상수 `const`
`let`과 대부분 동일합니다. **블록 레벨 스코프를 갖습니다.** 꼭 상수만을 위해 쓰는 개념은 아닙니다.
1. 재할당 금지 + 선언과 동시에 할당이 이루어져야함.
2. 상수로 쓸 때는 식별자를 대문자로 
3. 객체로 쓸 때, 참조는 변경하지 못 하지만 프로퍼티는 변경할 수 있다. (보호되지 않음)

### var vs. let vs. const
1. `var` 금지
2. 재할당이 필요한 경우에만 한정해 `let` 사용. 스코프는 최대한 좁게 만듭니다.
3. 재할당이 필요 없는 원시 값과 객체에는 `const` 키워드 사용. `const`가 안전하다.
일단 선언 시점에는 재할당이 필요할지 잘 모르기 때문에 일단 `const`로 선언한 다음 재할당이 필요하면 그 때 바꿔라.


# 실행 컨텍스트

[실행 컨텍스트](https://poiemaweb.com/js-execution-context)
물리적으로는 객체의 형태를 가진다. 그리고 3가지 프로퍼티를 소유한다. 
1. Variable object: vars, function declarations, parameter + arguments ... 
2. Scope chain: Variable object + all parent scopes
3. thisValue: Context object

# 동기식 모델과 비동기식 모델

# 이벤트
안드로이드 앱 프로그래밍을 할 때와 비슷하게, 브라우저에서도 사용자와 상호작용 하기 위해서는 **이벤트**를 감지 할 수 있어야 한다. 앱 프로그래밍을 할 때와 같이 이벤트를 감지하는 **이벤트 핸들러**를 함수에 달아줘서, 이벤트에 대응해주면 된다. 함수 이름까지 똑같다! 
```js
document.querySelector('.myButton').addEventListener('click', function () {
    alert('Clicked!');
});
```
document에서 `querySelctor()`로 요소를 지정해주고, `addEventListener()`를 통해 어떤 이벤트가 일어났을 때 어떤 동작을 할지 정해줍니다.

### 2. Event Loop and Concurrency
**브라우저는 단일 쓰레드에서 이벤트 드리븐 방식으로 동작합니다.** 그런데 웹 어플리케이션은 마치 멀티 쓰레드로 여러 task가 동시에 처리되는 것처럼 느껴집니다. 이런 자바스크립트의 Concurrency를 지원하는 것이 바로 **Event Loop(이벤트 루프)**입니다. (js엔진 V8 또한 싱글 쓰레드로 동작함)
<br>
자바스크립트 엔진은 크게 2개의 영역으로 나뉘게 됩니다.
1. **Call Stack:** js는 단 하나의 call stack을 가지며, 작업들을 순차적으로 처리합니다.
2. **Heap**: 동적으로 생성된 객체들의 인스턴스가 할당됨. (프언 시간에 배운 내용 그대로)

js 엔진은 그저 Call Stack을 사용해서 요청된 작업을 순차적으로 실행할 뿐입니다. **동시성을 위한 비동기 요청들의 처리는 js 엔진을 구동하는 환경 즉, 브라우저나 Node.js가 담당합니다.**

1. **Event Queue(Task Queue)**: 비동기 처리 함수의 콜백함수, 비동기식 이벤트 핸들러, Timer 함수의 콜백 함수들이 보관되는 영역으로, **Event Loop에 의해 Call Stack이 비어졌을 때 순차적으로 Call Stack으로 이동되어 실행됩니다.**
2. **Event Loop**: Call Stack 내에서 현재 실행중인 task가 있는지, 그리고 Event Queue에 task가 있는지 반복해서 확인해주는 Loop입니다! Call Satck이 비어져 있으면, Event Queue 내의 task를 이동시킵니다.


## Events
래퍼런스를 참고하자. (키워드: 이벤트의 종류)
[[래퍼런스]](https://poiemaweb.com/js-event)

## 핸들러 등록 방식
1. ~~HTML 요소에 속성으로 직접 등록: do not use!~~: js와 html은 관심사가 다르기 때문에 분리 하는 것이 좋다. (React나 앵귤러, 뷰 등의 CBD 방식의 프래임워크/라이브러리에선 이런 방식으로 처리하긴 한다. ) 주의할 것은 함수 호출을 전달하는 것이 아니라, 함수 자체를 전달한다. 때문에 여러개를 한번에 전달할 수도 있다.
```html
<button onclick="myHandler1(); myHandler2();">Click me</button>
```
2. **이벤트 핸들러 프로퍼티 방식**: js와 html이 뒤섞이는 문제를 해결 할 수 있는 데신에, 하나의 프로퍼티에 하나의 이벤트 핸들러만을 바인딩 할 수 있다. 
3. **addEventListener 메소드 방식**: `addEventListener` 메소드를 이용하여 대상 DOM 요소에 이벤트를 바인딩하고, 해당 이벤트가 발생했을 때 실행될 콜백 함수(이벤트 핸들러)를 지정합니다.
```js
EventTarget.addEventListener('event', funtionName [, useCapture]);
```
따로 대상 DOM 요소를 지정하지 않으면, 전역 객체 window에 이벤트를 바인딩합니다. 
**장점**
- 하나의 이벤트에 대해 하나 이상의 이벤트 핸들러 추가 가능
- 캡쳐링, 버블링 지원
- HTML 요소, 모든 DOM요소(HTML, XML, SVG)에 대해 동작. 
따로 타겟을

## 이벤트 위임
css에서 pointer-event: none으로도 처리가 가능
target: 바로 걔
currentTarget: 바인딩된 DOM 요소, addEventListener 앞에 기술된 객체

