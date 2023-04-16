#include<iostream>
#include"list.h"
using namespace std;

int main() {
    IntList il;
    int input;

    cout<<"==============Input============="<<endl;

    while(1) {//-1 을 받을 때 까지 반복
        cin>>input;
        if(input==-1) break;
        il.Insert(input);
        cout<<il;
    }
    cout<<"=============Delete============="<<endl;

    input=0;
    while(1) {//-1 을 받을 때 까지 반복
        cin>>input;
        if(input==-1) break;
        il.Delete(input);
        cout                        << il;
    }

    cout<<"===========Push_Front==========="<<endl;
    cin>>input; il.Push_Front(input); cout<<il;
    cin>>input; il.Push_Front(input); cout<<il;
    cout<<"===========Push_Back============"<<endl;
    cin>>input; il.Push_Back(input);cout << il;
    cin>>input; il.Push_Back(input);cout << il;
    return 0;
}
