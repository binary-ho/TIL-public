#include <iostream>
#include <locale.h>
#include <stdlib.h>

#define INIT_STUDENT_NUM 10
#define FILE_NAME_STRING "hw1db.txt"

using namespace std;

void charPointerCopy(char *ori, char *target) {
    while ((*ori++ = *target++) != '\0');
}


bool compareToName(char *left, char *right) {
    int index = 0;
    while (index < 8) {
        if (left[index] == '\0') {
            return true;
        }

        if (right[index] == '\0') {
            return false;
        }

        if (left[index] > right[index]) {
            return true;
        } else if (left[index] < right[index]) {
            return false;
        }

        index++;
    }

    return false;
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

struct Student {
    int num;
    char name[10];
    int score;
};

class Students {

public:
    Students() {
        studentSize = INIT_STUDENT_NUM;
        maxSize = 2 * INIT_STUDENT_NUM;
        students = (Student *) malloc(maxSize * sizeof(Student));
        generateMockStudent(studentSize);
    }

    void insertRecord(int index, char *name, int score);
    void deleteByName(char *name);
    void listByName(char *name);

    void sortByName();
    void sortByScore();

    void readDB(char name[]);
    void writeDB(char name[]);

    void printStudentsInfo();

private:
    int maxSize;
    int studentSize;
    Student *students;

    void validateFileNotNull(FILE *file);
    void generateMockStudent(int studentCount);
    void resizeArrayDouble();
    int getRecordIndexByNameMatchFirst(char *name);
    Student parseStudentInfo(char *studentInfoString, int index);
};

void Students::resizeArrayDouble() {
    maxSize *= 2;
    Student *temp = (Student *) malloc(maxSize * sizeof(Student));
    for (int i = 0; i < studentSize; i++) {
        temp[i] = students[i];
    }
    students = temp;
}

void Students::insertRecord(int index, char *name, int score) {
    if (studentSize == maxSize) {
        resizeArrayDouble();
    }

    Student *temp = (Student *) malloc(maxSize * sizeof(Student));
    for (int i = index; i < studentSize; i++) {
        temp[i] = students[i];
    }

    students[index].num = index;
    charPointerCopy(students[index].name, name);
    students[index].score = score;

    for (int i = index; i < studentSize; i++) {
        students[i + 1] = temp[i];
        students[i + 1].num = i + 1;
    }
    studentSize++;
}

int Students::getRecordIndexByNameMatchFirst(char *name) {
    for (int index = 0; index < studentSize; index++) {
        if(!equals(students[index].name, name)) {
            continue;
        }
        return index;
    }
    printf("no user\n");
    return -1;
}

void Students::deleteByName(char *name) {
    int targetIndex = getRecordIndexByNameMatchFirst(name);
    if (targetIndex == -1) {
        return;
    }

    Student *temp = (Student *) malloc(maxSize * sizeof(Student));
    for (int i = targetIndex + 1; i < studentSize; i++) {
        temp[i] = students[i];
    }

    for (int i = targetIndex + 1; i < studentSize; i++) {
        students[i - 1] = temp[i];
        students[i - 1].num = i - 1;
    }
    studentSize--;
}

void Students::listByName(char *name) {
    int targetIndex = getRecordIndexByNameMatchFirst(name);
    if (targetIndex == -1) {
        return;
    }

    printf("%d,%s,%d\n", students[targetIndex].num, students[targetIndex].name, students[targetIndex].score);
}

void Students::validateFileNotNull(FILE *file) {
    if (file == NULL) {
        printf("file open error %s\n", "hw1db.txt");
        exit(-1);
    }
}

void Students::writeDB(char *name) {
    FILE *file = fopen(name, "wt");
    validateFileNotNull(file);

    for (int i = 0; i < studentSize; i++) {
        fprintf(file, "%d,%s,%d\n", students[i].num, students[i].name, students[i].score);
    }

    fclose(file);
}

Student Students::parseStudentInfo(char *studentInfoString, int index) {
    char buffer[20];
    int idx = 0;
    Student student = Student();
    student.num = index;
    bool findName = false;

    int i;
    for (i = 0; studentInfoString[i] != '\n'; i++) {
        if (!findName && studentInfoString[i] != ',') {
            continue;
        } else if (!findName) {
            findName = true;
        } else if (findName && studentInfoString[i] != ',') {
            buffer[idx++] = studentInfoString[i];
        } else {
            buffer[idx] = '\0';
            charPointerCopy(student.name, buffer);
            break;
        }
    }

    int score = 0;
    for (i++; studentInfoString[i] != '\n'; i++) {
        score *= 10;
        score += studentInfoString[i] - '0';
    }
    student.score = score;
    return student;
}


void Students::generateMockStudent(int studentCount) {

    int randNumTemp, lowerUpperTemp;
    char nameTemp[10];
    for (int i = 0; i < studentCount; i++) {
        randNumTemp = rand() % 8 + 1;
        // 아스키  65 ~ 90 A ~ Z
        // 아스키 97 ~ 122
        for (int j = 0; j < randNumTemp; j++) {
            lowerUpperTemp = rand() % 2;
            if (lowerUpperTemp == 0) {
                lowerUpperTemp = 65;
            } else {
                lowerUpperTemp = 97;
            }

            nameTemp[j] = rand() % 25 + lowerUpperTemp;
        }
        nameTemp[randNumTemp] = '\0';

        students[i].num = i;
        charPointerCopy(students[i].name, nameTemp);
        students[i].score = rand() % 100;
    }

    writeDB(FILE_NAME_STRING);
}

void Students::readDB(char *name) {
    FILE *file = fopen(name, "rt");
    validateFileNotNull(file);

    int index = 0;
    char currentLine[30];
    while (fgets(currentLine, sizeof(currentLine), file) != NULL) {
        students[index] = parseStudentInfo(currentLine, index);
        index++;
    }

    fclose(file);
}

void Students::sortByScore() {
    Student temp;
    for (int i = 1; i < studentSize; i++) {
        temp = students[i];

        int j = i - 1;
        for (; j >= 0; j--) {
            if (students[j].score > temp.score) {
                students[j + 1] = students[j];
                continue;
            }
            break;
        }
        students[j + 1] = temp;
    }
}

void Students::sortByName() {
    Student temp;
    for (int i = 1; i < studentSize; i++) {
        temp = students[i];

        int j = i - 1;
        for (; j >= 0; j--) {
            if (compareToName(students[j].name, temp.name)) {
                students[j + 1] = students[j];
                continue;
            }
            break;
        }
        students[j + 1] = temp;
    }
}

void Students::printStudentsInfo() {
    for (int i = 0; i < studentSize; i++) {
        printf("%d,%s,%d\n", students[i].num, students[i].name, students[i].score);
    }
    printf("\n");
}



int main() {
    Students students = Students();
    students.readDB(FILE_NAME_STRING);

    char command[20];
    int indexBuffer, scoreBuffer;
    char nameBuffer[20];

    while (1) {
        scanf("%s", &command);
        if (equals(command, "insert")) {
            scanf("%d %s %d", &indexBuffer, &nameBuffer, &scoreBuffer);
            students.insertRecord(indexBuffer, nameBuffer, scoreBuffer);
        } else if (equals(command, "delete")) {
            scanf("%s", &nameBuffer);
            students.deleteByName(nameBuffer);
        } else if (equals(command, "list ")) {
            scanf("%s", &nameBuffer);
            students.listByName(nameBuffer);
        } else if (equals(command, "sort name")) {
            students.sortByName();
        } else if (equals(command, "sort score")) {
            students.sortByScore();
        } else if (equals(command, "read")) {
            scanf("%s", &nameBuffer);
            students.readDB(nameBuffer);
        } else if (equals(command, "write")) {
            scanf("%s", &nameBuffer);
            students.writeDB(nameBuffer);
        } else if (equals(command, "print")) {
            students.printStudentsInfo();
        } else if (equals(command, "exit")) {
            break;
        } else {
            printf("there is no command like that\n");
        }
    }


//    students.printStudentsInfo();
//
//    students.sortByName();
//    students.printStudentsInfo();
//
//    students.sortByScore();
//    students.printStudentsInfo();

    /* insert, delete, list
    students.insertRecord(0, "oneone", 11);
    students.insertRecord(0, "twotwo", 12);
    students.insertRecord(0, "threethree", 13);
    students.printStudentsInfo();

    students.deleteByName("twotwo");
    students.printStudentsInfo();

    students.listByName("oneone"); */
}
