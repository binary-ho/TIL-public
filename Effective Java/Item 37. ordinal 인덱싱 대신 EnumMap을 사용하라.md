# Item 37 ordinal 인덱싱 대신 EnumMap을 사용하라

가끔 타입 별로 객체들을 정리해야 할 때가 있다. <br>
예를 들어 식물의 생애주기를 나타낸 enum은 아래와 같다.
```java
public enum LifeCycle {
    ANUAL, PERENIAL, BIENNIAL
}
```

이 생애주기 별로 식물들을 정리하려고 할 때, 각 주기들이 가진 인덱스 0, 1, 2를 통해 배열을 만들 수도 있다. <Br>
그러나 각 인덱스가 가진 의미를 파악하기 힘들어서 레이블을 달아줘야 하고, 타입 안전하지 않기 때문에, 각 숫자와 상수를 적절하게 사용했는지 알아내기가 어렵다. 정말 각별히 조심해서 사용해야만 한다. <br>


## EnumMap
그러지 말고 우리 EnumMap으로 합시다. <br>
**열거 타입을 Key로 사용하도록 설계한 빠르고 멋진 Map 구현체가 존재하나니, 바로 `EnumMap`이 그 주인공이다!** <br>

예를 들어 위에서 보인 생애 주기별 식물 모음을 아래와 같이 나타낼 수 있을 것이다.
```java
Map<Plant.LifeCycle, Set<Plant>> plantByLifeCycle = new EnumMap<>(Plant.LifeCycle.class);

for (Plant.LifeCycle lifeCycle : Plant.LifeCycle.values()) {
  Plant.LifeCycle.put(lifeCycle, new HashSet<>());
}

for (Plant plant : garden) {
  plantsByLifeCycle.get(plant.lifeCycle).add(plant);
}
```
아주 깔끔하고 아름답게, 생애 주기별 식물을 모아둔 Map plantByLifeCycle을 만들어낼 수 있었다. <br>

맵의 key인 열거 타입이 출력용 문자열을 제공해줌으로써 출력 결과에 어렵게 레이블을 달아줄 일이 없다. <br>
배열 인덱스를 계산하는 과정에서의 오류도 원천 봉쇄된다. <br>
EnumMap이 내부적으로는 배열로 구현되어 있어, Map의 타입 안정성과 배열의 성능을 모두 얻어 냈다. 


## 스트림을 통해 EnumMap 생성하기

기존의 Map을 통해 열거 타입 Map을 만드는 경우에는, 빈 해쉬맵이 생성될 수 있었다. <br>
위의 생애 주기 식물의 예를 들어, 내 정원에는 한해 살이 식물이 없는데도, 스트림을 통해 생성하다 보면, 빈 한해 살이 식물에 대한 빈 해쉬맵이 생성될 수도 있다. 
```java
Arrays.stream(garden)
    .collect(groupingBy(plant -> plant.lifeCycle));
``` 

바로 위와 같이 말이다. <br>
이렇게 말고 스트림과 EnumMap을 통해 똑똑하게 EnumMap을 만들어보자. <br>
```java
Arrays.stream(garden)
    .collect(groupingBy(
        plant -> plant.lifeCycle, () -> new EnumMap<>(LifeCycle.class), toSet()
      ));
```
이런 식으로 똑똑하게 EnumMap을 만든다면, 없는 열거 타입에 대해서는 맵이 만들어 지지 않는다. <br>
groupingBy에 들어가는 인자들을 해설해주자면
1. garden 배열의 plant들의 lifeCycle을 꺼낸다. <br> 이 LifeCycle 별로 정리한다.
2. mapFactory 매개변수: 원하는 맵 구현체를 명시. LifeCycle 클래스 EnumMap을 만든다.
3. grouping 된 plant들의 set을 만든다.


이렇게 만들면 객체가 없는 타입에 대해서는 빈 Set이 생성되지 않으니까 참 좋다.

## 다차원 열거 타입 표현도 쉽다.
두 열거 타입을 매핑하는 예시를 살펴보자. <br>
이런 때에도 EnumMap의 사용은 정말 좋다. <br>
두 상태 (Phase)와 전이(Transtition)를 매핑한 프로그램이다. <br>
예를 덜어 액체 -> 고체로의 전이는 응고가 되고, 액체에서 기체로의 전이는 기화가 된다. <br>
아래는 기존의 ordinal() 인덱스를 사용한 방법이고 나쁜 예이니 참고만 하자.
```java
public enum Phase {
  SOLID, LIQID, GAS;

  public enum Transition {
    MELT, FREEZE, BOIL, CONDENSE, SUBLIME, DEPOSIT;

    private static final Transition[][] TRANSITIONS = {
      { null, MELT, SUBLIME },
      { FREEZE, null, BOIL },
      { DEPOSIT, CONDENSE, null }
    };

    public static Transition from(Phase from, Phase to) {
      return Transition[from.ordinal()][to.ordinal()];
    }
  }
}
```

너무 징그럽다. <br>
컴파일러는 ordinal과 배열 인덱스의 관계를 모르기 때문에
뭐 하나를 수정하려면 아주 아주 조심해서 `TRANSITIONS` 배열을 수정해야 한다. <br>
IndexOutOfBound 예외나 NullPointer 예외가 일어나기 너무나도 쉬운 상황에 놓이게 된다. 그나마 이건 운이 좋은 경우고 예외 없이 돌아가 버릴 수도 있는 것이다. <br>
그리고 `TRANSITIONS` 배열은 상태의 추가에 따라 크기가 제곱해서 커지는데 2차원 배열로 이를 가지고 있기 때문에 어쩔 수 없고, 위험한 null도 계속해서 늘어날 것이다. <br> <br>


시간낭비 말고, 중첩된 EnumMap을 통해 해결해보자. <br>

```java
public enum Phase {
    SOLID, LIQUID, GAS;
    public enum Transition {
        MELT(SOLID, LIQUID), FREEZE(LIQUID, SOLID),
        BOIL(LIQUID, GAS), CONDENSE(GAS, LIQUID),
        SUBLIME(SOLID, GAS), DEPOSIT(GAS, SOLID);

        private final Phase from;
        private final Phase to;
        Transition(Phase from, Phase to) {
            this.from = from;
            this.to = to;
        }

        private static final Map<Phase, Map<Phase, Transition>>
                m = Stream.of(values()).collect(groupingBy(t -> t.from,
                () -> new EnumMap<>(Phase.class),
                toMap(t -> t.to, t -> t,
                        (x, y) -> y, () -> new EnumMap<>(Phase.class))));
        
        public static Transition from(Phase from, Phase to) {
            return m.get(from).get(to);
        }
    }
}
```
간편(?) 하게 EnumMap의 중첩 Map을 만들 수 있다. <br>
맵을 만드는 부분이 복잡하니 부연하겠다. <br>

```java
private static final Map<Phase, Map<Phase, Transition>>
    transitionMap = Stream.of(values()).collect(groupingBy(transition -> transition.from,
    () -> new EnumMap<>(Phase.class),
    toMap(transition -> transition.to, transition -> transition, (x, y) -> y, () -> new EnumMap<>(Phase.class))));
```
위는 교재 코드에서 map을 만드는 부분만 가져와 읽기 좋게 변수명을 바꾸어 본 버전이다. 덕분에 더 길어졌다. <br>

일단 뭘 만드는지 부터 보고 가자 `Map<Phase, Map<Phase, Transition>>` 이런 Map을 만드는 것인데, 한글로 풀어서 보여주겠다. <Br>
`Map<이전 상태, Map<이후 상태, 전이>>` 이렇게만 봐도 전체 흐름의 이해가 쉬울 것이다. <br>

가장 처음 values()의 호출로 `Transition`들이 모이게 된다. <br>
각 Transition은 from과 to로 Phase로 가지고 있다는 점을 다시 떠올리자. <br>
`gropuinBy`를 보면 `transition -> transition.from`이라고 되어 있는데, 바깥 Map의 Key를 구성하기 위해 transition의 form을 기준으로 정리한 것이다. <br>
이후 두 번째 인자 맵 팩토리에 `() -> new EnumMap<>(Phase.class)`를 넣는데, Phase를 기준으로 EnumMap을 만든것이다. 그러니까 `Map<Phase, ?>` 이런 뼈대가 만들어진 것이다. <br>
이후 `?`에 들어갈 곳에 또 다른 EnumMap을 넣어주기 위해 `toMap()` 메서드를 호출했다. <br>
다시 새로운 맵을 구성하기 위한 3개의 인자가 들어가는데, 이제 이후 상태를 기준으로 Transition을 정리해야 한다. <br> 
따라서, `transition -> transition.to`이 첫 인자로 들어가고 두 번째 인자로 각 transition의 to에 맞는 transition이 매핑되어야 하므로 `transition -> transition`이 들어갔다. <br>
병합 함수 `(x, y) -> y`는 들어갔지만 쓰이지 않았다. 단지 EnumMap을 얻기 위해선 맵 팩터리가 필요하고, 수집기들은 점층적 팩터리를 제공하기 때문에 들어갔다. <br> (이 부분은 나도 잘 이해를 못 해서 다시 찾아볼 예정. 결론적으로는 들어가긴 했지만 실제론 쓰이지 않은 것은 맞다.) <br>
마지막으로 또 Transition의 to인 Phase를 기준으로 정리한 EnumMap이므로 `() -> new EnumMap<>(Phase.class)`가 들어갔다. <br> <br>


### 중첩 EnumMap 장점
위에서 언급한 배열을 EnumMap으로 바꾼 장점과 동일한 장점들을 모두 가져오며. <br>
새로운 상태를 추가할 때도 편하다. <Br>

```java
public enum Phase {
       SOLID, LIQUID, GAS, PLASMA;
       public enum Transition {
           MELT(SOLID, LIQUID), FREEZE(LIQUID, SOLID),
           BOIL(LIQUID, GAS), CONDENSE(GAS, LIQUID),
           SUBLIME(SOLID, GAS), DEPOSIT(GAS, SOLID),
           IONIZE(GAS, PLASMA), DEIONIZE(PLASMA, GAS);

        private final Phase from;
        private final Phase to;
        Transition(Phase from, Phase to) {
            this.from = from;
            this.to = to;
        }

        private static final Map<Phase, Map<Phase, Transition>>
                m = Stream.of(values()).collect(groupingBy(t -> t.from,
                () -> new EnumMap<>(Phase.class),
                toMap(t -> t.to, t -> t,
                        (x, y) -> y, () -> new EnumMap<>(Phase.class))));
        
        public static Transition from(Phase from, Phase to) {
            return m.get(from).get(to);
        }
    }
}
```
PLASMA와 IONIZE, DEIONIZE이 추가된 버전이다. <br>
이전 상태에서는 사이즈가 제곱으로 커지니, null이 계속해서 추가되니, 신중하게 배열을 짜지 않으면 아예 순서가 꼬이느니 여러 단점이 있었는데 <br>
이렇게 해주면 그냥 3개만 더 적어주고 끝낼 수 있다. <Br>
#### `PLASMA`, `IONIZE(GAS, PLASMA)`, `DEIONIZE(PLASMA, GAS)` 끝!

## Reference
- Effective Java <조슈아 블로크>
