# Props
props = properties <br>
**props는 어떤 값을 컴포넌트에게 전달해줘야 할 때 사용합니다.**
```js
function App() {
  return (
    <Hello name="react" />
  );
}

```
```js
function Hello(props) {
  return <div>안녕하세요 {props.name}</div>
}

export default Hello;
```
그냥 간단하게 펑션 파라미터를 아무렇게나 지어주면, 그걸 통해서 properties를 조회 가능

## props.children
컴포넌트 태그 사이에 넣은 값을 조회하고 싶을 땐, `props.children`을 조회해야합니다. 아래의 div 사이에 컴포넌트들을 넣고, 보이게 하려면 Wrapper에서 `props.children`을 랜더링해주어야 합니다.
```jsx
import React from 'react';

function Wrapper() {
  const style = {
    border: '2px solid black',
    padding: '16px',
  };
  return (
    <div style={style}>

    </div>
  )
}

export default Wrapper;
```
```js
function Wrapper({ children }) {
  const style = {
    border: '2px solid black',
    padding: '16px',
  };
  return (
    <div style={style}>
      {children}
    </div>
  )
}
```

## defaultProps
defaultProps로 기본값 설정 Props의 기본값을 설정할 수 있습니다. <br> 참고로 보통의 props도 값 설정을 생략해주면 true를 기본 값으로 갖게 됩니다.

## Props를 활용한 조건부 랜더링
```jsx
<div style={{ color }}>
  {isSpecial && <b>*</b>}
  안녕하세요 {name}
</div>
```
