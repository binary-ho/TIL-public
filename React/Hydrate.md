# React Hydrate
Hydrate는 HTML을 통해 렌더링 된 화면을 리액트가 관리해주도록 하기 위한 작업입니다. **정적인 상태의 페이지를 동적으로 만들어 주는 작업입니다.** 건조한 정적인 HTML을 촉촉하게? 동적으로 만들어 준다고 해서 Hydrate인 것 같습니다. <br> 
React Hydrate는 render 메소드와 비슷한 모습을 띄고 있습니다.
```jsx
// render
ReactDOM.render(element, container[, callback])

// hydrate
RecatDOM.hydrate(elemnet, container[, callback])
```
1. render: 리액트 컴포넌트를 넣어준다. 기존에 이미 렌더링 되어있다면, 업데이트만 해준다. 이후 콜백이 실행횐다.
2. **hydrate**: 랜더링은 하지 않고 **이벤트 핸들러만 붙여준다.** SSR을 하는 경우 hydrate로 콜백만 붙여준다고 한다. (CSR은 렌더링 자체가 필요하니까 render 이용)

hydrate를 걸어주지 않으면 굳이 굳이 dehydrate와 rehydrate 과정이 일어나면서 화면이 한번 더 그려지는 것 같습니다. 그래서 SSR인 경우에는 render 대신 hydrate 메소드를 이용해야한다고 합니다. 참조 블로그에 아주 잘 정리 되어있으니, 한번 더 볼 필요가 있을 것 같습니다. Rehydration 과정에 대한 그림도 재미있습니다.

### Reference
https://simsimjae.tistory.com/389
