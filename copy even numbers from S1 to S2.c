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

void displayStack(Stack *s, const char *name) {
    if (isEmpty(s)) { printf("%s is empty.\n", name); return; }
    Node *curr = s->top;
    printf("%s (top->bottom): ", name);
    while (curr) { printf("%d ", curr->data); curr = curr->next; }
    printf("\n");
}

// ─── Fill Stack ──────────────────────────────────────────

void fillStack(Stack *s, const char *name) {
    initStack(s);  // reset before filling
    int n, val;
    printf("How many elements for %s? ", name);
    scanf("%d", &n);
    printf("Enter %d positive integers:\n", n);
    // push in reverse so first entered = bottom
    int arr[100];
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    for (int i = n - 1; i >= 0; i--) push(s, arr[i]);
    printf("✔ %s filled: ", name);
    displayStack(s, name);
}

// ─── Exercise 04 — Part 1 ────────────────────────────────
// Move S1 -> S2: evens below odds, S1 becomes empty

void moveEvensBelowOdds(Stack *S1, Stack *S2) {
    Stack temp;
    initStack(&temp);

    while (!isEmpty(S1)) {
        int val = pop(S1);
        if (val % 2 != 0) push(S2, val);   // odds -> S2
        else               push(&temp, val); // evens -> temp
    }
    // push evens under odds
    while (!isEmpty(&temp))
        push(S2, pop(&temp));
}

// ─── Exercise 04 — Part 2 ────────────────────────────────
// Copy evens from S1 to S2, S1 stays identical

void copyEvens(Stack *S1, Stack *S2) {
    Stack temp;
    initStack(&temp);

    while (!isEmpty(S1)) {
        int val = pop(S1);
        push(&temp, val);
        if (val % 2 == 0) push(S2, val);
    }
    // restore S1
    while (!isEmpty(&temp))
        push(S1, pop(&temp));

    // reverse S2 to match original order
    Stack rev;
    initStack(&rev);
    while (!isEmpty(S2)) push(&rev, pop(S2));
    while (!isEmpty(&rev)) push(S2, pop(&rev));
}

// ─── MENU ────────────────────────────────────────────────

int main() {
    Stack S1, S2;
    initStack(&S1);
    initStack(&S2);

    int choice;

    do {
        printf("\n╔══════════════════════════════════╗\n");
        printf("║       EXERCISE 04 — MENU         ║\n");
        printf("╠══════════════════════════════════╣\n");
        printf("║  1. Fill S1                      ║\n");
        printf("║  2. Fill S2                      ║\n");
        printf("║  3. Display S1 & S2              ║\n");
        printf("╠══════════════════════════════════╣\n");
        printf("║  4. Move S1->S2 (evens below     ║\n");
        printf("║     odds) [S1 emptied]           ║\n");
        printf("║  5. Copy evens S1->S2            ║\n");
        printf("║     [S1 unchanged]               ║\n");
        printf("╠══════════════════════════════════╣\n");
        printf("║  0. Exit                         ║\n");
        printf("╚══════════════════════════════════╝\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                fillStack(&S1, "S1");
                break;

            case 2:
                fillStack(&S2, "S2");
                break;

            case 3:
                displayStack(&S1, "S1");
                displayStack(&S2, "S2");
                break;

            case 4:
                if (isEmpty(&S1)) {
                    printf("⚠ S1 is empty! Fill it first (option 1).\n");
                    break;
                }
                printf("\n--- Before ---\n");
                displayStack(&S1, "S1");
                displayStack(&S2, "S2");

                moveEvensBelowOdds(&S1, &S2);
               
                printf("\n--- After ---\n");
                displayStack(&S1, "S1 (now empty)");
                displayStack(&S2, "S2 (odds on top, evens below)");
                initStack(&S2);
                break;

            case 5:
                if (isEmpty(&S1)) {
                    printf("⚠ S1 is empty! Fill it first (option 1).\n");
                    break;
                }
                // reset S2 before copying
                initStack(&S2);

                printf("\n--- Before ---\n");
                displayStack(&S1, "S1");
                displayStack(&S2, "S2 (empty)");

                copyEvens(&S1, &S2);

                printf("\n--- After ---\n");
                displayStack(&S1, "S1 (unchanged)");
                displayStack(&S2, "S2 (evens only)");
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