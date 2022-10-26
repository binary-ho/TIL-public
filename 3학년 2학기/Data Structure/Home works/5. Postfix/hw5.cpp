#include <iostream>
#include <cstdio>
#include <stack>
#include "post.h"

int main(int argc, char *argv[]) {
    char line[MAXLEN];
    cout << "[B715152 Jinho Lee hw5 Postfix Result]" << '\n';
    while (cin.getline(line, MAXLEN, '\n')) {
	  Expression e(line);
        try {
            Postfix(e);
        }
        catch (char const *msg) {
            cerr << "Exception: " << msg << endl;
        }
    }
}
