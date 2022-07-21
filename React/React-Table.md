# React Table
기존 HTML로 작성된 테이블에 비해, 코드의 길이가 많이 짧아진다거나 하는 큰 장점이 있는 것은 아니지만, Mapping과 Sorting에 있어서 좋은 성능을 보입니다. <br> `useMemo()` 훅을 이용해 메모이제이션을 하여 한번 불러온 정보를 또 불러오는 비효율을 없앱니다. <br> `columns`에 header 데이터를, data에 전체 셀 데이터를 담습니다.
|Header|
|:----:|
|Data|
|Data|
|Data|

## 1. column 
column은 배열에 object형태가 들어가 있는 모습입니다. `Header`에는 header이름을, `accessor`에는 data object와 연결할 key name을 기재합니다.
```js
const columnDate = [
  {
    accessor: 'email',
    Header: 'Email',
  },
  {
    accessor: 'walletID',
    Header: 'Wallet ID',
  },
  {
    accessor: 'coin_list',
    Header: 'Wallet Balance',
  },
  {
    accessor: 'created_at',
    Header: 'Create At',
  },
  {
    accessor: 'edited_at',
    Header: 'Edited At',
  },
]

const colums = useMemo(() => columnData, []);
```
## 2. Data
데이터 또한 동일하게 배열 내 객체 형태로 입력. 포인트는 `colums`의 accessor와 key name이 일치한지 주의하여 입력합니다.

```js
const data = useMemo(() => [{
  "email": "dfghcvb11@naver.com",
  "walletID": "dfghcvb11",
  "coin_list": "2020-07-21 20:20:20",
  "created_at": "2020-07-21 20:20:20",
  "edited_at": ["BTC", "JinhoCoin", "ETH", "BCH"]
}], [])
```
이런 식이면, 그냥 JSON으로 받아온 자료는 다 처리가 된다. 
```js
const [info, setInfo] = useState();

const getTamWallet = () => {
  data.getTamWallet().then(item => setInfo(item));
};

const data = useMemo(() => info, [info])
```

## 3. Table
table을 출력하기 위해, `useTable()`을 이용하여 5가지 props를 가져옵니다.
1. `getTableProps()`: property, methode를 활용할 수 있음
2. `getTableBodyProps()`: table body를 만들어야 되는 경우 선언
3. `headerGroups`: header 부분에 들어갈 데이터를 담겨 있음.
4. `rows`: 전달한 data를 받는 곳
5. `prepareRow()`: 각각의 data들을 한 줄씩 묶음으로 가공함.
<br>
가져오는 예시는 아래와 같습니다.
```js
const Table = ({ columns, data }) => {
  const { getTableProps, getTableBodyProps, headerGroups, rows, prepareRow } = useTable({ columns, data });

...
}
이후 아래와 같이 사용합니다.
```js
return (
// Talbe 시작 테이블 프롭스를 넣어줘야한다
  <TableSheet {...getTableProps()}>
    // 헤더 라인
    <TableHead>
      {headerGroups.map(header => (
        // getHeaderGroupProps를 통해 header 배열을 호출한다
        <Header {...header.getHeaderGroupProps()}>
          {header.headers.map(col => (
            // getHeaderProps는 각 셀 순서에 맞게 header를 호출한다
            <Th {...col.getHeaderProps()}>{col.render('Header')}</Th>
          ))}
        </Header>
      ))}
    </TableHead>
    // 바디라인
    <tbody {...getTableBodyProps()}>
      {rows.map(row => {
        prepareRow(row);
        return (
          // getRowProps로 각 row data를 호출
          <tr {...row.getRowProps()}>
            {row.cells.map(cell => (
              // getCellProps로 각 cell data를 호출
              <Td {...cell.getCellProps()}>{cell.render('Cell')}</Td>
            ))}
          </tr>
        );
      })}
    </tbody>
  </TableSheet>
  );
};
```
