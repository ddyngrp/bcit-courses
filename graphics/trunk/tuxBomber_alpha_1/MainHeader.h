
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <cstdlib> 
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/************************************************************************************
 ***************************...Global variables ...**********************************
 ************************************************************************************/

//Quit flag
bool quit = false;
    
//Screen attributes
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 700;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 25;

//The Player dimensions
const int TUX_WIDTH = 35;
const int TUX_HEIGHT = 35;
const int PLAYER_X_POS = 35;
const int PLAYER_Y_POS = 35;



//The dimensions of the play field
const int FIELD_WIDTH = 600;
const int FIELD_HEIGHT = 600;

//play field offsets
int FIELD_X_OFFSET = SCREEN_WIDTH - FIELD_WIDTH;
int FIELD_Y_OFFSET = SCREEN_HEIGHT - FIELD_HEIGHT;

//Tile constants
const int TILE_WIDTH = 35;
const int TILE_HEIGHT = 35;
const int TOTAL_TILES = 306;
const int TILE_SPRITES = 3;

//The different tile sprites
const int ICECUBE= 0;
const int EMPTYSPACE = 1;
const int SNOWMAN= 2;

//The bombs array index
int BOMBS = 0;




//The tile
class Tile
{
    private:
    //The attributes of the tile
    SDL_Rect box;

    //The tile type
    int type;

    public:
    //Initializes the variables
    Tile( int x, int y, int tileType );

    //Shows the tile
    void show();

    //Get the tile type
    int get_type();

    //Get the collision box
    SDL_Rect get_box();
};

    //The tiles that will be used
    Tile *tiles[ TOTAL_TILES ];

//The Player
class Player
{
    private:
    //The Player's collision box
    SDL_Rect box;

    //The velocity of the Player
    int xVel, yVel;

    public:
    //Initializes the variables
    Player();

    //Takes key presses and adjusts the player's velocity
    void handle_input();

    //Moves the player
    void move( Tile *tiles[] );

    //Shows the player on the screen
    void show();

};

//The timer
class Timer
{
    private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

    public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks();

    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};

