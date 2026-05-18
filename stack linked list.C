#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

// Initialize
void initStack(Stack *s) {
    s->top = NULL;
}

// Check if empty
int isEmpty(Stack *s) {
    return s->top == NULL;
}

// Push
void push(Stack *s, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
}

// Pop
int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow!\n");
        return -1;
    }
    Node *temp = s->top;
    int value = temp->data;
    s->top = s->top->next;
    free(temp);
    return value;
}

// Peek
int peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return s->top->data;
}

// Display
void displayStack(Stack *s) {
    Node *curr = s->top;
    printf("Stack (top -> bottom): ");
    while (curr) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}