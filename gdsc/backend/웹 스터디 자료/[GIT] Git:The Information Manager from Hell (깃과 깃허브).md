안녕하십니까 GDSC Hongik 웹 기초 스터디 강사를 맡은 이진호입니다.

이번 수업 진행 속도가 너무 빨랐다는 피드백이 많아, 강의 내용 글로 작성합니다.

실제 수업에서 1주차 서버와 리소스의 복습 내용을 제외한 수업 내용을 정리하였습니다.

앞으로 더 나은 수업을 위해 노력하겠습니다. 감사합니다.

강의한 내용을 글로 옮겼기 때문에 글이 깁니다!

목차 1번 서문과 2, 3 번은 빠르게 넘어가거나 읽지 않으셔도 됩니다.

# 1\. 들어가면서..

(깁니다. 안 읽으셔도 좋습니다.)

오늘 수업 주제는 "Git : The Information Manager from Hell" + Github 입니다.

제가 프로그래밍을 막 시작할 때 쯤 필요에 의해 git을 배웠습니다.

구글링도 잘 할줄 몰랐고, 도움을 받을 만한 컴공과 친구도 단 한명 뿐이였습니다.

친구에게 git과 github의 공부법을 물어봤고,

친구가 시키는 대로 git의 공식 페이지에서 무료 제공되는 pro git이라는 책을 읽으며 굉장히 괴롭게 공부했던 기억이 납니다. (자세한 원리를 알고 싶으신 분은 꼭 읽어보세요.)

프로그래밍 입문 단계였던 저는 깃이 지옥같이 어려웠습니다. 원리나 사용법을 늦게까지도 잘 몰랐고, 제대로 사용하기까지 여러번 다시 배워야 했던 기억이 납니다.

저만 그런줄 알았는데, 주변의 개발을 잘 하는 친구들 조차 원리를 모르고 사용하는 친구가 많았습니다. add commit이 왜 두개로 나누어져 있는지, push는 왜 따로 있는건지 잘 모르는 채로 사용하는 친구들이 꽤 있었습니다. 리모트 리포지토리와 로컬 리포지토리의 차이를 모르는 친구도 가끔 있었습니다. 그리고 이런거 몰라도 잘 먹고 잘 산다고 말씀 주신 분들도 있었습니다. 이는 그 분들의 공부가 잘못된 것이 아닙니다. 단지 예전엔 git을 처음 배우는 사람의 눈높이에 맞는 자료가 별로 없었고, 옆에서 알려줄 사람이 없었기 때문이라고 생각합니다.

맞습니다. 사실 몰라도 깃을 사용하는데 크게 문제가 없을 수도 있습니다. 

저도 잘 모르는 채로 일을 시작했던것 같았습니다.이후 정말 애로사항이 끝도 없이 몰려왔습니다. 여러 팀원들과 함께 협업하면서 다양한 문제들을 만났고, 그 문제들을 해결하기 위해선 기초 지식을 제대로, 잘 알고 있어야 했었습니다.따로 많이 공부했고, 인내심있는 사수분을 만나 비로소 어느 정도 잘 사용하게 되었습니다.

저도 모든 원리를 알고 기술을 사용하진 않습니다.

코더와 디밸로퍼, 그리고 소프트웨어 엔지니어의 차이는 뭘까요?

구글 소프트웨어 엔지니어는 이렇게 말 했다라는 책에 따르면

코더는 말 그대로 기술의 사용법만을 알고 코딩을 하는 사람이고,

개발자는 설계를 고려할 줄 아는 사람이라고 합니다.

개발은 오늘 돌아가는게 가장 중요하지만, 내일 수정하기 쉬워야 합니다.

이는 더 나은 설계를 통해 이룩할 수 있습니다.

그리고 소프트웨어 엔지니어는 설계와 트레이드 오프를 고려하여 10년 20년짜리 프로그램을 짤 줄 아는 사람이라고 합니다. (트레이드 오프란 설계 과정에서 A, B의 선택지가 있을 때 A라는 선택지를 고를때 얻는 이점 대신 잃게 되는 점을 의미합니다.)

여러분은 어떤 개발자가 되고 싶으신가요?

저도 모든 원리를 알고 기술을 사용하진 않습니다.

다만 제가 자주 사용하는 부분은 꼭 원리를 이해하고 넘어가려 합니다.

깃은 조금 특이합니다.

배워야 하는 시기에 비해 꽤나 어렵고, 기본 사용법은 능숙해지면 어렵지 않기 때문입니다. 각종 GUI 툴들도 잘 되어 있구요.

여러분들도 대부분 입문 단계라고 들었습니다.

저희 커뮤니티 특성상 입문 단계지만 미리 Git을 배워야 하기 때문에 배우시는 분들이 많을겁니다.

그래서 여러분들이 최대한 이해하기 쉽게 설명하려 노력하겠습니다.

여러분은 제가 겪었던 고통을 받지 않았으면 좋겠다는 마음을 담아 2주차 수업을 준비해봤습니다.

이번 깃 수업 목표는 2주 동안 깃과 깃허브의 기본적인 원리와 사용법을 "제대로", "잘" 써먹을 수 있는 수준까지 익히는 것입니다! 이후 깃과 깃허브의 아주 다양한 기능들은 구글링을 통해 혼자 공부할 수 있을 것입니다.

# \# 2. Git:The Information Manager from Hell

깃이란 뭘까요?

[##_Image|kage@szQOl/btr5A4pCj65/SM0YdbdRvERZwHqcw6zKu1/img.png|CDM|1.3|{"originWidth":670,"originHeight":377,"style":"alignCenter"}_##]

프로그래밍을 접해보신 분이라면 오며가며 깃과 깃허브라는 단어를 많이 들어보셨을 겁니다.

혹은 이미 깃과 깃허브를 잘 사용하시는 분들도 계실겁니다.

사전적 정의는 위와 같습니다. 말이 어려운데

일단은 **파일의 변경 사항을 추적하고 협업 작업을 조율해주는 무언가..!**

정도만 알고 넘어가 보겠습니다.

(여기는 넘어가도 좋습니다.)

어떤 사람에게 깃이 무엇인지 물어보겠습니다.

> ??? : 깃은 지옥에서 왔다.  
> ??? : GIT 은 그냥 아무 알파벳 대충 3개 합친거고 의미 없다  
> ??? : 깃을 사용하면 기분이 좋고,  갑자기 천사들이 나타나며 빛이 방을 가득 채운다

누군가 위와 같이 깃에 대해 설명해줍니다.

설명이라기 보단 비꼬는 문장에 가깝습니다.

사실 더 심한 말들도 많았는데 제가 자른 것입니다.

누구일까요?

# **\# 3. 깃의 아버지 리누스**

[##_Image|kage@xmg1M/btr5BmcOBQK/jNGqjMwJEll5YoYr55ICy1/img.png|CDM|1.3|{"originWidth":670,"originHeight":366,"style":"alignCenter"}_##]

바로 깃의 아버지 리누스라는 분의 말입니다..

**바로 깃을 만드신 분입니다...**

그러니까 위 글은 자신이 만든 프로그램을 소개할때 쓴 표현입니다.

아무 알파벳 3개 합친거라니.. 좀 너무하죠?

왜 지옥에서 왔다고 하고, 저렇게 비꼴까요?

그냥 어려워서 입니다.

본인이 개발하면서 어려웠고, 사용하는 이들도 어려울 것 같아서라고 하네요.

재미있죠?

리누스는 많은 개발자들이 우러러보는 미친 실력의 개발자입니다.

이름이 낯이 익죠?

바로 리눅스의 개발자이기도 합니다.

만든 이유는 아래와 같다고 합니다.

[##_Image|kage@bzbtZ0/btr5E4Cejye/37bK6mtF8dZclm5KVdYIN1/img.png|CDM|1.3|{"originWidth":501,"originHeight":332,"style":"alignCenter"}_##]

"그냥.. 재미로"

정말 멋있죠?

Just For Fun이라는 멋진 말을 남겼습니다.

리누스는 평소에 프로젝트 관리를 위해 BitKeeper라는 서비스를 이용 중이였습니다.

항상 불편함을 느끼고 있었다고 하는데요?

BitKeeper에서 유료화를 선언한 것입니다.

[##_Image|kage@bEP9RO/btr5BV66qqu/vyAmawORKwfP4rH7TINn70/img.png|CDM|1.3|{"originWidth":616,"originHeight":348,"style":"alignCenter"}_##]

불만이 있으면 어떻게 해야하나요?

[##_Image|kage@pROZB/btr5rfTEdRG/FlXbeqOp1q8zrzkmr4P331/img.png|CDM|1.3|{"originWidth":630,"originHeight":357,"style":"alignCenter"}_##]

그냥 만들어 버렸습니다;

심지어 인기가 폭발합니다.

[##_Image|kage@dGp2Sf/btr5shqaDRt/4BnLOoOMj2pIkCBg8PJlek/img.png|CDM|1.3|{"originWidth":637,"originHeight":231,"style":"alignCenter"}_##]

깃의 공식 사이트에서 제공하는 깃 사용처입니다.

지구에서 제일가는 기업들만 모아 놓은 듯한 짤이네요

그래서 대체 왜 저런 멋진 기업들이 Git을 사용하는 걸까요?

다들 깃허브 깃허브 하는데 깃허브는 뭘까요?

이제 부터 알아봅시다.

# \# 4. 닥터스트레인지와 멀티버스

[##_Image|kage@bd7Q5j/btr5rcimwww/kzIflhrheu4zIJkf2fWYLK/img.png|CDM|1.3|{"originWidth":240,"originHeight":345,"style":"alignCenter","caption":"출처 : CGV 공식 사이트","filename":"닥스.png"}_##]

저는 깃을 닥터스트레인지에 비유하고 싶습니다.

깃은 정말 다양한 기능을 제공합니다.

[##_Image|kage@SzJdb/btr5DTnrkyD/QM4tdWmNSFWwzo9BOt0lv1/img.png|CDM|1.3|{"originWidth":1366,"originHeight":564,"style":"alignCenter","caption":"출처 : &amp;nbsp;marvel cinematic movie Loki","filename":"Loki_multiverse marvel cinematic universe wiki.png"}_##]

다들 멀티버스에 대해 들어보셨나요?

우주에 또 다른 분기가 생겨, 내가 살고 있는 현실과는 아주 다른 세상이 있다는 이론인데요. 어떤 세상에서의 나는 대통령일 수도 있고, 이미 죽었을 수도 있고, 아이언 맨일 수도 있습니다.

**깃은 코드의 멀티버스를 만들고 관리할 수 잇습니다.**

수 많은 코드의 분기를 만들어내고, 합치는 것이 가능합니다.

내 친구가 짠 코드가 너무 맘에 안 들어서,

친구가 코드를 짜기 전 상태에서 새로운 분기를 만들어 내 코드를 넣어볼 수 있고

내 코드가 더 낫다고 친구가 울면서 인정 또 인정한다면,

우리 프로그램에 다시 합칠 수도 있는겁니다.

위 그림이 나뭇가지 같지 않나요?

그래서 이 분기들을 Branch라고 부릅니다.

[##_Image|kage@uH4iX/btr5A5IW741/kGqBW6cKPlO4kjscwGJHK1/img.png|CDM|1.3|{"originWidth":785,"originHeight":507,"style":"alignCenter","width":629,"height":406,"caption":"만화 도막묵시록 카이지"}_##]

혹은 변화를 무를 수도 있습니다!

마치 타임머신 처럼 과거 특정 시점으로 돌아갈 수도 있고,

다양한 분기점과 시점을 오갈 수 있습니다.

코드를 잔뜩 고쳤는데 큰 오류가 난다거나 친구와 제 코드를 합쳤더니, 큰 오류가 발생했을 떄

변화 내용들을 추적해가며 문제 지점을 발견한 다음, 전부 무를 수 있습니다!

이러한 특성 때문에 Git을 버전 관리자라고 부르기도 합니다.

[##_Image|kage@bnUxKG/btr5re1yMZa/RiKrxQxDvFkuKLqrBHAKN0/img.png|CDM|1.3|{"originWidth":800,"originHeight":404,"style":"alignCenter","caption":"출처 : 마블 영화 어벤저스 인피니티 워","filename":"닥스 2.png"}_##]

어때요? 어벤저스 인피니티 워에 나온 닥터 스트레인지 같지 않나요?

이렇게 편리한 Git의 기본 명령어와 그 사용법도 한번 알아봅시다!

# \# 5. 깃의 기본 동작 방식

[##_Image|kage@bTR269/btr5AzRmdeZ/VHO83kM6byXHvluMwMyJ90/img.png|CDM|1.3|{"originWidth":521,"originHeight":302,"style":"alignCenter","width":438,"height":254}_##]

기본적으로 Git이 관리하는 파일엔 4가지 상태가 있습니다.

Git이 아예 추적하지 않는 상태, 추적하지만 변경이 없는 상태, 변경이 있는 상태 그리고 **Staged 상태가** 있습니다.

[##_Image|kage@EuF5L/btr5AZoHMIJ/LEETeCMd0NItVkUYyaeLP0/img.png|CDM|1.3|{"originWidth":533,"originHeight":300,"style":"alignCenter","width":442,"height":249}_##]

영어로 하면 이렇게 4가지 상태입니다.

[##_Image|kage@0Re70/btr5A4QNHFe/hbK5xPL9SGH9tYaJuuSMEk/img.png|CDM|1.3|{"originWidth":1089,"originHeight":462,"style":"alignCenter","filename":"track.png"}_##]

파일들은 조건에 따라 이 4가지 스테이트를 오갑니다.

(이 4가지 상태 변화 라이프 사이클에 대한 아주 자세한 설명은 이 글을 참고하세요 [https://dwaejinho.tistory.com/entry/Git-Git-file-status-lifecycle](https://dwaejinho.tistory.com/entry/Git-Git-file-status-lifecycle))

이렇게 화살표가 많으니 복잡하죠?

[##_Image|kage@bv4Aev/btr5BlLMTTR/PkDNfOFLCTdu8qFRujkrg0/img.png|CDM|1.3|{"originWidth":612,"originHeight":275,"style":"alignCenter"}_##]

일단 이 3가지 상태만 봅시다.

바로 위 그림에서 가장 왼쪽과 가운데가 더 위의 화살표 많은 그림과 같습니다. 

Working Directory는 "작업 공간"으로 내가 일하고 있는, 코드를 짜고 있는 바로 그 공간입니다.

Git은 기본적으로 코드의 변화를 추적할 뿐만아니라, 

**내 임의대로 일정 갯수의 변화들을 모아 저장할 수 있게 해줍니다.**

이게 아주아주 중요합니다.

[##_Image|kage@ctvQE0/btr5AApcdgG/bovgv6UoFP52txaKEmumYk/img.jpg|CDM|1.3|{"originWidth":1496,"originHeight":1496,"style":"alignCenter","width":380,"height":380,"filename":"교촌치킨.jpg"}_##]

제가 수업에서 늘 그랬듯 교촌 치킨의 예시를 들어봅시다.

어느날 사장님께서 제게 "교촌 허니콤보"라는 기능을 구현해오라고 하셨습니다.

그렇다면 저는 일단 치킨을 만들고, 소스를 개발해야 하는 **두 단계**의 과정을 거치게 됩니다.

이중 치킨 만들기를 더 자세히 풀어봅시다.

치킨을 만드는 과정은 닭을 손질하고, 염지를 한 다음, 튀김옷을 입히고, 튀겨냅니다.

소스를 개발하려면 다양한 소스를 연구하고, 전부 테스트 해보고, 실제 사용할 소스 한가지를 선정합니다.

그럼 제가 한 일들을 모두 적으면 이렇게 되겠습니다.

정확한 비유는 아니겠지만 일단은 이렇게 봐주세요

1\. 닭 손질

2\. 소스 연구

3\. 염지

4\. 튀김옷 입히기

5\. 소스 테스트 해보기

6\. 소스 선정

7\. 맛있게 튀기기 

8\. 소스 바르기

이런 8가지 과정을 거쳐 허니콤보를 완성했습니다!

소스 개발과 치킨 개발, 그리고 치킨에 소스 바르는 순서가 아주 뒤죽박죽 섞었습니다.

그런데 직접 만든 제가 보면 당연히 모든 과정이 이해가지만

사장님은 사실 외계인입니다! (두둥)

치킨의 치자도 모르는데 그냥 인기 많대서 만들어 보라고 한 것입니다.

과연 사장님이 아래와 같이 생각할 수 있을까요?

> **음!  
> **
> 
> **1, 3, 4, 7을 통해 치킨을 개발했고  
> ****2, 5, 6을 통해 소스를 선정한 다음  
> ****8번 과정을 통해 치킨에 소스를 발랐구만! 우하하!!**!
> 
>   

절대 그럴 수 없습니다.

다양한 변화들을 그저 쌓기만 한다면

당장 1주일 전에 자신이 짠 코드도 못 알아보는 개발 세상에서

다른 이들은 내가 뭘 했고, 뭘 의도했는지 알 수가 없습니다.

**이를 위해 staging area와 local repository가 구분되어 있습니다.**

# \# 6. Git add, commit

우리는 변화들을 엮을 수 있어야 합니다.

1, 3, 4, 7번은 치킨 개발이고

2, 5, 6은 소스 개발이라고 명시할 수 있어야 합니다.

제가 치킨을 열심히 만듭니다.

닭을 손질하고, 염지하고, 튀김옷을 입혀 튀겨냅니다.

**그리고 이름을 붙여줍니다.**

**이건 치킨 개발이오..**

**이 과정을 git commit이라고 합니다.**

**우리는 git commit 명령어를 통해 staging 영역에 쌓인 변화들을 논리적으로! 끊어! (엮어) 내어 이름을 지어줄 수 있습니다!**

**치킨 개발이라고!**

그럼 staging 영역은 뭘까요?

변화를 쌓아두는 어떤 공간이라고 생각하시면 편합니다.

실제로 사전에서도 "준비"와 같은 뜻을 찾아볼 수 있는데요?

**A, B, C, D의 다양한 변화를 내가 논리적으로 엮어 이름을 지어주기 위해**

**변화들을 쌓아놓는 공간이 바로 staging 영역이며**

**이런 staging영역에 변화들을 쌓을 때는 git add  명령어를 통해 쌓을 수 있습니다.**

[##_Image|kage@b6OeUb/btr5DTA2HYA/LerBq4XhIRr4DS22prs00K/img.png|CDM|1.3|{"originWidth":875,"originHeight":457,"style":"alignCenter","filename":"git add commit `.png"}_##]

결론적으로 우리가 만든 변화들을 모아둘 수 있는 공간을 Staging Area라고 부릅니다.

git add 명령어를 통해 이 영역으로 옮길 수 있고, 

적당히 변화들이 쌓여 이제 그들을 엮어 git commit 명령어로 커밋하는 순간!

비로소 우리가 이름을 불러주게 되고, 하나의 커밋이 됩니다.

닭을 손질하고, 염지하고 튀겨낸 변화들이 쌓여 있을 때

git commit -m "feat : 치킨 기능 구현" 과 같은 명령어로 이름을 붙여 줌으로써

위 그림에서 가장 오른 쪽의 Local Repository인 .git directory이란 곳에 "치킨 기능 구현" 이라는 이름으로 저장 가능합니다. 

Repository는 "저장소"라는 의미로 받아들이면 되고, Directory는 폴더의 다른 표현 쯤으로 생각하면 됩니다.

결국 Git이 관리하는 저장소가 있고, 커밋을 마친 코드는 이곳에 저장됩니다.

Staging Area는 잡동사니를 마구 쌓아 두는 중간 저장소 쯤으로 생각합시다.

이곳에 이름도 없는 여러 변화들을 쌓아 두고, 모아서 메인 저장소에 넘길 때는 이름을 붙여준다고 생각하시면 됩니다.

치킨의 예시 까지 종합하면 이렇습니다.

1\. 닭 손질, 염지, 튀김까지 Staging Area에 add 하고 -> "치킨 만들기"라는 이름으로 Local Repository에 commit 합니다.

2.  소스 연구, 소스 테스트, 소스 선정까지 Staging Area에 add 하고 -> "소스 개발하기" 라는 이름으로 Local Repository에 commit 합니다.

이렇게 쌓인 커밋은 이쁘게 기록됩니다.

[##_Image|kage@2PZ4y/btr5OyKL88i/GwkHsRnjZRlkGXIqhI8am1/img.png|CDM|1.3|{"originWidth":1102,"originHeight":577,"style":"alignCenter","width":811,"height":425}_##]

이렇게 이쁘게 정리되면 팀원들이 서로 뭘 했는지 한눈에 알 수 있죠?

저 줄들을 눌러 보면 친절하게 어떤 코드를 작성했는지도 모두 나오게 됩니다!

조금 감이 오시나요?

결국 어차저차 해서 Local Repository에 저장하는 겁니다.

왜 Local일까요?

컴퓨터의 Local 드라이브는 우리 컴퓨터에서만 사용 가능한 "저장소"입니다.

이와 같이 Local Repositoy는 단지 내 컴퓨터의 저장소입니다.

네.. 사실 이렇게 지지고 볶은게 전부

[##_Image|kage@b8bCeL/btr5QzIZQTN/PDY85TockthyxpkCJSjPz1/img.png|CDM|1.3|{"originWidth":916,"originHeight":472,"style":"alignCenter"}_##]

내 컴퓨터 안에서만 일어난 일이였던 것입니다...!

그런데 이상합니다.

깃은 분명 협업을 위한  것이라고 했습니다.

맞습니다 깃은 협업의 대장이나 마찬가지입니다...

그런데 내 컴퓨터에서만 일어나는 일이면 어떻게 공유하나요?

혹시 우리의 저번 수업이 기억 나시나요?

저희 학교의 정보를 얻기 위해, 데이터를 모아둔 컴퓨터를 학생회관 앞에 두고, 찾아와서 읽어보도록 하게 된다면..

학생들은 울고 말것입니다.

[##_Image|kage@vCUwp/btr5NLEeTCD/G54SkcSlPKiYDRcsm1d5O0/img.png|CDM|1.3|{"originWidth":774,"originHeight":516,"style":"alignCenter"}_##]

학교 정보를 공유하기 위해 데이터를 저장 해두고, 켜 놓는 컴퓨터가 있었습니다

바로 서버 개념이였습니다..!

맞습니다. 변화를 추적하고 저장하는 것은 좋은데,

그걸 저장해줄 서버가 있어야 비로소 여러 사람이 그 데이터들을 공유할 수 있는 것입니다.

[##_Image|kage@bswJoU/btr5NMbS0V8/Xcjg8n19ba1D3Jv2vOUQrK/img.png|CDM|1.3|{"originWidth":1190,"originHeight":498,"style":"alignCenter","width":784,"height":328}_##]

이를 리모트 리포지토리라고 부릅니다!!

공통의 외부 저장소가 있어야 비로소 팀원들은 서로 자료를 공유할 수 있는 것입니다.

리모트 리포지토리중 하나가 바로

[##_Image|kage@bcEvmC/btr5M8NjzsZ/kEKiYsLs4u0rdIgCq7pZd1/img.png|CDM|1.3|{"originWidth":1202,"originHeight":523,"style":"alignCenter","width":766,"height":333}_##]

깃허브 입니다.

깃허브 == 깃으로 알고 시작하는 입문자 분들이 많습니다. 저도 그랬구요.

깃허브는 이 Remote Repository를 제공해주는 서버중 하나이고, 서비스일 뿐입니다.

[##_Image|kage@ATQtp/btr5QiAMfvm/2dWz4NYxQU0Mk7VydYolG1/img.png|CDM|1.3|{"originWidth":1076,"originHeight":422,"style":"alignCenter"}_##]

결국 Git은 여러 remote 저장소 중 하나이고, 선택지는 아주 다양합니다..!

그럼 이 리모트 리포지토리와는 어떻게 정보를 교환할까요?

## \# 6. Git과 협업 Remote Repository로의 확장

[##_Image|kage@d3FR6n/btr5RgWNQgT/o3Z5A2xbhbH0XpjtRhd0Uk/img.png|CDM|1.3|{"originWidth":933,"originHeight":667,"style":"alignCenter"}_##]

직접 실습 영상 찍은 내용 공유합니다

로컬-리모트 리포지토리 연결 실습 및 간단 복습 영상 :  [https://www.youtube.com/watch?v=r5YnE7Ko32A&t=8s](https://www.youtube.com/watch?v=r5YnE7Ko32A&t=8s)

깃 데스크탑 실습 영상 : [https://www.youtube.com/watch?v=ocje6CElIqE&t=154s](https://www.youtube.com/watch?v=ocje6CElIqE&t=154s) 

##   
\## Reference

\- pro git

\- 마블 시네마틱
