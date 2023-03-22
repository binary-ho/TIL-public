# [Git] Git file status lifecycle

오늘 수업은 깃의 유래와 그 강력한 기능들, 그리고 기본 원리에 대해 다루었다.

수업 이후 수강 학우분 께서 깃이 관리하는 파일의 라이프 사이클에 대해 자세한 질문을 주셨다.

수업 중 제대로 짚고 넘어가지 못한 부분에 대해 설명하겠다.

## 1\. 추적하거나, 추적하지 않거나

[##_Image|kage@ciJysC/btr5dp2iEJc/6tkO0wKSUA24prsfnClKek/img.png|CDM|1.3|{"originWidth":1097,"originHeight":478,"style":"alignCenter","width":674,"height":294,"filename":"lifecycle.png"}_##]

위 그림은 깃이 관리하는 파일 상태의 라이프 사이클이다.

기본적으로 Git이 관리하는 파일의 상태는 두 가지 상태를 가진다.

1\. 추적 하거나

2\. 추적하지 않거나

(tracked, untrackted)

수업에서 언급했듯이 git은 파일의 변경 사항들을 기록해준다.

그런데 프로젝트 내에 모든 파일이 관리될 필요가 있을까?

저장소에 올리고 싶지 않은 비밀스런 파일이나

잠깐 테스트로 만들어 보고 지울 파일을 팀원들에게 보여줄 필요는 없을 것이다.

이에 Git은 명시적으로 지시할 때만 파일을 관리한다.

이 중 Git의 관리 하에 있는 파일들이 tracked 상태 파일이고,

Git이 관리하지 않는 파일이 untracked 파일이다.

[##_Image|kage@diaj7d/btr5dqGUh8r/aYVKGNYl60a2mLCk8POdW1/img.png|CDM|1.3|{"originWidth":1265,"originHeight":832,"style":"alignCenter","filename":"untracked1.png"}_##]

위의 사진은 수업때 쓰인 local repository의 모습이다.

새 txt 파일인 untracked.txt를 만든 다음 git status를 입력하니 사진 하단과 같이

```
Untracked files:
    untracked.txt
```

Untracked files로 untracked.txt 이 뜨게 되었다.

git은 갑자기 새로 만들어진 파일을 추적하지 않는다.

이제 위 파일을 tracked 상태로 만들어 보겠다.

[##_Image|kage@rE2Um/btr5guVQ4a1/pNviyA3PUms2afAJm7Gp1k/img.png|CDM|1.3|{"originWidth":887,"originHeight":283,"style":"alignCenter","filename":"tracked.png"}_##]

**add** 커맨드에 의해 untracked.txt 파일은 Staged 영역에 들어가게 되었고,

git의 관리 하에 놓여졌다.

변화가 일어날 경우 "추적 당할" 것이고,

이제 Staged 영역의 다른 파일들과 함께 한 논리적인 단위의 커밋을 묶일 수 있는 상태가 되었다.

## **2\. Modified**

아까 파일의 상태는 tracked와 untracked의 두 상태가 있다고 하였다.

tracked 파일은 이제 Git이 열심히 감시하여 기존 상태와 다른지 같은지를 체크한다.

당연히 추적 중일 때만 변했는지, 안 변했는지 판단이 가능하며

기존 상태에서 변경된 부분이 있는 상태를 Modified

기존 상태에서 변경된 부분이 없는 상태를 Unmodified 상태라고 부른다.

[##_Image|kage@bM2HSW/btr43PnzZW0/uiqo5saMHpnL16LHEndCP1/img.png|CDM|1.3|{"originWidth":1286,"originHeight":792,"style":"alignCenter","filename":"수정.png"}_##]

위와 같이 파일을 수정해 보니

Changes not dtaged for commit이라는 문구에 빨간 글씨로 modified로 파일 이름이 적혀 있다.

자세히 설명하겠다.

예를 들어 어떤 파일에 '1'이라는 숫자 하나가 적혀 있었다고 해보자.

그리고 add 명령어를 입력한다면, 1이 적힌 파일의 스냅샷이 staged 영역에 들어가게 될 것이다.

(스냅샷은 일종의 파일 상태를 찍은 사진으로, 파일의 어떤 한 순간을 찍어 냈다고 생각하면 편하다.)

이후, 파일의 내용물을 \`1+1=\`이라는 텍스트로 바꾸었다면,

기존 스냅샷과 "다른" 부분인 \`+1=\` 이라는 부분이 새로 생겨난 것인데,

이 부분을 파일의 수정된 부분이라고 보고, modified되었다고 부르는 것이다.

이미 add를 한 순간 부터, 그 당시의 코드의 스냅샷은 기록되고 변화가 추적되는 것이다.

**add는 단순히 변화 추적 선포가 아니다.**

"이 파일을 앞으로 추적하겠다"도 포함하고 있을 뿐이지 그런 의미로 받아들이기 보다는

"다음 커밋에 이 파일을 추가 시키겠다"고 받아들이는 편이 더 정확하다

그래서 이번 변화를 다음 커밋에 추가하고 싶지 않다면 추가하지 않아도 된다.

## **2. Unmodified**

질문자 분께선 Staged 영역에서 commit을 통해 Unmodified 상태가 되는 부분에 대해 질문 주셨다.

스테이징 영역에 쌓인 모든 변화를 commit 한다면 어떻게 될까?

변화는 기록되고, 이제 git이 생각하는 untracked.txt 파일의 "현재 상태"는 방금 커밋한 상태가 된다.

**즉, 변화를 추적하는 새로운 기준이 되는 것이다.**

변화를 추적한다는 것은 결국 기존의 상태에서 추가되거나 사라진 부분을 기록하겠다는 것인데,

"원래 파일"이라는 기준은 이제 방금 커밋한 \`1+1=\`이 되는 것이다.

**그래서 commit 이후의 파일 상태를 Unmodified라고 부르는 것이다.**

이 새로운 상태를 변하지 않은 상태라고 부르고 여기서 \`1+1=귀요미\` 등으로 내용이 바뀌면

다시 Modified라고 부르게 되는 것이다.

## **4\. 다시 Untracked**

추적중인 파일을 다시 추적하지 않으려면 어떻게 해야할까?

가장 간단한 방법은 삭제하는 것이다.

git rm 명령어를 통해 파일을 삭제해 보았다. (BTS 랩 몬스터 아님 ㅋ)

[##_Image|kage@9QJ4J/btr5cTP8rhP/GJFePJjXtmsmLYBXX7Gkk0/img.png|CDM|1.3|{"originWidth":1577,"originHeight":928,"style":"alignCenter","filename":"rm.png"}_##]

실제로 untracked.txt 파일이 삭제 되었다.

Changes를 보면 deleted라고 삭제됨이 추적됐는데, 이후의 변화는 추적되지 않는다. (사실 사라져서 이제 변할 것도 없다)

그럼 꼭 갱단처럼 세상에서 지워져야만 Git "관리 대상"에서 벗어날 수 있는걸까?

**git rm --cached 명령어를 사용하면 된다.**

[##_Image|kage@xk5YI/btr5d3kobwY/JimZsLEBF2fuVfU7cnyNRk/img.png|CDM|1.3|{"originWidth":1627,"originHeight":913,"style":"alignCenter","filename":"dontkillme.png"}_##]

너무 한번에 캡쳐해서 보기 힘들 수도 있겠다.

1\. dontkillme.txt 라는 빈 파일을 만든 다음 add를 통해 tracked 상태로 만들었다.

2\. 커밋 이후, \`**git rm --cached dontkillme.txt\`** 를 입력하였다.

3\. Chages에 deleted가 기록되었고, 이 변화를 커밋한다.

4\. 이후 dontkillme.txt에 \`돈킬미\`라는 문구를 추가하고 저장하였다.

5\. **정상적을 Untracked fIles에 표시되면서도 실제론 지워지지 않았다!**

앞으론 실수로 관리 대상에 추가해버린 중요한 파일이 있다면 이렇게 처리하자!

## **5\. Git ignore**

그런데 계속해서 untracked files에 뜨는게 거슬릴 수도 있다.

이미 이 프로젝트는 Git의 관리하에 있기 때문에, 변화가 추적되는 것은 당연하다.

이에 git에선 .gitignore 이라는 파일 통해 추적 무시 기능을 제공해준다.

[##_Image|kage@bpfR5L/btr45k17MGi/Ayg1lDUfKkq6JKiXDnzcz0/img.png|CDM|1.3|{"originWidth":1576,"originHeight":920,"style":"alignCenter","filename":"ignore.png"}_##]

그림과 같이

.gitignore 파일에 ignoreme.txt라는 문구를 넣은 다음

ignoreme.txt를 직접 만들어 주었다.

이후 git status 명령어를 입력했다

원래는 ignoreme.txt가 추적되지 않은 파일에 떠야하는데 .gitignore 덕분에 뜨지 않는다.

프로젝트에서 제외해야 할 파일이 있다면 이렇게 처리해주면 된다.

앞서 배운 git rm --cached와 함께 이용하면 더 좋다.

ex )

추적해선 안 되는 파일을 이미 추적한 상황에선

git rm --cached를 통해 추적 대상에서 제거하면서

동시에 gitignore로 아예 무시하면 된다.

이상 깃이 관리하는 파일들의 status 라이프 사이클에 대해 자세히 설명해 보았다.

질문 주신 학우분께 감사합니다.

**Reference**

\- pro git
