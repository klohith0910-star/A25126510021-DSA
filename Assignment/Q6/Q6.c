#include <stdio.h>
#include <stdlib.h>

struct Node {
    int page;
    struct Node *prev;
    struct Node *next;
};

struct Node *head = NULL;
struct Node *curr = NULL;

void insertPage(int id) {
    struct Node *n = malloc(sizeof(struct Node));

    if (n == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    n->page = id;
    n->prev = NULL;
    n->next = NULL;

    if (head == NULL) {
        head = n;
    } else {
        struct Node *temp = head;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = n;
        n->prev = temp;
    }

    curr = n;
    printf("Visited page %d\n", id);
}

void moveForward() {
    if (curr != NULL && curr->next != NULL) {
        curr = curr->next;
        printf("Moved forward to page %d\n", curr->page);
    } else {
        printf("Already at the latest page. Forward not possible.\n");
    }
}

void moveBackward() {
    if (curr != NULL && curr->prev != NULL) {
        curr = curr->prev;
        printf("Moved backward to page %d\n", curr->page);
    } else {
        printf("Already at the first page. Backward not possible.\n");
    }
}

void displayForward() {
    struct Node *temp = head;

    if (temp == NULL) {
        printf("No browsing history.\n");
        return;
    }

    printf("Pages (First-to-Last): ");

    while (temp != NULL) {
        printf("%d ", temp->page);
        temp = temp->next;
    }

    printf("\n");
}

void displayBackward() {
    struct Node *temp = head;

    if (temp == NULL) {
        printf("No browsing history.\n");
        return;
    }

    while (temp->next != NULL)
        temp = temp->next;

    printf("Pages (Last-to-First): ");

    while (temp != NULL) {
        printf("%d ", temp->page);
        temp = temp->prev;
    }

    printf("\n");
}

void deletePage(int id) {
    struct Node *temp = head;

    while (temp != NULL && temp->page != id)
        temp = temp->next;

    if (temp == NULL) {
        printf("Page %d not found in history.\n", id);
        return;
    }

    if (temp->prev != NULL)
        temp->prev->next = temp->next;
    else
        head = temp->next;

    if (temp->next != NULL)
        temp->next->prev = temp->prev;

    if (curr == temp)
        curr = temp->next != NULL ? temp->next : temp->prev;

    free(temp);

    printf("Page %d deleted from history.\n", id);
}

int main() {
    int choice, id;

    while (1) {
        printf("\n1.Visit Page 2.Forward 3.Backward 4.Display Forward 5.Display Backward 6.Delete Page 7.Exit: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter Page ID: ");
            scanf("%d", &id);
            insertPage(id);
        } else if (choice == 2) {
            moveForward();
        } else if (choice == 3) {
            moveBackward();
        } else if (choice == 4) {
            displayForward();
        } else if (choice == 5) {
            displayBackward();
        } else if (choice == 6) {
            printf("Enter Page ID to delete: ");
            scanf("%d", &id);
            deletePage(id);
        } else if (choice == 7) {
            break;
        } else {
            printf("Invalid selection!\n");
        }
    }

    while (head != NULL) {
        struct Node *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
