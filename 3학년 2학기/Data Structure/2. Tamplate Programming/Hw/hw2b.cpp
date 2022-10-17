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
