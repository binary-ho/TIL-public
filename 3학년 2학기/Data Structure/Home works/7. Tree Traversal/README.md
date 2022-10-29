# 7. Tree Traversal
트리 순회를 처리하는 bt.h 헤더파일을 완성하시오
## 1. 재귀를 하는 Preorder, Inorder, Postorder 만들기
```cpp
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
```

## 2. 재귀 없이 스택을 이용하여 트리를 순회하는 StackPreorder, StackPostorder, Levelorder 완성하기
StackPostorder가 은근히 어렵게 느껴졌다. <br> 
왼쪽 노드를 방문한 다음 오른쪽 노드를 방문해야 하는데, 
스택에 넣어주다 보니 왼쪽 노드를 방문한 다음 오른쪽 노드를 방문하기 전에 중앙 노드를 방문해버린다. <br>
제출 시간이 임박하기도 해서 간단하게 자식 노드들을 모두 제거한 버전의 중앙 노드를 다시 넣어줬다. <br> 
이렇게 구현하면 스택의 작동상 "자식 노드가 없는 경우 출력하라"를 통해 왼쪽 자식, 오른쪽 자식, 자기 자신 순서로 방문할 수가 있었다. 
```cpp
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
```
