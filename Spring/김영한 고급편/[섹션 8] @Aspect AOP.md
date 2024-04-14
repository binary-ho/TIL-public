# @Aspect AOP

스프링의 도움을 받으면 프록시 적용이 너무 쉬워진다. <br>
그냥 포인트컷과 어드바이스로 구성된 어드바이저를 만든 다음 빈으로 등록하면 <br>
나머지는 자동 프록시 생성기가 전부 자동으로 처리해준다.  <br>

### 자동 프록시 생성기가 해주는 일

1. 스프링 빈으로 등록된 어드바이저들을 찾고
2. 포인트 컷이 매칭되는 스프링 빈들에 자동으로 프록시를 적용해준다

스프링은 `@Aspect`라는 AspectJ 프로젝트에서 제공하는 애노테이션으로 
편리하게 포인트 컷과 어드바이스로 구성된 어드바이저 생성 기능을 지원해준다! <Br>

이제까지 만든 어드바이저를 리팩토링 해봅시다.

## 1. 자동 프록시 생성기 `AnnotationAwareAspectJAutoProxyCreator`
자동 프록시 생성기 `AnnotationAwareAspectJAutoProxyCreator`는 이름 그대로 `@Aspect` 어노테이션을 인식해서 
어드바이저로 변환해준다. <br> 


```java
@Slf4j
@Aspect
public class LogTraceAspect {

    private final LogTrace logTrace;

    public LogTraceAspect(LogTrace logTrace) {
        this.logTrace = logTrace;
    }

    /* MEMO : @Around 의 값이 포인트 컷이 되고,
        @Around가 달려있는 메서드가 어드바이스가 된다
        입력으로 조인 포인트를 받는다.
        이 하나의 메서드가 결국 어드바이저를 표현한 것이다!
    * */
    @Around("execution(* hello.proxy.app..*(..))")
    public Object execute(ProceedingJoinPoint joinPoint) throws Throwable {
        TraceStatus status = null;
        try {
            String message = joinPoint.getSignature().toShortString();
            status = logTrace.begin(message);

            //로직 호출
            Object result = joinPoint.proceed();

            logTrace.end(status);
            return result;
        } catch (Exception e) {
            logTrace.exception(status, e);
            throw e;
        }
    }
}
```
`AnnotationAwareAspectJAutoProxyCreator`는 클래스의 `@Aspect`를 인식한다. <br>
내부에 `@Around`가 달린 클래스를 보자. 
1. `@Around("execution(* hello.proxy.app..*(..))")` 가 포인트 컷이 된다.
2. 그리고 메서드가 어드바이스가 된다
3. 합치면 어드바이저가 되는 것이다.

자동 프록시 생성기는 2가지 일을 해주는데,

1. `@Aspect`를 보고 어드바이저로 변환해서 저장한다.
2. 어드바이저를 기반으로 프록시를 생성한다.

## 1.1 `@Aspect`를 어드바이저로 변환해서 저장하는 과정 

`AnnotationAwareAspectJAutoProxyCreator`는 어드바이저 빌더를 통해 어드바이저를 만들어 낸다. <Br>
어드바이저 빌더는 `BeanFactoryAspectJAdvisorBuilder` 클래스로, `@Aspect`의 정보를 기반으로 어드바이저를 만들고, <br>
`@Aspect` 어드바이저 빌더 내부 저장소에 캐시한다. <br>
어드바이저가 이미 만들어져 있는 경우 캐싱된 것을 반환한다.

1. 스프링 실행 : 스프링 애플리케이션 로딩 시점에 자동 프록시 생성기를 호출한다
2. 모든 `@Aspect` 빈 조회 : 자동 프록시 생성기는 스프링 컨테이너에서 `@Aspect` 어노테이션이 붙은 스프링 빈을 모두 조회한다. (?)
3. 어드바이저 생성 : `@Aspect` 어드바이저 빌더를 통해 `@Aspect` 애노테이션 정보를 기반으로 어드바이저 생성하고, <br> 어드바이저 빌더 내부에 저장한다.



## 1.2 어드바이저를 기반으로 프록시를 생성한다 
   자동 프록시 생성기의 작동 과정
1. 스프링 빈이 생성됨
2. 생성된 객체를 빈 저장소에 등록하기 직전에 빈 후처리기에 전달한다.
   1. **Advisor 빈 조회** : 스프링 컨테이너에서 Advisor 빈을 모두 조회
   2. **`@Aspect` Advisor 조회** : `@Aspect` 어드바이저 빌더 내부에 저장된 Advisor를 모두 조회 
3. **프록시 적용 대상 체크** : 직전 과정에서 조회한 Advisor에 포함 되어 있는 포인트컷을 사용 해서 <br> 해당 객체가 프록시를 적용할 대상 인지 아닌지 판단한다. <br> 이때 객체의 클래스 정보와, 해당 객체의 모든 메서드를 포인트컷에 하나 하나 모두 매칭해 본다. <br> 그래서 조건이 하나라도 만족하면 프록시 적용 대상 클래스가 된다. 
4. **프록시 생성**: 프록시 적용 대상이면 프록시를 생성하고 프록시를 반환 
5. **반환된 객체를 스프링 빈으로 등록** : 프록시를 스프링 빈으로 등록. 만약 프록시 적용 대상이 아니라면 원본 객체를 반환해서 원본 객체를 스프링 빈으로 등록
