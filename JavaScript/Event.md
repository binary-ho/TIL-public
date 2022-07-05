
# 이벤트, 이벤트 위임
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
- target: 바로 걔
- currentTarget: 바인딩된 DOM 요소, addEventListener 앞에 기술된 객체
- target을 이용하되, 버블링이 일어나므로, 클래스 네임이 일치할 때만 함수가 발동하도록 짜주면 된다.
