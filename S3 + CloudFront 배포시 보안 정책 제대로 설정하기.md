# S3 + CloudFront 배포시 보안 정책 제대로 설정하기

**\[이 글에서 결국 하고 싶은 말\]**

**1\. S3 + CloudFront를 통해 클라이언트를 배포할 때는 사용할 때는**

**S3 웹 호스팅을 기능을 비활성화 한 다음에,**

**버킷 엔드포인트과 CloudFront를 연결한 다음 OAC 설정하고,**

**S3 정책을 작성하여 CloudFront에서만 접근하도록 설정하세요.**

**2\. OAI 대신 새로 도입된 OAC에 대한 간단한 설명과**

**S3 버킷의 파일을 안전하게 보호하기 위한 Access 설정, S3 Bucket** **정책을 작성하는 방법을 알려드립니다.**

**3\. 소소하게, S3로 정적 프로젝트 배포시 CloudFront를 사용하는 장점과** 

****S3 버킷의 파일들을 CloudFront를 통해 배포하는 방법도 알려드립니다.****

안녕하세요? 이진호 TV의 이진호입니다.

오늘은 React Project를 S3와 CloudFront를 통해 배포할 때의 보안 설정에 대해 알아보겠습니다!

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FxBRpE%2FbtsilIUPSZA%2Ft3eHcE9UOn4cskHWYumhW0%2Fimg.jpg)


저의 출석 프로젝트 imhere! 은 아래와 같은 구조를 가지고 있습니다!

[https://imhere.im](https://imhere.im "홍익대학교 웹 스터디 출석 프로젝트 imhere!")

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FdRaduk%2Fbtsij9ZM1Fy%2Ft4CJvkOGRE36t2AyY1dIUK%2Fimg.png)
클라이언트 부분은 js로 작성한 react 프로젝트로, S3에 정적 파일들을 저장 중입니다.

그리고 CloudFront를 통해 브라우저에서 접근 가능합니다.

작년엔 저도 S3에서 데이터를 바로 내려주도록 설정 했었는데요?

**S3 버킷의 '속성' 탭에 들어가면 최하단에서 정적 웹 사이트 호스팅 설정이 가능합니다!**

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fsq8Qw%2FbtsinYCZN7o%2FLkKdaokKXNjtJHA8HIvUk1%2Fimg.png)


S3 버킷을 직접 호스팅할 수 있는 것이죠!

간단하게 정적 웹 사이트를 내려줄 때 편리하지만, 몇 가지 단점이 존재합니다.

1\. 버킷을 퍼블릭으로 설정해야 합니다.

2\. 별다른 처리가 없다면 http 프로토콜을 사용해야 합니다.

3\. 위 사진 하단처럼 S3 웹 호스팅 엔드포인트를 그대로 사용해야 합니다.  
  

즉, 내가 원하지 않게 소중한 정적 파일들이 그대로 새어나갈 수 있답니다!!

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2F9spFn%2FbtsijndxrY7%2F9h2xTUuQ1bVKCbqbhUaG8K%2Fimg.jpg)


???: 그건 그냥 CloudFront랑 같이 사용하면 다 해결되는거 아닌가요~~??

맞습니다. 그러나 아무 생각 없이 S3 웹 호스팅 기능과 CloudFront를 함께 사용시

그대로 정적 파일들이 노출될 수도 있습니다!

S3 웹 호스팅 기능을 사용하며, CloudFront 배포를 시도하면

버킷과 연결 시도시 알아서 S3 버킷 엔드포인트가 아닌,

S3 웹 호스팅 엔드포인트를 과 연결하는 것을 권합니다.

![image]([https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2F9spFn%2FbtsijndxrY7%2F9h2xTUuQ1bVKCbqbhUaG8K%2Fimg.jpg)

이 경우 Origin Access Control(OAC) 나, Origin Access Identity (OAI) 설정이 어려울 수도 있습니다.

이 글에선  S3와 CloudFront 연동시 OAC와 OAI 설정에 관해 다룰 것입니다.

방법만 보면 별거 없지만, 이 글을 쓴 이유는

아래 내용들을 직접 찾는 과정이 어려웠기 때문입니다.

다른 사람은 헤메지 않도록..

1\. S3 웹 호스팅 엔드포인트와 CloudFront 를 연결해 사용시 두가지 설정을 아예 적용할 수 없다는 점

2\. 대부분의 문서들이 레거시인 OAI 설정만 다루는데, OAC를 설정하는 법

이제 위 두가지 내용과 CloudFront로 S3 배포 연결을 하는 방법에 대해 알아봅시다~

## 1\. Hello CloudFront!

앞서 언급한 S3 정적 웹 호스팅을 직접 사용하는데엔 몇 가지 단점이 존재했습니다.

내가 Route 53등을 이용해 지정한 도메인에 접근하면 ex) imhere.im

S3에서 호스팅한 url에 연결하도록 해줄 수 있는데요? 

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FTG60J%2FbtsijPN9Qlj%2FIeiy5JzHQeQSoU38ntuk3k%2Fimg.png)

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Ft7iN3%2FbtsigD1LccT%2FcrfbXhP0JCSMO0FD5Kst9K%2Fimg.png)

자연스럽게 public인 버킷 호스팅 엔드포인트를 url을 어느 정도 숨길 수 있고,

유저가 데이터를 받을 때 캐싱을 지원하는 것 뿐만 아니라,

위와 같이 설정하여 https 연결을 위한 리다이렉션도 돕고, 요청 HTTP Method 또한 제한할 수 있습니다.


![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fz5lx9%2FbtsimEdIxth%2FtXBNg2InhrLUOmKhxiYjE1%2Fimg.png)


그리고 간단한 설정만으로 우리가 구매한 도메인을 대체 도메인으로 사용하고,

SSL 인증서를 등록 할 수 있습니다!

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FdeRpBd%2Fbtsij9ZNJi1%2Fhb1r2OJM0cNOINS4YvTFbK%2Fimg.png)


S3 정적 웹 호스팅 기능을 활성화 한 다음

CloudFront와 내 S3 버킷을 연동하려 하면, CloudFront가 알아서 호스팅 중인 엔드 포인트와 연결할 것을 추천합니다.

**하지만 정적 웹 호스팅을 비활성화 한 다음에, 버킷 엔드포인트과 연결하는 것이 좋습니다!**

호스팅 엔드포인트와 연결시 CloudFront 화면이 이렇게 되는데요?

이렇게 설정하는 경우, 몇 가지 문제점이 있습니다.

## 2\. S3 정적 웹 호스팅 엔드포인트를 CloudFront Origin으로 설정시 발생하는 문제점

아래 두 사진을 비교해봅시다.

아래 두 사진은 CloudFront에서 배포를 생성하는 과정의 가장 처음인 '원본'탭입니다.

왼쪽은 웹 호스팅 엔드포인트를 원본 도메인으로 설정한 화면이고, 

오른쪽은 버킷 엔드포인트를 원본 도메인으로 설정한 화면입니다.

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbMTHdT%2Fbtsij6IQkUF%2F7PtWX4BN3Oncaz6EbkJcIK%2Fimg.png)

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FVqUbZ%2FbtsinYQBa8b%2F3kmr47RGdToz8We9y5rw11%2Fimg.png)


웹 호스팅 엔드포인트로 설정한 경우 프로토콜을 설정하는 부분이 나타납니다.

그리고 **버킷 엔드포인트로 설정하는 경우 원본 엑세스를 설정하는 부분이 나타납니다.**

웹 호스팅 엔드포인트를 Origin Domain으로 설정하는 경우 원본 엑세스 설정이 어려워집니다.

생성 이후 편집을 시도해도 찾을 수 없습니다. 

물론 제가 못 찾은 것일 수도 있지만, 한참을 뒤져 봤음에도 찾지 못 했습니다.

이 경우 원본 엑세스에 대한 설정이 불가능하기 때문에 아래와 같은 일이 발생합니다.

1\. 엔드포인트에 브라우저나 curl로 바로 접속 가능하다.

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbDqISH%2Fbtsiop8qEXv%2FIcztKd3vi7Jpjwx9KfaVkK%2Fimg.png)

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FcmnGSl%2FbtsidVVZTfr%2FpSENCkVZaRctKSJ2AvfMmk%2Fimg.png)

**2\. URL을 통해 경로만 입력하면 정적 파일의 내용들을 바로 받아볼 수 있다.**

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FcDOvRd%2FbtsijXel1Om%2FOovmQwJEEWat5VZM4VmJgk%2Fimg.png)

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2F78DVm%2Fbtsil0uCmSB%2FaXZLxxcDQmx9shssAPOwXK%2Fimg.png)


**버킷 자체가 Public에 노출되었고, CloudFront와 연결할 때,**

**우리 CloudFront에서만 접근 가능하도록 설정하는 것이 불가능하기 때문에**

**파일들이 이렇게 전부 노출됩니다.**

버킷 자체가 완전히 노출된 상황인 것입니다.

직접 설정하며 나름 잘 알아보며 했지만, S3 웹 호스팅 이후 CloudFront 연동을 권하는 글이 많았기에 그대로 설정했던 것입니다. 이런 상황에 주의해야 합니다.

## 3\. 버킷 접근 제한하기!

이 문제들은 버킷의 접근들을 제한하면서 설정 가능합니다.

전부 설정한 이후엔 아래 처럼 직접 접근 시도시 AccessDenied를 반환하면서도,

CloudFront를 통한 접근은 허용할 수 있습니다.

![image]([https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2F78DVm%2Fbtsil0uCmSB%2FaXZLxxcDQmx9shssAPOwXK%2Fimg.png)

위의 상황과 똑같은 썸네일 url에 대해 AccessDenied 페이지가 뜹니다.

다른 모든 url에 대해서도 마찬가지입니다.

아래 설정들을 수행합니다.

1\. S3 웹 호스팅 비활성화

2\. 버킷 엔드포인트를 CloudFront Origin Domain 으로 설정

3\. 원본 엑세스 제어 (Origin Access Control - OAC) 설정 혹은 Origin Access Identities (OAI) 설정

4\. 각 설정에 맞게 Cloud Front에서 Bucket에 접근할 수 있도록 정책 작성

일단 S3 웹 호스팅 비활성화는 S3 속성 탭 최하단에서 쉽게 할 수 있습니다.

그리고 자연스럽게 엔드포인트가 비활성화 됩니다.

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FrfD6C%2FbtsijPtRwlR%2FkKsephp2TIx7FdcAtTGIR0%2Fimg.png)

그리고 CloudFront의 배포의 원본 탭에서 원본을 선택하고 편집을 눌러

엔드포인트를 S3 버킷의 엔드포인트로 바꿉니다.

그러면 아래와 같은 모습으로 바뀌게 됩니다.


![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FVqUbZ%2FbtsinYQBa8b%2F3kmr47RGdToz8We9y5rw11%2Fimg.png)

원본 엑세스를 설정 가능하게 되었습니다.

공개, 원본 엑세스 제어 (Origin Access Control), Legacy Access Identities가 보입니다.

아래 두개를 눌러 보안 설정이 가능합니다.

구글링을 해보면 대부분 Origin Access Identities 인 OAI에 대한 글 밖엔 없는데,

Amazone Document에 의하면 OAI는 레거시라고 합니다.

## 4\. OAC, OAI 설정 (원본을 보호하는 법)

OAC에 대한 글을 거의 찾아볼 수 없는데, OAC가 도입된 이유는 아래와 같습니다. 

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FdgEthd%2Fbtsij6hL2tr%2FkV07a5ei2zZD8wKrgztKO1%2Fimg.png)

출처 : [\[Amazon CloudFront, 오리진 액세스 제어(OAC) 도입\]](https://aws.amazon.com/blogs/networking-and-content-delivery/amazon-cloudfront-introduces-origin-access-control-oac/ "[Amazon CloudFront, 오리진 액세스 제어(OAC) 도입]")

두 가지 설정을 위해선 미리 보안 제어를 만들거나 OAI를 만들어야 합니다.

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FGwOTe%2FbtsihcKdsuy%2FYWTAFAFULKiULl44J3X7mK%2Fimg.png)

두 탭을 통해 생성 가능합니다.

각 탭에서 생성을 누른 다음, 제어설정 (OAC)를 만드는 경우 서명을 요구하도록 설정합니다.

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FL5wFV%2FbtsiopHoLNN%2FvPyi5MOrlzILo0hZ2ilO4K%2Fimg.png)

어차피 CloudFront는 들어오는 요청에 대해 Authorization 헤더가 있는 경우에도 매번 서명합니다.

Authorization 헤더를 삭제하고 CloudFront의 자격 증명으로 요청에 다시 서명한 다음 S3에 보냅니다.

어차피 매번 서명하기 때문에, 서명을 요청하도록 허용하면 좋겠지요.

또한 도큐먼트에선 " CloudFront에서 요청에 서명하면 클라이언트와 CloudFront 간에 전송되는 데이터가 줄어들어 애플리케이션 성능이 향상됩니다." 라고 적혀 있습니다.

OAI의 경우 단순히 이름만 지어주면 ID가 발급됩니다.

이후, 아까 보았던 CloudFront의 배포 탭에서 배포의 생성시, 혹은 이미 생성된 배포의 '원본' 탭에서

OAC나 OAI를 적용해줍니다.

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FVqUbZ%2FbtsinYQBa8b%2F3kmr47RGdToz8We9y5rw11%2Fimg.png)

Origin Access 부분에서

원본 엑세스 제어 설정을 누른 다음 만든 OAC를 설정해주거나,

Legacy access Identities를 눌러 OAI를 설정하세요.

이제 CloudFront에 원본 Access 설정을 하게 해준 것입니다.

**이제 원본은 보호 받습니다!**

## **5\. 원본 보호 방식에 맞는 S3 정책 작성하기**

S3 정책은 버킷의 권한 탭에서 설정 가능합니다.


![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fd79UeV%2FbtsikSKlmx0%2FSUvsfNMt1nELB63gFWWzIK%2Fimg.png)

두 가지 방식 중 권장되는 최신 방식인 OAC 먼저 알려드리겠습니다.

```
{
    "Version": "그대로 두세요",
    "Id": "그대로 두세요",
    "Statement": [
        {
            "Sid": "그대로 두세요",
            "Effect": "Allow",
            "Principal": {
                "Service": "cloudfront.amazonaws.com"
            },
            "Action": "s3:GetObject",
            "Resource": "arn:aws:s3:::그대로 두세요/*",
            "Condition": {
                "StringEquals": {
                    "AWS:SourceArn": "자신의 CLoudFront ARN을 붙여넣으세요"
                }
            }
        }
    ]
}
```

대부분의 부분들을 그대로 둡니다.

Principal의 내용을 위에 적힌 대로 바꿔주시고,

Condition을 추가합니다.

내부에 StringEquals와 자신의 ARN을 붙여 넣습니다.

그럼 S3는 요청이 온 Source의 String과 저장된 String을 비교해, 같은 경우에만 요청을 승인합니다!!

이 부분을 추가함으로써 CloudFront 외의 접근을 막을 수 있게 됩니다!

CloudFront 배포에 들어가면 '일반' 탭의 ARN에서 확인 가능합니다.

Action의 경우 현재는 Get 요청만 날리므로 Get을 설정했지만,

업로드가 필요하다면 \`s3:PutObject"를 추가해줘야 합니다.

이렇게 해주면 OAC 설정이 끝납니다.

**레거시인 OAI의 경우 아래와 같이 설정합니다.**

```
{
    "Version": "그대로 두세요",
    "Id": "그대로 두세요",
    "Statement": [
        {
            "Sid": "그대로 두세요",
            "Effect": "Allow",
            "Principal": {
                "AWS": "arn:aws:iam::cloudfront:user/CloudFront Origin Access Identity [배포 ID 넣기]"
            },
            "Action": "s3:GetObject",
            "Resource": "arn:aws:s3:::그대로 두세요/*"
        }
    ]
}
```

위에서 Principal 부분이 핵심이 됩니다.

\[배포 ID 넣기\] 부분 외엔 그대로 입력 해주셔야 합니다. 그리고 저 부분에 CloudFront 배포 탭의 ID를 넣어주면 끝입니다!

간단하죠?

이후 접근 엔드포인트 접근 시도시 AccessDenied를 던집니다.

![image](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fc23jIJ%2Fbtsilh4uMah%2FQfaG7K7B1dmz5tULVWXeOk%2Fimg.png)

이런 방식으로 안전하게 S3 데이터를 보호할 수 있습니다.

Reference

\- 읽어보세요 : [\[Amazon CloudFront, 오리진 액세스 제어(OAC) 도입\] (Amazone 공식 도큐먼트)](https://aws.amazon.com/blogs/networking-and-content-delivery/amazon-cloudfront-introduces-origin-access-control-oac/)

 [Amazon CloudFront introduces Origin Access Control (OAC) | Amazon Web Services

Amazon CloudFront is a global content delivery network that securely delivers applications, websites, videos, and APIs to viewers across the globe in milliseconds. Using CloudFront, customers can access different types of origin services to suit their use

aws.amazon.com](https://aws.amazon.com/blogs/networking-and-content-delivery/amazon-cloudfront-introduces-origin-access-control-oac/)

\- [\[우아한테크세미나\] 사례별로 알아보는 안전한 S3 보안 가이드](https://www.youtube.com/watch?v=vgYfAndrpPU)

\-
