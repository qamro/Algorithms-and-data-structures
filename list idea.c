// Length of list
int length(Node* head) {
    int c = 0;
    while (head) { c++; head = head->next; }
    return c;
}

// Max and Min
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

// Count occurrences of a value
int countOcc(Node* head, int val) {
    int c = 0;
    while (head) { if (head->data == val) c++; head = head->next; }
    return c;
}

// Sum and Average
int sum(Node* head) {
    int s = 0;
    while (head) { s += head->data; head = head->next; }
    return s;
}

// Reverse the list
void reverse(Node** head) {
    Node *prev = NULL, *cur = *head, *next;
    while (cur) {
        next = cur->next;
        cur->next = prev;
        prev = cur; cur = next;
    }
    *head = prev;
}

// Is list sorted (ascending)?
int isSorted(Node* head) {
    while (head && head->next) {
        if (head->data > head->next->data) return 0;
        head = head->next;
    }
    return 1;
}