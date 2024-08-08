# MySQL Clustering Index, Unique Index, Foreign Key Index
# 1. 클러스터링 인덱스
## 1.1 클러스터링 인덱스란? 
Cluster란 밀접해있는 다수의 무언가를 총칭하는 단어이다. 군집 무리 덩어리 등 밀집해있는 객체들을 Cluster라고 하고, Cluster로 만드는 것을 Clustering이라고 한다. <br>

클러스터링 인덱스도 비슷하다. <br>
**MySQL 클러스터링 인덱스란 테이블 레코드를 Primary Key를 기준으로 비슷한 것들 끼리 묶어서 저장한 인덱스를 의미한다.** <br> (이는 인덱스 알고리즘의 일종이라기 보다는 하나의 저장 방식이라고 볼 수 있다.) <br>

이는 비슷한 값들을 동시에 조회하는 경우가 많다는 점에서 착안했다. 예를 들어 범위 검색을 생각해보자. 3월 ~ 6월생 아이들을 검색할 때, 아이들이 출생년도 별로 레코드들이 물리적으로 정렬 되어 서로 모여 있다면, 왔다갔다 할 필요 없이 한번에 3월생 아이 부터 7월생 첫 아이 직전까지 한번에 검색하면 될 것이다. <br> <br>

MySQL에서 클러스터링 인덱스는 InnoDB 스토리지 엔진에서만 지원되고, **기본적으로 테이블을 만들면 Primary Key를 기준으로 오름차순 Clustering Index가 만들어진다.** (중요) <br>
이를 MySQL에서는 "Clustering Key"라고도 부른다. <br> <br>



## 1.2 MySQL InnoDB 클러스터링 인덱스
InnoDB의 모든 테이블은 기본적으로 Primary Key를 기준으로 클러스터링 되어 저장된다. **즉, 레코드는 PK 값의 순서대로 디스크에 저장된다!** <br>
**모든 Secondary Index는 레코드의 주소 대신 PK값을 논리적인 주소로 가지고 있다.** 덕분에 PK를 이용한 레인지 스캔은 상당히 빠르다! <br>

결과적으로 쿼리의 실행계획에서 PK는 다른 보조 인덱스에 비해 비중이 높게 설정 되어 있어 선택될 확률이 높다. <br> <br> 

또 MySQL InnoDB에서 **임의로 새로운 클러스터링 인덱스를 만들 수는 없다.** <br> 오직 Primary Key에 대해서만 만들 수 있다. <br> <br>
그리고 **Primary Key에 대해 실제 레코드 저장 위치가 결정되는데, Primary Key 값을 변경하는 경우 레코드가 물리적으로 저장되는 위치도 변경된다.** <br>
그래서 **클러스터링 인덱스는 인덱스 알고리즘의 일종이라기 보다는 하나의 테이블 레코드 저장 방식이라고 할 수 있다.** <br>
그래서 클러스터링 인덱스나 클러스터링 테이블은 같은 의미라고 생각하면 된다. 그리고 이런 정렬 기준이 되는 Primary Key를 **Clustering Key라고** 표현할 수 있다. <br> <br>

참고로, MyISAM에서는 클러스터링 키가 지원되지 않는다. 그래서 PK 인덱스나 세컨더리 인덱스나 구조적으로 아무런 차이가 없다. 그냥 유니크 속성이 걸린 정도의 차이가 있을 뿐이다. <br> <br>

### 1.2.1 일반 B-Tree 인덱스도 인덱스 키로 정렬되어 있는데 Clustering인가요?
조금 헷갈릴 수 있는데 B-Tree 또한 인덱스 키 값으로 정렬되어 있지만, 이를 클러스터링 인덱스라고 부르지는 않는다. 오직 테이블 레코드들이 실제로 Primary Key로 정렬되어 있는 겨웅에만 클러스터링 인덱스, 클러스터링 테이블이라고 부를 수 있다.

![image](https://github.com/depromeet/amazing3-be/assets/71186266/dd554b85-9517-46d3-9158-2e1584bd265a)

<br>

위 그림은 클러스터링 테이블의 그림이다. 여기에 차이가 있는데, **클러스터링 인덱스는 리프 노드에 실제 데이터들이 저장되어 있다.** 하지만, 일반적으로 **사용자가 임의로 생성하거나, Unique 컬럼에 대해 자동 생성되는 B-Tree는 "Secondary Index"로 리프 노드에 ~~실제 데이터 레코드나 주소값이 아닌~~ Primary Key가 저장되어 있다.** <br> <br>

그래서 Primary Key로 구성된 클러스터링 인덱스의 Key값을 바꿀 때는 신중해야 한다. Primary Key를 변경하면, 레코드를 Delete한 다음 새로 Insert하기 때문에 처리가 느리다. 또한, 레코드의 저장 위치가 Primary Key에 따라 결정되므로, 처리가 느리다. 

### 1.2.2 InnoDB 클러스터링 기준!
#### InnoDB에서 Primary Key가 없는 경우엔 어떻게 정렬될까?

InnoDB는 아래와 같은 기준으로 인덱스를 클러스터링 한다.

<br>

1. Primary Key가 있는 경우 Clustering Key로 선택된다.
2. **NOT NULL 옵션의 Unique Index 중 첫번째 인덱스가 Clustering Key로 선택된다.**
3. **자동으로 유니크한 값을 가지는 Sequential한 칼럼을 내부적으로 추가한 후, Clustering Key로 선택한다.**

<br>

InnoDB에서 테이블에 Primary Key가 없는 경우엔 2번 3번 순서대로 키를 결정한다. 3번 값을 통해 만들어진 일렬 번호는 사용자에게 노출되지 않고, 쿼리에 사용할 수 없다.


## 1.3 Secondary Index에 미치는 영향
**Secondary Index란 리프 노드에 실제 레코드가 저장되는 것이 아닌, 실제 레코드의 Primary Key가 저장된 인덱스이다.** <br> 
예를 들어 생일을 기준으로 인덱스를 생성한 경우, 생일 값과 실제 레코드의 Primary Key들이 저장되는 것이다. 해당 레코드의 다른 값들이 저장되지는 앖는다. <br> <br> MySQL에서 프라이머리 키를 제외한 나머지 모든 인덱스가 세컨더리 인덱스이다. <br> 
유니크 컬럼을 만들면 자동 생성되고, 우리가 임의로  만드는 인덱스도 세컨더리 인덱스이다.  <br> <br>

만약 세컨더리 인덱스가 실제 레코드가 저장된 주소값을 가지고 있었다면, 클러스터링 키 값이 변할 때마다 데이터 레코드의 주소가 변하기 때문에 Secondary Index 테이블이 가지고 있는 주소값들이 변경되어야 할 것이다. <br>
따라서, 이런 비효율을 제거하기 위해 **InnoDB의 모든 Secondary Index는 레코드 저장 주소가 아니라 Parimary Key 값을 저장하도록 구현되어 있다.** <br>
(참고로 MyISAM에선 레코드 주소가 저장되어 있다)


## 1.4 클러스터링 인덱스 장단점
MyISAM은 Primary Key가 클러스터링 되지 않는다. 이런 인덱스와 클러스터링 인덱스를 비교해 장단점을 따져 보자. <br>

대체로 빠른 읽기, 느린 쓰기라고 생각하면 된다.


### 장점
- **Primary Key로 검색할 때 성능이 매우 빠르다! 특히 범위 검색에 강하다.**
- 테이블의 모든 Secondary Index들은 Primary Key를 가지고 있기 때문에, 인덱스만으로 처리될 수 있는 경우가 많다. (커버링 인덱스)


### 단점
- 테이블의 모든 Secondary Index들이 Clustering Key를 갖기 때문에 **키 값의 크기가 큰 경우 전체적으로 인덱스의 크기가 커질 수도 있다.** (주소값이 아닌 키 값을 갖는 것의 단점)
- Secondary Index를 통해 검색할 때, Primary Key로 다시 한번 더 검색해야 하기 때문에 처리 성능이 느림.
- **INSERT시 Primary Key 값에 따라 실제 저장 위치를 결정해야 하기 때문에 느리다.** (아무렇게나 막 저장할 수 는 상태에 비해)
- **Primary Key 변경시 레코드를 Delete하고 다시 Insert하기 때문에 변경이 느리다.**

<br>

### 결론


결국 빠르게 읽는 대신에, 쓰기가 느린 것인데, 보통  웹 서비스의 읽기와 쓰기 비율은 8:2나 9:1에 가까우므로 이러한 상황에서는 감수할만하다고 볼 수 있다.


## 1.5 Clustering Table 주의 사항

1. **인덱스 키의 크기에 주의하라** <br> Clustering Table의 경우 모든 Secondary Index가 Primary Key를 포함하므로, Key의 크기가 커지면 세컨더리 인덱스 크기가 자동으로 커진다.
2. **하지만, 비즈니스적으로 레코드를 대표할 수 있는 값이 있다면, 크기가 커지는 것을 감수하고 그 값을 Primary Key로 써라.** <br> 키 값의 크기가 아무리 크더라도, 클러스터링 키로 사용되는 순간 검색 성능을 매우 빠르게 해주므로, 자주 쓰이고, 비즈니스 적으로 레코드를 대표할 수 있는 값이 있다면 Key로 써라
3. **Primary Key는 반드시 명시해라.** <br> 앞서 말했던 것처럼 어차피 일련번호 칼럼이 추가되는데, 이는 개발자가 사용할 수 없는 값이다. 이럴거면 차라리 AUTO_INCREMENT PK를 추가해서 사용해라. <br> 또한 ROW 기반 복제나, InnoDB Cluster에서는 모든 테이블이 PK를 가져야만 복제 기능이 보장되기도 해서, PK는 만드는 것이 좋다.



# 2. 유니크 인덱스

MySQL에서는 컬럼에 유니크 제약을 걸면 자동으로 인덱스를 생성한다. <br> 
문제는 반대로 인덱스 없이 유니크 제약은 걸 수가 없으니 인지하고 있어야 한다. 이러한 유니크 인덱스에서 NULL은 값으로 쳐주지 않기 때문에, 여러 레코드가 저장될 수 있다. <br>
(물론, PK는 NULL이 허용되지 않으니 착각 금지. 결이 다르다고 생각해라)


## 2.1 유니크 인덱스와 Secondary Index 비교
유니크 인덱스와 Secondary Index는 구조적으로 동일하다. 단지 인덱스 컬럼이 유니크하냐 아니냐의 차이가 있을 뿐이다.

### 2.1.1 인덱스 읽기 성능
성능차는 미미하다. <br>
일반 유니크 X인 세컨더리 인덱스 테이블이 당연히 더욱 읽기 힘든거 아니냐고 할 수 있겠지만, **디스크 읽기는 1번으로 동일하고, CPU에서 칼럼 값을 비교하는 작업이 몇번 더 일어날 뿐이기 때문에 성능상의 차이는 미미하다.** 결국 인덱스 자체의 특성 때문에 느리다고 말할 것은 아니다.


### 2.1.2 인덱스 쓰기 성능
쓰기 성능은 조금 차이가 나는데, 요인은 여러가지가 있다.

1. **중복 체크 과정이 상당히 느리다.**
2. 중복 체크를 해야 해서 버퍼링이 불가능하다.


유니크 인덱스의 경우는 중복된 값이 있는지 체크하는 과정이 있는데, 이 과정이 느리다. <br>
왜냐하면, MySQL에서는 
- **중복 체크를 위한 읽기시, 읽기 잠금 사용**
- **쓰기 시 쓰기 잠금 사용**

위 두가지 이유로 중복 체크 과정 자체가 느리다. **그리고 데드락이 아주 빈번히 발생한다.** <br>

또한, InnoDB는 인덱스 키 저장을 Change Buffer를 통해 버퍼링해서 원래는 빠른데, **유니크 인덱스의 경우 중복 체크 과정이 필요하기 때문에 버퍼링이 불가능하다.** <br>
따라서, 일반적인 Secondary Index에 비해 쓰기가 느리다.


### 2.1.3 인덱스 성능 차이 결론
1. **읽기는 비슷하다.** 결국 디스크 Read 횟수는 비슷하기 때문이다. (CPU 작업 횟수로 인한 차이는 미미하다.)
2. **쓰기는 유니크 인덱스가 느리다.** <br> 중복 검사를 확인하는 읽기-쓰기 작업에 모두 Lock이 있고, 중복 검사 때문에 버퍼링이 불가능하기 때문이다.


## 2.2 유니크 인덱스 주의사항
- 결론 : 유니크 인덱스는 그리 특별하지 않다. 그냥 Secondary Index랑 똑같다. 특별 대우 X


<br>

꼭 필요한 경우라면 유니크 인덱스를 만드는 것이 중요하지만, 가끔 유니크 인덱스라면 뭔가 더 나을 것 같아서 생성하는 사람들이 있다고 한다. 심지어 이미 인덱스가 있는데도 억지로 또 만드는 사람이 있다는데, 별 특별한건 없다. 어차피 그냥 세컨더리 인덱스와 동일하기 때문이다. <br> 
이 밖에는 실행 계획과 [파티션에 끼치는 영향](https://github.com/10000-Bagger/free-topic-study/blob/main/jin/%5BDB%5D%20MySQL%20%ED%8C%8C%ED%8B%B0%EC%85%94%EB%8B%9D.md)이 있으니, 알아두자.


# 3. 외래키 인덱스
**MySQL InnoDB는 외래키 제약이 설정되면 자동으로 연관되는 테이블의 칼럼에 인덱스를 생성한다.** <br> 
그리고 외래키가 제거되지 않은 상태에서는 이 인덱스를 제거할 수 없다! 그냥 계속 있는거라고 생각하자.. (참고로 MySQL에서 외래키는 InnoDB 스토리지 엔진에서만 생성할 수 있다.)


<br> <br>

InnoDB 외래키 관리에는 중요한 두가지 특징이 있다.

1. 테이블의 쓰기 작업으로 인한 Write Lock시 잠금 경합(잠금 대기)이 발생한다.
2. 외래키와 연관되지 않은 컬럼의 변경은 최대한 잠금 경합을 발생시키지 않는다.

<br>

언제 경합이 발생하고, 발생하지 않을까?

## 3.1 자식 테이블이 대기하는 경우

**부모 테이블에서 변경중인 레코드를 참조하는 자식 테이블 레코드. 혹은 부모 테이블에서 변경중인 레코드의 PK를 자식 테이블의 레코드가 새로 참조하게 되는 경우.** <br>

예를 들어
1. **id가 2인 부모 테이블 레코드가 변경을 위해 Write Lock을 획득했다.**
2. 자식 테이블의 어떤 레코드가 **자신의 외래키 값을 2로 변경했다.**
3. 이 경우 1번에서 이미 Write Lock을 획득했기 때문에 **잠금 경합이 발생한다.**


<br>

**만약 자식테이블의 외래키가 아닌 칼럼들을 변경하는 경우 잠금 확장이 발생하지 않는다. 하지만, 외래키 칼럼의 변경 또는 삭제는 부모 테이블의 확인이 필요하므로, 쓰기 잠금의 영향을 받게 된다.**

## 3.2 부모 테이블이 대기하는 경우

자식 테이블에서 변경중인 레코드가 참조중인 부모 테이블 레코드를 변경하려고 시도하는 경우 잠금 경합 발생한다.  <br>

예를 들어

1. 외래키 값이 2인 자식 테이블 레코드의 어떤 칼럼을 변경한다. 이때 Write Lock을 획득한다.
2. 부모 테이블에서 PK가 2인 레코드 삭제를 시도한다.
3. 잠금 경합이 발생한다.

<Br>

부모 레코드를 삭제하는 경우 자식 레코드도 삭제하도록 CASACADE를 걸어둔 경우 무조건 락이 걸리게 된다.


## 3.3 결론
외래키를 생성할 때는 이러한 잠금 경합까지 고려해서 모델링 해야한다. <br>
외래키가 걸린 자식 테이블에 레코드를 추가하면, 부모 테이블에 실제로 해당 참조키가 존재하는지 확인하는데, 이때 Read Lock이 걸린다. 외래키를 사용할 때는 이런 잠금 경합들을 이해하고 고려할 줄 알아야 한다.