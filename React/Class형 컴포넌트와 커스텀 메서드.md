
# 클래스형 컴포넌트
```js
import React, { Component } from 'react';

class Hello extends Component {
  render() {
    const { color, name, isSpecial } = this.props;
    return (
      <div style={{ color }}>
        {isSpecial && <b>*</b>}
        안녕하세요 {name}
      </div>
    );
  }
}
Hello.defaultProps = {
  name: '이름없음'
};
export default Hello;
```
클래스형 컴포넌트에서는 `render()` 메서드가 꼭 있어야 합니다. 이 메서드에서 렌더링하고 싶은 JFX를 반환하시면 됩니다. 그리고, `props`를 조회 해야 할 때에는 `this.props`를 조회하면 됩니다.

## 커스텀 메서드
커스텀 메서드와 컴포넌트 인스턴스의 연결은 보통 두 가지 방법으로 구현한다.
1. **생성자에서 bind해주기:** this 직접 지정. 클래스가 컴포넌트로서 작동 할 수 있도록 해주는 Component 쪽에 구현되어있는 생성자 함수를 먼저 실행해주고, 작업 시작하겠다 라는 것을 의미. 우리는 이렇게 해준다.
2. 화살표 함수 사용: 아무래도 정식 자바스크립트 문법은 아님.
3. ~~onClick 마다 새로운 함수: 당연히 안 좋은 방법.~~

## 상태 선언 + 업데이트
`state`를 사용하여 클래스형 컴포넌트에서 상태 관리하기! 
1. **`constructor` 내부에서 `this.state`를 설정해 주면 된다.**
2. 클래스형 컴포넌트의 `state`는 무조건 객체형태여야함.
3. `render` 메서드에서 `state`를 조회하려면 `this.state`
4. 상태 업데이트에는 `this.setState` 함수를 사용
여기까지 반영된 내용
```js
import React, { Component } from 'react';

class Counter extends Component {
    constructor(props) {
        super(props);
      /* 1번, 2번 */
        this.state = {
            counter: 0
        };
      /* 생성자에서 bind 해주기 */
        this.handleIncrease = this.handleIncrease.bind(this);
        this.handleDecrease = this.handleDecrease.bind(this);
    }

    handleIncrease() {
        /* 상태 업데이트 */
        this.setState({
            counter: this.state.counter + 1
        });
        console.log('increase');
    }

    handleDecrease() {
        this.setState({
            counter: this.state.counter - 1
        });
        console.log('decrease');
    }

  render() {
    return (
      <div>
        <h1>0</h1>
        <button onClick={this.handleIncrease}>+1</button>
        <button onClick={this.handleDecrease}>-1</button>
      </div>
    );
  }
}
export default Counter;
```
5. `setState`는 함수형 업데이트가 가능하다.
```js
handleIncrease() {
  this.setState(state => ({
       counter:state.counter + 1
  }));
};
handleDecrease() {
  this.setState(state => ({
      counter:state.counter - 1
  }));
};
```
`setState`를 한 메서드 안에서 여러번 사용하면, 제대로 적용되지 않을 수 있는데, 함수형 업데이트를 해주면 적용된다. 예를 들어
```js
handleIncrease() {
  this.setState({
      counter: this.state.counter + 1
  });
  this.setState({
       counter: this.state.counter + 1
   });
}
```
위와 같은 코드로는 카운터 값이 1만 증가한다.
```js
handleIncrease() {
    this.setState(state => ({
         counter:state.counter + 1
    }));
    this.setState(state => ({
         counter:state.counter + 1
    }));
};
```
이 코드는 2가 추가된다. 왜 이런 일이 발생할까요? <br>
`setState`는 단순히 상태를 바꾸는 함수가 아닙니다. **어떤 상태로 바꿔달라고 요청해주는 함수입니다. 이는 비동기적으로 업데이트가 되기 때문에, 1만 더해진 것입니다.** <br>

## 상태 업데이트 이후 작업 처리
`setState`의 두 번재 파라미터에 콜백 함수를 넣어주면, 업데이트 완료 후 수행됩니다. 
```js
setState(updater, [callback])
```
```js
handleIncrease = () => {
  this.setState(
  {
  counter: this.state.counter + 1
  },
  () => {
  console.log(this.state.counter);
  }
  );
};
```
