Errors ans Mistakes
====


1. id 찾을 때  container을 자동 완성 때문에 constraint로 적을 때가 의외로 많다, 조심
2. @Override에 에러가 뜨면 보통 이름을 잘못 쓴 것.
3. 
![override error.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/0c9c918f-0b3d-477e-bf93-0ce4f2eb1de0/override_error.png)


# 3. implements 밑줄

![implementation error2.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/e2106521-3d04-439f-9db2-2a313b951506/implementation_error2.png)

그림은 안 그런데 [com.android.support](http://com.android.support) 붙은 애들 죄다 빨간줄 천지였다.

뭘 해도 해결이 안 됐었는데,

![implementation error1.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/1d7398cd-dcd7-4cc3-a94b-7fc7914fc18c/implementation_error1.png)

compile 버젼을 낮춰주니까 됐다. 최대 27버젼까지만 지원해주는 애들이였고, 그 이후 버젼엔,
자세한 쓰임을 찾아내서 찝어주어야 되는 것 같다.    
앞으로는 컴파일 버전을 신경 쓰며 프로그래밍 해야 할 것 같다.
