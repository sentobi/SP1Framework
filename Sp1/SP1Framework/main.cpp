// This is the main file to hold everything together

#include "Framework\timer.h"
#include "game.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

StopWatch g_timer;            // Timer function to keep track of time and the frame rate
bool g_quitGame = false;      // Set to true if you want to quit the game
const unsigned char FPS = 5; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

enum Sequence 
{
    Menu,
    Play,             //1
    Instructions,     //2
    HighScore,        //3
    Options,          //4
    Exit,             //5
    MAX_SEQUENCE      //Last (6)
};
const char* menu[] = 
{
   "Play",
   "Instructions",
   "High Score",
   "Options",
   "Exit"
};

void gameLoop();
void displayMenu();
void userInput (Sequence &s);
void displayGame();
void displayInstructions();
void displayOptions();
void displayHighscore();
void displayExit();
int input;

// TODO:
// Bug in waitUnitil. it waits for the time from getElapsedTime to waitUntil, but should be insignificant.

int main()
{
	init();      // initialize your variables
    shutdown();  // do clean up, if any. free memory.
	gameLoop();
	return 0;
}

void gameLoop()
{
    Sequence seq = Menu;
    displayMenu();

    while (seq != Exit && seq != Play)
    {
        userInput(seq);

        switch(seq)
        {
            case Play : displayGame(); break;
            case Options : displayOptions(); break;
            case Exit : displayExit(); break;
        }
    }
}

void userInput (Sequence &s) //If s is modified, seq is modified as well
{
    int input;
    cout << endl;
    cout << "Enter your choice : ";
    cin >> input;
    cout << endl;
    //Cannot cin>>s cause it doesn't take in
    s = static_cast<Sequence>(input);
}

void displayMenu()
{
        cout << "Menu" << endl;
        cout << endl;
        for (Sequence s = Play; s != MAX_SEQUENCE; s = static_cast<Sequence>(s+1))
        {
         cout << "Menu Option " << s << " " << menu[s-1] << endl;
        }
}


void displayInstructions()
{

}

void displayHighscore()
{

}

void displayOptions()
{

}

void displayExit()
{

}

// This main loop calls functions to get input, update and render the game
// at a specific frame rate
//Game
void displayGame()
{
    g_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
    while (!g_quitGame)      // run this loop until user wants to quit 
	{        
        getInput();                         // get keyboard input
        update(g_timer.getElapsedTime());   // update the game
        render();                           // render the graphics output to screen
        g_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.      
	}    
}
