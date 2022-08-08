# Firebase 실시간 데이터 베이스 보안 규칙
JSON 기반의 firebase 실시간 데이터베이스의 보안규칙 구문입니다.
```json
{
  "rules": {
    "<<path>>": {
    // Allow the request if the condition for each method is true.
      ".read": <<condition>>,
      ".write": <<condition>>
    }
  }
}
```
규칙들은 **OR**문으로 작동됩니다. 여러 규칙들이 경로와 일치하고, 조건이 엑세스를 허용할 때 액세스가 허용됩니다.따라서 광범위한 규칙이 데이터 엑세스를 허용하는 경우에 의해 더 구체적인 규칙으로 제한을 할 수가 없는 문제가 발생할 수 있습니다. 이 문제를 해결하려면, 언어나 동작을 정확히 이해하고, 이를 기반으로 규칙을 최대한 겹치지 않도록 작성해야합니다. 

# 2. 보안 rule 언어
firebase의 실시간 데이터베이스 규칙은 JSON 구조에서 자바스크립트와 유사한 구문을 사용합니다. (Cloud Firestore, Cloud Storage의 규칙은 다름.) 

<br> <br>

규칙에는 3가지 기본 요소가 있습니다. 
1. **path**: DB의 위치입니다. DB의 JSON 구조를 반영합니다.
2. **request**: rule에서 액세스를 허용하기 위해 사용하는 method입니다. <br> `read`와 `write`는 광범위한 액세스에 쓰이고, `validate` rule은 수신되는 데이터나, 기존의 데이터들을 기반으로 액세스를 허용하는 일종의 2차 검증으로 작용합니다. <br> 예를 들어서 값의 형식이 올바른지, 하위 속성을 갖는지, 데이터 유형을 정의한다던지 할 떄 씁니다.
3. **condition**: true일 경우 요청을 허용합니다.
기본 구조는 아래와 같습니다.
```json
{
  "rules": {
    "<<path>>": {
    // Allow the request if the condition for each method is true.
      ".read": <<condition>>,
      ".write": <<condition>>,
      ".validate": <<condition>>
    }
  }
}
```


## 2.1 규칙의 구성
아래와 같은 구조의 데이터가 있다고 하자.
```json
  {
    "messages": {
      "message0": {
        "content": "Hello",
        "timestamp": 1405704370369
      },
      "message1": {
        "content": "Goodbye",
        "timestamp": 1405704395231
      },
      ...
    }
  }
```
위 구조를 반영해서 위치를 지정하려면, 
```json
{
  "rules": {
    "messages": {
      "$message": {
        // only messages from the last ten minutes can be read
        ".read": "data.child('timestamp').val() > (now - 600000",

        // new messages must have a string content and a numbertimestamp
        ".validate": "newData.hasChildren(['content','timestamp']) &&
                      newData.child('content').isString() &&
                      newData.child('timestamp').isNumber()"
      }
    }
  }
}
```
이런 식으로 지정해서 이용합니다. `$location` 변수로 경로 세그먼트를 일치시킵니다.

## 2.2 condition 작성하기
사전 정의된 변수들을 이용해서 간단히 규칙을 작성할 수 있습니다.
1. `now`: Linux를 기준으로 하는 현재 시간입니다. 밀리초로 나타내어 있으며, 타임스탬프를 검증하는데 유용합니다.
2. `root`: 작업 시도 **전에 Firebase DB에 존재하는 루트 경로**를 나타내는 RuleDataSnapshot
3. `newData`: **작업 시도 후에 존재할 데이터**를 나타내는  RuleDataSnapshot! 새로 기록되는 데이터와 기존 데이터를 포함한다.
4. `data`: 작업 시도 **전에 존제하는 데이터**를 나타내는 RuleDataSnapshot 
5. `$변수`: ID 및 동적 하위 키를 나타내는 데 사용되는 경로
6. `auth`: 인증된 사용자의 토큰 payload

**예시1:** `/foo/`노드에 기록되는 데이터의 문자열의 길이를 100자 미만으로 제한하고 싶을 때
```json
{
  "rules": {
    "foo": {
      // /foo is readable by the world
      ".read": true,

      // /foo is writable by the world
      ".write": true,

      // data written to /foo must be a string less than 100 characters
      ".validate": "newData.isString() && newData.val().length < 100"
    }
  }
}
```

**예시 2**: `/allow_writes/` 노드 값이 true이고, 상위 노드에 `readOnly` 플래그가 설정되지 않으며, 새로 기록되는 데이터에 foo라는 하위 항목이 있을 때 쓰기 작업을 허용하는 **데이터 기반 규칙**
```json
".write": "root.child('allow_writes').val() === true &&
          !data.parent().child('readOnly').exists() &&
          newData.child('foo').exists()"
```

# 3. 보안 규칙 작동 방식
