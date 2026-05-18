#include <stdio.h>
#define MAX_SIZE 100

typedef struct {
    int items[MAX_SIZE];
    int top;
} Stack;

// Initialize
void initStack(Stack *s) {
    s->top = -1;
}

// Check if empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Check if full
int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

// Push
void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack overflow!\n");
        return;
    }
    s->items[++(s->top)] = value;
}

// Pop
int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow!\n");
        return -1;
    }
    return s->items[(s->top)--];
}

// Peek (top element without removing)
int peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return s->items[s->top];
}

// Display
void displayStack(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack (top -> bottom): ");
    for (int i = s->top; i >= 0; i--)
        printf("%d ", s->items[i]);
    printf("\n");
}