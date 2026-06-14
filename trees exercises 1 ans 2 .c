#include <stdio.h>
#include <stdlib.h>

/* ============================================================
   EXERCISE 01 — Binary Tree (BT)
   ============================================================ */

/* ---------- Structure ---------- */
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

/* ---------- CreateNode ---------- */
Node *CreateNode(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    node->data  = value;
    node->left  = NULL;
    node->right = NULL;
    return node;
}

/* ---------- IsEmpty ---------- */
int IsEmpty(Node *root) {
    return root == NULL;
}

/* ---------- Traversals ---------- */
void InOrder(Node *root) {          /* Left → Root → Right */
    if (!root) return;
    InOrder(root->left);
    printf("%d ", root->data);
    InOrder(root->right);
}

void PreOrder(Node *root) {         /* Root → Left → Right */
    if (!root) return;
    printf("%d ", root->data);
    PreOrder(root->left);
    PreOrder(root->right);
}

void PostOrder(Node *root) {        /* Left → Right → Root */
    if (!root) return;
    PostOrder(root->left);
    PostOrder(root->right);
    printf("%d ", root->data);
}

/* ---------- Count ---------- */
int CountNodes(Node *root) {
    if (!root) return 0;
    return 1 + CountNodes(root->left) + CountNodes(root->right);
}

/* ---------- IsLeaf ---------- */
int IsLeaf(Node *node) {
    return node && node->left == NULL && node->right == NULL;
}

/* ---------- Display leaves ---------- */
void DisplayLeaves(Node *root) {
    if (!root) return;
    if (IsLeaf(root)) {
        printf("%d ", root->data);
        return;
    }
    DisplayLeaves(root->left);
    DisplayLeaves(root->right);
}

/* ---------- Depth ---------- */
int Depth(Node *root) {
    if (!root) return 0;
    int leftDepth  = Depth(root->left);
    int rightDepth = Depth(root->right);
    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}

/* ============================================================
   EXERCISE 02 — Binary Search Tree (BST)
   ============================================================ */

/* CreateNode is reused from Exercise 01 */

/* ---------- Insert ---------- */
Node *Insert(Node *root, int value) {
    if (!root) return CreateNode(value);        /* Base case: empty spot found */

    if (value < root->data)
        root->left  = Insert(root->left,  value);
    else if (value > root->data)
        root->right = Insert(root->right, value);
    /* Duplicate values are ignored */

    return root;
}

/* ---------- Search ---------- */
Node *Search(Node *root, int value) {
    if (!root || root->data == value) return root;  /* NULL or found */

    if (value < root->data)
        return Search(root->left,  value);
    else
        return Search(root->right, value);
}

/* ---------- FindMin (helper for Delete) ---------- */
Node *FindMin(Node *root) {
    while (root->left)
        root = root->left;
    return root;
}

/* ---------- Delete ---------- */
Node *Delete(Node *root, int value) {
    if (!root) return NULL;     /* Value not found */

    if (value < root->data) {
        root->left  = Delete(root->left,  value);
    } else if (value > root->data) {
        root->right = Delete(root->right, value);
    } else {
        /* Node to delete found */
        if (!root->left) {                      /* No left child */
            Node *temp = root->right;
            free(root);
            return temp;
        } else if (!root->right) {              /* No right child */
            Node *temp = root->left;
            free(root);
            return temp;
        }
        /* Two children: replace with in-order successor (smallest in right subtree) */
        Node *successor = FindMin(root->right);
        root->data  = successor->data;
        root->right = Delete(root->right, successor->data);
    }
    return root;
}

/* ============================================================
   MAIN — Tests for both exercises
   ============================================================ */
int main(void) {

    /* ---- Exercise 01 Demo ---- */
    printf("==============================================\n");
    printf("  EXERCISE 01 — Binary Tree\n");
    printf("==============================================\n\n");

    /*
         Build this tree manually:
                  10
                 /  \
                5    20
               / \   / \
              3   7 15  25
    */
    Node *bt = CreateNode(10);
    bt->left          = CreateNode(5);
    bt->right         = CreateNode(20);
    bt->left->left    = CreateNode(3);
    bt->left->right   = CreateNode(7);
    bt->right->left   = CreateNode(15);
    bt->right->right  = CreateNode(25);

    printf("Tree structure:\n");
    printf("        10\n");
    printf("       /  \\\n");
    printf("      5    20\n");
    printf("     / \\  /  \\\n");
    printf("    3   7 15  25\n\n");

    printf("Is tree empty?  %s\n", IsEmpty(bt) ? "Yes" : "No");

    printf("In-Order   (L-Root-R): ");  InOrder(bt);    printf("\n");
    printf("Pre-Order  (Root-L-R): ");  PreOrder(bt);   printf("\n");
    printf("Post-Order (L-R-Root): ");  PostOrder(bt);  printf("\n");

    printf("Node count:  %d\n",  CountNodes(bt));
    printf("Is node 5 a leaf? %s\n", IsLeaf(bt->left)  ? "Yes" : "No");
    printf("Is node 3 a leaf? %s\n", IsLeaf(bt->left->left) ? "Yes" : "No");

    printf("Leaves: ");  DisplayLeaves(bt);  printf("\n");
    printf("Depth:  %d\n", Depth(bt));

    /* ---- Exercise 02 Demo ---- */
    printf("\n==============================================\n");
    printf("  EXERCISE 02 — Binary Search Tree (BST)\n");
    printf("==============================================\n\n");

    Node *bst = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(values) / sizeof(values[0]);

    printf("Inserting: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
        bst = Insert(bst, values[i]);
    }
    printf("\n\n");

    printf("BST structure:\n");
    printf("         50\n");
    printf("        /  \\\n");
    printf("       30   70\n");
    printf("      / \\  /  \\\n");
    printf("     20 40 60  80\n\n");

    printf("In-Order (should be sorted): ");
    InOrder(bst);
    printf("\n");

    /* Search */
    int target = 40;
    Node *found = Search(bst, target);
    printf("\nSearch(%d): %s\n", target, found ? "Found" : "Not found");

    target = 99;
    found = Search(bst, target);
    printf("Search(%d): %s\n", target, found ? "Found" : "Not found");

    /* Delete a leaf */
    printf("\nDelete 20 (leaf):\n");
    bst = Delete(bst, 20);
    printf("In-Order after: "); InOrder(bst); printf("\n");

    /* Delete a node with one child */
    printf("\nDelete 30 (one child):\n");
    bst = Delete(bst, 30);
    printf("In-Order after: "); InOrder(bst); printf("\n");

    /* Delete the root */
    printf("\nDelete 50 (root, two children):\n");
    bst = Delete(bst, 50);
    printf("In-Order after: "); InOrder(bst); printf("\n");

    printf("\nAll operations completed successfully.\n");
    return 0;
}