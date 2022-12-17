//
// Created by Jinho on 12/14/2022.
//

#ifndef AVL_H
#define AVL_H
typedef struct Node* nodeptr;
#include <queue>
#include <iostream>
using namespace std;
struct Node {
    int data, height, balanceFactor;
    Node *leftChild, *rightChild;
    Node(int value);
};

class bstree {
public:
    void visit(Node* ptr);
    Node *insert(const int value, Node*& root);
    void show(Node* root);
    bool search(const int key, Node* root);
    Node *del(const int key, Node* root);
    void setBF(Node* startNode);
    void rotation(Node* start, Node* end);
    Node *rotation(Node* startNode, int value);
};

#endif //ALGORITHEM_AVL_H
