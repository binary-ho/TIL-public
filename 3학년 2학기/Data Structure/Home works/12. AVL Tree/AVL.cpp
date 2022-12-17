//
// Created by Jinho on 12/14/2022.
//
#include "AVL.h"

Node::Node(int value) {
    data = value;
    leftChild = rightChild = NULL;
    height = 1;
    balanceFactor = 0;
}

void bstree::visit(Node* ptr) {
    cout << ptr->data << "\t";
    if (ptr->leftChild) cout << "left : " << ptr->leftChild->data << '\t';
    else cout << "left : empty\t";
    if (ptr->rightChild) cout << "right : " << ptr->rightChild->data << '\t';
    else cout << "right : empty\t";
    cout << '\n';
}

void bstree::show(Node* root) {
    cout << '\n';
    queue<Node*> bfsQueue;
    bfsQueue.push(root);
    Node *nodeNow;
    while (!bfsQueue.empty()) {
        nodeNow = bfsQueue.front();
        bfsQueue.pop();
        visit(nodeNow);
        if (nodeNow->leftChild) bfsQueue.push(nodeNow->leftChild);
        if (nodeNow->rightChild) bfsQueue.push(nodeNow->rightChild);
    }
}

Node *bstree::insert(const int value, Node *&nodeNow) {
    if (!nodeNow) return nodeNow = new Node(value);
    if (value == nodeNow->data) return nodeNow;
    if (value < nodeNow->data) nodeNow->leftChild = insert(value, nodeNow->leftChild);
    if (value > nodeNow->data) nodeNow->rightChild = insert(value, nodeNow->rightChild);

    setBF(nodeNow);
    if (nodeNow->balanceFactor < -1 || nodeNow->balanceFactor > 1) return rotation(nodeNow, value);
    return nodeNow;
}

bool bstree::search(const int key, Node* root) {
    cout << root->data;

    if (root->data == key) {
        cout << '\n';
        return true;
    }

    cout << " -> ";

    Node *nodeNext = key <= root->data ? root->leftChild : root->rightChild;
    if (!nodeNext) {
        cout << " X (there is no nodes that has value " << key << ") \n";
        return false;
    }

    return search(key, nodeNext);
}

Node *bstree::del(const int key, Node* nodeNow) {
    if (!nodeNow) return nodeNow;
    if (key < nodeNow->data) nodeNow->leftChild = del(key, nodeNow->leftChild);
    else if (key > nodeNow->data) nodeNow->rightChild = del(key, nodeNow->rightChild);
    else {
        // find the node
        if (!nodeNow->leftChild && !nodeNow->rightChild) nodeNow = NULL;
        else if (!nodeNow->leftChild) nodeNow = nodeNow->rightChild;
        else if (!nodeNow->rightChild) nodeNow = nodeNow->leftChild;
        else {
            Node *ptr = nodeNow->leftChild;
            while (ptr->rightChild) {
                ptr = ptr->rightChild;
            }
            nodeNow->data = ptr->data;
            del(nodeNow->data, nodeNow->leftChild);
        }
    }
    if (!nodeNow) return nodeNow;

    setBF(nodeNow);
    if (nodeNow->balanceFactor < -1 || nodeNow->balanceFactor > 1) return rotation(nodeNow, key);
    return nodeNow;
}

void bstree::setBF(Node* startNode) {
    int leftHeight, rightHeight;
    leftHeight = startNode->leftChild ? startNode->leftChild->height : 0;
    rightHeight = startNode->rightChild ? startNode->rightChild->height : 0;
    startNode->height = leftHeight < rightHeight ? rightHeight + 1 : leftHeight + 1;
    startNode->balanceFactor = leftHeight - rightHeight;
}

Node *bstree::rotation(Node* startNode, int value) {
    // 1. LL rotation
    Node *tempNode;
    if (startNode->leftChild && value <= startNode->leftChild->data) {
        tempNode = startNode->leftChild;
        rotation(startNode, startNode->leftChild);
        return tempNode;
    }

    // 2. RR rotation
    if (startNode->rightChild && startNode->rightChild->data < value) {
        tempNode = startNode->rightChild;
        rotation(startNode, startNode->rightChild);
        return tempNode;
    }

    // 3. LR rotation
    if (value <= startNode->data) {
        tempNode = startNode->leftChild->rightChild;
        rotation(startNode->leftChild, startNode->leftChild->rightChild);
        rotation(startNode, startNode->leftChild);
    }

    // 4. RL rotation
    if (startNode->data < value) {
        tempNode = startNode->rightChild->leftChild;
        rotation(startNode->rightChild, startNode->rightChild->leftChild);
        rotation(startNode, startNode->rightChild);
    }
    return tempNode;
}

void bstree::rotation(Node* start, Node* end) {
    if (start->leftChild == end) {
        start->leftChild = end->rightChild;
        end->rightChild = start;
    } else {
        start->rightChild = end->leftChild;
        end->leftChild = start;
    }
}
