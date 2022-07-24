# Redux
리덕스는 **상태 관리 라이브러리입니다.** 복잡하고 코스트가 큰 상태 관리 로직을 **컴포넌트 밖에서 처리할 수 있습니다.** 보통 파일을 액션 타입, 액션 생성 함수, 리듀서의 세 종류로 분리하여 관리합니다. 이 전부를 한 파일에 모듈화하여 관리하는 Ducks 파일구조 추천. 
<br> 

1. **Redux 스토어**는 애플리케이션의 **상태 값**들을 내장하고 있습니다. 
2. 스토어 안의 상태가 바뀌는 경우, 스토어를 **구독**하고 있는 컴포넌트들에게 바로 전달합니다.
3. 상태 변화를 받을 떄는 **리듀서**를 통해 대신 받습니다.
4. 상태에 어떤 변화가 필요할 떄, **객체 형태의 Action**이라는 것이 스토어에 전달됩니다. **이를 Dispatch**라고 부릅니다.
5. 스토어가 액션을 받으면, **Reducer가 전달받은 액션을 기반으로 상태 변화를 결정하고**, 새 스토어에 저장합니다.

|주요 개념|설명|
|:----:|:----:|
|**스토어**|애플리케이션 상태 값들을 내장하는 스토어|
|**액션**|상태 변화를 일으킬 때 참조하는 **객체**|
|**디스패치**|액션을 스토어에 전달하는 행위|
|**리듀서**|상태를 변화시키는 로직이 있는 **함수**|
|**구독**|스토어 값이 필요한 컴포넌트들이 변화를 observe하기 위해 스토어를 구독함|


## 1. Action
action은 type값을 반드시 가지고 있어야하는 **객체입**니다. 액션 타입은 해당 액션이 어떤 작업을 하는 액션인지 정의합니다. **무엇을**할지에 해당하고, **어떻게 할지는 리듀서 함수에서 정의합니다.**
```js
const INCREMENT = 'INCREMENT';
const DECREMENT = 'DECREMENT';

const increment = (diff) => ({
  type: INCREMENT,
  diff: diff
});

const decrement = (diff) => ({
  type: DECREMENT,
  diff: diff
});

console.log(increment(1));
console.log(decrement(1));
```

## 2. Reducer
상태에 **변화**를 일으키는 함수입니다. 두 개의 파라미터를 받는데, 첫 번째 파라미터는 현재의 상태이고, 두 번째 파라미터는 액션 객체입니다. 리듀서가 첫 번째 파라미터에서 사용할 초기 상태 `initalState`의 값을 먼저 설정해 주어야 리듀서를 만들 수 있습니다. <br> 함수 내부에서 switch 문을 사용하여 action.type에 따라 새로운 상태를 만들어 반환해야합니다. switch문에서 스코프를 리듀서 함수 이름으로 사용 하기 때문에, 서로 다른 case에서 변수를 선언하거나 할 때 문제가 발생할 수 있습니다. 이는 나중에 리덕스-액션의 `handelAction`을 이용하여 해결할 수 있습니다.

```js
// 초기값 설정
const initialState = {
  number: 0,
  foo: 'bar',
  baz: 'qux'
};

// state가 undefine일 떄는 initial State를 사용합니다.
function counter(state = initialState, action) {
  switch(action.type) {
    case INCREMENT:
      return Object.assign({}, state, {
        number: state.number + action.diff
      });
    case DECREMENT:
      return Object.assign({}, state, {
        number: state.number - action.diff
      });
    default:
      return state;
  }
}
```
