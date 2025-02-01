
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

// Structure to store student details
typedef struct {
    char name[50];
    int rollNumber;
    char grade[5];
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

// Function to add a student
void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Student list is full.\n");
        return;
    }

    printf("Enter student name: ");
    scanf("%s", students[studentCount].name);

    printf("Enter student roll number: ");
    scanf("%d", &students[studentCount].rollNumber);

    printf("Enter student grade: ");
    scanf("%s", students[studentCount].grade);

    studentCount++;
    printf("Student added successfully!\n");
}

// Function to display all students
void displayStudents() {
    if (studentCount == 0) {
        printf("No students found.\n");
        return;
    }

    printf("\nStudent Details:\n");
    for (int i = 0; i < studentCount; i++) {
        printf("Name: %s, Roll Number: %d, Grade: %s\n", 
                students[i].name, students[i].rollNumber, students[i].grade);
    }
}

// Function to search a student by roll number
void searchStudent() {
    int rollNumber;
    printf("Enter roll number to search: ");
    scanf("%d", &rollNumber);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == rollNumber) {
            printf("Student found: \n");
            printf("Name: %s, Roll Number: %d, Grade: %s\n", 
                    students[i].name, students[i].rollNumber, students[i].grade);
            return;
        }
    }
    printf("Student with roll number %d not found.\n", rollNumber);
}

// Main function
int main() {
    int choice;

    while (1) {
        printf("\nStudent Management System\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student by Roll Number\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

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
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
