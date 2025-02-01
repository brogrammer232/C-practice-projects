
// Imports.
#include <stdio.h>
#include <stdlib.h>

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


// Functions declaration.
char getOption();
void printOptions();


// Main function.
int main() {
	char user_input = getOption();

	if ('e' == user_input) {exit(0);}

	return 0;
}


// Functions definition.
char getOption() {
	/* This option gets and returns a character from the user. */
	printOptions();
	char character = getchar();
	return character;
}


void printOptions() {
	/* This functions prints all the available options. */
	printf("Student Management System.\n");
	printf("    1: Display students.\n");
	printf("    e: Exit\n");
}