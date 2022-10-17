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


