#include <iostream>
#include <stack>
#include "post.h"
using namespace std;

bool Token::operator==(char b) { return len == 1 && str[0] == b; }
bool Token::operator!=(char b) { return len != 1 || str[0] != b; }
Token::Token() {}

Token::Token(char c) : len(1), type(c) { str = new char[1]; str[0] = c; }                 // default type = c itself
Token::Token(char c, char c2, int type) : len(2), type(type) { str = new char[2]; str[0] = c; str[1] = c2; }
Token::Token(char* arr, int l, int type = ID) : len(l), type(type){
    str = new char[len + 1];
    for (int i = 0; i < len; i++) str[i] = arr[i];
    str[len] = '\0';

    if (type == NUM) {
        ival = arr[0] - '0';
        for (int i = 1; i < len; i++) ival = ival * 10 + arr[i] - '0';
    } else if (type == ID) ival = 0;
    else throw "must be ID or NUM";
}

bool Token::IsOperand() {  return type == ID || type == NUM; }


ostream& operator<<(ostream& os, Token token) {
    if (token.type == UMINUS) os << "-u";
    else if (token.type == NUM) os << token.ival;
    else for (int i = 0; i < token.len; i++) os << token.str[i];
    os << " ";
    return os;
}

bool GetID(Expression& expression, Token& token) {
    char expString[MAXLEN]; int idLen = 0;
    char c = expression.str[expression.pos];

    if (!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')) return false;
    expString[idLen++] = c;
    expression.pos++;
    while ((c = expression.str[expression.pos])
           >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9') {
        expString[idLen++] = c;
        expression.pos++;
    }
    expString[idLen] = '\0';
    token = Token(expString, idLen, ID);            // return an ID
    return true;
}

bool GetInt(Expression& expression, Token& token) {
    char expIntString[MAXLEN]; int intLen = 0;
    char c = expression.str[expression.pos];

    if (!('0' <= c && c <= '9')) return false;
    expIntString[intLen++] = c;
    expression.pos++;
    while ('0' <= (c = expression.str[expression.pos]) && c <= '9') {
        expIntString[intLen++] = c;
        expression.pos++;
    }
    expIntString[intLen] = '\0';
    token = Token(expIntString, intLen, NUM);
    return true;
}


void SkipBlanks(Expression& e) {
    char c;
    while (e.pos < e.len && ((c = e.str[e.pos]) == ' ' || c == '\t')){
        e.pos++;
    }
}

bool TwoCharOp(Expression& expression, Token& token) {
    char c = expression.str[expression.pos];
    char c2 = expression.str[expression.pos + 1];

    int op = -1; // LE GE EQ NE AND OR UMINUS
    if(c2 == '=') {
        if (c == '<') op = LE;
        else if (c == '>') op = GE;
        else if (c == '=') op = EQ;
        else if (c == '!') op = NE;
    }
    else if (c == '&' && c2 == '&') op = AND;
    else if (c == '|' && c2 == '|') op = OR;
    else if (c2 == '-') op = UMINUS;

    if(op == -1) return false;

    token = Token(c, c2, op); expression.pos += 2;
    return true;
}

bool OneCharOp(Expression& e, Token& tok) {
    char c = e.str[e.pos];
    if (c == '-' || c == '!' || c == '*' || c == '/' || c == '%' ||
        c == '+' || c == '<' || c == '>' || c == '(' || c == ')' || c == '=') {
        tok = Token(c);
        e.pos++;
        return true;
    }
    return false;
}


Token NextToken(Expression& expression, bool INFIX = true) {
    static bool oprrFound = true;
    Token token;
    SkipBlanks(expression);     // skip blanks if any
    if (expression.pos == expression.len) { // No more token left in this expression
        if (INFIX) oprrFound = true;
        return Token('#');
    }

    if (GetID(expression, token) || GetInt(expression, token)) {
        if (INFIX) oprrFound = false;
        return token;
    }

    if (TwoCharOp(expression, token) || OneCharOp(expression, token)) {
        if (token.type == '-' && INFIX && oprrFound) {
            token = Token('-', 'u', UMINUS);
        }
        if (INFIX) oprrFound = true;
        return token;
    }
    throw "Illegal Character Found";
}

int icp(Token& t) {           // in-coming priority
    switch (t.type) {
        case '(': return 0;
        case '!': case UMINUS: return 1;
        case '*': case '/': case '%': return 2;
        case '+': case '-': return 3;
        case '<': case '>': case LE: case GE: return 4;
        case EQ: case NE: return 5;
        case AND: return 6;
        case OR: return 7;
        case '=': return 8;
        case '#': return 9;
    }
    return 0;
}

int isp(Token& t)   { // in-stack priority
    int type = t.type;    //stack 에서의 우선순위 결정
    switch (t.type) {
        case '!': case UMINUS: return 1;
        case '*': case '/': case '%': return 2;
        case '+': case '-': return 3;
        case '<': case '>': case LE: case GE: return 4;
        case EQ: case NE: return 5;
        case AND: return 6;
        case OR: return 7;
        case '=': return 8;
        case '#': return 9;
        case '(': return 10;
    }
    return 0;
}

void Postfix(Expression expression) {
    stack<Token> st;
    st.push(Token('#'));
    Token tokenNow = NextToken(expression);
    while(tokenNow.type != '#') {
        if(tokenNow.type == NUM || tokenNow.type == ID) cout << tokenNow;
        else if (tokenNow.type == '(') st.push(tokenNow);
        else if (tokenNow.type == ')') {
            while(st.top().type != '#' && st.top().type != '(') { cout << st.top(); st.pop(); }
            st.pop();
        }
        else {
            int priorityNow = icp(tokenNow);
            while (st.top().type != '#' && isp(st.top()) <= priorityNow) { cout << st.top(); st.pop(); }
            st.push(tokenNow);
        }
        tokenNow = NextToken(expression);
    }
    while (st.top().type != '#') { cout << st.top(); st.pop(); }
    cout << '\n';
}
