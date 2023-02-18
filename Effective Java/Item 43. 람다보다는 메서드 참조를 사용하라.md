# Item 43. 람다보다는 메서드 참조를 사용하라.
**람다로 할 수 없는 일이라면 메서드 참조로도 할 수 없다.** <br>
IDE조차 람다를 메서드 참조로 대체하라고 권한다. 예외적으로 제네릭 함수 타입을 구현할 때만 불가능하고, 웬만해선 람다는 메서드 참조로 대체 가능하다.  <br> 
메서드 참조는 아름답고 간결하고 이해하기 쉽다. <br>


## 메서드 참조 그게 뭔데 난리

```java
static void putValueByKey(int key) {
    Integer value = sushiMap.get(key);
    if (value == null) {
        sushiMap.put(key, 1);
        return;
    }
    sushiMap.put(key, value + 1);
}
```
위 코드는 바보같은 내가 바보같이 자바로 알고리즘을 풀 때 (순혈 C++러인데 가끔 자바로 푼다.) Map에 값을 넣은 방식이다. <br>
값이 없다면 1개가 되어야 하고, 이미 있다면 1개를 추가하기 위해 '용썼다' <br>
이렇게 해준 이유는 값이 없는 경우 null을 반환하는데, <br> 
거기서 무턱대고 1을 더했다간 에러가 발생하기 때문이다. <br>

위 코드를 저번 아이템에서 만난 아름다운 람다로 바꿔보겠다.
```java
sushiMap.merge(key, 1, (count, increase) -> count + increase);
```
할렐루야 <br>
위 merge는 java 8에 추가된 Map의 메서드로, 키, 값, 함수를 인수로 받는다. <br>
만약 값이 없다면, `(key, 1)`을 저장한다. <br>
이미 있다면 3번째 인자로 받은 함수를 적용하는데, `(key, 함수)`와 같이 적용된다. <Br>
더욱 자세히 설명하자면, count에는 기존 갯수가 들어가게 되고, increase엔 두번째 인수 '값'으로 들어간 1이 들어간다. <Br>
즉, 이미 있으면 갯수가 1개 증가하고, 없으면 1로 만든다. <br> <br>

이미 아름답지만, 꽤나 길다. <br> 
이제 메서드 참조를 적용하자
```java
map.merge(key, 1, Integer::sum);
```
너무 깔끔하고 아름답다. 그냥 이게 끝이다. <br>
이름을 보고 무엇을 하는지 알아채기 쉽고, 간결하다. <br>
대부분의 경우 람다는 메서드의 참조로 대체 가능하므로, 웬만하면 대채하라!


## 대체하는게 손해인 경우
물론 이 또한 예외는 있다. <br>
대체하는 편이 더 긴 상황도 있다. <Br>
대체로
1. 너무 간단하거나
2. 참조 메서드와 람다가 같은 클래스에 있을 때 그렇다. 

좀 억지스럽지만 `JinhoIsJJANG_OhMyGoshThisClassNameIsSooooHumongous` 클래스 안에서 참조 메서드 `action()`을 호출하고 있는 코드를 생각해보자.
```java
service.execute(JinhoIsJJANG_OhMyGoshThisClassNameIsSooooHumongous::action);
``` 
징그럽다. 하지만 람다를 쓴다면
```java
service.execute(() -> action());
```
훨씬 낫다 <br>


## 메서드 참조의 다섯 가지 유형
메서드 참조 유형은 5가지가 있다.

#### 1. 정적
가장 흔한 경우로, 앞서 계속 설명한 유형
ex) `Integer::parseInt` <br>
람다 버전: `str -> Integer.parseInt(str)`

#### 2. 한정적 (인스턴스)
한정적 인스턴스 메서드 참조는, 수신 객체를 특정한다. <br>
근본적으로는 정적 참조와 비슷하며, <br> 
함수 객체가 받는 인수와 참조되는 메서드가 받는 인수가 똑같다
ex) `Instant.now()::isAfter` <br>
람다 버전: 
```java
Instant then = Instant.now();
t -> then.isAfter(t);
```


#### 3. 비한정적 (인스턴스)
비한정적 인스턴스 메서드 참조는 수신 객체를 특정하지 않는다. <br>
함수 객체를 적용하는 시점에 수신 객체를 알려준다. <Br>
이를 위해 수신 객체 전달용 매개변수가 매개변수 목록의 첫 번째로 추가도니다. <Br>
그 뒤로는 참조되는 메서드 선언에 정의된 매개변수들이 뒤따르게 된다. <br>
주로 스트림 파이프라인에서의 매핑과 필터 함수에 쓰인다고 하는데, 뒤의 아이템 45를 보면 좋다고 한다. <Br>
ex) String::toLowerCase <br>
람다 버전: `str -> str.toLowerCase()`

#### 4. 클래스 생성자
생성자 참조는 팩터리 객체로 사용된다. <Br>
내가 자주 사용하는데 정말 유용하다.
ex) `TreeMap<K,V>::new` <br>
람다 버전: `() -> new TreeMap<K, V>()`
#### 5. 배열 생성자
ex) `int[]::new` <br>
람다 버전: `len -> new int[len]`

## Reference
- Effective Java <조슈아 블로크>
