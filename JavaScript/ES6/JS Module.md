# JS Module - ES6
자바스크립트는 본디 보조의 역할을 위해 만들어졌다. 그러다보니 꽤나 안 좋은 점들도 많은데, JS 파일을 불러올 때, 각자 독자적인 스코프를 갖지 않고 하나의 스코프를 공유하게 된다. 이는 당연히 문제가 되는데, 의도치 않게 값이 변화하는 일이 빈번하게 된다. ES6에서는 이를 보완하기 위해 JS Module을 제공한다. `<script></script>` 태그에 `type="module"` 어트리뷰트를 추가해주면 되고, 헷갈리지 않기 위해 파일 확장명을 `.mjs`로 해준다. 이렇게 불러오면, 각 파일은 자체적인 모듈 스코프를 갖게 된다!

## Export
모듈 파일 내의 객체들을 모듈 외부에서 사용하고 싶을 때는 선언문 앞에 `export` 키워드를 붙여줍니다. 하나 하나 해주어도 되고, 편리하게 한번에 모아서 해줄 수도 있습니다.
```js
// 변수, 함수 클래스를 하나의 객체로 구성하여 한번에 간단히 공개~!
export { pi, square, Person };
```

## Import
모듈에서 `export`한 대상들을 `import`하여 사용합니다. 위에서 든 예시를 이용 (모듈 파일 확장자 생략 불가)

```js
import { pi, square, Person } from './lib.mjs';

// 이름은 내 맘대로 정한다.
import { pi as PI, square as sq, Person as P } from './lib.mjs';

// 물론 *로 호출 하는 것도 문제 없음.
// 단 as로 식별자 하나 만들어 줘야 한다.
import * as lib from './lib.mjs';
console.log(lib.pi);
console.log(lib.square(10)); 
```
요소 딱 하나만 가져올 때는 `default` 키워드로 가져올 수 있다. 단, `var`, `let`, `const` 불가능. 아래와 같은 모습이 된다.
```js
// lib.mjs 내부
export default function (x) {
  return x * x;
}
//
import square from './lib.mjs';
console.log(square(3)); 
```
