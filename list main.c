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

void insertAt(Node** head, int val, int pos) {
    if (pos == 0) { insertFront(head, val); return; }
    Node* cur = *head;
    for (int i = 0; i < pos - 1 && cur; i++) cur = cur->next;
    if (!cur) { printf("  [!] Position out of range.\n"); return; }
    Node* n = createNode(val);
    n->next = cur->next;
    cur->next = n;
}

void insertSorted(Node** head, int val) {
    if (!*head || (*head)->data >= val) { insertFront(head, val); return; }
    Node* cur = *head;
    while (cur->next && cur->next->data < val) cur = cur->next;
    Node* n = createNode(val);
    n->next = cur->next;
    cur->next = n;
}

void deleteVal(Node** head, int val) {
    if (!*head) { printf("  [!] List is empty.\n"); return; }
    if ((*head)->data == val) {
        Node* tmp = *head;
        *head = (*head)->next;
        free(tmp);
        printf("  [+] Deleted first occurrence of %d.\n", val);
        return;
    }
    Node* cur = *head;
    while (cur->next && cur->next->data != val) cur = cur->next;
    if (!cur->next) { printf("  [!] Value %d not found.\n", val); return; }
    Node* tmp = cur->next;
    cur->next = tmp->next;
    free(tmp);
    printf("  [+] Deleted %d.\n", val);
}

void deleteAt(Node** head, int pos) {
    if (!*head) { printf("  [!] List is empty.\n"); return; }
    if (pos == 0) {
        Node* tmp = *head;
        *head = (*head)->next;
        free(tmp);
        printf("  [+] Deleted node at position 0.\n");
        return;
    }
    Node* cur = *head;
    for (int i = 0; i < pos - 1 && cur->next; i++) cur = cur->next;
    if (!cur->next) { printf("  [!] Position out of range.\n"); return; }
    Node* tmp = cur->next;
    cur->next = tmp->next;
    free(tmp);
    printf("  [+] Deleted node at position %d.\n", pos);
}

void search(Node* head, int val) {
    int pos = 0;
    while (head) {
        if (head->data == val) { printf("  [+] Found %d at position %d.\n", val, pos); return; }
        head = head->next; pos++;
    }
    printf("  [!] %d not found.\n", val);
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

int length(Node* head) {
    int c = 0;
    while (head) { c++; head = head->next; }
    return c;
}

void reverse(Node** head) {
    Node *prev = NULL, *cur = *head, *nxt;
    while (cur) { nxt = cur->next; cur->next = prev; prev = cur; cur = nxt; }
    *head = prev;
}

void display(Node* head) {
    if (!head) { printf("  List: (empty)\n"); return; }
    printf("  List: ");
    while (head) {
        printf("[%d]", head->data);
        if (head->next) printf(" -> ");
        head = head->next;
    }
    printf("\n");
}

void freeList(Node** head) {
    Node* cur = *head, *tmp;
    while (cur) { tmp = cur->next; free(cur); cur = tmp; }
    *head = NULL;
}

void printMenu() {
    printf("\n");
    printf("       LINKED LIST MENU         \n");
    printf("\n");
    printf(" 1. Insert at Front            \n");
    printf("  2. Insert at Back             \n");
    printf(" 3. Insert at Position         \n");
    printf("  4. Insert Sorted              \n");
    printf("  5. Delete by Value            \n");
    printf(" 6. Delete at Position         \n");
    printf("  7. Search                     \n");
    printf(" 8. Max / Min                  \n");
    printf("  9. Count Occurrences          \n");
    printf(" 10. Length                     \n");
    printf(" 11. Reverse                    \n");
    printf(" 12. Display                    \n");
    printf("  0. Exit                       \n");
    printf("\n");
    printf("  Choice: ");
}

int main() {
    Node* head = NULL;
    int choice, val, pos;

    printf("\n  === Linked List Interactive Menu ===\n");

    do {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("  Enter value: "); scanf("%d", &val);
                insertFront(&head, val);
                display(head); break;

            case 2:
                printf("  Enter value: "); scanf("%d", &val);
                insertBack(&head, val);
                display(head); break;

            case 3:
                printf("  Enter value: "); scanf("%d", &val);
                printf("  Enter position: "); scanf("%d", &pos);
                insertAt(&head, val, pos);
                display(head); break;

            case 4:
                printf("  Enter value: "); scanf("%d", &val);
                insertSorted(&head, val);
                display(head); break;

            case 5:
                printf("  Enter value to delete: "); scanf("%d", &val);
                deleteVal(&head, val);
                display(head); break;

            case 6:
                printf("  Enter position to delete: "); scanf("%d", &pos);
                deleteAt(&head, pos);
                display(head); break;

            case 7:
                printf("  Enter value to search: "); scanf("%d", &val);
                search(head, val); break;

            case 8:
                if (!head) { printf("  [!] List is empty.\n"); break; }
                printf("  Max = %d\n", maxVal(head));
                printf("  Min = %d\n", minVal(head)); break;

            case 9:
                printf("  Enter value: "); scanf("%d", &val);
                printf("  Occurrences of %d = %d\n", val, countOcc(head, val)); break;

            case 10:
                printf("  Length = %d\n", length(head)); break;

            case 11:
                reverse(&head);
                printf("  [+] List reversed.\n");
                display(head); break;

            case 12:
                display(head); break;

            case 0:
                printf("  Goodbye!\n");
                freeList(&head); break;

            default:
                printf("  [!] Invalid choice.\n");
        }

    } while (choice != 0);

    return 0;
}