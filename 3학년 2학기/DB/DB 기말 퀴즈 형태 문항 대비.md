# DB 퀴즈 형태 기말 대비

<details>
<summary>  1. 항상 일관되게 데이터를 분산된 환경에서 찾을 수 있도록 해주는 함수를 무엇이라 부르는가? </summary>
 <b> consistent hash, consistent hashing </b>
</details>

<details>
<summary> 2. Finger table이라는 라우팅 테이블을 가진 각 서버들이 logN의 시간 복잡도로 데이터를 조회하는 기법을 (a)라고 하며, (b) 라는 별칭으로 부른다. </summary>
<b> (a): Distributed Hash Table <Br> (b): Chord </b>
</details>

<details>
<summary> 장애 복구 차원에서, write, update 등의 행위를 하기에 앞서 해당 행위를 사전에 기록한 것을 무엇이라고 하는가?? </summary>
<b> Write Ahead Log </b>
</details>

<details>
<summary> 핑거 테이블이 커버하는 범위를 가늠하는 방향은?? </summary>
<b> 반시계!!!!!!!!!!!!!! </b>
</details>

<details>
<summary> CAP는 무엇의 약자인가 </summary>
<b> Consistency (일관성), Availability (가용성), Partitions (분리) </b>
</details>


<details>
<summary> CP는 어디서 선호 되고, AP는 어디서 선호되는가 </summary>
<b> Consistency (일관성): 은행과 같이, 데이터의 일관성이 깨지면 큰일 나는 서비스. 대신에 일관성이 깨질 수도 있는 문제 발생시 모든 접근을 막는다. <br> Availability (가용성): SNS같이 잠깐의 불일치를 감수하더라도 전체 정지가 없어야만 하는 서비스 </b>
</details>

<details>
<summary> 양 개체간의 직접적인 합의를 이끌기 힘들 때, transaction을 prepare-commit의 과정을 coordinator를 통해 관제하여 안전하게 수행하는 분산 기법을 무엇이라고 하는가? </summary>
<b> two-phase commit </b>
</details>

<details>
<summary> Proof of work </summary>
<b> </b>
</details>

<details>
<summary> 인터넷의 연결성은 ㅇㅇㅇ를 따른다 </summary>
<b> 멱함수: Power Law Distribution </b>
</details>

<details>
<summary> 암호화된 결과를 연산 이후에 복호화 하여도, 암호화 전의 숫자들을 연산한 것과 같은 결과를 만들 수 있는 암호화 방식은? </summary>
<b> homomorphic encryption - 동형 암호 </b>
</details>
