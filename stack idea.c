#include <stdio.h>
#include <stdlib.h> 
int stackMax(Node* top) {
    int m = top->data;
    while (top) { if (top->data > m) m = top->data; top = top->next; }
    return m;
}

// Count occurrences in stack
int stackCount(Node* top, int val) {
    int c = 0;
    while (top) { if (top->data == val) c++; top = top->next; }
    return c;
}

// Sort stack using a temporary stack
void sortStack(Node** top) {
    Node* tmp = NULL;
    while (!isEmpty(*top)) {
        int cur = pop(top);
        while (!isEmpty(tmp) && peek(tmp) > cur)
            push(top, pop(&tmp));
        push(&tmp, cur);
    }
    *top = tmp;
}

// Check balanced parentheses using stack
int isBalanced(char* s) {
    Node* top = NULL;
    for (int i = 0; s[i]; i++) {
        if (s[i] == '(') push(&top, s[i]);
        else if (s[i] == ')') {
            if (isEmpty(top)) return 0;
            pop(&top);
        }
    }
    return isEmpty(top);
}