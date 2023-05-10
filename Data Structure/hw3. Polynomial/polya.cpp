#include "polya.h"
#include <stdlib.h>
using namespace std;

istream& operator>> (istream& is, Polynomial& p) {
    int noofterms; float coef; int exp;
    is >> noofterms;
    for (int i = 0; i < noofterms; i++) {
        is >> coef >> exp;
        p.NewTerm(coef, exp);
    }
    return is;
}


ostream& operator<<(ostream& os, Polynomial& p) {
    string str;
    for(int i = 0; i < p.terms; i++) {
        Term termNow = p.termArray[i];
        if (i != 0) {
            if(termNow.coef > 0) str += "+";
            else str += "-";
        }
        if (termNow.coef != 1 && termNow.coef != -1) str += (abs((int) termNow.coef)) + '0';
        if(i != p.terms - 1) str += "x";
        if (termNow.exp != 1 && termNow.exp != 0) {
            str += "^";
            if (termNow.exp < 0) {
                str += "(-";
                str += (abs((int) termNow.exp)) + '0';
                str += ")";
            } else {
                str += (abs((int) termNow.exp)) + '0';
            }
        }
        str += " ";
    }
    return os <<  str << endl;
}

Polynomial::Polynomial() :capacity(1), terms(0) {
    termArray = new Term[capacity];
}

void Polynomial::NewTerm(const float theCoeff, const int theExp) {
    if (terms == capacity) {
        capacity *= 2;
        Term* temp = new Term[capacity];
        copy(termArray, termArray + terms, temp);
        delete[] termArray;
        termArray = temp;
    }
    termArray[terms].coef = theCoeff;
    termArray[terms++].exp = theExp;
}

Polynomial Polynomial::operator+(Polynomial& b) {
    Polynomial c;
    int aPos = 0, bPos = 0;
    while ((aPos < terms) && (bPos < b.terms)) {
        if (termArray[aPos].exp == b.termArray[bPos].exp) {
            float t = termArray[aPos].coef + b.termArray[bPos].coef;
            if (t) {
                c.NewTerm(t, termArray[aPos].exp);
                aPos++;
                bPos++;
            }
        }
        else if (termArray[aPos].exp < b.termArray[bPos].exp) {
            c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        }
        else {
            c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
    }
    for (; aPos < terms; aPos++) {
        c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
    }
    for (; bPos < b.terms; bPos++) {
        c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
    }
    return c;
}

int main() {
    Polynomial p1, p2;
    cin >> p1 >> p2;
    Polynomial p3 = p1 + p2;
    cout << p1 << p2 << p3;
}
