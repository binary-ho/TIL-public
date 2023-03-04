# Bucket4J
Bucket4J는 쓰로틀링을 위한 라이브러리다. <br>
**짧은 순간 너무 많은 요청으로 서버에 심각한 부하가 발생하는 것을 막아주기 위한 쓰로틀링에 적합하다.** <Br>
어플리케이션 레벨에서 쓰로틀링을 적용해줄 떄, 자바 라이브러리인 Bucket4J를 활용할 수 있다. <br>
작동 원리는 무엇일까? <br>
Bucket4J는 내부적으로 Token Bucket 알고리즘을 통해 입력이 들어오는 속도를 조절한다. <br>
과자가 담겨있는 마법의 항아리가 있다고 생각해보자. <br>
마법의 항아리는 총 10개의 과자를 담을 수 있고, <br> 
10개 보다 작은 갯수의 과자가 남게 되면 10초에 1개의 과자를 만들어낸다. <br>
진호는 너무 배가 고파서 아주 빠른 속도로 과자를 먹어치웠다. <br>
당연히 항아리는 금방 바닥을 보이게 되었고, <br>
과자가 없을 때는 10초를 세며 과자가 만들어지기를 기다려야만 한다. <Br>
이것이 바로 Token Bucket 알고리즘의 원리이다. <br>
**버킷은 초당 정해진 갯수의 토큰을 만들어낸다.** <br>
**가져갈 토큰이 남아 있는 경우에만 유저는 요청에 대한 처리를 받을 수 있고,** <br>
**토큰이 없는 경우 유저의 요청 처리는 반려될 수 있다.** <br> <br>

유저가 할 일은 용량과 토큰 생성 주기를 정해준 다음, <Br>
필터로 만들어서 서블렛 단에서 처리하거나, <br> 
핸들러 인터셉터를 만들어서 필터 이후 컨트롤러 직전에 처리하면 된다. <br>
이제 그 사용법을 알아보자.

## 1. Bucket 생성하기
기본적으로 Bucket을 생성하는 법을 알아보자. <br>
몇 가지 알아두어야 할 개념이 있다.
### 1.1 `Refill`
리필 클래스는 정해진 시간 동안 몇 개의 토큰을 리필할지 결정한다 <br> 
위에서 예시로 들었던 쿠키 항아리의 예시와 같이 토큰 생성 주기를 정하는 클래스이다.

#### Refill Intervally
```java
    private static final int INTERVAL_TOKEN_REFILL_SECONDS = 30;
    private static final int INTERVAL_TOKEN_REFILL_COUNT = 5;

    Refill intervalTokenRefill = Refill.intervally(INTERVAL_TOKEN_REFILL_COUNT, Duration.ofSeconds(INTERVAL_TOKEN_REFILL_SECONDS));
```
`intervally(갯수, 주기)` : 넣은 주기동안 interval하게 넣은 갯수의 토큰이 뿅 하고 전부 생긴다. <br>
위에 예시에서 주기를 30초, 토큰 갯수를 5개 넣었으니, 30초마다 5개가 뿅 하고 한번에 전부 생겨난다. <br>

### Refill Greedy
```java
    private static final int GREEDY_TOKEN_REFILL_MINUTES = 1;
    private static final int GREEDY_TOKEN_REFILL_COUNT = 12;

    Refill greedyTokenRefill = Refill.greedy(GREEDY_TOKEN_REFILL_COUNT, Duration.ofMinutes(GREEDY_TOKEN_REFILL_MINUTES));
```
`greedy(갯수, 주기)` : Greedy하게 생성한다는건, 정해진 기간동안 정해진 갯수만큼 서서히 생겨나는 것이다. <Br>
위의 예시에선 1분 동안 12개의 토큰이 greedy하게 생겨나길 주문했다. <Br>
그러므로 5초에 1개씩 생성된다. <br>

위 두 메서드를 이용하면 직관적으로 얼마 동안 몇 개가 **어떻게** 생성될지를 결정할 수 있다.


### 1.2 `Bandwidth`
Bandwidth는 위에서 만든 Refill을 통해 만들 수도 있고, 아주 간단하게 `simple`이라는 메서드로 만들 수 있는 클래스이다. <br>
전자는 정석적으로 만드는 방식이므로, `classic`이라는 이름의 메서드로 만들 수 있다. <br>
나는 전자전기공학부라 최대 응답 주파수 사이를 떠올렸으나, 컴퓨터 공학에선 데이터의 최대 전송 속도를 대역폭이라고 부른다고 한다. <br>
여기에선 토큰 최대 갯수, 버킷의 용량처럼 생각하면 될 것 같다.

```java
    private static final int MAX_BANDWIDTH = 10;

    Bandwidth intervalBandwidth = Bandwidth.classic(MAX_BANDWIDTH, intervalTokenRefill);
    Bandwidth greedyBandwidth = Bandwidth.classic(MAX_BANDWIDTH, greedyTokenRefill);
```
위와 같이 미리 만든 Refill을 통해 만드는 `classic`메서드이다. <br>
가장 앞에 들어간 `MAX_BANDWIDTH`는 최대 용량이다. <br>
해석해보면 첫 번째는 인터벌하게 토큰을 채우는 최대 용량 10짜리 Bandwidth를 만든 것이고, <br>
두 번째는 그리디하게 토큰을 채우는 최대 용량 10짜리 Bandwidth를 만든 것이 된다. <br>


```java
    private static final int MAX_BANDWIDTH = 10;

    Bandwidth simpleBandwidth = Bandwidth.simple(MAX_BANDWIDTH, Duration.ofMinutes(1));
```


### 1.3 `Bucket`
버킷 생성은 builder를 통해 진행한다. <br>
**addLimit 메서드를 통해 Bandwidth를 추가하여 버킷을 만들 수 있고, <br> 하나의 버킷에 다양한 Bandwidth를 추가할 수도 있다!!** <br>

```java
    Bucket intervalBucket = Bucket.builder()
        .addLimit(intervalBandwidth)
        .build();

    Bucket greedyBucket = Bucket.builder()
        .addLimit(greedyBandwidth)
        .build();

    Bucket simpleBucket = Bucket.builder()
        .addLimit(simpleBandwidth)
        .build();
```
위와 같이 버킷을 손 쉽게 만들 수 있다.  <br>
이렇게 버킷을 만들었으니 한번 적용해보겠다.

## 2. 사용해보기
여기선 사용해보는 법을 확인하겠다. <br>
이후 실제 인터셉터와 함께 적용하는 법도 보여주겠다.

```java
    private static final String HELLO_BUCKET4J = "Hello! Bucket4j!";
    private static final String STOP_REQUEST = "제발 멈추어주세요";

    ...

    @GetMapping("/test")
    public ResponseEntity<String> getData() {

        if (intervalBucket.tryConsume(1)) {
            System.out.println(HELLO_BUCKET4J);
            return ResponseEntity.ok(HELLO_BUCKET4J);
        }

        System.out.println(STOP_REQUEST);
        return ResponseEntity.status(HttpStatus.TOO_MANY_REQUESTS).build();
    }
```
이번엔 앞서 만든 인터벌 버킷을 사용할 것이다. <br>
인터벌 버킷은 인터벌 리필을 사용했었고, 30초에 5개의 토큰을 만들고 최대 10개의 토큰을 가질 수 있다. <br>

위와 같이 컨트롤러를 만들어서, 요청시 토큰을 사용하며 요청을 처리하는 API를 구현해보았다. <br>
사용한 메서드는 `tryConsum(long)`메서드로, 입력 받은 숫자 갯수만큼의 토큰을 사용한다. <Br>
사용할 토큰이 남아 있는 경우 true를 반환하면서 1개의 토큰을 사용하고, <Br>
불가능할 경우엔 false를 반환한다. <br>

![stoprequest](https://user-images.githubusercontent.com/71186266/222907084-a7b771d9-067e-40b1-af72-f4e53da02422.png)

포스트맨을 통해 계속해서 요청을 보내 보았다. <br>
위에 보이는 것과 같이, 10번이 넘어가는 요청은 걸러졌다. <br>
약 30초 이후 다시 실행해보았다. <br>

![5 request](https://user-images.githubusercontent.com/71186266/222907083-9912cdce-6e6e-4d18-b292-74cedd40d180.png)

딱 5번의 요청만 성공한 것을 확인할 수 있었다! <br>
남은 토큰 갯수를 확인하는 `tryConsumeAndReturnRemaining` 메서드와 <br>
사용 가능한 만큼 토큰을 소비하는 `tryConsumeAsMuchAsPossible` 도 있다. <Br>

tryConsumeAndReturnRemaining을 사용하면 아래와 같이 토큰 갯수를 확인할 수도 있다. <Br>

![reamining](https://user-images.githubusercontent.com/71186266/222907487-7d044399-8d91-4c41-a623-34efeb7a39bc.png)


## 3. 실제 적용
실제 적용은 아래와 같이 한다. <Br>
1. 버킷을 만든다.
2. `HandlerInterceptor`를 구현한 클래스를 만든다
3. `WebMvcConfigurer`를 구현한 클래스에 등록하여 적용한다



### 1. 버킷 만들기
```java
@Component
public class IntervalRateLimiter implements RateLimiter {
    private static final int INTERVAL_TOKEN_REFILL_SECONDS = 30;
    private static final int INTERVAL_TOKEN_REFILL_COUNT = 5;
    private static final int MAX_BANDWIDTH = 10;

    private final Bucket intervalBucket;

    public IntervalRateLimiter() {
        Refill intervalTokenRefill = Refill.intervally(INTERVAL_TOKEN_REFILL_COUNT, Duration.ofSeconds(INTERVAL_TOKEN_REFILL_SECONDS));
        Bandwidth intervalBandwidth = Bandwidth.classic(MAX_BANDWIDTH, intervalTokenRefill);
        intervalBucket = Bucket.builder()
            .addLimit(intervalBandwidth)
            .build();
    }

    @Override
    public boolean tryConsume(long numToken) {
        return intervalBucket.tryConsume(numToken);
    }
}

```
앞서 설명한 것과 비슷한 IntervalBucket을 만드는 IntervalRateLimiter클래스이다.


### 2. `HandlerInterceptor`를 구현한 클래스 만들어서 인터셉터 등록
`HandlerInterceptor`를 구현한 클래스를 만든다. <Br>
`preHandle` 메서드를 오버라이딩해서 인터셉터에서 컨트롤러 호출 전에 버킷에서 토큰 1개를 꺼낸다.
```java
@Component
public class ThrottlingInterceptor implements HandlerInterceptor {

    private final RateLimiter rateLimiter;

    public ThrottlingInterceptor(RateLimiter rateLimiter) {
        this.rateLimiter = rateLimiter;
    }

    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) {
        if (rateLimiter.tryConsume(1)) {
            System.out.println("Hello! Bucket4j!");
            return true;
        }

        System.out.println("그만하세요 제발");
        return false;
    }
}
```

### 3. `WebMvcConfigurer`를 구현한 클래스에 등록하여 적용하기

```java
@Component
public class WebConfiguration implements WebMvcConfigurer {

    private final ThrottlingInterceptor throttlingInterceptor;

    public WebConfiguration(ThrottlingInterceptor throttlingInterceptor) {
        this.throttlingInterceptor = throttlingInterceptor;
    }

    @Override
    public void addInterceptors(InterceptorRegistry registry) {
        registry.addInterceptor(throttlingInterceptor);
    }
}
```

인터셉터를 적용해주면 설정은 끝이 난다. <br>
10번 이상을 호출하니 아래와 같이 인터셉터가 잘 적용되었음을 확인할 수 있었다.

![final succes](https://user-images.githubusercontent.com/71186266/222912194-ede7a6c6-5455-4797-a7e7-8d214f541431.png)


## Reference
- [두둥 레포지토리](https://github.com/Gosrock/DuDoong-Backend)
- [Rest API 호출 제한 - Bucket4J](https://browndwarf.tistory.com/79)
- [Rate Limiting a Spring API Using Bucket4j](https://www.baeldung.com/spring-bucket4j)
