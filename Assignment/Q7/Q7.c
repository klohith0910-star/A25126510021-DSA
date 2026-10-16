#include <stdio.h>
#include <stdlib.h>

struct Node {
    int id;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int val) {
    struct Node *n = malloc(sizeof(struct Node));

    if (n == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    n->id = val;
    n->left = NULL;
    n->right = NULL;

    return n;
}

struct Node *insert(struct Node *root, int val) {
    if (root == NULL)
        return createNode(val);

    if (val < root->id)
        root->left = insert(root->left, val);
    else if (val > root->id)
        root->right = insert(root->right, val);

    return root;
}

void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->id);
        inorder(root->right);
    }
}

void preorder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->id);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct Node *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->id);
    }
}

int search(struct Node *root, int val) {
    if (root == NULL)
        return 0;

    if (root->id == val)
        return 1;

    if (val < root->id)
        return search(root->left, val);

    return search(root->right, val);
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
    int n, val, key;

    printf("Enter number of identification numbers: ");
    scanf("%d", &n);

    if (n < 0)
        return 1;

    printf("Enter unique IDs:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        root = insert(root, val);
    }

    printf("\nInorder Traversal: ");
    inorder(root);

    printf("\nPreorder Traversal: ");
    preorder(root);

    printf("\nPostorder Traversal: ");
    postorder(root);

    printf("\nEnter ID to search: ");
    scanf("%d", &key);

    if (search(root, key))
        printf("ID %d exists in the BST.\n", key);
    else
        printf("ID %d does not exist in the BST.\n", key);

    printf("Inorder traversal produces sorted values because it visits the left subtree, root, and right subtree.\n");

    freeTree(root);

    return 0;
}
