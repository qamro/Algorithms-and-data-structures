int queueMax(Node* front) {
    int m = front->data;
    while (front) { if (front->data > m) m = front->data; front = front->next; }
    return m;
}

// Count occurrences
int queueCount(Node* front, int val) {
    int c = 0;
    while (front) { if (front->data == val) c++; front = front->next; }
    return c;
}

// Reverse a queue using a stack
void reverseQueue(Node** front, Node** rear) {
    Node* stk = NULL;
    while (!isEmptyQ(*front))
        push(&stk, dequeue(front, rear));
    while (!isEmpty(stk))
        enqueue(front, rear, pop(&stk));
}

// Delete element with given value from queue
void deleteQVal(Node** front, Node** rear, int val) {
    Node* tmp = NULL, *tmpR = NULL;
    int n = sizeQ(*front);
    for (int i = 0; i < n; i++) {
        int x = dequeue(front, rear);
        if (x != val) enqueue(&tmp, &tmpR, x);
    }
    *front = tmp; *rear = tmpR;
}