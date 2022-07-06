# useState
## useState를 통해 컴포넌트에서 바뀌는 값 관리하기
컴포넌트에서 동적인 값을 **상태(state)**라고 부릅니다. 리액트의 `useState`라는 함수를 통해 컴포넌트 상태를 관리 할 수 있습니다. <br> `useState(input)`를 호출해주면 **배열이 반환됩니다.** 
- **첫번째 원소:** 현재 상태 (= input)
- **두번째 원소:** Setter 함수 

```jsx
const onIncrease = () => {
        console.log('++1');
    }
...
<button onClick={onIncrease}>++1</button>

// 잘못된 예
<button onClick={onIncrease()}>++1</button>
```
위와 같이 함수를 전달 할 때, **함수 형태를 넣어주어야 하지, 함수를 실행시켜주면 안 된다.** 아래의 잘못된 예 처럼 넣어주면, 랜더링 과정에서 함수가 호출되어 버립니다.

```js
import React, { useState } from 'react';

function Counter() {
  const [number, setNumber] = useState(0);

  const onIncrease = () => {
    setNumber(prevNumber => prevNumber + 1);
  }

  const onDecrease = () => {
    setNumber(prevNumber => prevNumber - 1);
  }

  return (
    <div>
      <h1>{number}</h1>
      <button onClick={onIncrease}>+1</button>
      <button onClick={onDecrease}>-1</button>
    </div>
  );
}

export default Counter;
```
