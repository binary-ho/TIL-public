#include <iostream>
#include <locale.h>
#include <stdlib.h>

#define INIT_STUDENT_NUM 10
#define FILE_NAME_STRING "hw1db.txt"

using namespace std;

struct Student {
    int num;
    char name[10];
    int score;
};

// 2. DB는 파일에 저 장 되 어 있고, 검색/삽입/삭제/소팅 등의 동작을 수행할 수있다.
// 인 터 페 이 스 명 령 어 는
// 1) insert num name height score : 번호의 위치에 해당 레 코 드 를 삽입
// 2) delete name : 입력 이름에 해 당 하 는 레 코 드 를 삭제
// 3) list name : 입력 이름에 해 당 하 는 레 코 드의 기록을 보여줌
// 4) sort name : 이름순으로 정렬
// 5) sort score : 성적순으로 정렬
// 6) read DB이름 : 해당 파일을 read목적으로 open 하고 data를 메모리로 읽음
// 7) write DB이름 : 해당 파일을 write목적으로 open 하고 파일에 내용을 적음.

class Students {

public:
    Students() {
        studentSize = INIT_STUDENT_NUM;
        students = (Student *) malloc(studentSize * sizeof(Student));
        generateMockStudent(studentSize);
    }

    void readDB(char name[]);
    void writeDB(char name[]);
    void insertSortByScore();
    void insertSortByName();
    void printStudentsInfo();

private:
    int studentSize;
    Student *students;

    void validateFileNotNull(FILE *file);

    void generateMockStudent(int studentCount);
};

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

void charPointerCopy(char *ori, char *target) {
    while ((*ori++ = *target++) != '\0');
}

Student parseStudentInfo(char *studentInfoString, int index) {
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

        students[i].num = i + 1;
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
        students[index] = parseStudentInfo(currentLine, index + 1);
        printf("%d %s %d\n", students[index].num, students[index].name, students[index].score);
        index++;
    }

    fclose(file);
}

void Students::insertSortByScore() {
    Student temp;
    for (int i = 1; i < studentSize; i++) {
        temp = students[i];
        for (int j = i - 1; j >= 0; j--) {
            if (students[j].score > temp.score) {
                students[j + 1] = students[j];
                continue;
            }
            students[j + 1] = temp;
            break;
        }
    }

    for (int i = 0; i < studentSize; i++) {
        printf("%d,%s,%d\n", students[i].num, students[i].name, students[i].score);
    }
}

// 왼쪽이 더 크면 true
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

void Students::insertSortByName() {
    Student temp;
    for (int i = 1; i < studentSize; i++) {
        temp = students[i];
        for (int j = i - 1; j >= 0; j--) {
            if (compareToName(students[j].name, temp.name)) {
                students[j + 1] = students[j];
                continue;
            }
            students[j + 1] = temp;
            break;
        }
    }

    for (int i = 0; i < studentSize; i++) {
        printf("%d,%s,%d\n", students[i].num, students[i].name, students[i].score);
    }
}

void Students::printStudentsInfo() {
    for (int i = 0; i < studentSize; i++) {
        printf("%d,%s,%d\n", students[i].num, students[i].name, students[i].score);
    }
}



int main() {
//    setlocale(LC_ALL, "");

//    FILE *file;
//    file = fopen("hw1db.txt", "wt");
//    if (file == NULL) {
//        printf("file open error %s\n", "hw1db.txt");
//        exit(-1);
//    }
//    Student *student = new Student({
//            1, "jinho", 00
//    });
//
//    fprintf(file, "%s %d", student->name, student->score);
//    fclose(file);

    Students students = Students();
    students.readDB(FILE_NAME_STRING);
    students.readDB(FILE_NAME_STRING);
    students.printStudentsInfo();
    students.readDB(FILE_NAME_STRING);
}
