
/* This is a snake game. Control the snake to get the food. Do not
hit the walls. Controls: Use the arrow keys. Press an arrow key then
press ctrl + d for the event to take effect. Change this later in
life. Make the changes take effect as soon as an arrow key is pressed.
*/

// Imports.
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>


// Global variables.
char field[20][41], direction = 'N', user_input = ' ';
int snake_posx[100], snake_posy[100];
int snake_length = 2, score = 0;
int food_posx, food_posy;
bool playing = true;


// Declaring functions.
void change_direction();
bool check_for_collision();
void draw();
void draw_food();
void get_food_pos();
void* get_user_input(void* argument);
void move_and_update_snake();
void move_snake();
void reset_field();
void setup();
void sleep_ms(int milliseconds);
void update_food();
void update_snake();


// Main function.
int main() {
	// Setup.
	bool collided;
	srand(time(NULL));
	setup();
	draw();

	// Starting a thread that gets user input.
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, get_user_input, NULL);


	// Mainloop.
	while (true) {
		// Working on user input.
		if (user_input == 'e') {break;}
		else {change_direction();}
		user_input = ' ';

		// Updating the screen.
		update_food();
		move_and_update_snake();

		// Checking for collision with the walls.
		collided = check_for_collision();
		if (collided) {break;}

		draw();
		sleep_ms(200);
	}

	playing = false;
	printf("Goodbye!!\n");


	return 0;
}


// Defining functions.
void change_direction() {
	/* This function changes the direction of travel of the player /
	snake based on user input. */
	switch (user_input) {
		case 'A':
			direction = 'N';
			break;

		case 'B':
			direction = 'S';
			break;

		case 'C':
			direction = 'E';
			break;

		case 'D':
			direction = 'W';
			break;
	}
}


bool check_for_collision() {
	/* This function checks if the player / snake has hit the wall
	or its own body. If so, true is returned. Else, false is returned.
	*/
	int posy = snake_posy[0], posx = snake_posx[0];

	// Checking for collision with walls.
	if (0 == posy || 19 == posy || 0 >= posx || 39 == posx) {
		return true;
	}
	
	// Checking for collision with self.
	for (int i = 1; i < snake_length; i ++) {
		if (posx == snake_posx[i] && posy == snake_posy[i]) {
			return true;
		}
	}

	return false;
}


void draw() {
	/* This function draws everything seen on the screen. */
	system("clear");

	printf("\t\t\t\t\tSCORE: %d\n", score);

	// Drawing the field.
	for (int row_index = 0; row_index < 20; row_index ++) {
		printf("\t\t\t%s\n", field[row_index]);
	}

	printf("Press 'e' to exit.\n");
}


void draw_food() {
	get_food_pos();
	field[food_posy][food_posx] = '*';
}


void get_food_pos() {
	/* This function sets random values for the variables 'food_posx'
	and 'food_posy'. */
	food_posx = (rand() % 38) + 1;
	food_posy = (rand() % 18) + 1;

	// Making sure the x position is odd.
	if (food_posx % 2 == 0) {
		if (food_posx == 38) {food_posx --;}
		else {food_posx ++;}
	}
}


void* get_user_input(void* argument){
	/* This function gets input from the user. The input is stored in
	the global variable 'user_input'. This function runs on a separate
	thread. */
	while (playing) {
		user_input = getchar();
	}

}


void move_and_update_snake() {
	/* This function simply calls the 'move_snake' function and the
	'update_snake' function. */
	move_snake();
	update_snake();
}


void move_snake() {
	/* This function moves the snake one step in the current direction
	of travel. */
	int prev_posx, prev_posy, head_posx, head_posy, posx, posy;

	// Moving the head.
	head_posx = snake_posx[0]; head_posy = snake_posy[0];
	prev_posx = head_posx; prev_posy = head_posy;

	if ('N' == direction || 'S' == direction) {
		if ('N' == direction) {head_posy --;}
		else if ('S' == direction) {head_posy ++;}
	}
	else if ('E' == direction || 'W' == direction) {
		if ('E' == direction) {head_posx += 2;}
		else if ('W' == direction) {head_posx -= 2;}
	}

	snake_posx[0] = head_posx; snake_posy[0] = head_posy;


	// Moving the body.
	for (int i = 1; i < snake_length; i ++) {
		posx = snake_posx[i]; posy = snake_posy[i];
		snake_posx[i] = prev_posx; snake_posy[i] = prev_posy;
		prev_posx = posx; prev_posy = posy;
	}

	// Clearing behind the snake.
	field[prev_posy][prev_posx] = ' ';
}


void reset_field() {
	/* This function resets the two dimensional array "field". It
	draws an empty field with only the walls. */
	char character;

	for (int row = 0; row < 20; row ++) {
		// Determining the character.
		if (row == 0 || row == 19) {
			character = '#';
		}
		else {character = ' ';}

		// Looping through the columns.
		for (int column = 0; column < 40; column ++) {
			// Drawing the vertical walls.
			if (column == 0 || column == (39)) {
				field[row][column] = '#';
			}

			// Drawing the character.
			else {
				field[row][column] = character;
			}
		}
	}
}


void setup() {
	/* This function prepares everything needed to start the game. */
	// Field and food.
	reset_field();
	draw_food();

	// Resetting the position of the snake.
	snake_posx[0] = 19; snake_posx[1] = 19;
	snake_posy[0] = 9;	snake_posy[1] = 10;
	update_snake();

}


void sleep_ms(int milliseconds){
	/* This function causes the program to sleep for the given number
	of milliseconds. 
	THIS FUNCTION WAS COPIED FROM GEEKS FOR GEEKS.
	*/
    usleep(milliseconds * 1000);
}


void update_food() {
	/* This function checks if the food has been eaten. If so, it
	draws food on another part of the screen and increments the
	score. If not, nothing happens.
	*/
	if (snake_posx[0] == food_posx && snake_posy[0] == food_posy) {
		draw_food();
		score ++; snake_length ++;
	}
}


void update_snake() {
	/* This function puts the snake in the field with updated
	coordinates. */
	int posx, posy;

	// Updating the head.
	int head_posx = snake_posx[0];
	int head_posy = snake_posy[0];
	field[head_posy][head_posx] = 'O';

	// Updating the body.
	for (int i = 1; i < snake_length; i ++) {
		posx = snake_posx[i];
		posy = snake_posy[i];
		field[posy][posx] = 'o';
	}
}