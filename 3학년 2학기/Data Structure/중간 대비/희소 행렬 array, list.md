
# 희소행렬
아마도, 희소 행렬의 연산과 희소 리스트로의 변화가 관찰 포인트가 되지 않을까?


## 1. 희소 행렬 Array
### 1.1 행렬의 전치
#### 기존 알고리즘
```c++
for (int i = 0; i < row; i++)
  for (int j = 0; j < columns; j++)
    b[j][i] = a[i][j];
```
당연히 O(row*columns)

#### terms로 개선한 알고리즘
**O(terms*cols)** <br> 
그냥 열마다 terms만큼 움직이고, 다 찾으면 엄춘다는 장점이 있는 듯

```c++
int (terms > 0)
{
  int currentB = 0;
  for (int c = 0; c < cols; c++)
  {
    for (int i = 0; i < terms; i++) 
    {  
      if (smArray[i].col == c) 
      {
        b.smArray[currentB].row = c;
        b.smArray[currentB].col = smArray[i].row;
        b.smArray[currentB++].value = smArray[i].value;
      }
    }
  }
}
```
돌면서 b의 어레이에 몇 번째 원소, row, col 어디있는지 + 값 이렇게 저장. <br>
*this와 b가 필요로하는 공간 외에는.. c, i, currentB만을 위한 고정 공간 필요 

#### 개선된 알고리즘
메모리 Tradeoff 각 열에 대한 원소 수를 미리 알고 간다.
<br> 실행시간 무려 O(cols + term)!

```c++
SparseMatrix sparseMatrix::FastTranspose()
{
    SparseMatrix b (cols, rows, terms);
    if (terms > 0)
    {
        int *rowSize = new int[cols];
        int *rowStart = new int[cols];
        
        fill (rowSize, rowSize + cols, 0);

        // 모든 원소 순회해서 col가져와서 ++
        // col 마다 원소ㅗ가 몇 개인지?
        for (int i = 0; i < terms; i++) rowSize[smArray[i].col]++;
        
        rowStart = 0;
        // 새로 만들 행렬에 넣어줄 원소가 원래 smArray에서 몇 번째
        // 원소였는지를 저장해뒀다가 또 쓴다. 이러면 중복이 없지!
        for (int i = 1; i < cols; i++) rowStart[i] = rowStart[i-1] + rowSize[i-1];
        for (int i = 0; i < terms; i++)
        {
            int j = rowStart[smArray[i].col];
            b.smArray[j].row = smArray[i].col;
            b.smArray[j].col = smArray[i].row;
            b.smArray[j].value = smArray[i].value;
            rowStart[smArray[i].col]++;
        }
        delete [] rowSize;
        delete [] rowStart;
    }
}
```

### 1.2 행렬 곱
무려 N^3
```c++
for (int i = 0; i < a.rows; i++) {
  for (int j = 0; j < b.cols; j++) {
    sum = 0;
    for (int k = 0; k < a.cols; k++)
      sum += (a[i][k] * b[k][j]);
    c[i][j] = sum;
  }
}
```


## 2. 희소 행렬 List
그냥 Matrix 모양의 Linked List를 만들자는 Idea. 
1. 헤더 노드가 있는 원형 리스트 사용
2. 0이 아닌 각 항은 **행 원형 리스트에** 속하는 동시에, **열 원형 리스트에 소속됨.**
3. 헤더 노드와 원소 노드를 나눈다. 열 리스트는 `down`, 행 리스트는 `right` 필드가 있다. 헤드 노드끼리는 `next` 필드가 연결. i쨰 헤더는 i쨰 열과 행의 헤더 역할을 모두 수행.
4. 원소 노드 - Matrix 전체 헤더 노드: 얘도 down, right 필드가 있다. 같은 열과 행의 0이 아닌 다음 항을 연결한다. 그리고 해당 원소의 정보를 저장하는 필드 row, col, value..

### 필요한 노드 수
r개의 0 아닌 항을 가진 n*m 희소행렬이라면, <br>
n과 m중 더 큰 값 max{n, m} + r + 1개 <br>
왜냐하면 행열노드 + 0 아닌 노드 + 전체 헤더 노드

## 각종 연산 구현 가능
