# Item 14. Comparable을 구현할지 고려하라
## 1. Comparable 구현의 즐거움!
Comparable 인터페이스의 유일한 메서드인 compareTo는 Object의 메서드가 아니다. <br> 
성격은 Object의 equals와 같지만, **`compareTo`는 단순 동치성 비교에 더해 순서까지 비교할 수 있으며, 제네릭하다.** <br>
애초에 **Comparable을 구현했을 때는 그 클래스의 인스턴스들에 natural order, 자연적인 순서가 있음을 뜻한다!** <br>

순서가 있는 클래스에 Comparable를 구현한다면, `Array.sort(a);`나, 여러 정렬, 검색, 극단값 계산 등의 **Comparable을 활용하는 다양한 제네릭 알고리즘과 컬렉션의 혜택을 누릴 수가 있다!!!!** <br>

사실상 자바 플랫폼 라이브러리의 모든 값 클래스와 열거 타입이 Comparable를 구현했다! <br>
그러니까 알파벳, 숫자, 연대 같이 순서가 명확한 값 클래스를 작성한다면 반드시 Comparable 인터페이스를 구현하자! <br>



## 2. 기본 규약과 equals와의 유사점
compareTo 메서드의 일반 규약은 equlas의 규약과 비슷하다. <br>
아래는 이를 간략하게 **변형하여** 나타낸 것이다.
```
이 객체와 주어진 객체의 순서를 비교한다. 이 객체가 주어진 객체보다 작으면 음의 정수를, 같으면 0을, 크면 양의 정수를 반환한다. 이 객체와 비교할 수 없는 타입의 객체가 주어지면, ClassCastException을 던진다. 

1. Compareable을 구현한 클래스는 모든 x, y에 대해 순서를 바꾸어도 같은 결과를 반환해야 한다.
2. Compareable을 구현한 클래스는 `추이성`을 보장해야 한다. 예를 들어 x > y로 판단하고, y > z로 판단했다면, x > z로 판단해야 한다.
3. Compareable을 구현한 클래스는 x == y라면, x와 z의 관계와 y와 z의 관계가 같아야 한다.
4. compareTo 메서드로 수행한 동치성 테스트의 결과가 equals의 결과와 같아야 한다. 필수는 아니지만 꼭 지키는게 좋고, 지키지 않는 경우 그 사실을 명시해라.
``` 
요약하자면, 반사성 대칭성 추이성을 충족해야 하고, equals와 같은 결과를 갖는 것이 좋다는 것이다. <br>
마지막 규약은 꼭 지키는 편이 좋다. 둘의 결과가 일치하지 않아도 동작은 잘 하지만, 잘 지켜주면 equals 메서드의 규약을 따르는 인터페이스들인 Collection, Set, Map등의 동작과 잘 어울리게 된다. <br>
이 정렬된 컬렉션들은 동치성을 비교할 때 equals가 아닌 compareTo를 사용하기 때문이다. <br>

**많은 부분이 equlas와 비슷하기 때문에 그 주의사항도 비슷하다.** <br>
**기존 클래스를 확장한 구체 클래스에서 새로운 값 컴포넌트를 추가했다면 comapreTo를 지킬 방법이 없다!** <br>
우회하는 방법도 똑같다. Comaprable을 구현한 클래스를 확장하고 싶으면, 확장하는 대신 **독립된 클래스를 만들고 이 클래스에 원래 클래스의 인스턴스를 가리키는 필드를 주자** <br>
그런 다음 내부 인스턴스를 반환하는 **`뷰` 메서드를 제공한다!** 그러면 **바깥 클래스에 우리가 원하는 compareTo 메서드를 구현해 넣을 수 있다.** <br>


## 3. 작성 요령들
### 3.1 equals와의 차이
comapreTo는 equals와 비슷하게 작성하면 된다. 몇 가지 차이점만 주의한다. <br>
Comparable은 타입을 인수로 받는 제네릭 인터페이스이다. 따라서, compareTo의 메서드 인수 타입은 컴파일 타입에정해진다. <br>
따라서 **입력 인수의 타입을 확인하거나 형변환할 필요가 없다.** 잘못된 경우 컴파일 자체가 안 되기 때문! <br>

### 3.2 null 인수 에러
또한 null을 인수로 넣어 호출하면 NullPointerException을 던져야 한다. 

### 3.3 객체 참조 필드의 비교
compareTo는 각 필드의 **동치성이 아닌 순서를 비교한다.** <br>
다라서 객체 참조 필드를 비교하려면, compareTo 메서드를 재귀적으로 호출해야 하는데, <br>
만약 Comparable을 구현하지 않은 필드나 표준이 아닌 내 마음대로 순서를 비교해야 한다면, **Comparator - 비교자를 사용한다.** <br>
비교자는 직접 만들어도 되고, 자바가 제공해주는 것을 쓰면 된다. <Br>
```java
public final class CaseInsensitiveString
        implements Comparable<CaseInsensitiveString> {
    private final String s;

    ...

    public int compareTo(CaseInsensitiveString cis) {
        return String.CASE_INSENSITIVE_ORDER.compare(s, cis.s);
    }
}
```
위의 코드는 자바가 제공하는 비교자를 사용했다! <br>
`Comparable<CaseInsensitiveString>`의 의미를 알아야 한다. <br>
위 코드는 **`CaseInsensitiveString`의 참조는 `CaseInsensitiveString` 참조와만 비교할 수 있다는 의미를 가지고 있다.**

### 3.4 관계 연산자 <와 >를 쓰지 마라.
**compare 메서드에서 관계 연산자 <와 >를 사용하는 것은 거추장스럽고 오류를 유발한다** <br>

대신 박싱된 기본 타입 클래스들에 새로 추가된 **정적 메서드인 compare을 사용하라.** <br>
```java
  public int compareTo(PhoneNumber pn) {
      int result = Short.compare(areaCode, pn.areaCode);
      if (result == 0)  {
          result = Short.compare(prefix, pn.prefix);
          if (result == 0)
              result = Short.compare(lineNum, pn.lineNum);
      }
      return result;
  }
```
위와 같이, PhoneNumber의 필드들이 Short로 정의되어 있는 것을 이용해 **기본 타입 클래스의 compare를 이용해서 구현하였다.** <br>

### 3.5 클래스의 핵심 필드가 여러개일 때
클래스의 핵심 필드가 여러개일 때는 **어느 것을 먼저 비교하는지가 매우 중요하다.** <br>
바로 위의 예시가 그렇다. 일단 `areaCode`를 비교했고, 그 다음으로는 `prefix`, 그리고 `lineNum`을 비교했다. <Br>
그리고 **값이 다른 경우엔 바로 비교를 끝냈다! 오직 같은 경우에만 다음 비교로 넘어갔다.** <br>
따라서, 가장 핵심적인 필드부터 비교해 나가야 한다. <br>

이런 구현을 더 이쁘게 해주는 `Comparator`인터페이스가 자바 8부터 나왔다. <Br>
이 인터페이스와 정적 임포트를 통한 구현은 약 10%나 느리지만, 코드가 이쁘다.

```java
  private static final Comparator<PhoneNumber> COMPARATOR =
          comparingInt((PhoneNumber pn) -> pn.areaCode)
                  .thenComparingInt(pn -> pn.prefix)
                  .thenComparingInt(pn -> pn.lineNum);

  public int compareTo(PhoneNumber pn) {
      return COMPARATOR.compare(this, pn);
  }
```

비교자 생성 메서드를 활용해서 구현해봤다. `comparingType`이나 `tennComparingType`은 기본 타입들에 대해 타입을 추론해서 알아서 계산해준다.


## Reference
- Effective Java <조슈아 블로크>
