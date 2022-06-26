

# 1. 동기화 상황에서 HashMap - ConcurrentHashMap 
옛날에는 HashTable이라는 Map을 썼다. 이 HashTable은 사용시마다 lock을 걸기 때문에 동기화가 알아서 이루어졌다. <br> 
그러나 이것은 너무 느린 동작을 일으키기 때문에, 이후 자동 동기화가 없는 HashMap이 추가된 이후로는 Map을 이용 할 때 HashMap을 이용하고, 
동기화 상황에서는 `Collections.synchronizedMap(HashMap);`을 함께 이용하였다. <br>
그러나, 이 보다도 더 빠른 자료구조가 나왔는데 바로 java.util의 `ConcurrentHashMap`이다. 이 ConcurrentHashMap 또한 사용시마다 lock을 걸기 때문에 따로 동기화 작업은 필요 없다. 
하지만, HashMap에 synchronizedMap을 걸어준 것보다 더 빠른 속도를 자랑하는데... 그것은 **Map을 조각내서 특정 부분들만 lock을 걸기 때문이라고 한다.** <br> 
그래서 동기화가 필요할 때는 ConcurrentHashMap을 이용해주자. 자세한 것은 아주 잘 쓰여진 블로그를 참고하자. <br>
[[바로가기]](https://ooz.co.kr/71)
