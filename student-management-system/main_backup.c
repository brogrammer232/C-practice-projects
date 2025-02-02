
// Imports.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Global variables.
struct Student {
	char name[20];
	int ID;
	int grade;
	struct {
		char town[10];
		char street[10];
		int zip;
	} address;
};

struct Student STUDENTS[10];
int studentCount = 0;


// Functions declaration.
void addStudent();
void displayStudents();
char getCharacter();
void printOptions();


// Main function.
int main() {
	char user_input;

	// Mainloop.
	while (true) {
		system("clear");
		printOptions();
		user_input = getCharacter();

		if ('e' == user_input) {exit(0);}
		else if ('1' == user_input) {displayStudents();}
		else if ('2' == user_input) {addStudent();}
		else {
			printf("Invalid option!! Try again.: %c\n", user_input);
		}
	}

	return 0;
}


// Functions definition.
void addStudent() {
    /* This function adds a student to STUDENTS. It asks the user to
    provide every required field. The student ID is automatically
    generated. */
    
    // Prevent adding a student if we reach the limit of 10 students.
    if (10 <= studentCount) {
        printf("Student limit reached! Cannot add more students.\n");
        return;
    }

    // Ask for student details
    system("clear");
    printf("What's the student's name: ");
    scanf("%19s", STUDENTS[studentCount].name); // Limit input to 19 chars for safety

    printf("Enter student's grade: ");
    scanf("%d", &STUDENTS[studentCount].grade);

    printf("Provide the following for the address.\n");
    printf("Town: ");
    scanf("%9s", STUDENTS[studentCount].address.town); // Limit input to 9 chars for safety

    printf("Street: ");
    scanf("%9s", STUDENTS[studentCount].address.street); // Limit input to 9 chars for safety

    printf("Zip: ");
    scanf("%d", &STUDENTS[studentCount].address.zip);

    STUDENTS[studentCount].ID = studentCount;

    // Increment student count after adding the student
    studentCount++;

    printf("Student added successfully!\n");
    printf("Press any key to continue.\n");
    getCharacter();
}


void displayStudents() {
	/* This function prints all the students in the system. */
	struct Student student;

	system("clear");
	if (0 == studentCount) {
		printf("There are currently no students in the system.\n");
	}
	else {
		for (int i = 0; i < studentCount; i++) {
			student = STUDENTS[i];
			printf("Student %d.\n", (i + 1));
			printf("    Name: %s\n", student.name);
			printf("    ID: %d\n", student.ID);
			printf("    Grade: %d\n", student.grade);
			printf("    Address: %s town, %s street, %d zip\n",
				student.address.town, student.address.street,
				student.address.zip);
		}
	}

	printf("Press any key to continue.\n");
    getCharacter();
}


char getCharacter() {
	/* This option gets and returns a character from the user. */
	char character = getchar();
	if ('\n' == character) {return getCharacter();} // Recursive function to avoid newlines.
	return character;
}


void printOptions() {
	/* This functions prints all the available options. */
	printf("Student Management System.\n");
	printf("    1: Display students.\n");
	printf("    2: Add student.\n");
	printf("    e: Exit\n");
}