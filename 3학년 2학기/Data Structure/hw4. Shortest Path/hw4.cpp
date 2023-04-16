#include <iostream>
#include <fstream>

#include "stdlib.h"
using namespace std;

void getdata(istream&, int&, int&);
void Path(int, int);
void ShortestPath(int, int);

int main(int argc, char* argv[])
{
    int m, p;
    argc = 4;
    if (argc == 1)
        cerr << "Usage: " << argv[0] << " maze_data_file" << endl;
    else {
        ifstream is(argv[1]);
        if (!is) { cerr << argv[1] << " dose not exis\n", exit(1); }
        cout << "For maze datafile (" << argv[1] << ")\n";
        getdata(is, m, p); is.close();
        
	Path(m, p);
        ShortestPath(m, p);
    }
}
