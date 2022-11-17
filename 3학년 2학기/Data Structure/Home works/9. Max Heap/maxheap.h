#ifndef MAXHEAP_H
#define MAXHEAP_H
#include<iostream>

using namespace std;

template<class T>
class Maxheap {
private:
    void ChangeSize1D(int);
    T* heap;
    int heapSize;
    int capacity;
public:
    Maxheap(int);
    void Push(const T &);

    void Pop();
    bool IsEmpty() {return heapSize == 0;}
    T Top() {return heap[1];}
    template<class T2> friend ostream &operator <<(ostream &, Maxheap<T2> &);
};

template<class T>
ostream &operator <<(ostream &os, Maxheap<T> &H)
{
    os << "<Heap contents> ";
    int i;
    for(i=1; i<=H.heapSize; i++)
        os << i << ":" << H.heap[i] << " ";
    os << endl;
    return os;
}

template<class T>
Maxheap<T>::Maxheap(int _capacity = 10) : heapSize(0)
{
    if(_capacity < 1)
        throw " Must be > 0";
    capacity = _capacity;
    heap = new T[capacity+1];
}

template<class T>
void Maxheap<T>::ChangeSize1D(int size)
{
    T temp[size+1];
    for (int i = 1; i < capacity; i++) {
        temp[i] = heap[i];
    }
    heap = temp;
    capacity = size;
}

template<class T>
void Maxheap<T>::Push(const T &value) {
    if (heapSize == capacity) ChangeSize1D(2*capacity);

    heapSize++;
    if (heapSize == 1) {
        heap[1] = value;
    } else {
        T parent = heap[heapSize >> 1];

        int idx = heapSize;
        T child = heap[idx];
        while (idx != 1 && heap[idx / 2] < heap[idx]) {
            int temp = heap[idx / 2];
            heap[idx / 2] = heap[idx];
            heap[idx] = temp;

            idx = idx / 2;
        }
    }
}

template<class T>
void Maxheap<T>::Pop() {
    if(heapSize <= 0) {
        return;
    } else if (heapSize == 1) {
        heapSize--;
        return heap[1];
    }
    heap[1] = heap[heapSize];
    heapSize--;

    int idx = 1;
    while(idx*2 <= heapSize) {
        int child;
        if (idx*2 + 1 > heapSize) {
            child = idx * 2;
        } else {
            child = heap[idx * 2] > heap[idx * 2 + 1] ? idx * 2 : idx * 2 + 1;
        }

        if(heap[child] <= heap[idx]) break;
        int temp = heap[child];
        heap[child] = heap[idx];
        heap[idx] = temp;

        idx = child;
    }
}



#endif
