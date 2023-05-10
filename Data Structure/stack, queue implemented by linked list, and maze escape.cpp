#include <iostream>
#include <stack>

#define NODE_CNT 10000
using namespace std;

int maze[6][6] = {
        {0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0},
        {0, 1, 0, 1, 0, 0},
        {0, 0, 0, 1, 1, 1},
        {0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0},
};
int dy[4] = {0, 0, -1, 1};
int dx[4] = {1, -1, 0, 0};

// Stack
struct StackNode {
    int val = -1;
    StackNode *next = nullptr;
};

int sNodeCnt;
StackNode sNodePool[NODE_CNT];

StackNode *getStackNode(int val) {
    sNodePool[sNodeCnt].val = val;
    return &sNodePool[sNodeCnt++];
}

// top의 바로 뒤에 계속 붙이자
struct Stack {
private:
    StackNode topNode;
    int stackSize;

public:
    Stack() {
        stackSize = 0;
        topNode.val = -1;
        topNode.next = nullptr;
    }

    int top() {
        if (stackSize == 0) {
            printf("[ERROR] : stack is empty!\n");
            return -1;
        }
        return topNode.next->val;
    }

    void push(int val) {
        StackNode *newNode = getStackNode(val);
        if (topNode.next == nullptr) {
            topNode.next = newNode;
            newNode->next = nullptr;
        } else {
            newNode->next = topNode.next;
            topNode.next = newNode;
        }
        stackSize++;
    }

    void pop() {
        if (stackSize == 0) {
            printf("[ERROR] : stack is empty!\n");
            return;
        }

        if (topNode.next->next == nullptr) {
            topNode.next = nullptr;
        } else {
            topNode.next = topNode.next->next;
        }
        stackSize--;
    }

    int size() {
        return stackSize;
    }
};

// Queue
struct QueueNode {
    int val = -1;
    QueueNode *next = nullptr,  *prev = nullptr;
};

int qNodeCnt;
QueueNode qNodePool[NODE_CNT];

QueueNode *getQueueNode(int val) {
    qNodePool[qNodeCnt].val = val;
    return &qNodePool[qNodeCnt++];
}

struct Queue {
private:
    QueueNode head, tail;
    int qSize;

public:
    Queue() {
        qNodeCnt = qSize = 0;
        head.val = tail.val = -1;
        head.next = &tail;
        tail.prev = &head;
        tail.next = head.prev = nullptr;
    }

    // head next next tail
    int front() {
        if (qSize != 0 && tail.prev != &head) {
            return tail.prev->val;
        }
        printf("[ERROR] : queue is empty!\n");
        return -1;
    }

    void push(int val) {
        QueueNode *newNode = getQueueNode(val);
        newNode->next = head.next;
        newNode->next->prev = newNode;
        head.next = newNode;
        newNode->prev = &head;

        qSize++;
    }

    void pop() {
        if (qSize == 0 || tail.prev == &head) {
            printf("[ERROR] : queue is empty!\n");
            return;
        }

        tail.prev->prev->next = &tail;
        tail.prev = tail.prev->prev;
        qSize--;
    }

    int size() {
        return qSize;
    }
};

// 미로 탈출
bool check[36];
void escapeMaze(int start, int end) {

    Stack stack = Stack();
    stack.push(start);
    check[start] = true;
    while (stack.size() > 0) {
        int top = stack.top();
        stack.pop();

        check[top] = true;
        if (top == end) {
            printf("find {%d, %d}! -> escape!\n", top / 6, top % 6);
            return;
        }

        int yNow = top / 6;
        int xNow = top % 6;
        printf("node now : {%d, %d}\n", yNow, xNow);

        for (int i = 0; i < 4; i++) {
            int nextY = yNow + dy[i];
            int nextX = xNow + dx[i];

            if (0 > nextY || nextY > 5) continue;
            if (0 > nextX || nextX > 5) continue;
            if (check[nextY * 6 + nextX] || maze[nextY][nextX] == 0) continue;

            stack.push(nextY * 6 + nextX);
        }
    }
}

int main() {

    
    Stack stack = Stack();
    Queue queue = Queue();

    for (int i = 1; i <= 5; i++) {
        stack.push(i);
        queue.push(i);
    }

    printf("stack size : %d\n", stack.size());
    for (int i = 1; i<= 6; i++) {
        int top = stack.top();
        if (top != -1) {
            printf("stack top : %d\n", top);
        }

        stack.pop();
    }
    printf("stack size : %d\n", stack.size());

    printf("queue size : %d\n", queue.size());
    for (int i = 1; i<= 6; i++) {
        int front = queue.front();
        if (front != -1) {
            printf("queue front : %d\n", front);
        }
        queue.pop();
    }
    printf("queue size : %d\n", queue.size()); 

    // 미로 탈출 예제
    pair<int, int> start = {1, 0}, end = {3, 5};
    escapeMaze(start.first * 6 + start.second, end.first * 6 + end.second); 
}
