# 더 편하게 쓰기
1. Ducks 구조: 액션 타입, 액션 생성함수, 리듀서 함수 전부 한 파일에 넣기
2. redux-actions를 이용한 더 쉬운 액션관리

### 1. Ducks 구조
액션 타입, 액션 생성함수, 리듀서 함수 전부 한 파일에 넣기.
1. 리듀서는 `export default`로 내보내기
2. 액션 생성 함수는 `export`로 내보내기
3. 액션 타입 이름은 접두사를 붙여주기
```js
// Ducks 패턴을 따를 때는 액션의 이름에 접두사를 붙여주는 편이 좋다.
// 다른 모듈과 액션 이름이 중복되는 것을 방지하기 위해 ㅇㅇ
const SET_DIFF = 'counter/SET_DIFF';
const INCREASE = 'counter/INCREASE';
const DECREASE = 'counter/DECREASE';

// 액션 생성 함수 만들기
export const setDiff = diff => ({type: SET_DIFF, diff});
export const increase = () => ({type: INCREASE});
export const decrease = () => ({type: DECREASE});

// 초기 상태 만들어주기
const initialState = {
  number: 0,
  diff: 1
};

// 리듀서는 export default로 빼주는게 좋음, 해당 모듈의 핵심이니까 ㅇㅇ
export default function counter(state = initialState, action) {
  switch(action.type) {
    case SET_DIFF:
      return {
        ...state,
        diff: action.diff
      };
    case INCREASE:
      return {
        ...state,
        number: state.number + state.diff 
      };
      case DECREASE:
        return {
          ...state,
          number: state.number - state.diff 
        };
    default: return state; 
  }
}
```

## 2. redux-actions
1. `createAction`: 액션 생성 자동화
2. `handleAction`: switch문을 대신함. scope와 블록 안에서 변수를 선언하거나 할 때 편리해짐

```js
// createAction

// 사용 전
export const increment = (index) => ({
  type: types.INCREMENT,
  index
});
export const decrement = (index) => ({
  type: types.DECREMENT,
  index
})

// 사용 후
export const increment = createAction(types.INCREMENT); 
export const decrement = createAction(types.DECREMENT); 

// 결과
increment(3);
/*
{
  type: 'INCREMENT',
  payload: 3
}
*/
```
사용하면 위와 같이 `payload` 키에 파라미터로 받은 값을 넣어 객체를 만들어줍니다. <br>
파라미터가 여러개인 경우 + 명확히 하고 싶은 경우, <br>
**두번째 파라미터에 payload 생성 함수를 전달합니다.**
```js
export const setColor = createAction(types.SET_COLER, ({index, color}) => ({index, color}));

// 
setColor({ index: 5, color: '#fff'})
/* 결과
{ 
  type: 'SET_COLOR',
  payload: {
    index: 5,
    color: '#fff'
  }
}
*/
```

2. handleActions
```js
const reducer = handleActions({
  INCREMENT: (state, action) => ({
    counter: state.counter + action.payload
  }),

  DECREMENT: (state, action) => ({
    counter: state.counter - action.payload
  })
}, {counter: 0});

```
# 프리젠테이셔널 컴포넌트
프리젠테이셔널 컴포넌트란, UI를 선언하는 것에 좀 더 집중하고,
리덕스 스토어에 직접적으로 접근하지 않고 필요한 값이나 함수를 props 로 받아와서 사용하는 컴포넌트이다. <br>
```js
function Counter({ number, diff, onIncrease, onDecrease, onSetDiff }) {
  const onChange = e => {
    onSetDiff(parseInt(e.target.value, 10));
  };
  return (
    <div>
      <h1>{number}</h1>
      <div>
        <input type="number" value={diff} min="1" onChange={onChange} />
        <button onClick={onIncrease}>+</button>
        <button onClick={onDecrease}>-</button>
      </div>
    </div>
  );
}
```

보면 알겠지만, 스토어에서 필요한 값들이나 함수를 인자로 받아서 쓴다.

# Container Component 만들기
Container Component란, 리덕스 스토어의 상태를 조회하거나, 
액션을 디스패치 할 수 있는 컴포넌트를 의미합니다. <br>
즉, 무언가를 하는 컴포넌트. 프리젠테이셔널 Component에서 UI를 선언했고, 그걸 불러와서 사용함.
```js
function CounterContainer() {
  // useSelector는 리덕스 스토어의 상태를 조회하는 Hook입니다.
  // state의 값은 store.getState() 함수를 호출했을 때 나타나는 결과물과 동일합니다.
  const { number, diff } = useSelector(state => ({
    number: state.counter.number,
    diff: state.counter.diff
  }));

  // useDispatch 는 리덕스 스토어의 dispatch 를 함수에서 사용 할 수 있게 해주는 Hook 입니다.
  const dispatch = useDispatch();
  // 각 액션들을 디스패치하는 함수들을 만드세요
  const onIncrease = () => dispatch(increase());
  const onDecrease = () => dispatch(decrease());
  const onSetDiff = diff => dispatch(setDiff(diff));

  return (
    <Counter
      // 상태와
      number={number}
      diff={diff}
      // 액션을 디스패치 하는 함수들을 props로 넣어줍니다.
      onIncrease={onIncrease}
      onDecrease={onDecrease}
      onSetDiff={onSetDiff}
    />
  );
}
```

상태에 어떤 변화를 일으켜야 할 때는 액션이라는 것을 스토어에 전달해야함. 
액션은 객체 형태이며, 상태 를 변화시킬 때 참조함.
액션을 전달하는 과정을 Dispatch라고 함.

스토어가 액션을 받으면, 리듀서가 전달받은 액션을 기반으로 상태를 어떻게 변경시켜야 할지 정함.
액션을 처리하면 새 상태를 스토어에 저장함. 덮어씌움
