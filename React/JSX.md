
## JSX
1. JSX에서 HTML 태그는 무조건 닫혀있어야 합니다. `<br>` 이런거 안 됩니다. `<br />`, `<Hello />` 됩니다.
2. 두개 이상의 태그는 무조건 하나의 태그로 감싸져있어야 합니다.
```js
function App() {
  return (
      <Hello />
      <div>안녕히계세요</div>
  );
}
```
안 됩니다. 아래와 같이 합니다.
```js
function App() {
  return (
    <div>
      <Hello />
      <div>안녕히계세요</div>
    </div>
  );
}
```
그렇다고 불필요한 div를 남발하면 복잡해지게 됩니다. 그럴 땐 React Fragment를 이용합니다.
3. **React Fragment:** 빈 태그를 만들어 주면, Fragment가 만들어집니다. public/index.html root에 알아서 들어감.
```js
// 해당 코드는
function App() {
  return (
    <>
      <Hello />
      <div>안녕히계세요</div>
    </>
  );
}
```
3. JSX 안에 자바스크립트 값 사용하기: `{}`로 감싸서 나타냅니다.
```js
function App() {
  const name = 'react';
  const style = {
    backgroundColor: 'black',
    color: 'aqua',
    fontSize: 24, // 기본 단위 px
    padding: '1rem' // 다른 단위 사용 시 문자열로 설정
  }

  return (
    <>
      <Hello />
      <div style={style}>{name}</div>
    </>
  );
}
```
**인라인 스타일은 객체 형태로 작성해야합니다.** `-`로 이어져있는 성분들이 있는데, 카멜 케이스 형태로 바꿔줍니다. <br> ex) `background-color` => `backgroundColor`
4. class는 `class=`처럼 나타내지 않고, `className=`과 같이 나타냅니다. `<div className="gray-box"></div>`
5. 주석은 `/**/`형태를 사용하나, **대괄호로 감싸줍니다.** 특이하네요, `{/* 주우우석 */}` 이런 형태가 되겠습니다. <br> 열리는 태그 안에서는 `//` 주석도 허용.
