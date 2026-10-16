/*
 * ===========================================================
 *   STUDENT RECORD MANAGEMENT SYSTEM (Singly Linked List)
 * ===========================================================
 *  Features:
 *   1. Add Student
 *   2. Display Records
 *   3. Search Student (by Roll No)
 *   4. Update Student (Name / Marks)
 *   5. Delete Student
 *   6. Exit
 *   + Duplicate Roll Number Handling
 * ===========================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------------- Node Structure ---------------- */
typedef struct Student {
    int rollNo;
    char name[50];
    float marks;
    struct Student *next;
} Student;

/* Global head pointer for the linked list */
Student *head = NULL;

/* ---------------- Function Prototypes ---------------- */
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
int isRollNumberExists(int rollNo);
Student* createNode(int rollNo, char name[], float marks);
void freeAllMemory();

/* ---------------- Main Function ---------------- */
int main() {
    int choice;

    printf("=====================================================\n");
    printf("     STUDENT RECORD MANAGEMENT SYSTEM (Linked List)\n");
    printf("=====================================================\n");

    do {
        printf("\n===== STUDENT RECORD MANAGEMENT =====\n");
        printf("1. Add Student\n");
        printf("2. Display Records\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("======================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            // clear invalid input
            while (getchar() != '\n');
            printf("Invalid input! Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                printf("\nExiting program... Freeing allocated memory.\n");
                freeAllMemory();
                printf("Thank you for using the system!\n");
                break;
            default:
                printf("Invalid choice! Please select between 1-6.\n");
        }

    } while (choice != 6);

    return 0;
}

/* ---------------- Create a New Node ---------------- */
Student* createNode(int rollNo, char name[], float marks) {
    Student *newNode = (Student*) malloc(sizeof(Student));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->rollNo = rollNo;
    strcpy(newNode->name, name);
    newNode->marks = marks;
    newNode->next = NULL;
    return newNode;
}

/* ---------------- Check Duplicate Roll Number ---------------- */
int isRollNumberExists(int rollNo) {
    Student *temp = head;
    while (temp != NULL) {
        if (temp->rollNo == rollNo)
            return 1;   // Duplicate found
        temp = temp->next;
    }
    return 0;   // No duplicate
}

/* ---------------- Add Student Record ---------------- */
void addStudent() {
    int rollNo;
    char name[50];
    float marks;

    printf("\n--- Add New Student ---\n");
    printf("Enter Roll Number: ");
    scanf("%d", &rollNo);

    /* Duplicate Roll Number Handling */
    if (isRollNumberExists(rollNo)) {
        printf("Error: Student with Roll No %d already exists!\n", rollNo);
        return;
    }

    printf("Enter Name: ");
    scanf("%s", name);

    printf("Enter Marks: ");
    scanf("%f", &marks);

    Student *newNode = createNode(rollNo, name, marks);

    /* Insert at the end of the list */
    if (head == NULL) {
        head = newNode;
    } else {
        Student *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }

    printf("Student record added successfully!\n");
}

/* ---------------- Display All Records ---------------- */
void displayStudents() {
    printf("\n--- Student Records ---\n");

    if (head == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("--------------------------------------------\n");
    printf("| %-8s | %-15s | %-8s |\n", "Roll No", "Name", "Marks");
    printf("--------------------------------------------\n");

    Student *temp = head;
    while (temp != NULL) {
        printf("| %-8d | %-15s | %-8.2f |\n",
               temp->rollNo, temp->name, temp->marks);
        temp = temp->next;
    }
    printf("--------------------------------------------\n");
}

/* ---------------- Search Student by Roll Number ---------------- */
void searchStudent() {
    int rollNo;
    printf("\n--- Search Student ---\n");
    printf("Enter Roll Number to search: ");
    scanf("%d", &rollNo);

    Student *temp = head;
    while (temp != NULL) {
        if (temp->rollNo == rollNo) {
            printf("\nStudent Found!\n");
            printf("Roll No: %d\n", temp->rollNo);
            printf("Name   : %s\n", temp->name);
            printf("Marks  : %.2f\n", temp->marks);
            return;
        }
        temp = temp->next;
    }

    printf("Student with Roll No %d not found!\n", rollNo);
}

/* ---------------- Update Student Record ---------------- */
void updateStudent() {
    int rollNo, choice;
    printf("\n--- Update Student ---\n");
    printf("Enter Roll Number to update: ");
    scanf("%d", &rollNo);

    Student *temp = head;
    while (temp != NULL) {
        if (temp->rollNo == rollNo) {
            printf("Student Found: %s, Marks: %.2f\n", temp->name, temp->marks);
            printf("What do you want to update?\n");
            printf("1. Name\n2. Marks\n3. Both\n");
            printf("Enter choice: ");
            scanf("%d", &choice);

            if (choice == 1 || choice == 3) {
                printf("Enter new Name: ");
                scanf("%s", temp->name);
            }
            if (choice == 2 || choice == 3) {
                printf("Enter new Marks: ");
                scanf("%f", &temp->marks);
            }

            printf("Record updated successfully!\n");
            return;
        }
        temp = temp->next;
    }

    printf("Student with Roll No %d not found!\n", rollNo);
}

/* ---------------- Delete Student Record ---------------- */
void deleteStudent() {
    int rollNo;
    printf("\n--- Delete Student ---\n");
    printf("Enter Roll Number to delete: ");
    scanf("%d", &rollNo);

    if (head == NULL) {
        printf("No records available to delete!\n");
        return;
    }

    Student *temp = head, *prev = NULL;

    /* If head node itself holds the roll number */
    if (temp->rollNo == rollNo) {
        head = temp->next;
        free(temp);
        printf("Student record deleted successfully!\n");
        return;
    }

    /* Search for the node to delete */
    while (temp != NULL && temp->rollNo != rollNo) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Student with Roll No %d not found!\n", rollNo);
        return;
    }

    /* Unlink the node from the list */
    prev->next = temp->next;
    free(temp);
    printf("Student record deleted successfully!\n");
}

/* ---------------- Free All Allocated Memory ---------------- */
void freeAllMemory() {
    Student *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
