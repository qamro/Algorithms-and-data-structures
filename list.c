#include <stdio.h>
#include <stdlib.h> 
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Always initialize head to NULL
Node* head = NULL;

Node* createNode(int val) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = val;
    n->next = NULL;
    return n;
}

// Insert at front — O(1)
void insertFront(Node** head, int val) {
    Node* n = createNode(val);
    n->next = *head;
    *head = n;
}

// Insert at back — O(n)
void insertBack(Node** head, int val) {
    Node* n = createNode(val);
    if (*head == NULL) { *head = n; return; }
    Node* cur = *head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
}

// Insert at position k (0-indexed)
void insertAt(Node** head, int val, int k) {
    if (k == 0) { insertFront(head, val); return; }
    Node* cur = *head;
    for (int i = 0; i < k-1 && cur != NULL; i++) cur = cur->next;
    if (!cur) return; // position out of range
    Node* n = createNode(val);
    n->next = cur->next;
    cur->next = n;
}

// Delete front
void deleteFront(Node** head) {
    if (!*head) return;
    Node* tmp = *head;
    *head = (*head)->next;
    free(tmp);
}

// Delete node with given value (first occurrence)
void deleteVal(Node** head, int val) {
    if (!*head) return;
    if ((*head)->data == val) { deleteFront(head); return; }
    Node* cur = *head;
    while (cur->next && cur->next->data != val)
        cur = cur->next;
    if (cur->next) {
        Node* tmp = cur->next;
        cur->next = tmp->next;
        free(tmp);
    }
}

// Delete ALL nodes with given value
void deleteAllVal(Node** head, int val) {
    while (*head && (*head)->data == val) deleteFront(head);
    Node* cur = *head;
    while (cur && cur->next) {
        if (cur->next->data == val) {
            Node* tmp = cur->next;
            cur->next = tmp->next;
            free(tmp);
        } else cur = cur->next;
    }
}

// Search — returns 1 if found
int search(Node* head, int val) {
    while (head) {
        if (head->data == val) return 1;
        head = head->next;
    }
    return 0;
}

void display(Node* head) {
    while (head) { printf("%d ", head->data); head = head->next; }
    printf("\n");
}

void freeList(Node** head) {
    Node* cur = *head, *tmp;
    while (cur) { tmp = cur->next; free(cur); cur = tmp; }
    *head = NULL;
}