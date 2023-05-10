#include <iostream>
#include <queue>

using namespace std;

void charPointerCopy(char *ori, char *target) {
    while ((*ori++ = *target++) != '\0');
}

// 원본이 더 크면 1 작으면 -1
int compareByName(char *ori, char *target) {
    int index = 0;
    while (index < 9) {
        if (ori[index] == '\0' && target[index] == '\0') {
            return 0;
        }

        if (ori[index] == '\0') {
            return 1;
        }

        if (target[index] == '\0') {
            return -1;
        }

        if (ori[index] > target[index]) {
            return 1;
        } else if (ori[index] < target[index]) {
            return -1;
        }

        index++;
    }
    return 0;
}

bool equals(char *left, char *right) {
    int index = 0;
    while (index < 9) {
        if (left[index] == '\0' && right[index] == '\0') {
            return true;
        } else if (left[index] == '\0' || right[index] == '\0') {
            return false;
        } else if (left[index] != right[index]) {
            return false;
        }
        index++;
    }
    return false;
}

class Student {
public:
    char name[10];
    int score;
    Student *leftChild, *rightChild;

    Student(char *_name, int _score) {
        charPointerCopy(name, _name);
        score = _score;
        leftChild = rightChild = NULL;
    }
};

class Students {

public:
    Students(Student *student) {
        studentSize = 1;
        root = student;
        generateMockStudent(10);
    }

    void insertRecord(char *name, int score);
    void listByName(char *name);

    void sortByNameWithInOrder();
    void sortByScoreWithPriorityQueue();

private:
    int studentSize;
    Student *root;

    void generateMockStudent(int studentCount);
    void inOrderSearch(Student *studentNow);
    void inOrderSearch(Student *studentNow, char *name);
    void inOrderSearch(Student *studentNow, int target);
    Student *findParentsByName(char *name);

    void pushToPriorityQueue(Student *studentNow);
};

Student *Students::findParentsByName(char *name) {
    Student *ptr = root;

    int temp;
    while (1) {
        temp = compareByName(ptr->name, name);
        if (temp >= 0 && ptr->leftChild != NULL) {
            ptr = ptr->leftChild;
        } else if (temp < 0 && ptr->rightChild != NULL) {
            ptr = ptr->rightChild;
        } else {
            return ptr;
        }
    }
};

void Students::insertRecord(char *name, int score) {

    Student *student = new Student(name, score);
    Student *ptr = findParentsByName(name);

    if (compareByName(ptr->name, name) >= 0) {
        ptr->leftChild = student;
    } else {
        ptr->rightChild = student;
    }
    studentSize++;
}

int idx;
int findIdx;
void Students::inOrderSearch(Student *studentNow, char *name) {
    if (studentSize < idx) {
        findIdx = -1;
        return;
    }

    if (studentNow->leftChild) inOrderSearch(studentNow->leftChild, name);
    if (compareByName(studentNow->name, name) != 0) {
        idx++;
    } else {
        findIdx = idx;
    }
    if (studentNow->rightChild) inOrderSearch(studentNow->rightChild, name);

    return;
}

Student findStudent = Student("", -1);
void Students::inOrderSearch(Student *studentNow, int target) {
    if (studentSize < idx) {
        return;
    }
    if (studentNow->leftChild) inOrderSearch(studentNow->leftChild, target);
    if (idx == target) {
        findStudent = Student(studentNow->name, studentNow->score);
        return;
    } else {
        idx++;
    }
    if (studentNow->rightChild) inOrderSearch(studentNow->rightChild, target);
}

void Students::inOrderSearch(Student *studentNow) {
    if (studentSize < idx) {
        return;
    }

    if (studentNow->leftChild != NULL) inOrderSearch(studentNow->leftChild);
    cout << "idx : " << idx++ << " -> name : " << studentNow->name << ", score : " << studentNow->score << '\n';
    if (studentNow->rightChild != NULL) inOrderSearch(studentNow->rightChild);
}

void Students::listByName(char *name) {
    idx = 1;
    inOrderSearch(root, name);
    if (findIdx == -1) {
        cout << "no user error\n";
        return;
    }

    idx = 1;
    inOrderSearch(root, findIdx);

    if (findStudent.score == -1 || !equals(findStudent.name, name)) {
        cout << "no user error\n";
        return;
    }

    printf("index : %d -> name : %s, score : %d\n", findIdx, findStudent.name, findStudent.score);
}

void Students::sortByNameWithInOrder() {
    idx = 1;
    inOrderSearch(root);
    return;
}

auto compare = [](Student s1, Student s2) { return s1.score > s2.score; };
priority_queue<Student, vector<Student>, decltype(compare)> que(compare);

void Students::pushToPriorityQueue(Student *studentNow) {
    if (studentSize < idx) {
        return;
    }

    if (studentNow->leftChild) pushToPriorityQueue(studentNow->leftChild);
    que.push(Student(studentNow->name, studentNow->score));
    idx++;
    if (studentNow->rightChild) pushToPriorityQueue(studentNow->rightChild);
}

void Students::sortByScoreWithPriorityQueue() {
    idx = 1;
    pushToPriorityQueue(root);

    idx = 1;
    while (!que.empty()) {
        printf("%d -> name : %s, score : %d\n", idx++, que.top().name, que.top().score);
        que.pop();
    }
}

void Students::generateMockStudent(int studentCount) {

    int randNumTemp, lowerUpperTemp;
    char nameTemp[10];
    for (int i = 0; i < studentCount; i++) {
        randNumTemp = rand() % 8 + 1;
        // 아스키 a ~ z -> 97 ~ 122
        lowerUpperTemp = 97;
        for (int j = 0; j < randNumTemp; j++) {

            nameTemp[j] = rand() % 25 + lowerUpperTemp;
        }
        nameTemp[randNumTemp] = '\0';

        insertRecord(nameTemp, rand()%100);
    }
}

int main() {

    char command[20];
    int scoreBuffer;
    char nameBuffer[20] = "jinho";
    char insert[20] = "insert";
    char list[20] = "list";
    char sortName[20] = "sort1";
    char sortScore[20] = "sort2";
    char print[20] = "print";
    char exit[20] = "exit";
    Students students = Students(new Student(nameBuffer, 100));

    while (1) {
        scanf("%s", &command);
        printf("%s\n", command);
        if (equals(command, insert)) {
            scanf("%s %d", &nameBuffer, &scoreBuffer);
            students.insertRecord(nameBuffer, scoreBuffer);
        } else if (equals(command, list)) {
            scanf("%s", &nameBuffer);
            students.listByName(nameBuffer);
        } else if (equals(command, sortName)) {
            students.sortByNameWithInOrder();
        } else if (equals(command, sortScore)) {
            students.sortByScoreWithPriorityQueue();
        } else if (equals(command, print)) {
            students.sortByNameWithInOrder();
        } else if (equals(command, exit)) {
            break;
        } else {
            printf("there is no command like that\n");
        }
    }
}
