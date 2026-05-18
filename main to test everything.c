#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

// ─── Core Stack Operations ───────────────────────────────

void initStack(Stack *s) { s->top = NULL; }

int isEmpty(Stack *s) { return s->top == NULL; }

void push(Stack *s, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) { printf("Memory error!\n"); return; }
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
}

int pop(Stack *s) {
    if (isEmpty(s)) { printf("Stack underflow!\n"); return -1; }
    Node *temp = s->top;
    int value = temp->data;
    s->top = s->top->next;
    free(temp);
    return value;
}

int peek(Stack *s) {
    if (isEmpty(s)) { printf("Stack is empty!\n"); return -1; }
    return s->top->data;
}

void displayStack(Stack *s, const char *name) {
    if (isEmpty(s)) { printf("%s is empty.\n", name); return; }
    Node *curr = s->top;
    printf("%s (top->bottom): ", name);
    while (curr) { printf("%d ", curr->data); curr = curr->next; }
    printf("\n");
}

// ─── Exercise 04 Functions ───────────────────────────────

// Part 1: Move S1 to S2, evens below odds
void moveEvensBelowOdds(Stack *S1, Stack *S2) {
    Stack temp;
    initStack(&temp);

    while (!isEmpty(S1)) {
        int val = pop(S1);
        if (val % 2 != 0) push(S2, val);
        else               push(&temp, val);
    }
    while (!isEmpty(&temp))
        push(S2, pop(&temp));
}

// Part 2: Copy evens from S1 to S2, S1 unchanged
void copyEvens(Stack *S1, Stack *S2) {
    Stack temp;
    initStack(&temp);

    while (!isEmpty(S1)) {
        int val = pop(S1);
        push(&temp, val);
        if (val % 2 == 0) push(S2, val);
    }
    while (!isEmpty(&temp))
        push(S1, pop(&temp));

    // Reverse S2 to match original order
    Stack rev;
    initStack(&rev);
    while (!isEmpty(S2)) push(&rev, pop(S2));
    while (!isEmpty(&rev)) push(S2, pop(&rev));
}

// ─── Helper: fill a stack from user input ────────────────

void fillStack(Stack *s, const char *name) {
    int n, val;
    printf("How many elements to push into %s? ", name);
    scanf("%d", &n);
    printf("Enter %d positive integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        push(s, val);
    }
}

// ─── MENU ────────────────────────────────────────────────

int main() {
    Stack S1, S2;
    initStack(&S1);
    initStack(&S2);

    int choice;

    do {
        printf("\n╔══════════════════════════════════════╗\n");
        printf("║         STACK OPERATIONS MENU        ║\n");
        printf("╠══════════════════════════════════════╣\n");
        printf("║  --- Basic Operations (Ex03) ---      ║\n");
        printf("║  1. Push element into S1              ║\n");
        printf("║  2. Pop element from S1               ║\n");
        printf("║  3. Peek top of S1                    ║\n");
        printf("║  4. Display S1                        ║\n");
        printf("║  5. Display S2                        ║\n");
        printf("╠══════════════════════════════════════╣\n");
        printf("║  --- Stack Manipulation (Ex04) ---    ║\n");
        printf("║  6. Fill S1 with custom values        ║\n");
        printf("║  7. Move S1->S2 (evens below odds)    ║\n");
        printf("║  8. Copy evens S1->S2 (S1 unchanged)  ║\n");
        printf("╠══════════════════════════════════════╣\n");
        printf("║  9. Reset both stacks                 ║\n");
        printf("║  0. Exit                              ║\n");
        printf("╚══════════════════════════════════════╝\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1: {
                int val;
                printf("Enter value to push: ");
                scanf("%d", &val);
                push(&S1, val);
                printf("✔ %d pushed into S1.\n", val);
                break;
            }

            case 2: {
                int val = pop(&S1);
                if (val != -1)
                    printf("✔ Popped from S1: %d\n", val);
                break;
            }

            case 3: {
                int val = peek(&S1);
                if (val != -1)
                    printf("✔ Top of S1: %d\n", val);
                break;
            }

            case 4:
                displayStack(&S1, "S1");
                break;

            case 5:
                displayStack(&S2, "S2");
                break;

            case 6:
                fillStack(&S1, "S1");
                printf("✔ S1 filled.\n");
                displayStack(&S1, "S1");
                break;

            case 7:
                if (isEmpty(&S1)) {
                    printf("S1 is empty! Push elements first.\n");
                } else {
                    printf("Before:\n");
                    displayStack(&S1, "S1");
                    displayStack(&S2, "S2");
                    moveEvensBelowOdds(&S1, &S2);
                    printf("After:\n");
                    displayStack(&S1, "S1");
                    displayStack(&S2, "S2");
                }
                break;

            case 8:
                if (isEmpty(&S1)) {
                    printf("S1 is empty! Push elements first.\n");
                } else {
                    printf("Before:\n");
                    displayStack(&S1, "S1");
                    displayStack(&S2, "S2");
                    copyEvens(&S1, &S2);
                    printf("After:\n");
                    displayStack(&S1, "S1 (unchanged)");
                    displayStack(&S2, "S2 (evens only)");
                }
                break;

            case 9:
                initStack(&S1);
                initStack(&S2);
                printf("✔ Both stacks reset.\n");
                break;

            case 0:
                printf("Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 0);

    return 0;
}