//
// Created by Jinho on 12/2/2022.
//

#ifndef ALGORITHEM_SORT_H
#define ALGORITHEM_SORT_H
#define MAXNODE 100001
#include <vector>

using namespace std;

double getResult(struct timeval start_t, struct timeval end_t) {
    return (double)(end_t.tv_sec-start_t.tv_sec)+ ((double)(end_t.tv_usec-start_t.tv_usec)/1000000);
}

void insertionSort(int *arr, int N) {
    int value;
    for(int i = 1; i < N ; i++){
        value = arr[i];
        for(int j = i - 1 ; j >= 0 ; j--){
            if(arr[j] <= value){
                arr[j+1] = arr[j];
                continue;
            }
            arr[j+1] = value;
            break;
        }
    }
}

double insertionSort(int *arr, int N, struct timeval start_t, struct timeval end_t) {
    gettimeofday(&start_t, NULL);
    insertionSort(arr, N);
    gettimeofday(&end_t, NULL);
    return getResult(start_t, end_t);
}

void quickSort(int *arr, int start, int end) {
    if(start >= end) return;

    int pivot = start;
    int i = pivot+1;
    int j = end;

    while(i<=j){
        while(i <= end && arr[i]<=arr[pivot]) ++i;
        while(j>start && arr[j]>arr[pivot])  --j;

        if(i>=j) break;

        if(i != j) swap(arr[i], arr[j]);
    }

    if(pivot != j) swap(arr[pivot], arr[j]);

    quickSort(arr, start, j-1);
    quickSort(arr, j+1, end);
}

double quickSort(int *arr, int start, int end, struct timeval start_t, struct timeval end_t) {
    gettimeofday(&start_t, NULL);
    quickSort(arr, start, end);
    gettimeofday(&end_t, NULL);
    return getResult(start_t, end_t);
}

void mergeSort(int *num, int size) {
    int left[size], right[size], leftSize = 0, rightSize = 0;
    int cur = num[0], p = 0;
    for (int i = 0; i < size; i++) {
        if (num[i] < cur) p ^= 1;
        if (p == 0) {
            left[leftSize++] = cur = num[i];
            continue;
        }
        right[rightSize++] = cur = num[i];
    }

    if (rightSize == 0) return;
    mergeSort(left, leftSize);
    mergeSort(right, rightSize);

    int leftIdx = 0, rightIdx = 0, arrayIdx = 0;
    while (leftIdx < leftSize && rightIdx < rightSize) {
        if (left[leftIdx] < right[rightIdx]) num[arrayIdx++] = left[leftIdx++];
        else num[arrayIdx++] = right[rightIdx++];
    }
    while (leftIdx < leftSize) num[arrayIdx++] = left[leftIdx++];
    while (leftIdx < leftSize) num[arrayIdx++] = left[leftIdx++];
}

double mergeSort(int *num, int size, struct timeval start_t, struct timeval end_t) {
    gettimeofday(&start_t, NULL);
    mergeSort(num, size);
    gettimeofday(&end_t, NULL);
    return getResult(start_t, end_t);
}

struct Node {
    int data;
    Node *parent, *child[2];
};

struct Heap {
    Node *root;
    int size;

    void init();
    Node* get_node(int data);
    Node* find_node(int idx);
    void push(int data);
    void pop();
    bool empty() { return size == 0; }
    int top() { return root->data; }
} heap;

void Heap::init() {
    root = NULL;
    size = 0;
}

Node* Heap::get_node(int data) {
    Node *node = new Node;
    node->data = data;
    node->parent = node->child[0] = node->child[1] = NULL;
    return node;
}

Node* Heap::find_node(int idx) {
    if(idx > size) return NULL;
    if(idx == 1) return root;
    return find_node(idx >> 1)->child[idx & 1];
}

void Heap::push(int data) {
    if (size >= MAXNODE) return;

    Node *node = get_node(data);
    size++;

    if (size == 1) {
        root = node;
        return;
    }
    Node *parent = find_node(size >> 1);
    parent->child[size & 1] = node;
    node->parent = parent;
    while (node != root && node->parent->data < node->data) {
        int temp = node->parent->data;
        node->parent->data = node->data;
        node->data = temp;

        node = node->parent;
    }
}

void Heap::pop() {
    if(size <= 1) {
        size = 0;
        return;
    }

    Node *node = find_node(size);
    root->data = node->data;
    node->parent->child[size & 1] = NULL;
    size--;
    node = root;

    while(node->child[0] != NULL) {
        Node *child;
        if(node->child[1] == NULL) child = node->child[0];
        else child = node->child[0]->data < node->child[1]->data ? node->child[1] : node->child[0];

        if(child->data < node->data) break;
        int temp = child->data;
        child->data = node->data;
        node->data = temp;

        node = child;
    }
}

double heapSort(int *arr, int N, struct timeval start_t, struct timeval end_t) {
    heap.init();
    gettimeofday(&start_t, NULL);
    for (int i = 0; i < N; i++) heap.push(arr[i]);
    while (!heap.empty()) { heap.pop(); }
    for (int i = N - 1; i >= 0 && !heap.empty(); i--, heap.pop()) arr[i] = heap.top();
    gettimeofday(&end_t, NULL);
    return getResult(start_t, end_t);
}

#endif //ALGORITHEM_SORT_H
