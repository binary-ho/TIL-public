#include "maxheap.h"
#include <iostream>
int main(int argc, char *argv[])
{
    int N, i, data;
    Maxheap<int> H(10);
    if(argc != 2)
    {
        cerr << "wrong argument count" << endl; return 1;
    }
    fstream fin(argv[1]);
    if(!fin)
    {
        cerr << argv[1] << " open failed" << endl;
        return 1;
    }
    fin >> N; for(i=0; i<N; i++)
    {
        fin >> data;
        H.Push(data);
    }

    cout << H; while(!H.IsEmpty())
    {

        cout << H.Top() << " " ; H.Pop();
    }
    cout << endl;
    fin.close();
    return 0;
}
