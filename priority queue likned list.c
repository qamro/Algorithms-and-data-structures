#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    int priority;
    struct node *next;
} Node;

typedef struct {
    Node *front;
} PriorityQueue;

// ─────────────────────────────────────────
// Initialize
// ─────────────────────────────────────────
void initPQ(PriorityQueue *pq) {
    pq->front = NULL;
}

// ─────────────────────────────────────────
// Check if empty
// ─────────────────────────────────────────
int isPQEmpty(PriorityQueue *pq) {
    return pq->front == NULL;
}

// ─────────────────────────────────────────
// Enqueue — insert by priority order
// (smaller priority number = inserted closer to front)
// ─────────────────────────────────────────
void enqueuePQ(PriorityQueue *pq, int value, int priority) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data     = value;
    newNode->priority = priority;
    newNode->next     = NULL;

    // Case 1: empty queue OR new node has highest priority (smallest number)
    if (isPQEmpty(pq) || priority < pq->front->priority) {
        newNode->next = pq->front;
        pq->front = newNode;
        return;
    }

    // Case 2: find correct position
    Node *curr = pq->front;
    while (curr->next != NULL && curr->next->priority <= priority)
        curr = curr->next;

    newNode->next = curr->next;
    curr->next    = newNode;
}

// ─────────────────────────────────────────
// Dequeue — always remove from front
// ─────────────────────────────────────────
int dequeuePQ(PriorityQueue *pq) {
    if (isPQEmpty(pq)) {
        printf("Priority Queue is empty!\n");
        return -1;
    }
    Node *temp = pq->front;
    int value  = temp->data;
    pq->front  = pq->front->next;
    free(temp);
    return value;
}

// ─────────────────────────────────────────
// Count elements
// ─────────────────────────────────────────
int countPQ(PriorityQueue *pq) {
    int count = 0;
    Node *curr = pq->front;
    while (curr) {
        count++;
        curr = curr->next;
    }
    return count;
}

// ─────────────────────────────────────────
// Display elements
// ─────────────────────────────────────────
void displayPQ(PriorityQueue *pq) {
    if (isPQEmpty(pq)) {
        printf("Priority Queue is empty.\n");
        return;
    }
    Node *curr = pq->front;
    printf("Priority Queue (front -> rear):\n");
    while (curr) {
        printf("  [data: %d | priority: %d]\n", curr->data, curr->priority);
        curr = curr->next;
    }
}

// ─────────────────────────────────────────
// Main — test all operations
// ─────────────────────────────────────────
int main() {
    PriorityQueue pq;
    initPQ(&pq);

    enqueuePQ(&pq, 40, 4);
    enqueuePQ(&pq, 10, 1);   // highest priority
    enqueuePQ(&pq, 30, 3);
    enqueuePQ(&pq, 20, 2);
    enqueuePQ(&pq, 50, 2);   // same priority as 20 → goes after it

    displayPQ(&pq);
    printf("Total elements: %d\n\n", countPQ(&pq));

    printf("Dequeued: %d\n", dequeuePQ(&pq));  // 10 (priority 1)
    printf("Dequeued: %d\n", dequeuePQ(&pq));  // 20 (priority 2)

    printf("\nAfter 2 dequeues:\n");
    displayPQ(&pq);
    printf("Total elements: %d\n", countPQ(&pq));

    return 0;
}