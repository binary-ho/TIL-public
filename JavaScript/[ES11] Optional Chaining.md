# Optional Chaining
세상에. 얼마 전부터 회사 코드 중간 중간에 `?.` 문법이 보이기 시작했다. 검색해보니 이는, JS의 Optional Chaining 이였다. <br>
js의 배열이나 객체를 접근할 때, 조심해야 할 점이 있다. 그것은 내가 접근하길 원하는 프로퍼티가 없는데도 접근하는 경우, 에러가 발생한다는 점이다. <br> 
깊이가 깊어지거나, 어떤 객체는 가지고 있고, 어떤 객체는 가지고 있지 않는 경우의 체크는 매우 번거롭기 때문에, 저는 이런 번거로운 처리들을 도와주는 JS의 유명한 라이브러리 lodash의 기능을 사용해서 해결해왔습니다. <br>

Optional Chaining은 이런 문제를 빠르게 해결해줍니다. 
```js
alert( user1?.[key] );
alert( user1?.[key]?.something?.not?.existing); 
```
`?.`을 통해 왼 쪽에 있는 객체나 프로퍼티가 존재한다면, 오른쪽 객체를 가져옵니다. 위의 예시는 
1. `user1`이 있다면 `user1[key]`을 가져와라
2. `user1`이 있다면 `user1[key]`를 가져와라. `user1[key]`도 있다면, `user1[key].somthing`을 가져와라. `user1[key].somthing`이 있다면 ... (생략)

아주 간단하고 심플하다! 그리고 강력하다! 객체, 프로퍼티를 넘어 **메소드 까지도 똑같은 방식으로 확인하고 꺼낼 수가 있다.** 그리고 이름 부터 Chaining인 것처럼, 체인을 통해 계속해서 확인 할 수가 있다! <br>

`?.` 왼 쪽에 있는 객체나 프로퍼티가 `null`이거나 `undefined`라면, 결과는 `undefined`로 나온다. <br>
만약 중간에 하나라도 없다면 short circuit이 발생하여 역시 `undefined`이 나온다. 


## lodash 보다 나을까?
js native에서 이제 해당 기능을 제공해주니, 당연히 더 빠르겠다고는 생각했지만, 실제로 그런지, 왜 그런지, 얼마나 빠른지에 대해 확인해보기로 했다. <br>
![god](https://user-images.githubusercontent.com/71186266/198874902-d57f8d99-8531-4a80-9415-f9b6cecf65b7.png)

lodash의 get은 매번 array의 경로를 만들어낸다고 한다. 내가 찾으려는 객체나 프로퍼티들만 뽑아서 어떤 path를 만들어 낸 다음 루프를 돈다고 한다. 참고한 글을 정확히 이해하지는 못 했으나, ([참고한 블로그 링크](https://medium.com/@mezenok/why-you-should-use-optional-chaining-instead-of-lodash-get-9548e69f7b0e)) 꽤나 복잡한 과정을 통해 내부적으로 처리하기 때문에 **무려 12배의 속도 차이가 난다고 한다.** <br>
따라서 이제 부터는 굳이 lodash를 쓸 필요 없이 `?.`를 사용하면 되겠다. 

## Reference
- [블로그 글: why you should use optional chaining instead of lodashget](https://medium.com/@mezenok/why-you-should-use-optional-chaining-instead-of-lodash-get-9548e69f7b0e)

- https://ko.javascript.info/optional-chaining
