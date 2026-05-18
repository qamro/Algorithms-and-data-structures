#include <stdio.h>
#include <stdlib.h>

/* ─────────────────────────────────────────
   SHARED NODE STRUCTURE
   ───────────────────────────────────────── */
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

/* ─────────────────────────────────────────
   LINKED LIST
   ───────────────────────────────────────── */
void insertFront(Node** head, int val) {
    Node* n = createNode(val);
    n->next = *head;
    *head = n;
}

void insertBack(Node** head, int val) {
    Node* n = createNode(val);
    if (!*head) { *head = n; return; }
    Node* cur = *head;
    while (cur->next) cur = cur->next;
    cur->next = n;
}

void insertAt(Node** head, int val, int k) {
    if (k == 0) { insertFront(head, val); return; }
    Node* cur = *head;
    for (int i = 0; i < k - 1 && cur; i++) cur = cur->next;
    if (!cur) { printf("  [!] Position out of range\n"); return; }
    Node* n = createNode(val);
    n->next = cur->next;
    cur->next = n;
}

void deleteVal(Node** head, int val) {
    if (!*head) return;
    if ((*head)->data == val) {
        Node* tmp = *head;
        *head = (*head)->next;
        free(tmp); return;
    }
    Node* cur = *head;
    while (cur->next && cur->next->data != val) cur = cur->next;
    if (cur->next) {
        Node* tmp = cur->next;
        cur->next = tmp->next;
        free(tmp);
    }
}

int maxVal(Node* head) {
    int m = head->data;
    while (head) { if (head->data > m) m = head->data; head = head->next; }
    return m;
}

int minVal(Node* head) {
    int m = head->data;
    while (head) { if (head->data < m) m = head->data; head = head->next; }
    return m;
}

int countOcc(Node* head, int val) {
    int c = 0;
    while (head) { if (head->data == val) c++; head = head->next; }
    return c;
}

void displayLL(Node* head) {
    printf("  List: ");
    if (!head) { printf("(empty)\n"); return; }
    while (head) { printf("%d", head->data); if (head->next) printf(" -> "); head = head->next; }
    printf("\n");
}

void freeList(Node** head) {
    Node* cur = *head, *tmp;
    while (cur) { tmp = cur->next; free(cur); cur = tmp; }
    *head = NULL;
}

/* ─────────────────────────────────────────
   STACK  (LIFO — only touch the head)
   ───────────────────────────────────────── */
void push(Node** top, int val) {
    Node* n = createNode(val);
    n->next = *top;
    *top = n;
}

int pop(Node** top) {
    if (!*top) { printf("  [!] Stack underflow\n"); return -1; }
    Node* tmp = *top;
    int val = tmp->data;
    *top = (*top)->next;
    free(tmp);
    return val;
}

int peek(Node* top) {
    if (!top) { printf("  [!] Stack empty\n"); return -1; }
    return top->data;
}

void displayStack(Node* top) {
    printf("  Stack (top->bottom): ");
    if (!top) { printf("(empty)\n"); return; }
    while (top) { printf("%d", top->data); if (top->next) printf(" -> "); top = top->next; }
    printf("\n");
}

/* ─────────────────────────────────────────
   QUEUE  (FIFO — enqueue rear, dequeue front)
   ───────────────────────────────────────── */
void enqueue(Node** front, Node** rear, int val) {
    Node* n = createNode(val);
    if (!*rear) { *front = *rear = n; return; }
    (*rear)->next = n;
    *rear = n;
}

int dequeue(Node** front, Node** rear) {
    if (!*front) { printf("  [!] Queue empty\n"); return -1; }
    Node* tmp = *front;
    int val = tmp->data;
    *front = (*front)->next;
    if (!*front) *rear = NULL;   /* queue became empty */
    free(tmp);
    return val;
}

void displayQueue(Node* front) {
    printf("  Queue (front->rear): ");
    if (!front) { printf("(empty)\n"); return; }
    while (front) { printf("%d", front->data); if (front->next) printf(" -> "); front = front->next; }
    printf("\n");
}

/* ─────────────────────────────────────────
   MAIN — TEST EVERYTHING
   ───────────────────────────────────────── */
int main() {

    /* ══════════════════════════════════════
       1. LINKED LIST TESTS
       ══════════════════════════════════════ */
    printf("╔══════════════════════════════╗\n");
    printf("║        LINKED  LIST          ║\n");
    printf("╚══════════════════════════════╝\n");

    Node* head = NULL;

    printf("\n[+] insertBack: 10, 20, 30, 40, 50\n");
    insertBack(&head, 10);
    insertBack(&head, 20);
    insertBack(&head, 30);
    insertBack(&head, 40);
    insertBack(&head, 50);
    displayLL(head);

    printf("\n[+] insertFront: 5\n");
    insertFront(&head, 5);
    displayLL(head);

    printf("\n[+] insertAt position 3: value 99\n");
    insertAt(&head, 99, 3);
    displayLL(head);

    printf("\n[+] deleteVal: 99\n");
    deleteVal(&head, 99);
    displayLL(head);

    printf("\n[+] deleteVal: 5 (head)\n");
    deleteVal(&head, 5);
    displayLL(head);

    printf("\n[+] insertBack: 20, 20 (duplicates)\n");
    insertBack(&head, 20);
    insertBack(&head, 20);
    displayLL(head);

    printf("\n[+] countOcc(20) = %d\n", countOcc(head, 20));
    printf("[+] max = %d\n", maxVal(head));
    printf("[+] min = %d\n", minVal(head));

    freeList(&head);
    printf("\n[+] After freeList:\n");
    displayLL(head);

    /* ══════════════════════════════════════
       2. STACK TESTS
       ══════════════════════════════════════ */
    printf("\n╔══════════════════════════════╗\n");
    printf("║           STACK              ║\n");
    printf("╚══════════════════════════════╝\n");

    Node* top = NULL;

    printf("\n[+] push: 10, 20, 30, 40\n");
    push(&top, 10);
    push(&top, 20);
    push(&top, 30);
    push(&top, 40);
    displayStack(top);

    printf("\n[+] peek = %d\n", peek(top));

    printf("\n[+] pop = %d\n", pop(&top));
    displayStack(top);

    printf("\n[+] pop = %d\n", pop(&top));
    displayStack(top);

    printf("\n[+] push: 99\n");
    push(&top, 99);
    displayStack(top);

    printf("\n[+] pop all:\n");
    while (top) printf("  popped: %d\n", pop(&top));

    printf("\n[+] pop on empty stack:\n");
    pop(&top);

    /* ══════════════════════════════════════
       3. QUEUE TESTS
       ══════════════════════════════════════ */
    printf("\n╔══════════════════════════════╗\n");
    printf("║           QUEUE              ║\n");
    printf("╚══════════════════════════════╝\n");

    Node* front = NULL;
    Node* rear  = NULL;

    printf("\n[+] enqueue: 10, 20, 30, 40\n");
    enqueue(&front, &rear, 10);
    enqueue(&front, &rear, 20);
    enqueue(&front, &rear, 30);
    enqueue(&front, &rear, 40);
    displayQueue(front);

    printf("\n[+] dequeue = %d\n", dequeue(&front, &rear));
    displayQueue(front);

    printf("\n[+] dequeue = %d\n", dequeue(&front, &rear));
    displayQueue(front);

    printf("\n[+] enqueue: 99\n");
    enqueue(&front, &rear, 99);
    displayQueue(front);

    printf("\n[+] dequeue all:\n");
    while (front) printf("  dequeued: %d\n", dequeue(&front, &rear));

    printf("\n[+] dequeue on empty queue:\n");
    dequeue(&front, &rear);

    printf("\n--- All tests done ---\n");
    return 0;
}