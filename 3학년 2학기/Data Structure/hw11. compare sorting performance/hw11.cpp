#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sys/time.h>
#include "sort.h"

using namespace std;
int* getArray(char *file);

struct timeval start_t, end_t;
int N, i;
using namespace std;

int main(int argc, char *argv[])
{
    int T = atoi (argv[1]);
    cout << "T=" << T << endl;
    double result[4], diff_t;

    if (argc < 3) {
        cerr << "worng argument count" << endl;
        return 1;
    }

    int *arr[4], temp, *arrForMerge;
    cout << "--INS--|--QUICK--|--NATIMG--|--HEAP--|" << endl;
    for (i = 2; i < T + 2; i++) {
        arr[0] = arr[1] = arr[2] = arr[3] = getArray(argv[i]);
        result[0] = insertionSort(arr[0], N, start_t, end_t);
        result[1] = quickSort(arr[1], 0, N-1, start_t, end_t);
        result[2] = mergeSort(arr[2], N, start_t, end_t);
        result[3] = heapSort(arr[1], N, start_t, end_t);

        cout.precision(5);
        cout << fixed;

        for (int j = 0; j < 4; j++) {
            cout << result[j] << "|";
        }
        cout << "N=" << N << endl;
    }
}

int* getArray(char *file) {
    fstream fin(file);
    fin >> N;
    int *arr = new int[N];
    for(int j=0; j< N; j++) fin >> arr[j];
    fin.close();
    return arr;
}
