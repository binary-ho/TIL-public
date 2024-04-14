

## 1. 포인트 컷의 적용

### 1.1 기본 적용법

기본 적용이다. `hello.aop.order` 패키지와 그 하위 패키지 `..`를 지정하는 AspectJ 표현식 사용 <br>
-> `execution(* hello.aop.order..*(..))`

```java
@Slf4j
@Aspect
public class AspectV1 {

    @Around("execution(* hello.aop.order..*(..))")
    public Object doLog(ProceedingJoinPoint joinPoint) throws Throwable {
        log.info("[log] {}", joinPoint.getSignature());
        return joinPoint.proceed();
    }
}

```

<br>

`joinPoint.getSignature()`로 메서드의 시그니처를 기록해봤다.

<br>

실제로 AspectJ를 사용하는 것은 아니다. 스프링 AOP는 단지 AspectJ의 문법을 지원할 뿐이다.  <br>
`@Aspec`를 포함한 `org.aspectj` 패키지 관련 기능은 `aspectjweaver.jar` 라이브러리가 제공 <br>
**하지만 계속 말 하지만 AspectJ가 제공하는 어노테이션이나 관련 인터페이스만 사용하고, 실제 AspectJ가 제공하는 컴파일, 로드타임 위버 등을 사용하는 것은 아님 <br>
스프링은 프록시 방식 AOP를 사용함** <br>


### 1.2 포인트 컷 시그니처 적용

```java

@Slf4j
@Aspect
public class AspectV2 {

    // hello.aop.order 패키지와 하위 패키지
    // MEMO : 포인트 컷 시그니처!
    @Pointcut("execution(* hello.aop.order..*(..))")
    private void allOrder() {}

    @Around("allOrder()")
    public Object doLog(ProceedingJoinPoint joinPoint) throws Throwable {
        log.info("[log] {}", joinPoint.getSignature()); 
        return joinPoint.proceed();
    }

    @Around("allOrder() && allService()")
    public Object doTransaction(ProceedingJoinPoint joinPoint) throws Throwable {
        try {
            log.info("[트랜잭션 시작] {}", joinPoint.getSignature());
            Object result = joinPoint.proceed();
            log.info("[트랜잭션 커밋] {}", joinPoint.getSignature());
            return result;
        } catch (Exception e) {
            log.info("[트랜잭션 롤백] {}", joinPoint.getSignature());
            throw e;
        } finally {
            log.info("[리소스 릴리즈] {}", joinPoint.getSignature());
        }
    }
}

```
포인트 컷 시그니처를 사용해서 여러군데에서 편하게 쓸 수 있게 됐다. <br>
논리 연산자와 함께 여러 조건 하에 적용할 수도 있다.

### 1.3 포인트컷 클래스 운용

```java
public class Pointcuts {

    // hello.aop.order 패키지와 하위 패키지
    @Pointcut("execution(* hello.aop.order..*(..))")
    public void allOrder() {}

    // 클래스 이름 패턴이 *Service
    @Pointcut("execution(* *..*Service.*(..))")
    public void allService() {}

    // hello.aop.order 패키지와 하위 패키지 이면서 클래스 이름 패턴이 *Service 임
    @Pointcut("allOrder() && allService()")
    public void allOrderAndService() {}
}
```

위와 같이 포인트 컷들을 모아둔 클래스를 만들어서 사용해도 된다. <br>
사용은 아래와 같이 패키지명 전체를 적으며 사용해야 한다.
```java
@Slf4j
@Aspect
public class AspectV4 {

    @Around("hello.aop.order.aop.Pointcuts.allOrder()")
    public Object doLog(ProceedingJoinPoint joinPoint) throws Throwable {
        log.info("[log] {}", joinPoint.getSignature());
        return joinPoint.proceed();
    }

    // hello.aop.order 패키지와 하위 패키지 이면서 클래스 이름 패턴이 *Service 임
    @Around("hello.aop.order.aop.Pointcuts.allOrderAndService()")
    public Object doTransaction(ProceedingJoinPoint joinPoint) throws Throwable {
        try {
            log.info("[트랜잭션 시작] {}", joinPoint.getSignature());
            Object result = joinPoint.proceed();
            log.info("[트랜잭션 커밋] {}", joinPoint.getSignature());
            return result;
        } catch (Exception e) {
            log.info("[트랜잭션 롤백] {}", joinPoint.getSignature());
            throw e;
        } finally {
            log.info("[리소스 릴리즈] {}", joinPoint.getSignature());
        }
    }
}
```

### 1.4 어드바이스 순서 적용
어드바이스의 순서는 오직 @`Aspect` 단위로만 지정할 수 있다. <br>
따라서, 불편하겠지만 inner class를 사용해서 해결해야 한다. <br>
inner class를 만든 다음`@Aspect`를 달아주고 `Order(N)` 어노테이션을 통해 순서를 지정해준다.

```java
package hello.aop.order.aop;

import lombok.extern.slf4j.Slf4j;
import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.springframework.core.annotation.Order;

@Slf4j
public class AspectV5Order {

    @Aspect
    @Order(2)
    public static class LogAspect {
        @Around("hello.aop.order.aop.Pointcuts.allOrder()")
        public Object doLog(ProceedingJoinPoint joinPoint) throws Throwable {
            log.info("[log] {}", joinPoint.getSignature()); //join point 시그니처
            return joinPoint.proceed();
        }
    }

    @Aspect
    @Order(1)
    public static class TransactionAspect {
        @Around("hello.aop.order.aop.Pointcuts.allOrderAndService()")
        public Object doTransaction(ProceedingJoinPoint joinPoint) throws Throwable {
            try {
                log.info("[트랜잭션 시작] {}", joinPoint.getSignature());
                Object result = joinPoint.proceed();
                log.info("[트랜잭션 커밋] {}", joinPoint.getSignature());
                return result;
            } catch (Exception e) {
                log.info("[트랜잭션 롤백] {}", joinPoint.getSignature());
                throw e;
            } finally {
                log.info("[리소스 릴리즈] {}", joinPoint.getSignature());
            }
        }
    }
}
```

## 2. 어드바이스의 종류와 적용
1. `@Around:` 메서드 호출 전후에 수행, 가장 강력한 어드바이스, 조인 포인트 실행 여부 선택, 반환값 변환, 예외 변환 그냥 모든 것이 가능
2. `@Before` : 조인 포인트 실행 이전에 실행. 작업 흐름을 변경할 수는 없음 이 로직이 끝나면 알아서 원래 로직이 실행됨
3. `@AfterReturning`: 조인 포인트가 정상 완료후 실행. <br> `returning` 속성으로 결과를 사용할 수 있는데, 만약 `Object`가 아닌 다른 자료형을 사용하면 Return이 해당 자료형이거나 하위 타입인 메서드만 적용된다. 
4. `@AfterThrowing` : 메서드가 예외를 던지는 경우 실행. `throwing` 옵션으로 Exception 사용 가능
5. `@After`: 조인포인트가 정상 또는 예외에 관계없이 실행 -> finally 와 같다.


사실상 `@Around` 외에는 `@Around`가 할 수 있는 일을 세분화 한 것이다. <br>
`@Around`를 쓸 때는 `ProceedingJoinPoint`를 써야 하는데, `@Around`를 쓸 때는 직접 `proceed()` 메서드를 호출해서 실행해줘야 한다. <br>
`@Around`는 기능이 참 많다
1. 조인 포인트 실행 여부 선택 : `joinPoint.procedd()` 호출 여부 자체를 선택할 수 있음
2. 조인 포인트 proceed 여러번 실행도 가능
3. 전달 값을 변환할 수 있음 : `joinPoint.proceed(args[])`
4. 반환 값을 변환할 수 있음
5. 예외를 변환할 수 있음
6. 트랜잭션과 같이 try-catch 처리 가능


각 어노테이션은 아래와 같이 사용할 수 있다.

```java
@Slf4j
@Aspect
public class AspectV6Advice {

    @Around("hello.aop.order.aop.Pointcuts.allOrderAndService()")
    public Object doTransaction(ProceedingJoinPoint joinPoint) throws Throwable {

        try {
            // @Before
            log.info("[트랜잭션 시작] {}", joinPoint.getSignature());
            Object result = joinPoint.proceed();

            // @AfterReturning : proceed 이후
            log.info("[트랜잭션 커밋] {}", joinPoint.getSignature());
            return result;
        } catch (Exception e) {

            // @AfterThrowing
            log.info("[트랜잭션 롤백] {}", joinPoint.getSignature());
            throw e;
        } finally {

            // @After
            log.info("[리소스 릴리즈] {}", joinPoint.getSignature());
        }
    }

    @Before("hello.aop.order.aop.Pointcuts.allOrderAndService()")
    public void doBefore(JoinPoint joinPoint) {
        log.info("[@Before] {}", joinPoint.getSignature());
    }

    @AfterReturning(value = "hello.aop.order.aop.Pointcuts.allOrderAndService()", returning = "result")
    public void doReturn(JoinPoint joinPoint, Object result) {
        log.info("[@AfterReturning] {} return={}", joinPoint.getSignature(), result);
    }

    @AfterThrowing(value = "hello.aop.order.aop.Pointcuts.allOrderAndService()", throwing = "ex")
    public void doThrowing(JoinPoint joinPoint, Exception ex) {
        log.info("[@AfterThrowing] {} message={}", ex, ex.getMessage());
    }

    @After(value = "hello.aop.order.aop.Pointcuts.allOrderAndService()")
    public void doAfter(JoinPoint joinPoint) {
        log.info("[@After] {}", joinPoint.getSignature());
    }
}

```
