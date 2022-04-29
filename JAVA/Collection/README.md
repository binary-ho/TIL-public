JAVA Collection Framework
==
# 1. 핵심 인터페이스
컬렉션 프레임워크에서는 데이터 그룹을 크게 3가지로 나누었고, 각 컬렉션을 다루기 위한 3개의 인터페이스 List, Set, Map을 정의하였다. 그리고 List와 Set의 공통된 부분을 다시 뽑아서 새로운 인터페이스 Collection을 추가로 정의하였다.

![image](https://user-images.githubusercontent.com/71186266/166002517-02b9f6ee-a207-4d73-9ee7-df262b0cf5e8.png)

1. List: 순서가 있는 데이터 집합. 중복 허용함.
2. Set: 순서를 유지하지 않는 데이터 집합. 중복 허용 X.
3. Map: key와 value의 쌍으로 이루어진, 순서를 유지하지 않는 데이터 집합.    
  키의 중복 허용 X.


### 구현 클래스
1. List -> ArrayList, LinkedList, Stack, Vector 등..
2. Set -> HashSet, SortedSet, TreeSet 등..
3. Map -> HashMap, SortedMap, TreeMap, HashTable, Properties 등..


# 2. List 인터페이스 클래스
**순서가 있는 데이터 집합! 중복 허용! 각 클래스의 차이를 이해 해야함.**

## 2.1 ArrayList
<U>기존의 Vector를 개선!</U> Vector와 구현원리와 기능적인 측면에서 동일하다고 할 수 있음! <U>**내부적으로 배열을 통해 구현**되어있고, 저장할 공간이 모자르면 보다 큰 새로운 배열을 생성해서 기존의 배열에 저장된 내용을 새로운 배열로 복사한 다음에 저장합니다.</U>

소스코드 내부에서 선언된 배열의 타입이 모든 객체의 최고조상인 Object이기 때문에 모든 종류의 객체를 담을 수 있습니다.

```Java
ArrayList<String> arr = new ArrayList<>();
```

**ArrayList와 같이 배열을 이용한 자료구조는 읽고 쓰는 데에는 빠르지만, 용량의 변경이 필요할 때는 효율이 떨어진다! 인스턴스를 생성할 때 애초에 저장할 데이터 갯수를 잘 고려하여 충분한 용량의 인스턴스를 생성해야한다!** + 중간에 있는 데이터를 삭제할 때도 느리다고 할 수 있다. 그냥 내부적으로 배열을 이용해 구현되었다는 점이 핵심!

## 2.2 LinkedList
**내가 생각하는 그 링크드 리스트.** 순차대로 노드끼리 다음 노드를 가르키고 있는 방식. 물론 전 노드도 가르키고 있는 더블 링크드 리스트 방식이다. 여기에 더해 마치 원형 큐 처럼 처음과 끝을 이어 놓았는데. **결론적으로 Java의 LinkedList는 "Double Circular Linked List"로 구현되어 있다.** 그러니 접근 속도가 느린 대신 중간 데이터를 추가/삭제 할 때 ArrayList에 비해 효율이 굉장히 좋다. 

### 사용법
자세히 다루지 않고, 내게 낯설게 느껴지는 **add, poll, peek** 4가지만 정리해보겠다.    

#### 2.2.1 poll 
단어적으로 낯선 느낌이 있는데, poll은 '**개표하다**'라는 의미를 가지고 있다. 개표는 투표함에서 종이를 **꺼내어, 열어보는** 행위이다.    
이와 같이 poll은 **Linked List의 첫 번째 요소를 꺼내어 제거하고, 해당 요소를 반환한다.** 즉, pop을 하며 값도 반환하는 행위인 것이다.

#### 2.2.2 peek
peek도 평소에 쓰지 않아 낯선 단어인데 peek은 '**흘깃 훔쳐보다**'라는 의미를 가지고 있다. 의미대로 **Linked List의 첫 번째 요소를 반환하되, 제거하지는 않는다.** 

#### 2.2.2 First, Last
위에서 제시한 add는 Linked List의 맨 끝에, poll, peek은 첫 번째 요소를 반환한다고 쓰여 있다. 이는 내게 모호하고 헷갈리게 다가온다.    
내가 아는 원래의 Linked List라면 Head와 Tail이 존재하기 마련이다. 여기서는 이를 **First, Last**로 부르고 있고, 그저 세 메서드에 붙여주면 된다.    
**ex) addFirst, pollFirst,  peekFirst / addLast, pollLast, peekLast**
**Linked List맨 앞에 적용 하고 싶다면 First, 맨 뒤에 적용 하고 싶다면 Last를 이요해주면 되겠다!**


## 2.3 ArrayList와 LinkedList의 상대적 차이

##### 1. ArrayList: 배열 기반, 접근이 빠른 대신 중간 데이터 추가와 삭제가 느리다. (순차적 추가는 근소하게 빠름) 또한, 정해진 용량을 벗어냐면 아주 느린 효율로 용량을 늘린다.
##### 2. LinkedList: 노드 이어 만듬, 접근이 느린 대신 중간 데이터 추가와 삭제가 빠름. 데이터가 많을 수록 접근성은 떨어지게 된다.
   
##### 데이터 갯수가 정해졌다. -> ArrayList
##### 데이터 갯수가 동적으로 변할 수 있고, 접근이 적다. -> LinkedList


## 2.4 Stack과 Queue
Stack은 순차적 삽입과 삭제가 잦으므로 ArrayList,    
Queue는 맨 앞 요소의 삭제가 잦으므로 Linked List가 구현에 적합하다.
내가 잘 아는 역할에 맞는 push와 pop을 써도 되고, List 함수를 써도 된다.
    
Java에서는 Stack Class는 따로 구현을 해 놓았지만 Queue Class는 따로 구현해 두지 않았다. 다면, Queue 인터페이스가 있으므로, 해당 인터페이스를 구현한 다양한 메서드들 중 적절한 것을 쓰면 된다. )ex) LinkedList, PriorityQueue, ArrayDeque 등이 있음.)
