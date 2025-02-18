
// Imports.
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

// Global variables.
int computer_score = 0, player_score = 0;

// Functions.
void win();
void draw();
void lose();
char get_computer_choice();
void print_score();

int main() {
	// Setup.
	char player_choice, computer_choice;
	unsigned int seed = time(NULL);
	srand(seed);

	// Welcoming.
	printf("Welcome to ROCK, PAPER, SCISSORS.\n");
	print_score();

	// Mainloop.
	while (true) {
		// Getting computer's choice.
		computer_choice = get_computer_choice();

		// Getting user input.
		printf("What's your choice: rock (r), paper (p), scissors (s), exit (e).\n\t");
		scanf("%c", &player_choice); // Press Ctrl + D after writing input.
		printf("\nComputer's choice: %c", computer_choice);

		// Quiting.
		if ('e' == player_choice) {break;}

		// Determining the winner.
		if ('r' == player_choice) {
			if ('r' == computer_choice) {draw();}
			else if ('p' == computer_choice) {lose();}
			else if ('s' == computer_choice) {win();}
		}

		else if ('p' == player_choice) {
			if ('r' == computer_choice) {win();}
			else if ('p' == computer_choice) {draw();}
			else if ('s' == computer_choice) {lose();}
		}

		else if ('s' == player_choice) {
			if ('r' == computer_choice) {lose();}
			else if ('p' == computer_choice) {win();}
			else if ('s' == computer_choice) {draw();}
		}

		else {
			printf("INVALID OPTION.\n");
		}

		// Printing the score.
		print_score();
	}

	printf("\nGoodbye!!");

	return 0;
}


void win() {
	/* This function displays a 'you win' message and increments the
	player's score. */
	printf("\n\n\t***** YOU WIN. *****\n\n");
	player_score ++;
}


void draw() {
	/* This function displays a draw message and adds one to both the
	player's and computer's score.*/
	printf("\n\n\t***** DRAW. *****\n\n");
	computer_score ++; player_score ++;
}


void lose() {
	/* This function displays a 'you lose' message and increments the
	computer's score.*/
	printf("\n\n\t***** YOU LOSE. *****\n\n");
	computer_score ++;
}


char get_computer_choice() {
	/* This function returns the computer's choice. One of r,p,s. */

	// Getting random number.
	int random_number = (rand() % 100) + 1;

	// Getting the choice.
	char choice;
	if (random_number <= 33) {choice = 'r';}
	else if (random_number <= 66) {choice = 'p';}
	else if (random_number <= 100) {choice = 's';}
	else {printf("Random number above 100 in function 'get_computer_choice'.");}


	return choice;
}


void print_score() {
	/* This function prints the computer's score and the player's
	score. */
	printf("Computer's score: %d\n", computer_score);
	printf("Player's score: %d\n", player_score);
}