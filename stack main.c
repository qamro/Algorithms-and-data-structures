#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int val) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = val;
    n->next = NULL;
    return n;
}

int isEmpty(Node* top) { return top == NULL; }

void push(Node** top, int val) {
    Node* n = createNode(val);
    n->next = *top;
    *top = n;
    printf("  [+] Pushed %d onto the stack.\n", val);
}

int pop(Node** top) {
    if (isEmpty(*top)) { printf("  [!] Stack underflow — stack is empty.\n"); return -1; }
    Node* tmp = *top;
    int val = tmp->data;
    *top = (*top)->next;
    free(tmp);
    return val;
}

int peek(Node* top) {
    if (isEmpty(top)) { printf("  [!] Stack is empty.\n"); return -1; }
    return top->data;
}

int size(Node* top) {
    int c = 0;
    while (top) { c++; top = top->next; }
    return c;
}

int maxVal(Node* top) {
    int m = top->data;
    while (top) { if (top->data > m) m = top->data; top = top->next; }
    return m;
}

int minVal(Node* top) {
    int m = top->data;
    while (top) { if (top->data < m) m = top->data; top = top->next; }
    return m;
}

int countOcc(Node* top, int val) {
    int c = 0;
    while (top) { if (top->data == val) c++; top = top->next; }
    return c;
}

void display(Node* top) {
    if (isEmpty(top)) { printf("  Stack: (empty)\n"); return; }
    printf("  Stack (top -> bottom): ");
    while (top) {
        printf("[%d]", top->data);
        if (top->next) printf(" -> ");
        top = top->next;
    }
    printf("\n");
}

void freeStack(Node** top) {
    Node* cur = *top, *tmp;
    while (cur) { tmp = cur->next; free(cur); cur = tmp; }
    *top = NULL;
}

void printMenu() {
    printf("\n");
    printf("          STACK MENU            \n");
    printf("\n");
    printf("  1. Push                       \n");
    printf(" 2. Pop                        \n");
    printf("  3. Peek (top element)         \n");
    printf("  4. isEmpty                   \n");
    printf(" 5. Size                       \n");
    printf(" 6. Max / Min                  \n");
    printf("  7. Count Occurrences          \n");
    printf("  8. Display                    \n");
    printf("  0. Exit                       \n");
    printf("\n");
    printf("  Choice: ");
}

int main() {
    Node* top = NULL;
    int choice, val;

    printf("\n  === Stack Interactive Menu ===\n");

    do {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("  Enter value to push: "); scanf("%d", &val);
                push(&top, val);
                display(top); break;

            case 2:
                val = pop(&top);
                if (val != -1) printf("  [+] Popped: %d\n", val);
                display(top); break;

            case 3:
                val = peek(top);
                if (val != -1) printf("  [+] Top element: %d\n", val);
                break;

            case 4:
                printf("  Stack is %s.\n", isEmpty(top) ? "EMPTY" : "NOT empty");
                break;

            case 5:
                printf("  Size = %d\n", size(top)); break;

            case 6:
                if (isEmpty(top)) { printf("  [!] Stack is empty.\n"); break; }
                printf("  Max = %d\n", maxVal(top));
                printf("  Min = %d\n", minVal(top)); break;

            case 7:
                printf("  Enter value: "); scanf("%d", &val);
                printf("  Occurrences of %d = %d\n", val, countOcc(top, val)); break;

            case 8:
                display(top); break;

            case 0:
                printf("  Goodbye!\n");
                freeStack(&top); break;

            default:
                printf("  [!] Invalid choice.\n");
        }

    } while (choice != 0);

    return 0;
}