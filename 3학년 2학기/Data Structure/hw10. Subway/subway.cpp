#include "subway.h"

map<string, idxArrayWrapper> stationToIdx;
vector<int> connected[110];
int costTo[2][110];
Station idxToStation[110];
int stationCnt = 0;

int getAbs(int num) {
    return num < 0 ? num*(-1) : num;
}

string toString(int num) {
    int ten = num / 10;
    int left = num % 10;
    string numStr;
    numStr += (char) (ten + '0');
    numStr += (char) (left + '0');
    return numStr;
}

int getStationIdx(int line, string &src) {
    if (stationToIdx.find(src) == stationToIdx.end() || stationToIdx[src].line[line] == -1) {
        idxToStation[stationCnt].line = line;
        idxToStation[stationCnt].station = src;
        idxToStation[stationCnt].prevIdx = -1;
        stationToIdx[src].line[line] = stationCnt++;
    }

    return stationToIdx[src].line[line];
}

void setStation(int line1, string &src, int line2, string &dst) {
    int station1 = getStationIdx(line1, src);
    int station2 = getStationIdx(line2, dst);
    if (line1 != line2) return;
    connected[station1].push_back(station2);
    connected[station2].push_back(station1);
}

void Heap::push(Node *node) {
    heap.push_back(node);
    if (size() == 1) return;
    temp = size();
    while (temp != 1 && heap[temp / 2 - 1]->costNow < heap[temp - 1]->costNow) {
        swap(heap[temp / 2 - 1], heap[temp - 1]);
        temp /= 2;
    }
}

void Heap::pop() {
    if (empty()) return;
    swap(heap.front(), heap.back());
    heap.pop_back();
    if (empty()) return;
    temp = 1;
    int child;

    while (temp * 2 < size()) {
        child = temp * 2;
        if (temp * 2 + 1 < size() && heap[temp * 2]->costNow < heap[temp * 2 + 1]->costNow) child++;
        if (heap[child] <= heap[temp]) break;
        swap(heap[child], heap[temp]);
        temp = child;
    }
}


void traceStation(int dstIdx) {
    stack<string> st;
    Station *stationNow;
    while (dstIdx != -1) {
        stationNow = &idxToStation[dstIdx];
        if (st.empty() || st.top() != stationNow->station) st.push(stationNow->station);
        dstIdx = stationNow->prevIdx;
    }
    while (!st.empty()) {
        cerr << st.top() << endl;
        st.pop();
    }
}

void dijkstra(int sourceIdx, int destinationIdx, int step) {
    Heap *heapTree = new Heap;
    heapTree->push(new Node(sourceIdx, 0, -1));

    int idxNow;
    Station *stationNow;

    while (!heapTree->empty()) {
        Node *nodeNow = heapTree->top();
        heapTree->pop();
        idxNow = nodeNow->stationIdx;

        if (costTo[step][idxNow] <= nodeNow->costNow) continue;
        costTo[step][idxNow] = nodeNow->costNow;
        stationNow = &idxToStation[idxNow];
        stationNow->prevIdx = nodeNow->stationPrev;

        if (idxNow == destinationIdx) continue;

        // �ֱ�
        for (int line = 1; line < 10; line++) {
            if (stationToIdx[stationNow->station].line[line] == -1) continue;
            if (line == stationNow->line) continue;
            heapTree->push(new Node(stationToIdx[stationNow->station].line[line], nodeNow->costNow + 30, idxNow));
        }
        for (int i = 0; i < connected[idxNow].size(); i++) {
            heapTree->push(new Node(connected[idxNow][i], nodeNow->costNow + 60, idxNow));
        }
    }
}

void printTimeNoNewline(int time) {
    int second = time % 60;
    cerr << time / 60 << ":" << toString(second) << endl;
}

void getMiddleStation() {
    int ans = INF;
    int cost[2];
    string stationName;
    for (int i = 0; i < stationCnt; i++) {
        for (int j = 0; j < stationCnt; j++) {
            if (idxToStation[i].station != idxToStation[j].station) continue;
            if (ans < getAbs(costTo[0][i] - costTo[1][j])) continue;
            ans = getAbs(costTo[0][i] - costTo[1][j]);
            cost[0] = costTo[0][i];
            cost[1] = costTo[1][j];
            stationName = idxToStation[i].station;
        }
    }
    cerr << stationName << " //middle point" << endl;

    int first = cost[0] >= cost[1] ? 0 : 1;
    printTimeNoNewline(cost[first]);
    printTimeNoNewline(cost[1 - first]);
}

void initDijkstra(int line1, string &src, int line2, string &dst) {
    for (int i = 0; i < 2; i++) for (int j = 0; j < 110; j++) costTo[i][j] = INF;

    int sourceIdx = stationToIdx[src].line[line1];
    int destinationIdx = stationToIdx[dst].line[line2];
    dijkstra(sourceIdx, destinationIdx, 0);
    traceStation(destinationIdx);
    printTimeNoNewline(costTo[0][destinationIdx]);

    dijkstra(destinationIdx, sourceIdx, 1);
    getMiddleStation();
}
