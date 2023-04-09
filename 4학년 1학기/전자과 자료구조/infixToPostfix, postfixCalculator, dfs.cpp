#include <iostream>
#include <stack>
#include <tuple>

#define DIV 6
//#define TEST_MATLAB
//#define TEST_MAZE_GEN
#define TEST_MAZE_OUT

using namespace std;
int maze[6][6] = {
        {0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0},
        {0, 1, 0, 1, 0, 0},
        {0, 0, 0, 1, 1, 1},
        {0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0},
};
int dy[DIV] = {0, 0, -1, 1, 0};
int dx[DIV] = {1, -1, 0, 0, 0};

#ifdef TEST_MATLAB
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

bool contains(char *ori, char target) {
    for (int i = 0; i < strlen(ori); i++) {
        if (ori[i] == '\0') {
            return false;
        }

        if (ori[i] == target) {
            return true;
        }
    }
    return false;
}

int prec(char operation) {
    switch (operation) {
        case '(' : case ')': return 0;
        case '^' : return 1;
        case '+' : case '-': return 2;
        case '*' : case '/': return 3;
    }
    return -1;
}

char *convertInfixToPostfix(char exp[]) {
    stack<char> st;
    char chNow, *ret;
    int expLength =  strlen(exp);

    int idx = 0;
    ret = (char *)malloc(sizeof(char) * expLength);
    printf("- infix to postfix result : ");

    for (int i = 0; i < expLength; i++) {
        chNow = exp[i];
        switch (chNow) {
            case ' ':
                break;
            case '(':
                st.push(chNow);
                break;
            case ')':
                while (!st.empty() && st.top() != '(') {
                    printf("%c", st.top());
                    ret[idx++] = st.top();
                    st.pop();
                }

                if (st.empty()) {
                    printf("error! wrong exp\n", st.top());
                    break;
                }

                st.pop();

                break;
            case '+': case '-': case '*': case '/': case '^':
                while (!st.empty() && prec(chNow) <= prec(st.top())) {
                    printf("%c", st.top());
                    ret[idx++] = st.top();
                    st.pop();
                }
                st.push(chNow);
                break;
            default:
                printf("%c", chNow);
                ret[idx++] = chNow;
                break;
        }
    }

    while (!st.empty()) {
        printf("%c", st.top());
        ret[idx++] = st.top();
        st.pop();
    }

    printf("\n");
    ret[idx] = '\0';
    return ret;
}

int calculatePostfix(char exp[]) {
    int temp, idx = 0, expLength = strlen(exp);
    stack<int> st;
    while (idx < expLength) {
        // 숫자인 경우 48 ~ 57
        if (48 <= exp[idx] && exp[idx] <= 57) {
            st.push(exp[idx++] - '0');
            continue;
        }

        // 연산자인 경우
        int num1, num2;
        num1 = st.top();
        st.pop();
        num2 = st.top();
        st.pop();

        switch (exp[idx++]) {
            case '+': st.push(num2 + num1); break;
            case '-': st.push(num2 - num1); break;
            case '*': st.push(num2 * num1); break;
            case '/': st.push(num2 / num1); break;
            // 제곱의 경우
            default:
                temp = 1;
                for (int i = 0; i < num1; i++) {
                    temp *= num2;
                }
                st.push(temp);
        }
    }
    return st.top();
}

int calculateExp(char exp[]) {
    char *postfixExp = convertInfixToPostfix(exp);
    return calculatePostfix(postfixExp);
}

void getArray(char exp[]) {
    int idx = 0, expLength = strlen(exp);
    while (idx < expLength && exp[idx] != '[') {
        idx++;
    }

    stack<int> st;
    while (exp[idx] != ';') {

        if (48 <= exp[idx] && exp[idx] <= 57) {
            st.push(exp[idx++] - '0');
            continue;
        }
        idx++;
    }

    int arrayLength = st.size();
    int arr[2][arrayLength];

    while (!st.empty()) {
        arr[0][st.size() - 1] = st.top();
        st.pop();
    }

    idx++;
    int idx2 = 0;
    while (idx < expLength && exp[idx] != ']') {
        if (48 <= exp[idx] && exp[idx] <= 57) {
            arr[1][idx2++] = exp[idx++] - '0';
            continue;
        }
        idx++;
    }

    // 3가지 연산 구현
    printf("array parse done\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < arrayLength; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("moack Array 1 for plus minus\n");
    int mockArray[2][arrayLength];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < arrayLength; j++) {
            mockArray[i][j] = rand() % 10;
            printf("%d ", mockArray[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // 더하기
    printf("===array plus===\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < arrayLength; j++) {
            printf("%d ", arr[i][j] + mockArray[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // 뺴기
    printf("===array minus===\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < arrayLength; j++) {
            printf("%d ", arr[i][j] - mockArray[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // 곱하기
    printf("moack Array 2 for multiply\n");
    int mockArray2[arrayLength][2];
    for (int i = 0; i < arrayLength; i++) {
        for (int j = 0; j < 2; j++) {
            mockArray2[i][j] = rand() % 10;
            printf("%d ", mockArray2[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("===array multiply===\n");
    int temp;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            temp = 0;
            for (int k = 0; k < arrayLength; k++) {
                temp += (arr[i][k] * mockArray2[k][j]);
            }
            printf("%d ", temp);
        }
        printf("\n");
    }
    printf("\n");
}

void go () {
    char command[100];
    while (1) {
        printf("command :");
        gets(command);

        if (equals(command, "end")) {
            break;
        }

        if (equals(command, "script")) {
            // 미구현
            continue;
        }

        // 배열의 경우
        if (contains(command, '[')) {
            getArray(command);
            continue;
        }

        // 수식인 경우
        printf("- calculate result : %d\n", calculateExp(command));
    }
}
#endif

#ifdef TEST_MAZE_GEN

bool stop;
int saveY = 1, saveX = 0;

bool makeMaze(int y, int x) {
    if (stop || (y == 3 && x == 5)) {
        return stop = true;
    }

    int idx;
    while (1) {
        idx = rand() % DIV;
        if (idx >= 4) return false;
        if (0 > y + dy[idx] || y + dy[idx] > 5) return false;
        if (0 > x + dx[idx] || x + dx[idx] > 5) return false;
        break;
    }
    saveY = y + dy[idx];
    saveX = x + dx[idx];
    maze[saveY][saveX] = 1;
    return makeMaze(saveY, saveX);
}

void go() {
    memset(maze, 0, sizeof(maze));
    saveY = 1, saveX = 0;
    maze[saveY][saveX] = 1;
    stop = false;
    while (!makeMaze(saveY, saveX)) {
        stop = false;
    }

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }
}
#endif

#ifdef TEST_MAZE_OUT
bool check[6][6];
pair<int, int> from[6][6];
void go() {
    // 현재 좌표, 이전 좌표
    stack<pair<pair<int, int>, pair<int, int>>> st;
    st.push({{1, 0}, {-1, -1}});
    check[0][0] = true;
    while (!st.empty()) {
        pair<pair<int, int>, pair<int, int>> top = st.top();
        st.pop();
        int yNow = top.first.first;
        int xNow = top.first.second;
        check[yNow][xNow] = true;
        from[yNow][xNow] = {top.second.first, top.second.second};

        if (yNow == 3 && xNow == 5) {
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nextY = yNow + dy[i];
            int nextX = xNow + dx[i];

            if (0 > nextY || nextY > 5) continue;
            if (0 > nextX || nextX > 5) continue;
            if (check[nextY][nextX] || maze[nextY][nextX] == 0) continue;

            st.push({{nextY, nextX}, {yNow, xNow}});
        }
    }

    int y = 3, x = 5;
    stack<pair<int, int>> trace;
    while (y != -1 && x != -1) {
        trace.push({y, x});
        tie(y, x) = from[y][x];
    }

    int idx = 0;
    while (!trace.empty()) {
        if (idx++ % 5 != 0) {
            printf(" -> ");
        }

        trace.top();
        printf("{%d, %d}", trace.top().first, trace.top().second);
        trace.pop();

        if (idx % 5 == 0) {
            printf("\n");
        }
    }
}
#endif

int main() {
    srand((unsigned int)time(NULL));
    go();
}
