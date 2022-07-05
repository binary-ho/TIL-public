# Class - ES6
자바스크립트는 prototype-based 객체지향 언어다. 클래스 없이, 프로토타입과 클로저로 객체지향 언어의 상속, 캡슐화 등의 개념을 구현한다. <br> <br>

먼저, ES5에서의 생성자 함수, 프로토 타입, 클로저를 이용한 클래스 선언과 상속을 보겠습니다.
```js
// ES5
var Person = (function () {
  // Constructor
  function Person(name) {
    this._name = name;
  }
  Person.prototype.sayHi = function () {
    console.log('Hi! ' + this._name);
  };
  return Person;
}());

var me = new Person('Lee');
```

이런 프로토타입 base 객체지향은 정말 낯섭니다. C-family이면서 JS는 계속 왜 이러는지.. 그래서 ES6에서는 클래스 기반 객체지향이 익숙한 프로그래머들을 위한 패턴들을 제공해준답니다. 와~... 이는 prototype-base 방식의 Syntactic Sugar나 거의 마찬가지 입니다. (더 엄격해서 완전히는 아님). 좌우간, 위에서 보인 예제를 `class` 키워드로 다시 만들어보겠습니다. 
```js
// 클래스 선언문
class Person {
  // constructor(생성자)
  constructor(name) {
    this._name = name;
  }
  sayHi() {
    console.log(`Hi! ${this._name}`);
  }
}
// 인스턴스 생성
const me = new Person('Lee');
```


**이것은 정적 메소드는 this를 사용할 수 없다는 것을 의미한다**

**staticMethod는 생성자 함수 Foo의 메소드**이고, <br>
일반 메소드 prototypeMethod는 프로토타입 객체 Foo.prototype의 메소드이다. **따라서 staticMethod는 foo에서 호출할 수 없다.**

자식 인스턴스가 부모의 정적 메소드는 참조가 불가능하지. 프로토타입 체인에 따르면 정적 메소드는 프로토타입 안에 있는게 아니고 클래스 안에 있기 떄문에, 자식 인스턴스는 부모의 프로토타입만 참조할 수 있지.

클래스 생성자는 1개만 가능.
클래스 필드는 생성자 안에서만,
