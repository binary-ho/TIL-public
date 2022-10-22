# hw2a.cpp
```cpp
#include <iostream>
using namespace std;

int add(int x, int y) {
    return x + y;
}

double add(double x, double y) {
    return x + y;
}

float add(float x, float y) {
    return x + y;
}

int main() {
    int intX = 1, intY = 2;
    double dbX = 3.3, dbY = 4.4;
    float fX = 09.24, fY = 10.07;

    cout << add(intX, intY) << endl;
    cout << add(dbX, dbY) << endl;
    cout << add(fX, fY) << endl;

    return 0;
}
```

# hw2b.cpp
```cpp
#include <iostream>
using namespace std;

template <typename T>
class CPoint
{
  T arg1, arg2;

public:
  CPoint(T _arg1, T _arg2)
  {
    arg1 = _arg1;
    arg2 = _arg2;
  }
  void Move(T _arg1, T _arg2);
  void Print();
};

template <typename T>
void CPoint<T>::Move(T _arg1, T _arg2)
{
  arg1 += _arg1;
  arg2 += _arg2;
}

template <typename T>
void CPoint<T>::Print()
{
  cout << "(" << arg1 << ", " << arg2 << ")" << endl;
}

int main()
{
  CPoint<int> P1(1, 2);
  CPoint<double> P2(1.1, 2.2);

  P1.Move(2, 3);
  P2.Move(2.2, 3.3);

  P1.Print();
  P2.Print();
  return 0;
}
```

# hw2c.cpp
```cpp
#include <iostream>
using namespace std;

template <typename T>
class CPoint {
public:
    T arg1, arg2;
    CPoint(T _arg1, T _arg2) {
        arg1 = _arg1;
        arg2 = _arg2;
    }
    void Move(T _arg1, T _arg2);
};

template <typename T>
void CPoint<T>::Move(T _arg1, T _arg2) {
    arg1 += _arg1;
    arg2 += _arg2;
}

template <typename T>
ostream& operator <<(ostream& out, const CPoint<T> &cPoint) {
    return out << "(" << cPoint.arg1 << ", " << cPoint.arg2 << ")" << endl;
}

int main() {
    CPoint<int> P1(1, 11);
    CPoint<double> P2(1.1, 2.2);

    P1.Move(8, 13);
    P2.Move(8.97, 20.39);

    cout << P1 << P2;

    return 0;
}
```
