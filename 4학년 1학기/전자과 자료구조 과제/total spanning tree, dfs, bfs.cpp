//
// Created by Jinho on 2023-05-04.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Edge {
public:
    int to;
    int cost;
    Edge(int _to, int _cost) {
        to = _to;
        cost = _cost;
    }
};

class Node {
public:
    vector<Edge> link = vector<Edge>();
} nodePool[10];
bool check[10];

int getNumber(char ch) {
    return ch - 'a';
}

int graphCnt = 0;
int minCost = 987654321;
void dfs(int nodeCnt, int nodeNumberNow, int costNow, vector<int> &path) {
    if (nodeCnt == 0) {
        graphCnt++;
        cout << "path : ";
        for (int p : path) {
            cout << (char ) ('a' + p) << " -> ";
        }
        cout << "(cost : ";
        if (minCost >= costNow) {
            minCost = costNow;
            cout << minCost << " -> " << costNow;
        } else {
            cout << costNow;
        }
        cout << "), (minCost : " << minCost << ")\n";
        return;
    }

    for (int i = 0; i < nodePool[nodeNumberNow].link.size(); i++) {
        Edge edgeNow = nodePool[nodeNumberNow].link[i];

        if (check[edgeNow.to]) continue;

        check[edgeNow.to] = true;
        path.emplace_back(edgeNow.to);
        dfs(nodeCnt - 1, edgeNow.to, costNow + edgeNow.cost, path);
        path.pop_back();
        check[edgeNow.to] = false;
    }
}


int dist[10];
queue<int> que;
void bfs(int start) {

    que.push(start);
    check[start] = true;
    while (!que.empty()) {
        int nodeNow = que.front();
        que.pop();

        for (Edge edge : nodePool[nodeNow].link) {
            if (check[edge.to]) continue;
            check[edge.to] = true;
            dist[edge.to] = dist[nodeNow] + edge.cost;
            que.push(edge.to);
            cout << (char) (nodeNow + 'a') << " -> " << (char ) (edge.to + 'a') << '\n';
        }
    }
}

int main() {

    nodePool[getNumber('a')].link.emplace_back(Edge(getNumber('b'), 29));
    nodePool[getNumber('a')].link.emplace_back(Edge(getNumber('f'), 10));

    nodePool[getNumber('b')].link.emplace_back(Edge(getNumber('a'), 29));
    nodePool[getNumber('b')].link.emplace_back(Edge(getNumber('c'), 16));
    nodePool[getNumber('b')].link.emplace_back(Edge(getNumber('g'), 15));

    nodePool[getNumber('c')].link.emplace_back(Edge(getNumber('b'), 16));
    nodePool[getNumber('c')].link.emplace_back(Edge(getNumber('d'), 12));

    nodePool[getNumber('d')].link.emplace_back(Edge(getNumber('c'), 12));
    nodePool[getNumber('d')].link.emplace_back(Edge(getNumber('e'), 22));
    nodePool[getNumber('d')].link.emplace_back(Edge(getNumber('g'), 18));

    nodePool[getNumber('e')].link.emplace_back(Edge(getNumber('d'), 22));
    nodePool[getNumber('e')].link.emplace_back(Edge(getNumber('f'), 27));
    nodePool[getNumber('e')].link.emplace_back(Edge(getNumber('g'), 25));

    nodePool[getNumber('f')].link.emplace_back(Edge(getNumber('a'), 10));
    nodePool[getNumber('f')].link.emplace_back(Edge(getNumber('e'), 27));

    nodePool[getNumber('g')].link.emplace_back(Edge(getNumber('b'), 15));
    nodePool[getNumber('g')].link.emplace_back(Edge(getNumber('d'), 18));
    nodePool[getNumber('g')].link.emplace_back(Edge(getNumber('e'), 25));

//    bfs(getNumber('a'));
//    return 0;

    vector<int> path = vector<int>();
    path.emplace_back(getNumber('a'));
    check[getNumber('a')] = true;
    dfs(6, getNumber('a'), 0, path);
    cout << "total spanning tree : " << graphCnt << '\n';
}

