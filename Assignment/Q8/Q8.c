#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int val) {
    struct Node *n = malloc(sizeof(struct Node));

    if (n == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    n->data = val;
    n->left = NULL;
    n->right = NULL;

    return n;
}

struct Node *insert(struct Node *root, int val) {
    if (root == NULL)
        return createNode(val);

    if (val < root->data)
        root->left = insert(root->left, val);
    else if (val > root->data)
        root->right = insert(root->right, val);

    return root;
}

struct Node *findMin(struct Node *root) {
    while (root != NULL && root->left != NULL)
        root = root->left;

    return root;
}

struct Node *deleteNode(struct Node *root, int val, int *deleted) {
    if (root == NULL)
        return NULL;

    if (val < root->data) {
        root->left = deleteNode(root->left, val, deleted);
    } else if (val > root->data) {
        root->right = deleteNode(root->right, val, deleted);
    } else {
        *deleted = 1;

        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        } else {
            struct Node *temp = findMin(root->right);
            root->data = temp->data;
            int successorDeleted = 0;
            root->right = deleteNode(root->right, temp->data, &successorDeleted);
        }
    }

    return root;
}

void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void freeTree(struct Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    struct Node *root = NULL;
    int n, val, delVal;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    if (n < 0)
        return 1;

    printf("Enter values to insert:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        root = insert(root, val);
    }

    printf("Inorder before deletion: ");
    inorder(root);
    printf("\n");

    while (1) {
        printf("\nEnter value to delete (-1 to exit): ");
        scanf("%d", &delVal);

        if (delVal == -1)
            break;

        printf("Inorder before: ");
        inorder(root);
        printf("\n");

        int deleted = 0;
        root = deleteNode(root, delVal, &deleted);

        if (!deleted)
            printf("Node %d not found in the BST.\n", delVal);

        printf("Inorder after: ");
        inorder(root);
        printf("\n");
    }

    freeTree(root);

    return 0;
}
