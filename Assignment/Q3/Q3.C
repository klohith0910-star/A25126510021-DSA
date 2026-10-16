#include <stdio.h>
#include <ctype.h>

char stack[100];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    if (top == -1)
        return '\0';

    return stack[top--];
}

int prec(char c) {
    if (c == '^')
        return 3;
    if (c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;

    return 0;
}

int main() {
    char exp[100], pst[100];
    int k = 0;

    printf("Enter infix expression: ");
    scanf("%99s", exp);

    for (int i = 0; exp[i] != '\0'; i++) {
        char ch = exp[i];

        if (isalnum((unsigned char)ch)) {
            pst[k++] = ch;
        } else if (ch == '(') {
            push(ch);
        } else if (ch == ')') {
            while (top != -1 && stack[top] != '(')
                pst[k++] = pop();

            if (top != -1)
                pop();
        } else {
            while (top != -1 && stack[top] != '(' &&
                  (prec(stack[top]) > prec(ch) ||
                  (prec(stack[top]) == prec(ch) && ch != '^'))) {
                pst[k++] = pop();
            }

            push(ch);
        }
    }

    while (top != -1)
        pst[k++] = pop();

    pst[k] = '\0';

    printf("Postfix expression: %s\n", pst);

    return 0;
}
