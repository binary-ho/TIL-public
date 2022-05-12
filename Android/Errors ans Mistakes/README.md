Errors ans Mistakes
====


1. id 찾을 때  container을 자동 완성 때문에 constraint로 적을 때가 의외로 많다, 조심
2. @Override에 에러가 뜨면 보통 이름을 잘못 쓴 것.

![image](https://user-images.githubusercontent.com/71186266/167997302-b7136dd5-7edb-498d-b425-339479e4eef8.png)


# 3. implements 밑줄

![image](https://user-images.githubusercontent.com/71186266/167997346-9b6fbb16-2d7e-4e74-9dc9-a22aa4f268fb.png)

그림은 안 그런데 [com.android.support](http://com.android.support) 붙은 애들 죄다 빨간줄 천지였다.

뭘 해도 해결이 안 됐었는데,

![image](https://user-images.githubusercontent.com/71186266/167997369-f0d73e3d-81c6-4bc4-bf62-eb281132ab59.png)

compile 버젼을 낮춰주니까 됐다. 최대 27버젼까지만 지원해주는 애들이였고, 그 이후 버젼엔,
자세한 쓰임을 찾아내서 찝어주어야 되는 것 같다.    
앞으로는 컴파일 버전을 신경 쓰며 프로그래밍 해야 할 것 같다.
