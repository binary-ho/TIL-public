# AVL 트리 실전 예제
AVL 트리 실전적인 풀이에서 신경 써야 할 부분은 딱 개이다. <br>
1. RL, LR 등의 판단은 처음 BF가 깨진 곳에서 판단.
2. **BF가 깨진 곳이 부모-자식간에 이어서 여러 곳에서 발생했다면, 아래쪽을 선택해서 재분배한다**
3. LR, RL 회전시 그냥 세 노드에 대해 **중간 값 노드를 루트로 해서, 그 노드를 기준으로 다시 서브트리를 만든다.**

## 예제 1
{MAR, MAY, NOV, AUG, APR, JAN, DEC, JUL, FEB, JUN, OCT, SEP} <br>

기본적으로 책에서 제공된 순서이다. 여러번 연습했다.
![avl1](https://user-images.githubusercontent.com/71186266/206129643-ca66c1e0-50c5-443c-929d-ced7d696c8d9.png)



1. 첫 LR 회전이다. **BF가 깨진 루트를 기준으로** LR로 판단한 것을 확인할 수 있다.
2. MAY, AUG, MAR에 대해 중간값인 MAR이 루트가 되어 새로 트리가 짜인 것을 확인할 수 있다.
3. 왜 MAY 부터 AUG, MAR로 골랐는가? **깨진 곳이 기준이니까**



#### 여기도 중요하다. BF 깨진 곳이 두 곳!
![avl2](https://user-images.githubusercontent.com/71186266/206129645-9c719999-f566-4bd7-9c94-e55f822de919.png)


1. **위에서 언급한 것 처럼 MAR, AUG 둘 다 깨졌지만, AUG를 기준으로 회전한다.**
2. **둘 다 깨졌으면 자식쪽!!!** 그래서 **RL회전이라고 부른다!!**
3. AUG, JAN, DEC를 기준으로 회전하는데, 중간값인 DEC를 루트로 새로 서브트리들을 작성한다

![avl3](https://user-images.githubusercontent.com/71186266/206129648-9db227a8-c645-4abb-8f02-f94b46bb72ea.png)

완성된 모습..

## 예제 2
{'NOV', 'APR', 'OCT', 'MAY', 'DEC', 'AUG', 'SEP', 'JAN', 'JUL', 'JUN', 'MAR', 'FEB'}의 순서로 입력이 들어온 상황. <br>

![KakaoTalk_20221207_172605855](https://user-images.githubusercontent.com/71186266/206127258-74df178f-0901-4c4e-87e6-7b09e65a4db5.jpg)
![RET3](https://user-images.githubusercontent.com/71186266/206127250-103e32e1-b55d-4036-9b40-91298f5261d8.png)

위의 사진은 직접 그려본 것이고, 아래 사진은 visualizer를 사용한 결과이다. 같은 key값의 집합에 대해, 같은 결과를 만든 것을 확인할 수 있다.

### 결론: 
1. 같은 정책 하의 같은 key 구성이여도 입력 순서가 다르면, 트리가 다를 수 있다.
2. 동일 key값이 존재한다면 동일 key값 처리 정책에 따라 트리가 달라질 수 있다.

## Reference
- Fundamentals of Data Structures in C++ \<HOROWITZ, SAHNI, MEHTA 저>
- [AVL Tree Visualizer](https://www.cs.usfca.edu/~galles/visualization/AVLtree.html)
