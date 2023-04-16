#include <iostream>
#include "list.h"

ostream& operator<<(ostream& os, IntList& il) {
    Node *ptr = il.first;
    while (ptr != NULL) {
        os << ptr->data << " "; ptr = ptr->link;
    }
    os << endl;
    return os;
}

void IntList::Push_Back(int e) {
    if (!first)
        first = last = new Node(e);
    else {
        last->link = new Node(e);
        last = last->link;
    }
}
void IntList::Push_Front(int e) {
    if (!first) {
        first = last = new Node(e);
    } else {
        Node* new_first = new Node(e);
        new_first->link = first;
        first = new_first;
    }
}
void IntList::Insert(int e) {
    if (!first) {
        first = last = new Node(e);
    }
    else if (first->data >= e){
	 Push_Front(e);
    }
    else{
        Node *ptr = first;
        
	while (ptr->link != NULL && ptr->link->data < e) { 
		ptr = ptr->link;
	}
	
        if (ptr->link != NULL) {
            Node *new_node = new Node(e);
            new_node->link = ptr->link;
            ptr->link = new_node;
        } else Push_Back(e);
    }
}

void IntList::Delete(int e) {
    if(first){
        if(first->data == e) {
            first = first->link;
        } else{
            Node *ptr = first;
            while (ptr-> link != NULL &&  ptr->link->data != e) ptr = ptr->link;
            if(ptr->link != NULL) {
		if (ptr->link == last) last = ptr;
		ptr->link = ptr->link->link; 
            }
        }
    }
}
