
/* This is a game of tic tac toe played on the terminal. The computer
is O and the player is X. */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// Global variables.
char pos_array[9] = "         ";
char rows[3][6] = {{}, {}, {}};
int empty_cells[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

// Functions.
bool check_if_draw();
char check_if_win();
void draw_board();
int get_computer_move();
int get_user_input();
void play();
void print();
void update_board();


// Main function.
int main() {
	int replay;
	srand(time(NULL));

	while (true) {
		play();

		// Replaying or quiting.
		printf("Do you want to play again? (y/n)\n\t");
		replay = getchar();
		if (replay == 'y') {
			printf("Fix this. It's not working.");
			break;
		}
		else if (replay == 'n') {
			printf("Goodbye!!");
			break;
		}
		else {printf("Invalid option. Quiting..");}
	}

	return 0;
}


// Functions definition.
bool check_if_draw() {
	/* This function returns true if the game has ended without a
	winner, false otherwise. */
	for (int i = 0; i <= 8; i ++) {
		if (pos_array[i] == ' ') {return false;}
	}

	return true;
}


char check_if_win() {
	/* This function checks if the game has been won. If so, the
	winner's character is returned ('X' or 'O'). If the game has not
	been won, false is returned. */

	// Horizontal win.
	if (pos_array[0] == pos_array[1] && pos_array[1] == pos_array[2]) {
		return pos_array[0];
	}
	else if (pos_array[3] == pos_array[4] && pos_array[4] == pos_array[5]) {
		return pos_array[3];
	}
	else if (pos_array[6] == pos_array[7] && pos_array[7] == pos_array[8]) {
		return pos_array[6];
	}

	// Vertical win.
	else if (pos_array[0] == pos_array[3] && pos_array[3] == pos_array[6]) {
		return pos_array[0];
	}
	else if (pos_array[1] == pos_array[4] && pos_array[4] == pos_array[7]) {
		return pos_array[1];
	}
	else if (pos_array[2] == pos_array[5] && pos_array[5] == pos_array[8]) {
		return pos_array[2];
	}

	// Diagonal win.
	else if (pos_array[0] == pos_array[4] && pos_array[4] == pos_array[8]) {
		return pos_array[0];
	}
	else if (pos_array[2] == pos_array[4] && pos_array[4] == pos_array[6]) {
		return pos_array[2];
	}

	// No winner.
	else {return 'f';}
}


void draw_board() {
	/* This function draws an updated version of the board on the
	screen. The screen is cleared first before drawing the board.*/
	system("clear");
	
	for (int i = 0; i < 3; i ++) {
		print(rows[i]);
	}
	
}


int get_computer_move() {
	/* This function returns an integer of the computer's move. */
	int computer_move, cell_index;

	computer_move = (rand() % 9) + 1;

	// Checking if the cell is free.
	cell_index = computer_move - 1;
	if (empty_cells[cell_index]) {
		empty_cells[cell_index] = false;
		return computer_move;
	}

	return get_computer_move();
}


int get_user_input() {
	/* This function gets and returns a valid input from the user. 
	This is a recursive function. */
	int player_move, cell_index;

	printf("\nYour move: ");
	scanf("%d", &player_move);

	// Checking if the input is valid.
	cell_index = player_move - 1;
	if (empty_cells[cell_index]) {
		empty_cells[cell_index] = false;
		return player_move;
	}

	printf("Invalid option!\n");
	return get_user_input();
}


void play() {
	/* This function contains the mainloop. */
	int computer_choice, player_choice, winner, draw;

	// Mainloop.
	update_board();
	draw_board();
	while (true) {
		// Computer's turn.
		computer_choice = get_computer_move();
		pos_array[computer_choice - 1] = 'O';

		update_board();
		draw_board();

		// Checking if the game has been won.
		winner = check_if_win();
		if (winner == 'X' || winner == 'O') {
			printf("%c wins.", winner);
			break;
		}
		draw = check_if_draw();
		if (draw) {
			printf("DRAW.\n");
			break;
		}

		// Player's turn.
		player_choice = get_user_input();
		pos_array[player_choice - 1] = 'X';

		update_board();
		draw_board();
		
		// Checking if the game has been won.
		winner = check_if_win();
		if (winner == 'X' || winner == 'O') {
			printf("%c wins.", winner);
			break;
		}
		draw = check_if_draw();
		if (draw) {
			printf("DRAW.\n");
			break;
		}
	}
}


void print(char string[]) {
	/* This function prints the given string with some indentation.
	The new line at the end is automatically added, do not include
	it in the string argument.*/
	printf("\t\t\t%s\n", string);
}


void update_board() {
	/* This function updates the board, drawing x or o where needed.
	*/
	int increment_value, index;

	for (int i = 0; i < 3; i ++) {
		increment_value = 3 * i;

		for (int j = 0; j < 5; j ++) {
			rows[i][j] = '|';

			if (j % 2 == 0) {
				index = (j / 2) + increment_value;
				rows[i][j] = pos_array[index];
			}
		}
	}
}