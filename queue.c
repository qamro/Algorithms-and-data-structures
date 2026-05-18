#include <stdio.h>
#define MAX_SIZE 100

typedef struct {
    int items[MAX_SIZE];
    int front, rear;
} Queue;

// Initialize
void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if empty
int isEmpty(Queue *q) {
    return q->front == -1;
}

// Check if full
int isFull(Queue *q) {
    return q->rear == MAX_SIZE - 1;
}

// Enqueue (insert at rear)
void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue is full!\n");
        return;
    }
    if (isEmpty(q))
        q->front = 0;
    q->items[++(q->rear)] = value;
}

// Dequeue (remove from front)
int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    int value = q->items[q->front];
    if (q->front == q->rear)
        initQueue(q);      // queue becomes empty
    else
        q->front++;
    return value;
}

// Peek (front element without removing)
int peekQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return q->items[q->front];
}

// Display
void displayQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue (front -> rear): ");
    for (int i = q->front; i <= q->rear; i++)
        printf("%d ", q->items[i]);
    printf("\n");
}

// Main test
int main() {
    Queue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    displayQueue(&q);           // 10 20 30

    printf("Dequeued: %d\n", dequeue(&q));  // 10
    printf("Front element: %d\n", peekQueue(&q)); // 20
    displayQueue(&q);           // 20 30

    return 0;
}