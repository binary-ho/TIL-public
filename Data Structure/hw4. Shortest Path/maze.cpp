#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>
using namespace std;

const int MAXSIZE = 100;
bool maze[MAXSIZE+2][MAXSIZE+2];
bool mark[MAXSIZE+1][MAXSIZE+1] = { 0 };


enum directions { N, NE, E, SE, S, SW, W, NW };
struct offsets {
    int a, b;
} movea[8] = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
struct Items {
    Items(int xx=0, int yy=0, int dd=0): x(xx), y(yy), dir(dd) {}
    int x, y, dir;
};
struct ItemsWithIdx {
    ItemsWithIdx(int x, int y, int idx) : x(x), y(y), idx(idx) {}
    int x, y, idx;
};

template<class T>
ostream& operator<<(ostream& os, stack<T>& s) {
    stack<T> temp;
    while(!s.empty()) {
        temp.push(s.top());
        s.pop();
    }
    while(!temp.empty()) {
        os << " -> " <<  temp.top();
        temp.pop();
    }
    return os;
}

ostream& operator<<(ostream& os, Items& items) {
    static int count = 0;
    os << "(" << items.x << "," << items.y << ")";
    count++;
    if((count % 5) == 0) cout << endl;
    return os;
}

ostream& operator<<(ostream& os, ItemsWithIdx& items) {
    static int count = 0;
    os << "(" << items.x << "," << items.y << ")";
    count++;
    if((count % 5) == 0) cout << endl;
    return os;
}

void Path(const int m, const int p) {
    mark[1][1] = 1;

    int nodes_visited = 0;
    stack<Items> stack;
    Items temp(1, 1, E);
    stack.push(temp);
    nodes_visited++;

    while (!stack.empty()) {
        temp = stack.top(); stack.pop();
        int i = temp.x; int j = temp.y; int d = temp.dir;
        while (d < 8) {
            int g = i + movea[d].a; int h = j + movea[d].b;
            if ((g == m) && (h == p)) {
                cout << stack;
                temp.x = i; temp.y = j;
                cout << " -> " << temp;
                temp.x = m; temp.y = p;
                cout << " -> " << temp << endl;
                cout << "#nodes visited = " << nodes_visited << " out of " << m*p << '\n';
                return;
            }
            if ((!maze[g][h]) && (!mark[g][h])) {
                mark[g][h] = 1;
                temp.x = i; temp.y = j; temp.dir = d + 1;
                stack.push(temp);
                nodes_visited++;
                i = g; j = h; d = N;
            }
            else d++;
        }
    }
    cout << "No path in maze." << endl;
}

void ShortestPath(const int m, const int p) {
    memset(mark, false, sizeof(mark));
    cout << '\n';
    
    vector<ItemsWithIdx> items;
    queue<ItemsWithIdx> que;

    int nodes_visited = 0;
    ItemsWithIdx item_now(1, 1, items.size());
    que.push(item_now);
    items.push_back(ItemsWithIdx(1, 1, -1));
    nodes_visited++;
    mark[1][1] = 1;

    int x_now, y_now, idx_now, next_x, next_y;
    while (!que.empty()) {
        item_now = que.front();
        que.pop();
        x_now = item_now.x; y_now = item_now.y; idx_now = item_now.idx;

        for (int i = 0; i < 8; i++) {
            next_x = x_now + movea[i].a;
            next_y = y_now + movea[i].b;
            if ((next_x == m) && (next_y == p)) {
                stack<ItemsWithIdx> trace;
                while (idx_now != -1) {
                    trace.push(items[idx_now]);
                    idx_now = items[idx_now].idx;
                }

                while (!trace.empty()) {
                    cout << " -> " << trace.top();
                    trace.pop();
                }
                cout << " -> " << "(" << next_x << "," << next_y << ")\n";
                cout << "#nodes visited = " << nodes_visited << " out of " << m*p << '\n';
                return;
            }
            if(1 > next_x || next_x > MAXSIZE || 1 > next_y || next_y > MAXSIZE) continue;
            if(maze[next_x][next_y] || mark[next_x][next_y]) continue;
            que.push(ItemsWithIdx(next_x, next_y, items.size()));
            items.push_back(ItemsWithIdx(next_x, next_y, idx_now));
            nodes_visited++;
            mark[next_x][next_y] = 1;
        }

    }
    cout << "No path in maze." << endl;
}


void getdata(istream& is, int& m, int& p) {
    is >> m >> p;
    for (int i = 0; i < m + 2; i++) { maze[i][0] = 1; maze[i][p+1] = 1; }
    for (int j = 1; j <= p; j++) { maze[0][j] = 1; maze[m+1][j] = 1; }
    for (int i = 1; i <=m; i++)
        for(int j = 1; j <= p; j++)
            is >> maze[i][j];
}
