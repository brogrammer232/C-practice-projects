
// Imports.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
void exitApp(int status);
char getCharacter(char valid_characters_array[], int array_size);
int getInteger(int *variable);
char* getLine();
void printOptions();
void removeStudent();
void showContinueMessage();
int sortStudents();

int sortNameAscending(const void *a, const void *b);
int sortNameDescending(const void *a, const void *b);
int sortGradeAscending(const void *a, const void *b);
int sortGradeDescending(const void *a, const void *b);


// Main function.
int main() {
	char user_input;

	// Mainloop.
	while (true) {
		system("clear");
		printOptions();

		// Taking user input.
		char valid_characters[] = {'e', '1', '2', '3', '4'};
		int array_size = (sizeof(valid_characters) / sizeof(valid_characters[0]));
		user_input = getCharacter(valid_characters , array_size);

		if ('e' == user_input) {exitApp(0);}
		else if ('1' == user_input) {displayStudents();}
		else if ('2' == user_input) {sortStudents();}
		else if ('3' == user_input) {addStudent();}
		else if ('4' == user_input) {removeStudent();}
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
		printf("There are currently no students in the system.\n\n");
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


void exitApp(int status) {
	/* This function does everything needed before exiting the app,
	then it exits. */
	struct Student student;

	// Freeing memory.
	for (int i = 0; i < studentCount; i++) {
		student = STUDENTS[i];
		free(student.name);
		free(student.address.town);
		free(student.address.street);
	}

	// Exiting.
	exit(status);
}


char getCharacter(char valid_characters_array[], int array_size) {
	/* This function gets and returns a character from the user.
	It takes two parameters:
		valid_characters_array: An array of valid characters. The user
			will be prompted to enter a character if the previously
			entered character is not in the array. If the array is
			empty, all characters will be accepted.

		array_size: This is the size of the 'valid_characters_array'.
			Set this to 0 to accept all characters.
	*/

	char character = getchar();
	if ('\n' == character) {return getCharacter(valid_characters_array, array_size);} // Recursive function to avoid newlines.

	// Validating input.
	bool valid_input = false;
	if (0 < array_size) {
		char valid_character;
		for (int i = 0; i < array_size; i++) {
			valid_character = valid_characters_array[i];

			if (valid_character == character) {
				valid_input = true;
				break;
			}
		}

		if (!valid_input) {
			printf("Invalid choice. Try again:\n");
			return getCharacter(valid_characters_array, array_size);}
	}
	else if (0 == array_size) {valid_input = true;}

	// Returning the result.
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
	printf("    2: Sort students.\n");
	printf("    3: Add student.\n");
	printf("    4: Remove student.\n");
	printf("    e: Exit\n");
}


void removeStudent() {
	/* This function removes a student from the array. */
	char *student_name;

	system("clear");

	// Showing enrolled students.
	if (0 == studentCount) {
		printf("There are currently no enrolled students.\n\n");
		showContinueMessage();
		return;
	}

	printf("Enrolled students:\n");
	for (int i = 0; i < studentCount; i++) {
		student_name = STUDENTS[i].name;
		printf("%s; ", student_name);
	}
	printf("\n");

	// Getting the name of the student to remove.
	printf("Enter the name of the student to remove: ");
	student_name = getLine();


	for (int i = 0; i < studentCount; i++) {
		// Confirming the given student exists.
		if (*STUDENTS[i].name == *student_name) {
			printf("\nRemoving the student...\n");

			// Removing the student with the given name.
			for (int j = i; j < studentCount; j++) {
				STUDENTS[j] = STUDENTS[j + 1];
			}
			studentCount--;
			printf("Student removed.\n\n");
			showContinueMessage();
			return;
		}

	}
	printf("No student has the name given.\n");
	showContinueMessage();
}


void showContinueMessage() {
	/* This function simply directs the user to press a certain key
	to move to the next screen. */
	printf("Press ENTER to continue.\n");
	getchar();
}


int sortStudents() {
	/* This function sorts the STUDENTS list either by name or by
	grade. */
	int sort_by, order;

	system("clear");

	// Bailing if there are not students.
	if (0 == studentCount) {
		printf("There are currently no enrolled students.\n\n");
		showContinueMessage();
		return 1;
	}

	// Getting required information from the user.
	printf("Sort by (1:name, 2:grade): ");
	getInteger(&sort_by);

	printf("Order (1:ascending, 2:descending): ");
	getInteger(&order);


	// Executing.
	switch (sort_by) {
	case 1:
		if (1 == order) {
			qsort(STUDENTS, studentCount, sizeof(struct Student), sortNameAscending);
		}
		else if(2 == order) {
			qsort(STUDENTS, studentCount, sizeof(struct Student), sortNameDescending);
		}

	case 2:
		if (1 == order) {
			qsort(STUDENTS, studentCount, sizeof(struct Student), sortGradeAscending);
		}
		else if(2 == order) {
			qsort(STUDENTS, studentCount, sizeof(struct Student), sortGradeDescending);
		}
	}

	return 0;
}


int sortNameAscending(const void *a, const void *b) {
	/* This function is passed to the 'qsort' function to sort STUDENTS
	by name	in ascending order. */
	return strcmp((((struct Student *)a) -> name),
		(((struct Student *)b) -> name));
}

int sortNameDescending(const void *a, const void *b) {
	/* This function is passed to the 'qsort' function to sort STUDENTS
	by name in descending order. */
	return strcmp((((struct Student *)b) -> name),
		(((struct Student *)a) -> name));
}

int sortGradeAscending(const void *a, const void *b) {
	/* This function is passed to the 'qsort' function to sort STUDENTS
	by grade in ascending order. */
	return (((struct Student *)a) -> grade
		) - (((struct Student *)b) -> grade);
}

int sortGradeDescending(const void *a, const void *b) {
	/* This function is passed to the 'qsort' function to srot STUDENTS
	by grade in descending order. */
	return (((struct Student *)b) -> grade
		) - (((struct Student *)a) -> grade);
}