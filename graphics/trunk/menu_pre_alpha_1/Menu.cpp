/*------------------------------------------------------------------------------------------------------------------
--       SOURCE FILE:               Menu.cpp
--
--       PROGRAM:                   menu
--
--       FUNCTIONS:		SDL_Surface *load_image( std::string filename )
--				void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
--				bool init()
--				bool load_files()
--				void clean_up()
--				void draw_options()
--				int main( int argc, char* args[] )
--                                  
--
--
--       DATE:                      Febuary 5th 2009
--
--       REVISIONS:                 Clay Sayer - Restructured the source code. Added more menus.
--
--       DESIGNER:                  Tajinder Thind
--
--       PROGRAMMER: Tajinder Thind
--
--       NOTES:
--       This program is a prototype menu system for the Tux Bomber game. Use the Up Down arrow keys to naviagate the
--	 options on the menu. 
--	 Compile with "g++ -Wall -o menu Menu.cpp -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer"
----------------------------------------------------------------------------------------------------------------------*/


//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <string>
#include <iostream>

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The surfaces
SDL_Surface *background = NULL;
SDL_Surface *upMessage = NULL;
SDL_Surface *downMessage = NULL;
SDL_Surface *leftMessage = NULL;
SDL_Surface *rightMessage = NULL;
SDL_Surface *message = NULL;
SDL_Surface *screen = NULL;

//The music that will be played
Mix_Music *music = NULL;

//The event structure
SDL_Event event;

//The font
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 0, 0, 0 };
SDL_Color selectColor = { 255, 0, 0 };


SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

//blits two images together, with the source being pasted on the destination starting at x,y
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

//initialises the libraries, as well as the screen. sets screen size and window caption.
bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }

    //Initialize SDL_mixer 
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) 
    { 
    	return false; 
    } 
    //Set the window caption
    SDL_WM_SetCaption( "Mitesh is a sack.", NULL );

	SDL_ShowCursor(SDL_DISABLE);
    //If everything initialized fine
    return true;
}

//loads in the files needed.
bool load_files()
{
    //Load the background image
    background = load_image( "background.png" );

    //Open the font
    font = TTF_OpenFont( "lazy.ttf", 72 );
    
    //If there was a problem in loading the background
    if( background == NULL )
    {
        return false;
    }
    music = Mix_LoadMUS( "mc.ogg" );
    if(music == NULL)
    {
    	return false;
    }

    //If there was an error in loading the font
    if( font == NULL )
    {
        return false;
    }

    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surfaces
    SDL_FreeSurface( background );
    SDL_FreeSurface( upMessage );
    SDL_FreeSurface( downMessage );
    SDL_FreeSurface( leftMessage );
    SDL_FreeSurface( rightMessage );

	Mix_FreeMusic( music );
    //Close the font
    TTF_CloseFont( font );

    //Quit SDL_ttf
    TTF_Quit();

    //Quit SDL
    SDL_Quit();
}

void draw_options()
{
	bool goBack = false;
	std::string option_messages[5];
	SDL_Surface *messages[5];
	int selectPos = 0;
	int option_message;
	
	option_messages[0] = "Screen Resolution";
	option_messages[1] = "Ping Pong Pong";
	option_messages[2] = "Derka Lerka";
	option_messages[3] = "I am Clayton Sayer, the Set Rep of Data Comm.";
	option_messages[4] = "Go Back";
	
	apply_surface(0,0,background,screen);
	//draw the messages to the screen
	for(int i = 0; i < 5; i++)
	{
		messages[i] = TTF_RenderText_Solid(font, option_messages[i].c_str(), i == 0? selectColor : textColor);
		apply_surface(0, i * 100, messages[i], screen);
	}
	
	//message loop
	while(!goBack)
	{
		SDL_WaitEvent(&event);
		
		if(event.type == SDL_KEYDOWN)
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_UP:
					if(selectPos > 0)
					{
						option_message = 1;
						--selectPos;
						messages[selectPos] = TTF_RenderText_Solid(font, option_messages[selectPos].c_str(), selectColor);
						messages[selectPos + 1] = TTF_RenderText_Solid(font, option_messages[selectPos + 1].c_str(), textColor);
					}
					break;
				case SDLK_DOWN:
					if(selectPos < 4)
					{
						option_message = 1;
						selectPos++;
						messages[selectPos] = TTF_RenderText_Solid(font, option_messages[selectPos].c_str(), selectColor);
						messages[selectPos - 1] = TTF_RenderText_Solid(font, option_messages[selectPos - 1].c_str(), textColor);
					}
					break;
				case SDLK_ESCAPE:
					goBack = true;
					break;
				default:
				break;
				
			}
		}
		else if(event.type == SDL_QUIT)
			goBack = true;
		
		if(option_message != 0)
		{
			apply_surface(0,0,background,screen);
			for(int i = 0; i < 5; i++)
			{
				apply_surface(0, i * 100, messages[i], screen);
			}
			option_message = 0;
		}
		
		if(SDL_Flip(screen) == -1)
			return;
	}
	
	//clean up
	for(int i = 0; i < 5; i++)
		SDL_FreeSurface( messages[i]);	
}

int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;
    std::string messages[4];
    int selectPos = 0;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( load_files() == false )
    {
        return 1;
    }
	
	messages[0] = "Create Game";
	messages[1] = "Join Game";
	messages[2] = "Options";
	messages[3] = "Exit";
	
    //Generate the message surfaces
    upMessage = TTF_RenderText_Solid( font, messages[0].c_str(), selectColor );
    downMessage = TTF_RenderText_Solid( font, messages[1].c_str(), textColor );
    leftMessage = TTF_RenderText_Solid( font, messages[2].c_str(), textColor );
    rightMessage = TTF_RenderText_Solid( font, messages[3].c_str(), textColor );


    //Apply the background
    apply_surface( 0, 0, background, screen );
	apply_surface(0,100,upMessage,screen);
	apply_surface(0,200,downMessage,screen);
	apply_surface(0,300,leftMessage,screen);
	apply_surface(0,400,rightMessage,screen);
	
	if( Mix_PlayMusic( music, 1 ) == -1 )
	{
		return 1;
	}
					
    //While the user hasn't quit
    while( quit == false )
    {
        //If there's an event to handle
        SDL_WaitEvent(&event);
		//If a key was pressed
		if( event.type == SDL_KEYDOWN )
		{
			//Set the proper message surface
			switch( event.key.keysym.sym )
			{
				case SDLK_UP: 
					if(selectPos > 0)
					{
						message = upMessage;
						selectPos-=1;
						switch(selectPos)
						{
							case 0:
								upMessage = TTF_RenderText_Solid( font, messages[selectPos].c_str(), selectColor );
								downMessage = TTF_RenderText_Solid( font, messages[selectPos + 1].c_str(), textColor );
							break;
							case 1:
								downMessage = TTF_RenderText_Solid( font, messages[selectPos].c_str(), selectColor );
								leftMessage = TTF_RenderText_Solid( font, messages[selectPos + 1].c_str(), textColor );
							break;
							case 2:
								leftMessage = TTF_RenderText_Solid( font, messages[selectPos].c_str(), selectColor );
								rightMessage = TTF_RenderText_Solid( font, messages[selectPos + 1].c_str(), textColor );
							break;
						
						}
					}
					break;
				case SDLK_DOWN:
					if(selectPos < 3)
					{
						message = downMessage;
						selectPos += 1;
						switch(selectPos)
						{
							case 1:
								upMessage = TTF_RenderText_Solid( font, messages[selectPos - 1].c_str(), textColor );
								downMessage = TTF_RenderText_Solid( font, messages[selectPos ].c_str(), selectColor );
							break;
							case 2:
								downMessage = TTF_RenderText_Solid( font, messages[selectPos - 1].c_str(), textColor );
								leftMessage = TTF_RenderText_Solid( font, messages[selectPos].c_str(), selectColor );
							break;
							case 3:
								leftMessage = TTF_RenderText_Solid( font, messages[selectPos - 1].c_str(), textColor );
								rightMessage = TTF_RenderText_Solid( font, messages[selectPos].c_str(), selectColor );
							break;
							
						}
					}
					break;
				case SDLK_ESCAPE:
					quit = true;
					break;
				case SDLK_RETURN:
					switch(selectPos)
					{
						case 0:
						break;
						case 1:
						break;
						case 2:
							draw_options();
						break;
						case 3:
							quit = true;
						break;
					}
				default:
				break;
			}
		}

		//If the user has Xed out the windowstd::string messages[4];
		else if( event.type == SDL_QUIT )
		{
			//Quit the program
			quit = true;
		}
	

        //If a message needs to be displayed
        if( message != NULL )
        {
            //Apply the background to the screen
            apply_surface( 0, 0, background, screen );
			apply_surface(0,100,upMessage,screen);
			apply_surface(0,200,downMessage,screen);
			apply_surface(0,300,leftMessage,screen);
			apply_surface(0,400,rightMessage,screen);
            //Apply the message centered on the screen

            //Null the surface pointer
            message = NULL;
        }

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }
    }

    //Clean up
    clean_up();

    return 0;
}
