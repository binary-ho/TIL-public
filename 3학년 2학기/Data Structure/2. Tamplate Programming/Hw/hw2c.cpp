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
