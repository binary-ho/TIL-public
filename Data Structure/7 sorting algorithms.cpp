//
// Created by Jinho on 2023-05-13.
//

#include <iostream>
#include <queue>
#include <cstring>
#include <locale.h>
#include <stdlib.h>
#include <algorithm>
#include <cmath>


#define MAX_ARRAY_NUMBER 100
using namespace std;

class SortingAlgorithm {
public:
    SortingAlgorithm(int _size) {
        size = _size;
    }

    void selectionSort();
    void insertionSort();
    void bubbleSort();
    void shellSort();
    void mergeSort();
    void quickSort();
    void radixSort();

    void printArray();

private:
    int size;
    int *arr;
    void generateRandomArray();
    void mergeSort(int start, int end);
    void quickSort(int start, int end);
};

void SortingAlgorithm::generateRandomArray() {
    arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % MAX_ARRAY_NUMBER;
    }
    printArray();
}

void SortingAlgorithm::selectionSort() {
    cout << "============ selectionSort ============\n";
    generateRandomArray();

    int minNumber, minIdx;
    for (int select = 0; select < size; select++) {
        minNumber = MAX_ARRAY_NUMBER;
        for (int i = select; i < size; i++) {
            if (minNumber > arr[i]) {
                minNumber = arr[i];
                minIdx = i;
            }
        }
        swap(arr[select], arr[minIdx]);
    }

    printArray();
}

void SortingAlgorithm::printArray() {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n\n";
}

void SortingAlgorithm::insertionSort() {
    cout << "============ insertionSort ============\n";
    generateRandomArray();

    int j, temp;
    for (int i = 1; i < size; i++) {
        temp = arr[i];
        for (j = i - 1; j >= 0; j--) {
            if (arr[j] > temp) {
                arr[j + 1] = arr[j];
                continue;
            }
            break;
        }
        arr[j + 1] = temp;
    }

    printArray();
}

void SortingAlgorithm::bubbleSort() {
    cout << "============ bubbleSort ============\n";
    generateRandomArray();

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }

    printArray();
}

void SortingAlgorithm::shellSort() {
    cout << "============ shellSort ============\n";
    generateRandomArray();

    int gap;
    for (gap = size / 2; gap > 0; gap /= 2) {
        if (gap % 2 == 0) {
            gap++;
        }

        for (int k = 0; k < gap; k++) {
            int j, temp;
            for (int i = k + gap; i < size; i += gap) {
                temp = arr[i];
                for (j = i - gap; j >= k && temp < arr[j]; j -= gap) {
                    arr[j + gap] = arr[j];
                }
                arr[j + gap] = temp;
            }
        }
    }

    printArray();
}

void SortingAlgorithm::mergeSort() {
    cout << "============ mergeSort ============\n";
    generateRandomArray();

    mergeSort(0, size - 1);

    printArray();
}

void SortingAlgorithm::mergeSort(int start, int end) {
    if (start == end) return;

    int mid = (start + end) / 2;
    mergeSort(start, mid);
    mergeSort(mid + 1, end);

    int *tempArr = new int[size];
    int i = start, j = mid + 1, k = start;
    while (i <= mid && j <= end) {
        if (arr[i] < arr[j]) {
            tempArr[k++] = arr[i++];
        } else {
            tempArr[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        tempArr[k++] = arr[i++];
    }
    while (j <= end) {
        tempArr[k++] = arr[j++];
    }

    for (i = start; i <= end; i++) {
        arr[i] = tempArr[i];
    }
}

void SortingAlgorithm::quickSort() {
    cout << "============ quickSort ============\n";
    generateRandomArray();

    quickSort(0, size - 1);
    printArray();
}

void SortingAlgorithm::quickSort(int start, int end) {
    if (start >= end) return;

    int pivotValue = arr[start];
    int pivot = start;

    for (int j = start + 1; j <= end; j++) {
        if (arr[j] < pivotValue) {
            swap(arr[j], arr[++pivot]);
        }
    }
    swap(arr[start], arr[pivot]);
    quickSort(start, pivot - 1);
    quickSort(pivot + 1, end);
}

void SortingAlgorithm::radixSort() {
    cout << "============ radixSort ============\n";
    generateRandomArray();

    int temp = MAX_ARRAY_NUMBER, ten = 0;
    while (temp > 0) {
        temp /= 10;
        ten++;
    }
    queue<int> que[10];

    // 자릿수
    for (int idx = 0; idx < ten; idx++) {
        for (int j = 0; j < size; j++) {
            que[(arr[j] / (int) pow((int) 10, (int) idx)) % 10].push(arr[j]);
        }
        int newIdx = 0;
        for (int j = 0; j < 10; j++) {
            while (!que[j].empty()) {
                arr[newIdx++] = que[j].front();
                que[j].pop();
            }
        }
    }

    printArray();
}


int main() {
    srand((unsigned int) (time(0)));

    SortingAlgorithm sortingAlgorithm = SortingAlgorithm(10);
    sortingAlgorithm.selectionSort();
    sortingAlgorithm.insertionSort();
    sortingAlgorithm.bubbleSort();
    sortingAlgorithm.shellSort();
    sortingAlgorithm.mergeSort();
    sortingAlgorithm.quickSort();
    sortingAlgorithm.radixSort();
}
