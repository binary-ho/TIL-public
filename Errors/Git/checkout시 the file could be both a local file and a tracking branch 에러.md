# checkout시 the file could be both a local file and a tracking branch 에러 

binary-ho로 명명한 branch로 checkout 하기 위해 checkout 명령어를 입력했는데, 아래와 같은 오류가 발생했습니다. 
```sh
fatal: 'binary-ho' could be both a local file and a tracking branch 
```
<br>

이는 branch와 이름이 같은 tracking 중인 directory가 있을 때 발생하는 오류입니다. 이럴 때는 그냥 명령어 뒤에 `--`를 붙여주면 됩니다. <br> 예를 들어, `git checkout binary-ho --`와 같이 입력해 주면 됩니다. <br> <br>

`--`의 앞은 branch, 뒤는 directory를 의미합니다. 지금은 branch에 접근하기 위해 `--` 앞에 명령어를 적어둔 것이고, 만약에 directory와 관련된 명령이였다면, `git checkout -- binary-ho`와 같이 입력해 주면 됩니다. 

![branchfileerror](https://user-images.githubusercontent.com/71186266/192127458-c1782183-1273-4dc6-8ad1-0a13c2f37e88.png)
