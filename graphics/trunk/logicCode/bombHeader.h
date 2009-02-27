#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "SDL/SDL_thread.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 20;

//The attributes of the Player
const int SQUARE_WIDTH = 20;
const int SQUARE_HEIGHT = 20;



//Function Prototypes
SDL_Surface *load_image( std::string filename );

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination);

bool check_collision( SDL_Rect A, SDL_Rect B );

bool init();

bool load_files();

void clean_up();

class Bomb
{
    private:
    SDL_Rect bombSquare;
    
    
    public:
    Bomb();
    
    void setRect(int, int);
    
    int getRectX(){return bombSquare.x;};
    
    int getRectY(){return bombSquare.y;};
    
    void explode();
    
    void placeBomb();
};

class Player
{
    private:
    //The collision box of the Player
    SDL_Rect box;
    Bomb myBomb[5];
    int isPlanted[6];
    int bombCount;

    //The velocity of the Player
    int xVel, yVel;
    
    public:
    //Initializes the variables
    Player();

    //Takes key presses and adjusts the Player's velocity
    void handle_input();

    //Moves the Player
    void move();

    //Shows the Player on the screen
    void show();
    
    void plantBomb(){bombCount++;};
    
    void removeBomb(){bombCount--;};
    
    void setBombStatus(int bombNo, bool status);
    
    bool getBombStatus(int bombNo){return isPlanted[bombNo];};
};
