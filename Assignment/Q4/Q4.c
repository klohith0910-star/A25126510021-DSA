#include <stdio.h>
#define SIZE 5
int q[SIZE], front = -1, rear = -1;
void enqueue(int id) {
    if ((front == 0 && rear == SIZE - 1) ||
        (front == rear + 1)) {
        printf("Queue Overflow! Request buffer is full.\n");
        return;
    }

    if (front == -1) {
        front = rear = 0;
    } else if (rear == SIZE - 1) {
        rear = 0;
    } else {
        rear++;
    }

    q[rear] = id;
    printf("Request %d inserted at slot %d\n", id, rear);
}
void dequeue() {
    if (front == -1) {
        printf("Queue Underflow! Buffer is empty.\n");
        return;
    }

    printf("Request %d processed and removed from slot %d\n",
           q[front], front);

    if (front == rear) {
        front = rear = -1;
    } else if (front == SIZE - 1) {
        front = 0;
    } else {
        front++;
    }
}

void display() {
    if (front == -1) {
        printf("Request buffer is empty.\n");
        return;
    }

    printf("Current Buffer: ");

    int i = front;

    while (1) {
        printf("[%d: %d] ", i, q[i]);

        if (i == rear)
            break;

        i = (i + 1) % SIZE;
    }

    printf("\n");
}

int main() {
    int choice, val;

    while (1) {
        printf("\n1.Insert Request 2.Process Request 3.Display Buffer 4.Exit: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter Request ID: ");
            scanf("%d", &val);
            enqueue(val);
        } else if (choice == 2) {
            dequeue();
        } else if (choice == 3) {
            display();
        } else if (choice == 4) {
            break;
        } else {
            printf("Invalid selection!\n");
        }
    }

    return 0;
}
