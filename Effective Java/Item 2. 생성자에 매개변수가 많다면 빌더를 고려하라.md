# 아이템 2. 생성자에 매개변수가 많다면 빌더를 고려하라.
이 파트도 머리를 맞은듯 했다. 뇌세포 다 죽겠다. <br>
정적 팩터리나, 생성자나 똑같이 가진 제약 사항이 있는데, **선택적 매개변수가 많을 때 대응이 어렵다는 점이다.** <br>
예를 들어 다양한 0번에서 10번까지의 속성들을 가진 객체가 있는데, 상황에 따라, 0 ~ 3번 속성만 받아서 객체를 만들 수도 있고, 0 ~ 5번, 0 ~ 10번 전체를 받아 객체를 만들 수도 있는 것이다. <Br>
책에서 주어진 예시 코드를 보면 어떤 상황인지 바로 파악이 가능하다
```java
public class NutritionFacts {
    private final int servingSize;  // (mL, 1회 제공량)     필수
    private final int servings;     // (회, 총 n회 제공량)  필수
    private final int calories;     // (1회 제공량당)       선택
    private final int fat;          // (g/1회 제공량)       선택
    private final int sodium;       // (mg/1회 제공량)      선택
    private final int carbohydrate; // (g/1회 제공량)       선택

    public NutritionFacts(int servingSize, int servings) {
        this(servingSize, servings, 0);
    }

    public NutritionFacts(int servingSize, int servings,
                          int calories) {
        this(servingSize, servings, calories, 0);
    }

    public NutritionFacts(int servingSize, int servings,
                          int calories, int fat) {
        this(servingSize, servings, calories, fat, 0);
    }

    public NutritionFacts(int servingSize, int servings,
                          int calories, int fat, int sodium) {
        this(servingSize, servings, calories, fat, sodium, 0);
    }
    public NutritionFacts(int servingSize, int servings,
                          int calories, int fat, int sodium, int carbohydrate) {
        this.servingSize  = servingSize;
        this.servings     = servings;
        this.calories     = calories;
        this.fat          = fat;
        this.sodium       = sodium;
        this.carbohydrate = carbohydrate;
    }
}
```
어지럽다! 살다 보니 위와 같은 코드를 짜본 적이 있었는데, 그 때는 뭔가 더럽긴 하지만, 이런 식으로 자는게 올바른 코드라고 생각했었다. 생성자의 다형성?을 존중해주며 나름 뿌듯하기까지 했던것 같다. <br>
그러나 이런 방식은 **확장하기가 힘들다.** <br>
그리고 **사용자가 설정하기 원치 않는 매개변수까지 어쩔 수 없이 포함해 주어야 한다.** <br>

위와 같은 코드도.. 짤 수는 있지만, 매개 변수가 많아지면 클라이언트 코드의 작성하기나 읽기가 매우 어려워진다. <br>


### 자바 빈즈
가독성을 개선하기 위한 `자바 빈즈`라는 대안이 있다.

```java
public class NutritionFacts {
    // 매개변수들은 (기본값이 있다면) 기본값으로 초기화된다.
    private int servingSize  = -1; // 필수; 기본값 없음
    private int servings     = -1; // 필수; 기본값 없음
    private int calories     = 0;
    private int fat          = 0;
    private int sodium       = 0;
    private int carbohydrate = 0;

    public NutritionFacts() { }
    // Setters
    public void setServingSize(int val)  { servingSize = val; }
    public void setServings(int val)     { servings = val; }
    public void setCalories(int val)     { calories = val; }
    public void setFat(int val)          { fat = val; }
    public void setSodium(int val)       { sodium = val; }
    public void setCarbohydrate(int val) { carbohydrate = val; }

    public static void main(String[] args) {
        NutritionFacts cocaCola = new NutritionFacts();
        cocaCola.setServingSize(240);
        cocaCola.setServings(8);
        cocaCola.setCalories(100);
        cocaCola.setSodium(35);
        cocaCola.setCarbohydrate(27);
    }
}
```
자바 빈즈로 개선한 코드.. 물론 가독성은 나아졌다만,
객체 하나를 생성하기 위해 여러 메서드를 호출해야 하고, 계속 setter들을 호출하면서 객체가 완성되기 전까지 일관성이 무너진 상태에 놓이게 된다. <br>

일관성 면에서는 점층적인 생성자 방식 보다도 나쁘다. 디버깅도 어렵고, **클래스를 불변으로 만들 수도 없다.** <br>
총체적 난국이다...


## Builder Pattern
빌더 패턴은 점층적 생성자 패턴의 **안정성과 자바 빈즈 패턴의 가독성을 모두 잡은 패턴이다.** <br>
필요한 객체를 클라이언트가 직접 만드는 대신, 필수 매개변수만으로 생성자나 정적 팩토리를 호출해 빌더 객체를 얻어내는 것이다. <br>
그리고 빌더 객체가 제공하는 메서드들로 선택 매개변수들을 설정한다. <br>
이런 과정들이 모두 끝났다면, 마지막에 매개변수가 없는 `build` 메서드를 호출해서 완성된 객체를 얻어낸다! <br>

설명만 보면 좀 헷갈린데, 코드를 보자. 보통은 생성할 클래스 안에 정적 맴버 클래스로 만들어 둔다.

```java
public class NutritionFacts {
    private final int servingSize;
    private final int servings;
    private final int calories;
    private final int fat;
    private final int sodium;
    private final int carbohydrate;

    public static class Builder {
        // 필수 매개변수
        private final int servingSize;
        private final int servings;

        // 선택 매개변수 - 기본값으로 초기화한다.
        private int calories      = 0;
        private int fat           = 0;
        private int sodium        = 0;
        private int carbohydrate  = 0;

        public Builder(int servingSize, int servings) {
            this.servingSize = servingSize;
            this.servings    = servings;
        }

        public Builder calories(int val)
        { calories = val;      return this; }
        public Builder fat(int val)
        { fat = val;           return this; }
        public Builder sodium(int val)
        { sodium = val;        return this; }
        public Builder carbohydrate(int val)
        { carbohydrate = val;  return this; }

        public NutritionFacts build() {
            return new NutritionFacts(this);
        }
    }

    private NutritionFacts(Builder builder) {
        servingSize  = builder.servingSize;
        servings     = builder.servings;
        calories     = builder.calories;
        fat          = builder.fat;
        sodium       = builder.sodium;
        carbohydrate = builder.carbohydrate;
    }

    public static void main(String[] args) {
        NutritionFacts cocaCola = new NutritionFacts.Builder(240, 8)
                .calories(100).sodium(35).carbohydrate(27).build();
    }
}
```


NutritionFacts 클래스는 불변이다. <br>
**빌더의 세터 메서드들은 빌더 자신을 반환하기 때문에, 마치 스트림 처럼 이쁘게 연쇄 호출이 가능하다.** <br>

```java
NutritionFacts cocaCola = new NutritionFacts.Builder(240, 8).calories(100).sodium(35).carbohydrate(27).build();
```


너무 아름답다.. <br>
이런 방식을 흐르듯 연결되는 메서드라는 뜻으로 **Fluent API 혹은 Method Chaining이라고 부른다.** 플루언트 API. 메서드 연쇄는 쓰기도 쉽고 읽기도 너무 쉽다. 

### 요약
생성자나 정적 팩터리가 처리해야할 매개변수가 많다면 빌더 패턴을 선택하는 것이 좋다. <Br>
매개변수 중 다수가 필수가 아니거나, 같은 타입인 경우 더욱 유용하다. <br>
하지만 빌더를 만드는 것도 나름 코스트이므로, 매개변수가 4개 이상은 되어야 그 값어치를 할 수 있다고 생각하면 된다. <br>
확장성을 고려해서 나중에 커질 가능성이 크다면, 전환하기 보다는 처음 부터 빌더로 시작하는 것도 좋다.


## Reference
- Effective Java <조슈아 블로크>


