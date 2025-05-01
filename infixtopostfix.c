// infix to postfix
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 100
char stack[MAX];
int top = -1;
void push(char ch) {
    if (top < MAX - 1) {
        stack[++top] = ch;
    } else {
        printf("Stack overflow\n");
    }
}
char pop() {
    if (top != -1) {
        return stack[top--];
    } else {
        return -1;
    }
}
char peek() {
    if (top != -1) {
        return stack[top];
    } else {
        return -1;
    }
}
int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}
int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}
void infixToPostfix(char infix[MAX], char postfix[MAX]) {
    int i = 0, j = 0;
    while (infix[i] != '\0') {
        char ch = infix[i];

        if (isdigit(ch)) {
            postfix[j++] = ch;
        }
        else if (ch == '(') {
            push(ch);
        }
        else if (ch == ')') {
            while (top != -1 && peek() != '(') {
                postfix[j++] = pop();
            }
            pop();
        }
        else if (isOperator(ch)) {
            while (top != -1 && precedence(peek()) >= precedence(ch)) {
                postfix[j++] = pop();
            }
            push(ch);
        }
        i++;
    }

    while (top != -1) {
        postfix[j++] = pop();
    }
    postfix[j] = '\0';  
}
int main() {
    char infix[MAX],postfix[MAX];
    printf("Enter infix expression: ");
    scanf("%s", infix);
    printf("Infix expression :%s\n",infix);
    infixToPostfix(infix, postfix);
    printf("Postfix expression :%s\n", postfix);
}
