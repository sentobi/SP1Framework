// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <string>

using std::string;

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
COORD charLocation;
COORD consoleSize;

void maprender();
void maze1(int& rows, int& cols);
void maze2(int& rows, int& cols);
void mapgenerator(int rows, int cols);

char ** maze = 0;

void maprender() {

	int rows = 0;
	int cols = 0;

	if (1) {
		maze1(rows, cols);
	}
	else if (2) {
		maze2(rows, cols);
	}

	mapgenerator(rows, cols);

}

void mapgenerator(int rows, int cols) {

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (maze[i][j] == '@') { //teleporter
				colour(0x0A);
			}
			else if (maze[i][j] == '$') { //item
				colour(0x0B);
			}
			else if (maze[i][j] == '*') { //exit
				colour(0x0D);
			}
			else {
				colour(0x0F);
			}
			std::cout << maze[i][j];
		}
		std::cout << std::endl;
	}

}

void maze1(int& rows, int& cols) {

	string map1[21] = {
		"##################",
		"# #@             #",
		"# ### ######## # #",
		"#     #  #   # # #",
		"### ### ## # # # #",
		"#   #    # # # # #",
		"# ###### # #@# # #",
		"#     #@   ### ###",
		"##### ######     #",
		"#$# # # *  # #####",
		"# # ###    #     #",
		"#   #@#    ##### #",
		"# ### #    #     #",
		"#     #   @# # # #",
		"# ### ######## # #",
		"# # # #@#   ## # #",
		"### # # # # ## # #",
		"#@# #   # #    # #",
		"# # ##### # ## # #",
		"#         # #  #@#",
		"##################" };

	rows = 21;
	maze = new char * [rows];
	cols = 18;

	for (int i = 0; i < rows; ++i) {
		maze[i] = new char[cols];
		string temp = map1[i];
		for (int j = 0; j < cols; ++j) {
			maze[i][j] = temp[j];
		}
	}

}

void maze2(int& rows, int& cols) {

	string map2[13] = {
		"########################",
		"#      #       #       #",
		"#### # #  #### # ##### #",
		"#    #    #  # #     # #",
		"# #########  # #     # #",
		"#      #    ##       # #",
		"#### #############   # #",
		"#    #     *     #   # #",
		"########################",
		"#      #    #          #",
		"#  #####  ###########  #",
		"#      #               #",
		"########################" };

	rows = 13;
	maze = new char * [rows];
	cols = 24;

	for (int i = 0; i < rows; ++i) {
		maze[i] = new char[cols];
		string temp = map2[i];
		for (int j = 0; j < cols; ++j) {
			maze[i][j] = temp[j];
		}
	}

}

void init()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    SetConsoleTitle(L"SP1 Framework");

    // Sets the console size, this is the biggest so far.
    setConsoleSize(79, 28);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set the character to be in the center of the screen.
    charLocation.X = 1;
    charLocation.Y = 1;

	//set values as the character's coordinates

    elapsedTime = 0.0;
}

void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
}

void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

	int charX = charLocation.Y;
	int charY = charLocation.X;

    // Updating the location of the character based on the key press

    if (keyPressed[K_UP] && charLocation.Y > 0)
    {
		if (maze[charX-1][charY] != '#') {
			Beep(1440, 30);
			charLocation.Y--;
		}
    }
    if (keyPressed[K_LEFT] && charLocation.X > 0)
	{
		if (maze[charX][charY-1] == '#') {
			std::cout << "Collision detected" << std::endl;
		}
		else {
			Beep(1440, 30);
			charLocation.X--; 
		}
    }
    if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 1)
    {
		if (maze[charX+1][charY] == '#') {
			std::cout << "Collision detected" << std::endl;
		}
		else {
			Beep(1440, 30);
			charLocation.Y++; 
		}
    }
    if (keyPressed[K_RIGHT] && charLocation.X < consoleSize.X - 1)
    {
		if (maze[charX][charY+1] == '#') {
			std::cout << "Collision detected" << std::endl;
		}
		else {
			Beep(1440, 30);
			charLocation.X++; 
		}
    }

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        g_quitGame = true;    
}

void render()
{
    // clear previous screen
    colour(0x0F);
    cls();

    //render the game

    //render test screen code (not efficient at all)
    const WORD colors[] =   {
	                        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
	                        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	                        };

	maprender();

    // render time taken to calculate this frame
    /*gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;
	*/
    // render character
    gotoXY(charLocation);
    colour(0x0C);
    std::cout << (char)1;
}
