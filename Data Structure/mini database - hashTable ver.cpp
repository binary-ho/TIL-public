//
// Created by Jinho on 2023-05-13.
//

#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <queue>
#include <list>
#include <cstring>
#include <locale.h>
#include <stdlib.h>
#include <algorithm>


#define INIT_STUDENT_NUM 10
#define BUCKET_COUNT 1 << 10
#define DIV (BUCKET_COUNT - 1)
#define MAX_ARRAY_NUMBER 100
using namespace std;

class Student {
public:
    string name;
    int score;
    Student *next;
    Student() {
        name = "head";
        score = -1;
        next = nullptr;
    }

    Student(string _name, int _score) {
        name = _name;
        score = _score;
        next = nullptr;
    }
};

class Students {
public:
    Students() {
        initBucket();
    }

    void insertRecord(string &name, int score);
    void deleteByName(string &name);
    void listByName(string &name);
    void printStudentsInfo();

private:
    int studentSize;
    Student hashTable[BUCKET_COUNT];

    void generateMockStudent(int studentCount);
    Student *findPrevStudent(string &name);
    int getKey(string &name);
    void initBucket();
};

void Students::initBucket() {
    studentSize = 0;
    for (int i = 0; i < BUCKET_COUNT; i++) {
        hashTable[i].next = nullptr;
    }
    generateMockStudent(INIT_STUDENT_NUM);
}

void Students::insertRecord(string &name, int score) {
    Student *newStudent = new Student(name, score);
    int key = getKey(name);
    Student *ptr = &hashTable[key];
    while (ptr->next) {
        ptr = ptr->next;
    }
    ptr->next = newStudent;
    studentSize++;
}

void Students::deleteByName(string &name) {
    Student *ptr = findPrevStudent(name);
    if (ptr->next == nullptr) {
        cout << "there is no user name '" << name << "'\n";
        return;
    }

    cout << "delete user name : " << ptr->next->name << ", score : " << ptr->next->score << '\n';
    ptr->next = ptr->next->next;
    studentSize--;
}

void Students::listByName(string &name) {
    Student* ptr;
    ptr = findPrevStudent(name);
    if (ptr->next == nullptr) {
        cout << "there is no user name '" << name << "'\n";
        return;
    }

    cout << "find user name : " << ptr->next->name << ", score : " << ptr->next->score << '\n';
}

void Students::generateMockStudent(int studentCount) {

    int randNumTemp;
    string nameTemp;
    for (int i = 0; i < studentCount; i++) {
        randNumTemp = rand() % 8 + 1;
        nameTemp = "";
        // 아스키 97 ~ 122
        for (int j = 0; j < randNumTemp; j++) {
            nameTemp += rand() % 25 + 97;
        }
        insertRecord(nameTemp, rand() % 100);
    }
}

void Students::printStudentsInfo() {

    cout << "============ student count is " << studentSize << "]! print student info ============" << '\n';
    Student *ptr;
    int cnt = 1;
    for (int i = 0; i < BUCKET_COUNT; i++) {
        if (!hashTable[i].next) continue;
        ptr = hashTable[i].next;
        while (ptr) {
            cout << cnt++ << ". name : " << ptr->name << ", score : " << ptr->score << '\n';
            ptr = ptr->next;
        }
    }
}

int Students::getKey(string &name) {
    long long key = 5381;
    for (char ch : name) {
        key = ((key * 26) + key) + ch - 'a' + 1;
    }
    return (int) (key & DIV);
}

Student *Students::findPrevStudent(string &name) {
    int key = getKey(name);
    Student *ptr = &hashTable[key];
    while (ptr->next) {
        if (ptr->next->name == name) {
            return ptr;
        }
        ptr = ptr->next;
    }
    return ptr;
}

int main() {
    srand((unsigned int) (time(0)));
    string command;
    int scoreBuffer;
    string nameBuffer;

    string insert = "insert";
    string listName = "listName";
    string deleteByName = "delete";
    string print = "print";
    string exit = "exit";
    Students students = Students();

    while (1) {
        command = "";
        cin >> command;
        cout << command << '\n';
        if (command == insert) {
            cin >> nameBuffer >> scoreBuffer;
            students.insertRecord(nameBuffer, scoreBuffer);
        } else if (command == listName) {
            cin >> nameBuffer;
            students.listByName(nameBuffer);
        } else if (command == deleteByName) {
            cin >> nameBuffer;
            students.deleteByName(nameBuffer);
        } else if (command == print) {
            students.printStudentsInfo();
        } else if (command == exit) {
            break;
        } else {
            printf("there is no command like that\n");
        }
    }
}
