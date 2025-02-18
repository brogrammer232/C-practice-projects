
/* This is a simple dino game. Press d,ctrl + d on linux for the dino
to jump. */

// Imports.
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


// Global variables.
#define HEIGHT 10
#define WIDTH 50

char grid[HEIGHT][WIDTH + 1];
const int dino_posx = 1;
int dino_posy[2] = {(HEIGHT - 3), (HEIGHT - 2)};
int obstacle_posx, obstacle_posy = (HEIGHT - 2);
int score = 0;
bool jumping = false, playing = true;


// Functions declaration.
bool check_collision();
void draw();
void get_obstacle();
void* get_user_input(void* argument);
void move_obstacle();
void setup();
void update_dino();


// Main function.
int main() {
	setup();
	update_dino();

	// Starting a thread that gets user input.
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, get_user_input, NULL);

	// Mainloop.
	while (playing) {
		move_obstacle();
		update_dino();

		if (check_collision()) {break;}

		draw();
		usleep(50000);
	}

	playing = false;
	printf("The game has ended.\n");

	return 0;
}


// Functions definition.
bool check_collision() {
	/* This function returns true if the obstacle and the dino have
	collided. It returns false otheriwse. */
	int posy = dino_posy[1];

	if (dino_posx == obstacle_posx && posy == obstacle_posy) {return true;}

	return false;
}


void draw() {
	/* This function writes everything seen on the screen. */
	system("clear");
	printf("\t\t\t\tSCORE: %d\n", score);

	// Drawing the grid.
	for (int row_index = 0; row_index < HEIGHT; row_index ++) {
		printf("\t%s\n", grid[row_index]);
	}
}


void get_obstacle() {
	/* This function places an enemy at the right side of the screen. */
	obstacle_posx = WIDTH - 1;
	grid[obstacle_posy][obstacle_posx] = '*';
}


void* get_user_input(void* argument) {
	/* This function continuously gets user input. If the user presses
	'ctrl + d', this function sets 'jumping' to true if it is false.
	This function should run on its own thread. */
	char player_input;

	while (playing) {
		player_input = getchar();

		if ('d' == player_input) {
			if (!jumping) {jumping = true;}
		}

		else {playing = false;}
	}
}


void move_obstacle(){
	/* This moves the obstacle one step towards the left. If the
	obstacle gets to the end of the left side of the screen, it is
	placed back to the right side. */
	grid[obstacle_posy][obstacle_posx] = ' ';
	
	if (0 >= obstacle_posx) {get_obstacle(); score ++;}
	else {
		obstacle_posx --;
		grid[obstacle_posy][obstacle_posx] = '*';
	}
}


void setup() {
	/* This function prepares everything needed before the game
	starts. */
	char character;

	// Preparing the grid.
	for (int row_index = 0; row_index < HEIGHT; row_index ++) {
		// Determining the character to be printed.
		if (row_index == (HEIGHT - 1)) {character = '-';}
		else {character = ' ';}

		// Looping through columns.
		for (int column_index = 0; column_index < WIDTH; column_index ++) {
			grid[row_index][column_index] = character;
		}
	}

	// More things.
	get_obstacle();
}


void update_dino() {
	/* This function places the dino in the appropriate pos on the
	grid. This function also handles the jump animation. */
	int posy;
	int prev_posy[2] = {dino_posy[0], dino_posy[1]};

	// Handling the jumping animation.
	if (jumping) {
		if (dino_posy[0] > (HEIGHT - 6)) {
			grid[dino_posy[0]][dino_posx] = ' ';
			grid[dino_posy[1]][dino_posx] = ' ';

			dino_posy[0] = dino_posy[0] - 1;
			dino_posy[1] = dino_posy[1] - 1;
		}
		else {jumping = false;}
	}

	else if (dino_posy[0] < (HEIGHT - 3)) {
		grid[dino_posy[0]][dino_posx] = ' ';
		grid[dino_posy[1]][dino_posx] = ' ';

		dino_posy[0] = dino_posy[0] + 1;
		dino_posy[1] = dino_posy[1] + 1;
	}

	// Placing the dino on the grid.
	for (int i = 0; i < 2; i ++) {
		posy = dino_posy[i];
		grid[posy][dino_posx] = '#';
	}
}