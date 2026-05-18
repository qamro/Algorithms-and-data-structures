#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct {
    Node *top;
} Stack;


/*
 * Move all integers from S1 into S2
 * such that all even numbers are BELOW odd numbers in S2.
 */
void moveEvensBelowOdds(Stack *S1, Stack *S2) {
    Stack temp;
    initStack(&temp);

    // Step 1: Separate — push odds to S2, evens to temp
    while (!isEmpty(S1)) {
        int val = pop(S1);
        if (val % 2 != 0)
            push(S2, val);     // odd → goes to S2
        else
            push(&temp, val);  // even → goes to temp
    }

    // Step 2: Push evens from temp onto S2 (they end up below odds)
    while (!isEmpty(&temp)) {
        push(S2, pop(&temp));
    }

    // S1 is now empty, S2 has: odds on top, evens at bottom
}