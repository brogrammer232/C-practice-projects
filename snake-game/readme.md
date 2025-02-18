
# Snake game
This is the classic snake game but on the terminal.
The rules are the same, the snake eats and gets bigger. The game ends
when the snake collides with itself or with the walls.

**Controls:**
The arrow keys are used to control the snake.
Pressing the arrow key alone will not change the direction of travel of
the snake, you have to press `Ctrl+D` on Linux or `Ctrl+Z` on Windows.
I will fix this soon.


## For Windows users
Before drawing every frame, the terminal is first cleared.
This is done by using ```system("clear");```.
Note that this will not work on Windows if you are running it on the
command prompt.
Change this to ```system("cls");```, compile it and run.