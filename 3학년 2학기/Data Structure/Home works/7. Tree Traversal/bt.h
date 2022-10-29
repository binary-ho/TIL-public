#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <queue>
#include <stack>
#include <cstring>

using namespace std;

template <class T> struct Node {
    Node(T d, Node<T> *left=0, Node<T> *right=0)
            : data(d), leftChild(left), rightChild(right) { }

    Node<T> *leftChild;
    T data;
    Node<T> *rightChild;
};

template <class T> class Tree {
public:
    bool check[100];
    Tree() { root = 0; } // empty tree
    void Insert(T &value) { Insert(root, value); }
    void Preorder() { Preorder(root); }
    void Inorder() { Inorder(root); }
    void Postorder() { Postorder(root); }
    void init() { memset(check, false, sizeof(check)); }
    void StackPreorder() {
        init();
        stack<Node<T>*> st;
        Node<T>* node_now = root;
        while(1) {
            while(node_now) {
                cout << node_now->data << " ";
                st.push(node_now);
                node_now = node_now->leftChild;
            }
            if(st.empty()) break;
            node_now = st.top();
            st.pop();
            node_now = node_now->rightChild;
        }
    }
    void StackPostorder() {
        init();
        stack<Node<T>*> st;
        Node<T>* node_now = root;
        while(1) {
            while(node_now) {
                st.push(node_now);
                node_now = node_now->leftChild;
            }
            if(st.empty()) break;
            node_now = st.top();
            st.pop();
            if (node_now->rightChild) {
                Node<T>* ptr = new Node<T>(node_now->data);
                st.push(ptr);
            } else {
                cout << node_now->data << " ";
            }
            node_now = node_now->rightChild;
        }
    }
    void Levelorder() {
        init();
        queue<Node<T>*> que;
        Node<T>* node_now = root;
        que.push(root);
        while(!que.empty()) {
            node_now = que.front();
            que.pop();
            cout << node_now->data << " ";
            if(node_now->leftChild) que.push(node_now->leftChild);
            if(node_now->rightChild) que.push(node_now->rightChild);
        }
    }

private:
    void Visit(Node<T> *);
    void Insert(Node<T>* &, T &);
    void Preorder(Node<T> *);
    void Inorder(Node<T> *);
    void Postorder(Node<T> *);

    Node<T> *root;
};

template <class T>
void Tree<T>::Visit(Node<T> *ptr) { cout << ptr->data << " "; }

template <class T>
void Tree<T>::Insert(Node<T>* &ptr, T &value) { //Insert 의 helper 함수
    if (ptr==0) ptr = new Node<T>(value);
    else if (value < ptr->data) Insert(ptr->leftChild, value);
    else if (value > ptr->data) Insert(ptr->rightChild, value);
    else cout << endl << "Duplicate value " << value << " ignored\n";
}
template <class T>
void Tree<T>::Preorder(Node<T> *node_now) {
    cout << node_now->data << " ";
    if (node_now->leftChild) Preorder(node_now->leftChild);
    if (node_now->rightChild) Preorder(node_now->rightChild);
}

template <class T>
void Tree<T>::Inorder(Node<T> *node_now) {
    if (node_now->leftChild) Inorder(node_now->leftChild);
    cout << node_now->data << " ";
    if (node_now->rightChild) Inorder(node_now->rightChild);
}

template <class T>
void Tree<T>::Postorder(Node<T> *node_now) {
    if (node_now->leftChild) Postorder(node_now->leftChild);
    if (node_now->rightChild) Postorder(node_now->rightChild);
    cout << node_now->data << " ";
}


#endif
