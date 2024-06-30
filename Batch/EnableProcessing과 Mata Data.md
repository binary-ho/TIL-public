
## 1. @EnableBatchProcessing 살펴보기
main 함수에 `@EnableBatchProcessing`를 붙여 배치 Application을 활성화 시킬 수 있다. 궁금해서 구성 요소들과 기본값을 한번 살펴보았다.

```java
@Target({ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Import({BatchRegistrar.class, ScopeConfiguration.class, AutomaticJobRegistrarBeanPostProcessor.class, BatchObservabilityBeanPostProcessor.class})
public @interface EnableBatchProcessing {
    boolean modular() default false;

    String dataSourceRef() default "dataSource";

    String databaseType() default "";

    String transactionManagerRef() default "transactionManager";

    String executionContextSerializerRef() default "executionContextSerializer";

    String charset() default "UTF-8";

    String tablePrefix() default "BATCH_";

    int maxVarCharLength() default 2500;

    String incrementerFactoryRef() default "incrementerFactory";

    String jobKeyGeneratorRef() default "jobKeyGenerator";

    String lobHandlerRef() default "lobHandler";

    int clobType() default 2005;

    String isolationLevelForCreate() default "ISOLATION_SERIALIZABLE";

    String taskExecutorRef() default "taskExecutor";

    String conversionServiceRef() default "conversionService";
}
```

### 1.1 `@Import`로 가져온 클래스들
- `BatchRegistrar`: 배치 관련 빈들을 등록한다.
- `AutomaticJobRegistrarBeanPostProcessor`: JobRegistrar를 자동으로 등록하는 PostProcessor
- `ScopeConfiguration`: 스코프 설정 클래스
- `BatchObservabilityBeanPostProcessor`: 배치 작업 모니터링을 위한 PostProcessor

### 1.2 batch 5의 다양한 설정값들
### TODO : 지금은 봐도 용도를 모르겠는 값들이 많은데, 지금은 대략적으로 알아보고 나중에 용도를 정확히 알게 되면 보충하자


- `modular` : 모듈화된 배치 구성을 사용할건지 체크하는 설정이다. 아직은 어떤 용도인지 정확히는 모르겠다.
- `dataSourceRef()` `databaseType()`: 데이터 소스와 DB 타입을 지정할 수 있다
- `transactionManagerRef()` : 트랜잭션 매니저를 지정할 수 있다. 
- `executionContextSerializerRef()` : 실행 컨텍스트를 직렬화 하기 위한 빈을 지정할 수 있다. 아직은 정확히 어떤 용도인지 모르겠다. 실행 컨텍스트들은 꼭 직렬화 되어야 하는걸까? Job 수행마다 만들어지지 않는 걸까? 
- `charset()` : 인코딩 설정이 가능하다. 기본값은 "UTF-8"입니다.
- `tablePrefix()` : 테이블의 접두사를 지정한다. 아마 Batch Repository의 Table을 위한 설정인 것 같다. 나중엔 알게 되겠지
- `maxVarCharLength()` : repo의 VARCHAR 열 최대 길이 지정. 아직은 왜 있는건지 모르겠다. 왜 제한해야 하는가? 다 저장되면 좋을 것 같은데, 뭔가 문제가 생겨서 터무니 없이 큰 값이 저장될 수도 있고, 그것을 막는 것일까? 
- `incrementerFactoryRef()` : increment 방식으로 id 생성시 사용하는 빈을 선택한다.
- jobKeyGeneratorRef(): Job의 고유 키를 생성하는 데 사용할 JobKeyGenerator의 빈 이름을 지정합니다. 기본값은 "jobKeyGenerator"입니다.
- `lobHandlerRef()` : 큰 데이터를 저장하기 위한 CLOB, BLOB의 Handler 빈 이름 지정 - 기본값 "lobHandler"
- `clobType()` : CLOB 데이터 유형을 지정. 기본값은 2005인데, java.sql.Types.CLOB를 의미한다고 한다. 이게 무슨 개념이지? 클래스별로 숫자가 채번 되어있는건가?
- `isolationLevelForCreate()` : **트랜잭션 격리 수준을 지정. 기본값은 SERIALIZABLE이다.** Job의 기본 격리 수준은 Serializable이구나 왜일까?
- `taskExecutorRef()` : **배치 작업을 실행시 사용할 TaskExecutor 지정** - 기본 이름은 "taskExecutor"라지만, 이것은 빈 이름에 불과하지 않는가? 아래에서 더 찾아보았다.
- conversionServiceRef(): 타입 변환을 위한 ConversionService 빈 이름을 지정


### 1.3 Spring Batch 기본 TaskExecutor
결론적으론, SyncTaskExecutor가 사용된다. <br>
정말 평범하게 동기적으로 task를 실행시키기만 한다
```java
/**
 * {@link TaskExecutor} implementation that executes each task <i>synchronously</i>
 * in the calling thread.
 *
 * <p>Mainly intended for testing scenarios.
 *
 * <p>Execution in the calling thread does have the advantage of participating
 * in its thread context, for example the thread context class loader or the
 * thread's current transaction association. That said, in many cases,
 * asynchronous execution will be preferable: choose an asynchronous
 * {@code TaskExecutor} instead for such scenarios.
 *
 * @author Juergen Hoeller
 * @since 2.0
 * @see SimpleAsyncTaskExecutor
 */
@SuppressWarnings("serial")
public class SyncTaskExecutor implements TaskExecutor, Serializable {

	/**
	 * Executes the given {@code task} synchronously, through direct
	 * invocation of it's {@link Runnable#run() run()} method.
	 * @throws IllegalArgumentException if the given {@code task} is {@code null}
	 */
	@Override
	public void execute(Runnable task) {
		Assert.notNull(task, "Runnable must not be null");
		task.run();
	}

}
```

위 클래스를 사용한다는 사실은 Batch 4에서는 DefualtBatchConfiguration에서 찾아볼 수 있다.

![image](https://github.com/depromeet/amazing3-be/assets/71186266/04751652-cebe-4f37-9332-4c487401f32d)

<br> <br>

Batch 


## 2. 스프링 배치 초기화 설정 클래스
![image](https://github.com/depromeet/amazing3-be/assets/71186266/dec46d9f-ae2f-4c02-ac16-cfc90ca03d8e)


1. SimpleBatchConfiguration : JobBuilderFactory와 StepBuilderFactory를 생성한다.
  - **스프링 배치의 주요 구성 요소를 프록시 객체로 생성한다.**
2. BatchConfigurerConfiguration
   - BasicBatchConfigurer : SimpleBatchConfiguration에서 생성한 프록시 객체의 실제 대상 객체를 생성한다. 빈으로 의존성 주입을 받아 주요 객체들을 참조해 사용할 수 있다. -> 향로님 글에서 본 유틸 빈 추가를 여기서 할 수 있는걸까?
   - JpaBatchConfigurer : JPA 관련 객체를 생성해주는 설정 클래스이다.
   - 사용자 정의 BatchConfigurer 인터페이스를 구현해 사용할 수 있다. -> 
3. BatchAutoConfiguration : 스프링 배치가 초기화 될 때 자동으로 실행되는 설정 클래스이다.
  - Job을 수행하는 JobLauncherApplicationRunner 빈을 생성한다.

## 3. Spring Batch Meta Data
Spring Batch는 Job, Step, JobParameters 등의 여러 정보들을 저장하고 업데이트하고 조회할 수 있는 다양한 스키마를 제공해준다. 과거 현재의 실행에 대한 세세한 정보들과 실행에 대한 성공-실패 여부 등을 일목요연하게 관리함으로써 배치 운용을 돕는다.

<br>

스키마는 DB의 유형별로 제공되고, 생성 옵션으로 수동으로 생성할지, 자동으로 생성할지, 자동으로 생성한다면 어떤 상황에서 생성할지 선택 가능하다.

![image](https://github.com/depromeet/amazing3-be/assets/71186266/9cc159fa-b115-4a81-8296-e37133329761)

가장 왼쪽 세로줄의 두 테이블엔 Step에 대한 Meta Data들이 담겨있다. 각 Execution들이 언제 어떻게 진행되는지, 얼마나 진행됐는지 (Read Write Count) 등 자세한 정보들이 담겨있다. 그리고 나머지 2개의 테이블엔 Job에 대한 정보들이 담겨져 있다. Job의 한번 시행마다 생성되는 Instance에 대한 정보, 시행마다의 정보, Params에 대한 정보 등 아주 자세한 정보들이 주어진다. 이 정보들을 통해 Job들의 성공-실패를 확인할 수 있고, 실패한 경우 상황에 대한 정보를 받아볼 수 있다.

### 3.1알고 넘어가야 할 점들
1. `BATCH_JOB_INSTANCE` : 
   - job_name과 job_key를 키로 하여 데이터가 저장된다.
   - **JOB_KEY는 job_name과 jobParameter를 합쳐 해싱한 값이 저장된다. 즉, job_name과 jobParameter로 Instance가 식별되는 셈** 그런데 파라미터가 달라도 해싱된 값 자체는 같을 수도 있는거 아닌가?
2. `BATCH_JOB_EXECUTION` : Job 인스턴스가 여러개의 Execution을 가질 수 있음. JOB의 실행정보 저장. 
- Job 생성 시작, 종료시간, 실행상태, 메시지 등을 관리
- END_TIME 값의 경우 Job 실행중 오류가 발생해 중단된다면 값이 저장되지 않을 수도 있다.
