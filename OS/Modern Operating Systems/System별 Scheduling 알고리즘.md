# System별 Scheduling 알고리즘
## Scheduling in Batch Systems
### 목표: 
1. **Throughput:** 단위 시간 내 완료된 job 갯수 최대화
2. **Turnaround time:** job이 system에 제출된 시간부터 완료된 시간까지의 차이를 최소화.
3. **결론: 빨리! 많이! 처리해!**

### 알고리듬:
1. **First-come First-served:** queue 같은 흐름
2. **Shortets Job First:** 짧은 애부터 - 동시 도착만 최적 보장
3. **Shortest Remaining Time Next:** 남은 시간 적은 애 부터. (preemptive)
4. **Three level scheduling:** CPU 스케줄러 사용. CPU가 다음 process 결정

## Scheduling in Interactive Systems
### 목표: 빠른 반응
알고리즘
1. **Round Robin Scheduling:** 퀀텀! 짧으면 switch 많아서 효율 문제, 길면 response가 낮아
2. **Priority Scheduling:** tick 마다 우선순위 낮추고 더 높은거 발견되면 그걸 쓴다. 동적 부여에는 양보가 있음. <br> **한 우선순위 안에서는 round robin! 우선순위 간에는 priority!**
3. **Multiple Queues!**
- CTSS: 1, 2, 4 퀀텀스... switch 횟수 잘 세라! 처음에도 세야 한다! IO 요청 많은 프로세스는 높은 우선순위를 유지하므로 response time에 유리!
4. **Shortest Process Next:** a와 1-a로 추정치를 계속 만드는 **Aging 알고리즘** a*추정치 + (1 - a)\*실측치가 다음 연산의 추정치가 된다. a가 클 수록 이전 결과의 영향이 높아
5. **Guaranteed Scheduling:** 수행시간을 보장해준다. 실사용량/할당량 ratio 계산해서 낮을 수록 자기 궈리를 못 찾았으니, 보상해준다.
6. 복권: 서로 교환 가능해서 몰아준다
7. Fair-Share 스케쥴링

## Scheduling in Real-time Systems
### 목표: 데드라인을 지키다! 느린 답이 틀린 답보다 나빠

하드 타임, 소프트 타임 <br>

m개의 주기적 이벤트가 주어진 경우 모든 process의 Ci/Pi 값이 1보다 작거나 같아야 정상적으로 수행이 가능하다!!



## Reference
- Modern Operating Systems \<ANDRE S,TANENBAUM 저>
