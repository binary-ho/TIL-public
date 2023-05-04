#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>

#define NODE_SIZE 100
using namespace std;

struct Node {
    int val = -1;
    Node *next;
} nodePool[NODE_SIZE];

struct List {
private:
    Node head = Node();
    int nodeCnt = 0;

public:
    int get(int _idx) {
        Node *ptr = &head;
        int idx = _idx;
        while(ptr->next && idx >= 0) {
            ptr = ptr->next;
            idx--;
        }

        if (idx > -1) {
            cout << "list is smaller than " << _idx << '\n';
            return -1;
        } else {
            return ptr->val;
        }
    }

    void push(int val) {
        Node *ptr = &head;
        while(ptr->next) {
            ptr = ptr->next;
        }
        nodePool[nodeCnt].val = val;
        ptr->next = &nodePool[nodeCnt++];
    }

    void print() {
        if (!head.next) {
            cout << "null list\n";
            return;
        }
        Node *ptr = &head;
        while(ptr->next) {
            ptr = ptr->next;
            cout << ptr->val << " ";
        }
        cout << '\n';
    }
} list;

void listTest() {

    cout << "================ list example ================\n";
    list.print();

    int temp;
    for (int i = 0; i < 10; i++) {
        temp = rand() % 100 + 1;
        cout << "list push number : " << temp << '\n';
        list.push(temp);
    }
    cout << "----------------------------------------------\n";
    for (int i = 0; i < 10; i++) {
        temp = rand() % 10;
        cout << "list get " << temp <<" node : " << list.get(temp) << '\n';
    }

    cout << "====== list print all ======\n";
    list.print();
    cout << "================ END ================\n\n\n";
}

void stackTest() {
    stack<int> st;
    cout << "================ stack example ================\n";
    int temp;
    for (int i = 0; i < 10; i++) {
        temp = rand() % 100 + 1;
        cout << "stack push number : " << temp << '\n';
        st.push(temp);
    }
    cout << "----------------------------------------------\n";
    while (!st.empty()) {
        cout << "stack pop number : " << st.top() << '\n';
        st.pop();
    }
    cout << "================ END ================\n\n\n";
}

void queueTest() {
    queue<int> que;
    cout << "================ queue example ================\n";
    int temp;
    for (int i = 0; i < 10; i++) {
        temp = rand() % 100 + 1;
        cout << "queue push number : " << temp << '\n';
        que.push(temp);
    }
    cout << "----------------------------------------------\n";
    while (!que.empty()) {
        cout << "queue pop number : " << que.front() << '\n';
        que.pop();
    }
    cout << "================ END ================\n\n\n";
}

void priorityQueueTest() {
    priority_queue<int> que;
    cout << "================ priority queue example ================\n";
    int temp;
    for (int i = 0; i < 10; i++) {
        temp = rand() % 100 + 1;
        cout << "priority queue push number : " << temp << '\n';
        que.push(temp);
    }
    cout << "----------------------------------------------\n";
    while (!que.empty()) {
        cout << "priority queue pop number : " << que.top() << '\n';
        que.pop();
    }
    cout << "================ END ================\n\n\n";
}

struct TreeNode {
    int val = -1;
    TreeNode *left = nullptr, *right = nullptr;
} treeNodePool[100];

struct BST {
private:
    TreeNode root = TreeNode();
    int size = 0, idx;
    int treeNodeCnt = 0;

    void search(TreeNode *node) {
        if (size < idx) {
            return;
        }

        if (node->left != nullptr) search(node->left);

//        if (node->val != -1) {
            cout << "idx : " << idx++ << ", val : " << node->val << '\n';
//        }

        if (node->right != nullptr) search(node->right);
    }

public:
    void push(int val) {
        size++;
        TreeNode *ptr = &root;
        while (1) {
            if (ptr->val > val) {
                if (ptr->left) {
                    ptr = ptr->left;
                } else {
                    treeNodePool[treeNodeCnt].val = val;
                    ptr->left = &treeNodePool[treeNodeCnt++];
                    return;
                }
            } else {
                if (ptr->right) {
                    ptr = ptr->right;
                } else {
                    treeNodePool[treeNodeCnt].val = val;
                    ptr->right = &treeNodePool[treeNodeCnt++];
                    return;
                }
            }
        }
    }

    void search() {
        idx = 0;
        if (root.right) {
            search(root.right);
            return;
        }
        cout << "null search tree\n";
    }
} bst;

void binarySearchTreeExample() {
    cout << "================ binary search tree example ================\n";
    bst.search();
    int temp;
    for (int i = 0; i < 10; i++) {
        temp = rand() % 100 + 1;
        cout << "binary search tree push number : " << temp << '\n';
        bst.push(temp);
    }
    cout << "====== binary search tree inorder search! ======\n";
    bst.search();
    cout << "================ END ================\n\n\n";
}

int board[5][5] = {
        {0, 1, 0,0,0},
        {0, 1, 0,1,0},
        {0, 1, 0,1,0},
        {0, 1, 0,1,0},
        {0, 0, 0,1,0},
};
int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, 1, -1};

void graphExample() {
    cout << "================ graph example - bfs maze ================\n";
    cout << "======== MAZE ========\n";

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << board[i][j] << " ";
        }
        cout << '\n';
    }

    bool check[5][5];
    memset(check, false, sizeof (check));
    queue<pair<pair<int, int>, int>> que;

    pair<int, int> start = {0, 0};
    pair<int, int> end = {4, 4};

    que.push({start, 0});
    check[start.first][start.second] = true;

    pair<int, int> nodeNow, nextNode;
    int distNow;
    while (!que.empty()) {
        nodeNow = que.front().first;
        distNow = que.front().second;
        que.pop();

        if (nextNode.first == end.first && nextNode.second == end.second) {
            cout << "arrived! " << end.first << ", " << end.second << " -> dist : " << distNow << '\n';
            cout << "================ END ================\n";
            return;
        }

        for (int i = 0; i < 4; i++) {
            nextNode.first = nodeNow.first + dy[i];
            nextNode.second = nodeNow.second + dx[i];

            if (0 > nextNode.first || nextNode.first >= 5
                || 0 > nextNode.second || nextNode.second >= 5) continue;
            if (check[nextNode.first][nextNode.second]) continue;
            cout << nodeNow.first << ", " << nodeNow.second << ", dist : " << distNow << " -> " << distNow + 1 << '\n';
            check[nextNode.first][nextNode.second] = true;
            que.push({nextNode, distNow + 1});
        }
    }

    cout << "can't reach to destination!\n";
    cout << "================ END ================\n";
}

int main() {
    srand((unsigned int) (time(0)));
    listTest();
    stackTest();
    queueTest();
    priorityQueueTest();
    binarySearchTreeExample();
    graphExample();
}
