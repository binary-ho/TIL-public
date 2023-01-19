# Item 7. 다 쓴 객체 참조를 해제하라.
자바는 가비지 컬렉터를 기원한다. 가비지 컬렉터는 프로그래머가 신경쓰지 알아도 '알아서' 메모리 관리를 해준다. <br>
필요 없는 객체가 있다면, 가비지 컬렉터는 매몰차게 메모리를 수거해간다. <br>

아! 이제 가비지 컬렉터가 있으니, 메모리 관리는 신경 안 써도 되겠다!고 생각해도 될까? <br>
이미 위 문장을 읽으며 느꼈겠지만, 전혀 그렇지 않다. <br>
가비지 컬렉터는 '사용중인' 것은 수거해가지 않는다. 가비지 컬렉터 아저씨는 마술사가 아니다! 내가 쓰는 척을 하고 있는데, 스스로 판단해서 가져가서 버릴 수는 없는 노릇이다. <Br> 
이런 문제는 아래와 같은 코드에서 발생할 수 있다.
```java
public class Stack {
    private Object[] elements;
    private int size = 0;
    private static final int DEFAULT_INITIAL_CAPACITY = 16;

    public Stack() {
        elements = new Object[DEFAULT_INITIAL_CAPACITY];
    }

    public void push(Object e) {
        ensureCapacity();
        elements[size++] = e;
    }

    public Object pop() {
        if (size == 0)
            throw new EmptyStackException();
        return elements[--size];
    }

    private void ensureCapacity() {
        if (elements.length == size)
            elements = Arrays.copyOf(elements, 2 * size + 1);
    }
}
```
아름다운 Stack님을 구현한 코드이다. <br>
그런데 어디선가 악취가 풍겨온다. `pop()` 쪽을 보자. <br>
이런이런.. 사이즈를 줄여가는 상황에서 그냥 `size` 변수의 값을 1 줄이고 있다. <Br>
물론 스택으로서의 역할은 완벽하게 수행할 수 있지만, 생각해보자. <br>
실제로 배열이 할당 받은 크기가 줄어든 것이 아니라, 그냥 배열의 접근 가능한 최대 크기를 줄이고 있다. <br>
예를 들어 할당 받은 크기가 32라고 했을 때, 계속 pop() 연산을 수행해 size가 1이 되었다고 생각해보자. <br>
스택으로서는 완벽하게 원소 하나가 남은 상황이지만, 실제로는 여전히 32 크기의 메모리가 할당 되어있는 것이다. <Br>
이런 숨어 있는 `메모리 누수`는 가벼워 보이지만, 이 프로그램을 오래 돌린다면 결국 성능을 저하시키고, 심각한 경우 디스크 페이징이나 `OutOfMemoryError`를 일으켜 **프로그램을 종료 시킬 수도 있는 문제다.** <Br> <br>

어떻게 이런 현상을 막을 수 있을까.. 당연히 **할당된 메모리를 도로 뺐으면 된다.** <br>
그런데 어떻게?? 새로운 pop()을 만나보자.
```java
...

    public Object pop() {
        if (size == 0)
            throw new EmptyStackException();
        Object result = elements[--size];
        elements[size] = null;
        return result;
    }

...
```
아름답다.. 완벽하게 메모리를 뺐었다. 그리고 size를 벗어난 부분을 접근하는 경우 `NullPointException`까지 뱉어낼 수 있는 것이다. <br>

## null 집착 광공
그렇다고 이제부터 쓰지 않는 메모리를 null 처리 하는 것에 혈안이 될 필요는 없다! <br>
**객체 참조를 null 처리하는 일은 예외적인 경우여야 한다.** <br>
**다 쓴 참조를 해제하는 가장 좋은 방법은 그 참조를 담은 변수를 Scope 밖으로 밀어내는 것이다.** <br>
아이템 57을 참고하라! <br>
변수의 범위를 최소가 되게 정의했다면 이것은 자연스럽게 이루어진다고 한다. <br> <br>

null 처리를 백날 해줄 수는 없다. <Br>
**null 처리는 자신이 다루는 자원의 풀을 직접 다루는 객체에 한해 이루어 지면 된다.** <br>
프로그래머는 집중해서, 가비지 컬렉터가 알아차리지 못하는 부분을 직접 할당 해제해서 알려주면 된다! <br>

즉,
#### 자기 메모리를 직접 관리하는 클래스는 항상 메모리 누수에 주의해야 한다.

<br>

## 나머지 누수의 주범들
또한 캐시와 리스너, 콜백 함수 등도 메모리 누수의 주범이니 주의해야 한다. <Br>
책에 적힌 내용들을 이해하기 어려우니 여러번 읽어봐야 겠다.


## Reference
- Effective Java <조슈아 블로크>

