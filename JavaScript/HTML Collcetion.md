## HTMLCollection
반환 값이 HTMLCollection인 경우에는 유의. 이는 유사배열로, 변화가 바로 반영되는 객체이다. 이를 live하다고 표현한다. 마치 vector에서 erase할 때 처럼, 변화가 바로 반영되기 때문에, 길이가 계속해서 변해버릴 수가 있기 떄문에 반복문을 통해 어떤 처리를 할 때는 항상 유의해야한다. 
1. **역순으로 접근하기**: 계속 변화가 일어나서, 유사배열 안의 원소들이 갑자기 사라지거나 할 수 있는데, 그래도 문제가 발생하지 않도록 **인덱스 역순 부터 접근하는 방식이다.**
2. **배열로 변경하기**: 권장하는 방법임
```js
const elems = document.getElementsByClassName('red');

// 유사 배열 객체인 HTMLCollection을 배열로 변환한다.
// 배열로 변환된 HTMLCollection은 더 이상 live하지 않다.
console.log([...elems]); // [li#one.red, li#two.red, li#three.red]

[...elems].forEach(elem => elem.className = 'blue');
```
3. 애초에 NodeList로 받기 `querySelectorAll`
```js
// querySelectorAll는 Nodelist(non-live)를 반환한다. IE8+
const elems = document.querySelectorAll('.red');
[...elems].forEach(elem => elem.className = 'blue');
```
