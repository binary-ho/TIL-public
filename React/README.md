# React
기존 자바스크립트의 방식으로는 복잡하고 다양한 요소의 상호작용이 너무 어려웠습니다. 
React는 어떠한 상태가 바뀌었을때, 그 상태에 따라 DOM의 업데이트 방식을 정하는 것이 아니라, 아예 싹 날려버리고 새로 만들어서 보여준다면 어떨까? 라는 아이디어에서 출발합니다. 
<br> <br> 실제로 전부 처음부터 만들게 된다면, 속도가 굉장히 느려지게 됩니다. 그래서 React에서는 Virtual DOM이라는 것을 사용했습니다. 
이는 실제로는 JavaScript 객체로, 상태 업데이트가 필요한 곳의 UI를 Virtual DOM을 통해 랜더링합니다. 
그리고 리액트 비교 알고리즘을 통해 차이가 있는 곳을 감지해서, 실제 DOM에 패치 시켜줍니다. 이를 통해, 업데이트 방식에 대한 고민 없이 빠른 성능으로 UI 업데이트가 가능해졌습니다. 
<br> 

- **WebPack:** 여러 컴포넌트 파일을 한개로 합치기 위한 도구.
- **Babel:** JSX를 비롯한 새로운 자바스크립트 문법을 사용하기 위한 도구 
프로젝트 시작 커맨드
```
npx create-react-app 프로젝트명
cd 프로젝트명
yarn start
```