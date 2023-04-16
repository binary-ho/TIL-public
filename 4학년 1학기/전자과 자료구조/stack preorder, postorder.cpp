#include <iostream>
#include <stack>

using namespace std;

struct TreeNode {
    int val = -1;
    TreeNode *leftChild = nullptr, *rightChild = nullptr;
};

TreeNode *root;
TreeNode nodePool[10];

void initTree() {

    int idx = 1;
    TreeNode *rootNode = &nodePool[idx];
    rootNode->val = idx;
    root = rootNode;

    while (idx < 4) {
        TreeNode *leftChild = &nodePool[idx*2];
        TreeNode *rightChild = &nodePool[idx*2 + 1];
        leftChild->val = idx*2;
        rightChild->val = idx*2 + 1;

        nodePool[idx].leftChild = leftChild;
        nodePool[idx].rightChild = rightChild;
        idx++;
    }
}

// root을 1등으로, 꼴지로
void traversalPreOrder() {
    printf("========== traversalPreOrder ==========\n");
    stack<TreeNode*> st;
    TreeNode *nodeNow = root;
    while (1) {
        while (nodeNow != nullptr) {
            printf("PreOrder val : %d\n", nodeNow->val);
            st.push(nodeNow);
            nodeNow = nodeNow->leftChild;
        }
        if (st.empty()) {
            break;
        }
        nodeNow = st.top();
        st.pop();
        nodeNow = nodeNow->rightChild;
    }
    printf("\n");
}

void traversalPostOrder() {
    printf("========== traversalPostOrder ==========\n");
    stack<TreeNode*> st;
    TreeNode *nodeNow = root;
    while (1) {
        while (nodeNow) {
            st.push(nodeNow);
            // 왼쪽 자식을 전부 넣어 준다.
            nodeNow = nodeNow->leftChild;
        }
        if (st.empty()) {
            break;
        }

        nodeNow = st.top();
        st.pop();
        if (nodeNow != nullptr && nodeNow->rightChild != nullptr) {
            // 오른쪽 자식이 있다면 일단 현재 노드 데이터를 스택에 넣는다.
            TreeNode *mockNode = new TreeNode();
            mockNode->val = nodeNow->val;
            st.push(mockNode);
        } else {
            printf("PostOrder val : %d\n", nodeNow->val);
        }
        nodeNow = nodeNow->rightChild;
    }
    printf("\n");
}

int main() {

    // PreOrder PostOrder 테스트
    initTree();
    traversalPreOrder();
    traversalPostOrder();
}
