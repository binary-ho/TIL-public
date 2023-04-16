#include "subway.h"

int main(int argc, char *argv[])
{
    argc = 3;
    int numLine, line1, line2, cost;
    string src, dst;

    if(argc != 3) {
        cerr << "Argument Count is " << argc << endl << "Argument must be " << argc << endl;
        return 1;
    }

    fstream fin(argv[1]);
    if(!fin) {
        cerr << argv[1] << " open failed " << endl;
        return 1;
    }

    fin >> numLine;
    while (numLine--) {
        fin >> line1 >> src >> line2 >> dst;
        setStation(line1, src, line2, dst);
    }
    fin.close();

    fstream fin2(argv[2]);
    if(!fin2) {
        cerr << argv[2] << " open failed" << endl;
        return 1;
    }
    fin2 >> line1 >> src;
    fin2 >> line2 >> dst;
    fin2.close();

    initDijkstra(line1, src, line2, dst);
    return 0;
}
