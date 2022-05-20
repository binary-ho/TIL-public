Ruby 기본 문법 정리
=== 
루비의 기본 문법을 공부하고 정리하였습니다. 

# 1. Data type & Variable
루비의 모든 변수에는 타입이 따로 주어지지 않습니다. **그러나 루비의 모든 값에는 타입이 존재합니다.** 마치 Java의 `var` C++의 `auto`를 쓴 것처럼, **그냥 타입 명시 없이 저장을 해주면 되겠습니다.** 예시로 string을 저장하는 모습을 보이겠습니다. <br/>

```ruby
s = "Hello World!"
```
그냥 위와 같이 해주면 됩니다. 자료형의 확인은 자료형.class로 확인해볼 수 있습니다.
```ruby
s.class
```
결과로는 `String`이 나오게 됩니다. <br/>
![echo](https://user-images.githubusercontent.com/71186266/169415830-e01056cb-64de-4323-ae1f-2d6d43adb057.PNG)

(**<U>모든 문장은 값을 반환합니다. 단순 echo가 아닙니다. 주의하세요.</U>** Ruby는 꼭 필요한 경우에만 return을 씁니다.) <br/>
Ruby는 everything is an object입니다. 즉, 모든 변수에서 메소드를 호출 할 수 있습니다.

<br/>

# 1.1 Data types

루비의 기본 자료형에는 정수, 실수, 큰 정수, array, 해시, range가 존재합니다. 


1. **number**: 그냥 숫자를 쓰면 알아서 정수인지, 실수인지, 큰 정수인지 알려준다.
**제곱 연산이 존재하는데 `**`를 이용해서 제곱 연산을 할 수 있다.**
2. **String**: 따옴표와 쌍따옴표를 사용합니다. **덧셈 연산이 가능합니다.**
```ruby
s1 = 'Hello Ruby'
s2 = "Hello Ruby"

// 문자열의 덧셈
s3 = 'Hello '
s4 = 'Ruby'
s3 + s4
// 결과 => Hello Ruby 
```
<br/>

3. **nil: ruby에서는 비어있는 상태를 `nil`라고 부릅니다.**
4. **array: 대괄호 []를 통해 만들어줄 수 있고**, 다양한 접근법이 존재합니다.
**곱하기 연산이 가능합니다.**
```ruby
array = ['a', 'b', 'c', 'd', 'e']
```
위와 같이 만들어 주고, 접근 할 때는 아래와 같은 방법들이 있다.
![array](https://user-images.githubusercontent.com/71186266/169416832-5585962f-2f7e-4fc4-b825-87fce553dd21.PNG)

우리가 아는 평범한 array이다. 자료형은 알아서 인식해주고, 섞어 넣을 수 있다. 인덱스를 통해 접근 가능하며 `array[1..3]`과 같은 접근도 가능하다. index 1~3을 array로 반환한다. 또한 `-2`와 같이 음수로 Tail에서 부터의 접근이 가능하다. 그리고 범위를 벗어나면 nii를 반환한다. <br/>

번외로 넣은 아래 `(0..10).to_a`는 to array라는 의미로 `range`로 array를 만들어준 모습니다. <br/>

### array 곱하기 연산이 가능합니다.
곱해준 숫자 만큼 모든 원소를 복사해서 뒤에 붙여줍니다.
![multiplyarray](https://user-images.githubusercontent.com/71186266/169442086-b852f7b5-2fac-4654-b8cb-8fa0b77194bf.PNG)
위와 같이 사용하면 됩니다.

5. **Hash: key-value mapping 자료구조. 중괄호로 선언합니다. key-value 매칭하는 방법이 2지 있습니다.**
```ruby
// 심볼로 저장하기
hash = {name: 'Homer Simpson', age: 39, 'weight': 117.9}
// 위와 같이 저장할 경우 name, age, weight 모두 심볼로 저장됩니다.


// 일반 String으로 저장하기
hash2 = {'name'=>'Homer Simpson', 'age'=>39, 'weight'=>117.9}
hash2['son'] = 'bart' 
// 이 경우에는 String으로 저장된다.
```
첫 번째 방법의 경우 단순히 편해보여서 사용했더니, **key값을 symbol로 저장해오고 있었다. 그렇기 때문에, key가 내가 생각한 것과 다르게 저장될 수 있으므로 항상 주의하자.** 아래 그림을 참고하자.
![hashSymbol](https://user-images.githubusercontent.com/71186266/169429632-522777f0-75c0-4635-a060-6747ddbb6d15.png)

위와 같이 알아서 `:`이 붙은 형태로 저장이 된다. 불러올 때도 주의해서 불러와야한다. <br/> <br/>

## 1.2 Symbol이란?
**symbol은 변경이 불가능(immutable)한 객체입니다. 한번 값이 할당되고 나면, 객체에 할당된 값을 변경할 수가 없습니다.** 루비는 인터프리터 언어이기 때문에, 실행 시점까지는 어떤 문자열이 실제로 어떤 값을 가지고 있는지 알 수 없습니다. 그래서 **각 String들은 매번 새로운 객체로 만들어지고, 이는 메모리 손상을 야기할 수 있습니다.** Symbol은 이런 문제를 해결하기 위해 등장했습니다. 한번 할당되면 그 내용이 변하지 않으니, 어떤 String을 Symbol로 만들어 주면, 해당 문자열의 '내용'이 필요할 때 마다, 새로운 객체를 만들어 줄 필요 없이, 그냥 Symbol을 재활용 해주면 되는 것이지요. <br/> <br/> 여러 곳에 쓰일 수 있으나, 위에서 보인 것과 같이 Hash의 Key로써 쓰기에 적당합니다. 


# 1.3 Variable
처음 언급한 것과 같이 심플하게 선언한다.
```ruby
x = 5
hello = "world"
```
x에 5가 저장 되었고, hello에는 world가 저장 되었다.

## 변수 종류
1. **지역변수**
```ruby
foo = 'foo in top level'
```
<br/>

2. **전역변수 $**
```ruby
$foo = 'foo in whole'
```
<br/>

3. **인스턴스 변수 @: 클래스 내의 인스턴스에서 호출 가능.**
메소드 끼리만 사용이 가능하고, 메소드 밖 + class 안쪽에서는 사용 불가능
```ruby
@foo = 'foo in instance'
```
<br/>

4. **클래스 변수 @@: 클래스 내의 어디에서든 불러올 수 있다.**
```ruby
@@foo = 'foo in class'
```
<br/>

# 2. 흐름 제어

# 2.1 if문
if문 제어의 끝에 **end**가 들어갑니다. **줄 바꾸기는 중요한 요소지만 들여쓰기에 문법적인 의미는 없습니다.**  
**⭐중요: Ruby의 조건문에서는 false와 nil은 false를 의미하고, 나머지는 true입니다.**

예시를 하나 보이겠습니다.
```ruby
if 1 + 6 == 7
    puts "I'm Feeling Lucky!"
else
    puts "what?"
end
```
위와 같이 if문을 사용할 수 있습니다. <br/> <br/>

**줄 바꾸기에 `;`을 이용할 수도 있습니다.** 한 줄로 나타낸 if문을 보이겠습니다.
```ruby
// 줄 바꾸기가 없는 버젼
if 1 + 6 == 7 then puts "I'm Feeling Lucky!" else puts "what?" end

// 세미콜론을 이용해 줄을 바꿔준 버젼
if 1 + 6 == 7; puts "I'm Feeling Lucky!!" else puts "what??" end

// if문의 반환값 자체를 String으로 해주고, 반환되는 값을 println한 버젼
puts (if 1 + 6 == 7 then "I'm Feeling Lucky!!!" else "What???" end)

// 영어처럼 나타내기! unless는 전체에 !를 씌워준 듯한 효과
puts "Lucky!" if 1 + 6 == 7
puts "what?!" unless 0 + 6 == 7 
```
영어처럼 나타낸 부분은 너무 멋있죠? 루비는 이런 영어식 코딩을 지원합니다.    
`;`은 줄 바꾸기의 역할을 합니다!
<br/> 

### 삼항연산자 
```ruby
puts (1 + 6 == 7 ? "I'm Feeling Lucky!" : "what?")
```
<br/>

# 2.2 case문
case문을 보이겠습니다. 매개변수를 전달 할 수도, 안 할 수도 있습니다. 전달하지 않는 경우, 위에서 부터 차례대로 실행되어 처음 참인 문장이 실행된 후에 종료합니다.
```ruby
// 매개변수가 있는 경우, 매개변수와 조건을 비교합니다.
num = 7
case num
when 7; puts "num is 7"
when 4; puts "num is not 7"
end


// 매개변수가 없는 경우, 문장 자체의 참거짓을 판별합니다.
num = 7
case
when num == 4; puts "num is not 7"
when num == 7; puts "num is 7"
end
```
<br/>

# 2.3 While
들여쓰기 상관 없음
```ruby
num = 1
while num <= 10
    if num % 2 == 0
        puts num.to_s + " is even"
    end
    num = num + 1
end
```

![while](https://user-images.githubusercontent.com/71186266/169445311-8403e6d4-594f-4b7e-b7b5-02e3ce1c8eed.PNG)
<Br/>

# 2.4 For
2가지 사용이 가능하다. 기존의 for문과, 향상된 for문과 같은 형식 2가지가 가능하다.

### 보통 for문 - 마지막 숫자는 포함하지 않는다!
```ruby
for num in 1..10
    if num%2 == 0
        puts num.to_s + " is even"
    end
end
```
![for1](https://user-images.githubusercontent.com/71186266/169445304-6f1e3b42-0fe6-4ac7-9523-ee3f5ffe89ad.PNG)
<br/>

### 향상된 for문
```ruby
list = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

for num in list
    if num%2 == 0
        puts num.to_s + " is even"
    end
end
```
![for2](https://user-images.githubusercontent.com/71186266/169445309-08e2b889-1754-4e78-b8d4-9bab918d0e3c.PNG)
<br/>


### 비교연산자와 논리연산자는 다른 언어와 거의 같습니다. and not or는 영어로도 사용이 가능합니다.

# 3. Method
메소드의 정의와 호출
```ruby
def print_even(lim)
    cnt = 0
    for num in 1..lim
        if num % 2 == 0
            puts num.to_s + " is even"
            cnt = cnt + 1
        end
    end
    return cnt
end

print_even(10)
```
![print_evec](https://user-images.githubusercontent.com/71186266/169446216-c2260b2c-bffe-49bc-abac-e41964a1286b.PNG)


### 참조
서민구 Ruby For Impatient Nuby - **[[바로가기]](https://docs.google.com/document/d/15yEpi2ZMB2Lld5lA1TANt13SJ_cKygP314cqyKhELwQ/preview)**
황대산 루비 프로그래밍 언어 FAQ - **[[바로가기]](https://web.archive.org/web/20190521035426/http://beyond.daesan.com/pages/ruby-faq)**
HAHWUL님 블로그 - Ruby language에서의 Symbol(심볼)이란? - **[[바로가기]](https://www.hahwul.com/2018/03/28/ruby-language-symbol/)**
Hosang Jeon님 블로그 - RUBY의 심볼(SYMBOL)과 문자열(STRING)은 서로 어떻게 다른가? - **[[바로가기]](http://guruble.com/ruby-symbol-vs-string/)**
Youtube Channel 코딩전도사 - **[[바로가기]](https://www.youtube.com/user/shj5508)**
