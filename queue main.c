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

int isEmpty(Node* front) { return front == NULL; }

void enqueue(Node** front, Node** rear, int val) {
    Node* n = createNode(val);
    if (isEmpty(*front)) { *front = *rear = n; }
    else { (*rear)->next = n; *rear = n; }
    printf("  [+] Enqueued %d at rear.\n", val);
}

int dequeue(Node** front, Node** rear) {
    if (isEmpty(*front)) { printf("  [!] Queue underflow — queue is empty.\n"); return -1; }
    Node* tmp = *front;
    int val = tmp->data;
    *front = (*front)->next;
    if (!*front) *rear = NULL;  /* queue is now empty */
    free(tmp);
    return val;
}

int frontVal(Node* front) {
    if (isEmpty(front)) { printf("  [!] Queue is empty.\n"); return -1; }
    return front->data;
}

int rearVal(Node* rear) {
    if (!rear) { printf("  [!] Queue is empty.\n"); return -1; }
    return rear->data;
}

int size(Node* front) {
    int c = 0;
    while (front) { c++; front = front->next; }
    return c;
}

int maxVal(Node* front) {
    int m = front->data;
    while (front) { if (front->data > m) m = front->data; front = front->next; }
    return m;
}

int minVal(Node* front) {
    int m = front->data;
    while (front) { if (front->data < m) m = front->data; front = front->next; }
    return m;
}

int countOcc(Node* front, int val) {
    int c = 0;
    while (front) { if (front->data == val) c++; front = front->next; }
    return c;
}

/* delete first occurrence of val from queue */
void deleteVal(Node** front, Node** rear, int val) {
    if (isEmpty(*front)) { printf("  [!] Queue is empty.\n"); return; }
    if ((*front)->data == val) {
        int v = dequeue(front, rear);
        printf("  [+] Deleted %d from front.\n", v);
        return;
    }
    Node* cur = *front;
    while (cur->next && cur->next->data != val) cur = cur->next;
    if (!cur->next) { printf("  [!] Value %d not found.\n", val); return; }
    Node* tmp = cur->next;
    cur->next = tmp->next;
    if (tmp == *rear) *rear = cur;  /* deleted the rear */
    free(tmp);
    printf("  [+] Deleted %d.\n", val);
}

void display(Node* front) {
    if (isEmpty(front)) { printf("  Queue: (empty)\n"); return; }
    printf("  Queue (front -> rear): ");
    while (front) {
        printf("[%d]", front->data);
        if (front->next) printf(" -> ");
        front = front->next;
    }
    printf("\n");
}

void freeQueue(Node** front, Node** rear) {
    Node* cur = *front, *tmp;
    while (cur) { tmp = cur->next; free(cur); cur = tmp; }
    *front = *rear = NULL;
}

void printMenu() {
    printf("\n");
    printf("          QUEUE MENU            \n");
    printf("\n");
    printf("  1. Enqueue                    \n");
    printf("  2. Dequeue                    \n");
    printf("  3. Peek Front                 \n");
    printf(" 4. Peek Rear                  \n");
    printf(" 5. isEmpty                    \n");
    printf("  6. Size                       \n");
    printf("  7. Max / Min                  \n");
    printf("  8. Count Occurrences          \n");
    printf("  9. Delete by Value            \n");
    printf(" 10. Display                    \n");
    printf("  0. Exit                    \n");
    printf("\n");
    printf("  Choice: ");
}

int main() {
    Node* front = NULL;
    Node* rear  = NULL;
    int choice, val;

    printf("\n  === Queue Interactive Menu ===\n");

    do {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("  Enter value to enqueue: "); scanf("%d", &val);
                enqueue(&front, &rear, val);
                display(front); break;

            case 2:
                val = dequeue(&front, &rear);
                if (val != -1) printf("  [+] Dequeued: %d\n", val);
                display(front); break;

            case 3:
                val = frontVal(front);
                if (val != -1) printf("  [+] Front element: %d\n", val);
                break;

            case 4:
                val = rearVal(rear);
                if (val != -1) printf("  [+] Rear element: %d\n", val);
                break;

            case 5:
                printf("  Queue is %s.\n", isEmpty(front) ? "EMPTY" : "NOT empty");
                break;

            case 6:
                printf("  Size = %d\n", size(front)); break;

            case 7:
                if (isEmpty(front)) { printf("  [!] Queue is empty.\n"); break; }
                printf("  Max = %d\n", maxVal(front));
                printf("  Min = %d\n", minVal(front)); break;

            case 8:
                printf("  Enter value: "); scanf("%d", &val);
                printf("  Occurrences of %d = %d\n", val, countOcc(front, val)); break;

            case 9:
                printf("  Enter value to delete: "); scanf("%d", &val);
                deleteVal(&front, &rear, val);
                display(front); break;

            case 10:
                display(front); break;

            case 0:
                printf("  Goodbye!\n");
                freeQueue(&front, &rear); break;

            default:
                printf("  [!] Invalid choice.\n");
        }

    } while (choice != 0);

    return 0;
}