//
// Created by Jinho on 11/18/2022.
//

#ifndef SUBWAY_H
#define SUBWAY_H
#define INF 98765432

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <stack>

using namespace std;

struct Station {
    int line, prevIdx;
    string station;

    Station() { line = -1; station = ""; prevIdx = -1;}
};

struct idxArrayWrapper {
    int line[10];
    idxArrayWrapper() {
        for (int i = 0; i < 10; i++) line[i] = -1;
    }
};

struct Node {
    int stationIdx, costNow, stationPrev;

    Node(int stationIdx, int costNow, int stationPrev)
            : stationIdx(stationIdx), costNow(costNow), stationPrev(stationPrev) {}
};

class Heap {
    int temp;
public:
    vector<Node*> heap;
    void pop();
    Node* top() { return heap.front(); }
    int size() { return heap.size(); }
    bool empty() { return heap.empty(); }
    void push(Node*);
};

void setStation(int line1, string &src, int line2, string &dst);
void initDijkstra(int line1, string& src, int line2, string& dst);

#endif //SUBWAY_H
