# 1. immer
immer 라이브러리는 리액트에서 상태를 업데이트 해 줄 때, 도움을 주는 라이브러리입니다! <br> 리액트의 객체는 **불변성을** 가지고 있습니다. 이 때문에, 배열이나 객체를 업데이트 해줄 때는, **직접 접근하여 업데이트 해주는 것이 아니라, 새로운 객체를 만들어 덮어 씌워주었습니다.** 

<br> 그래서 원래는 업데이트 해주고 싶은 부분이 있다면, `{} -> state -> 덮어 쓸 부분` 이렇게 업데이트 해줍니다.

```js
case INCREMENT:
  return Object.assign({}, state, {
    number: state.number + action.diff
  });
```
위와 같이, 혹은
```js
case INCREMENT:
  return {
    ...state,
    number: state.number + action.diff
  };
```
위와 같이 나타내는 것이 일반적입니다.
<br> <br>

간단한 경우에는 이렇게 나타내어도 가독성이 그리 나쁘지 않지만, 객체 안의 객체, 배열 등의 복잡한 구조를 업데이트 해야 할 때는 매우 보기 힘든 코드가 나오게 됩니다. immer 라이브러리는 이런 불변성을 고려하지 않고 코드를 작성하는 데에 도움을 줍니다. 사용 예를 보이겠습니다.

### immer 라이브러리 사용 예시
아래와 같은 복잡한 객체가 있습니다.
```js
const state = {
  posts: [
    {
      id: 1,
      title: '제목 1',
      body: '내용 1',
      comments: [
        {
          id: 1,
          text: '댓글 1'
        }
      ]
    },
    {
      id: 2,
      title: '제목 2',
      body: '내용 2',
      comments: [
        {
          id: 2,
          text: '댓글 2'
        }
      ]
    }
  ],
  selectedId: 1
};
```
posts 아이디가 1인 객체의 새로운 댓글을 추가해줘야 하는 상황에서, 원래는 아래와 같이 복잡한 방식으로 업데이트가 이뤄집니다.

```js
const nextState = {
  ...state,
  posts: state.posts.map(post => post.id === 1 ? 
    {
      ...post,
      comments: post.comments.concat({
        id: 3,
        text: '댓글 3!'
      })
    }
    : post
  )
};
```

이런 상황에서 immer 라이브러리를 사용하면, 아래와 같이 구현이 가능합니다. produce 함수의 첫 번째 파라미터에는 수정하고 싶은 state를, 그리고 두 번째 파라미터에는 어떻게 업데이트 할지를 정의하는 함수를 넣어줍니다.

```js
const nextState = produce(state, draft => {
  const post = draft.posts.find(post => post.id === 1);

  post.comments.push({
    id: 3,
    text: '댓글 3'
  });

});
```
**immer를 사용한다고 해서 항상 코드가 간결해 지는 것은 아닙니다.** 업데이트 할 내용들이 객체의 깊은 곳에 위치하지 않는 경우, 그냥 concat 이나 filter를 사용하는 것이 더 짧을 수도 있습니다. 
<br> <br>

위에서 produce 함수로 immer를 이용했습니다. 이는 immer를 import 해올 때 보통 아래와 같이 임포트 해오기 때문입니다. 
```js
import produce from 'immer';
```

# 2. Rematch

# Reference
밸로퍼트의 리액트 Git Book
