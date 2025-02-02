
// Imports.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Global variables.
struct Student {
	char *name;
	int ID;
	int grade;
	struct {
		char *town;
		char *street;
		int zip;
	} address;
};

struct Student STUDENTS[10];
int studentCount = 0;


// Functions declaration.
void addStudent();
void displayStudents();
void showContinueMessage();
char getCharacter();
int getInteger(int *variable);
char* getLine();
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
    STUDENTS[studentCount].name = getLine();

    printf("Enter student's grade: ");
    getInteger(&STUDENTS[studentCount].grade);

    printf("Provide the following for the address.\n");
    printf("Town: ");
    STUDENTS[studentCount].address.town = getLine();

    printf("Street: ");
    STUDENTS[studentCount].address.street = getLine();

    printf("Zip: ");
    getInteger(&STUDENTS[studentCount].address.zip);

    STUDENTS[studentCount].ID = ++studentCount;

    printf("Student added successfully!\n\n");
    showContinueMessage();
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
			printf("    Address: %s town, %s street, %d zip\n\n",
				student.address.town, student.address.street,
				student.address.zip);
		}
	}

	showContinueMessage();
}


void showContinueMessage(){
	/* This function simply directs the user to press a certain key
	to move to the next screen. */
	printf("Press ENTER to continue.\n");
	getchar();
}


char getCharacter() {
	/* This option gets and returns a character from the user. */
	char character = getchar();
	if ('\n' == character) {return getCharacter();} // Recursive function to avoid newlines.
	getchar();
	return character;
}


int getInteger(int *variable) {
	/* This function gets an integer input from the user and stores it
	in the given variable. It also takes the newline character to avoid
	bugs. */
	scanf("%d", variable);
	getchar();
}


char* getLine() {
	/* This function gets a line of unlimited size and returns it. */
	char character;
	int input_size = 0;

	// Initial memory allocation.
	char *line = (char*) malloc(1);
	if (!line) {
		printf("Memory allocation failed.\n");
		return NULL;
	}


	// Getting characters until a new line is encountered.
	while (true) {
		character = getchar();

		// Breaking out of the loop.
		if ('\n' == character || EOF == character) {
			if (0 == input_size) {continue;} // Dealing with stray newline.
			break;
		}

		// Taking the input.
		line[input_size++] = character;

		// Increasing memory size.
		line = (char*) realloc(line, (input_size + 1));
		if (!line) {
			printf("Memory reallocation failed.\n");
			return NULL;
		}

	}

	line[input_size] = '\0';
	return line;
}


void printOptions() {
	/* This functions prints all the available options. */
	printf("Student Management System.\n");
	printf("    1: Display students.\n");
	printf("    2: Add student.\n");
	printf("    e: Exit\n");
}