#include "DPlaya.h"
#include "funcs.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

SDL_Surface *screen;
SDL_Event event;
bool quit;


void sdl_init()
{
    SDL_Init( SDL_INIT_EVERYTHING );

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        //turn video on
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    atexit(SDL_Quit);
    
    //video settings
    screen = SDL_SetVideoMode(SCREEN_HEIGHT, SCREEN_WIDTH, 16, SDL_DOUBLEBUF);

    if (screen == NULL)
    {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        exit(2);
    }

    SDL_WM_SetCaption( "Tux Bomber", NULL ); 
}

int main()
{
	int **map;
	DPlaya player;
	sdl_init();

	SDL_Surface *image_set = load_image( "empty.png" );

	int numImages = 3;
	int width = 18;
	int height = 17;
	
	map = genRandomMap(height,width);

	
	for( int i = 0 , j = -1 ; i < 306; i++)
	{
		if (i %18 == 0 )
		{
			printf("\n");
			j++;
		}
		printf(" %d",map[j][i%18]);
	}
	
	printf("\n");
	fflush(stdout);
	
	player.setX(35);
	player.setY(35);
	user_map uMap(map,image_set,numImages,height,width);

	uMap.draw_map(screen);
	player.setImage("batmanTuxSmal.gif");
	player.refresh(screen);
	SDL_Flip(screen);
	while(quit == false)
	{
	while( SDL_PollEvent( &event ) )
    {
		//If the user has Xed out the window
		if( event.type == SDL_QUIT )
		{
			//Quit the program
			quit = true;
		}
		else if( event.type == SDL_KEYDOWN )
		{
			//Adjust the velocity
			switch( event.key.keysym.sym )
			{
				case SDLK_UP:
					while(SDL_GetKeyState(NULL)[SDLK_UP])
					{
					SDL_PollEvent( &event );
					player.move(map, 0);
					uMap.draw_map(screen);
					player.refresh(screen);
					}
					break;
				case SDLK_DOWN:
					while(SDL_GetKeyState(NULL)[SDLK_DOWN])
					{
					SDL_PollEvent( &event );
					player.move(map, 1);
					uMap.draw_map(screen);
					player.refresh(screen);
					}				
					break;
				case SDLK_LEFT:
					while(SDL_GetKeyState(NULL)[SDLK_LEFT])
					{
					SDL_PollEvent( &event );
					player.move(map, 2);
					uMap.draw_map(screen);
					player.refresh(screen);
					}	
					break;
				case SDLK_RIGHT:
					while(SDL_GetKeyState(NULL)[SDLK_RIGHT])
					{
					SDL_PollEvent( &event );
					player.move(map, 3);
					uMap.draw_map(screen);
					player.refresh(screen);
					}	
					break;
				case SDLK_SPACE:
					//Send bomb request
					break;
				default: ;
			}
		}
    	//If a key was released
		else if( event.type == SDL_KEYUP )
		{
			//Adjust the velocity
			switch( event.key.keysym.sym )
			{/*
				case SDLK_UP: player.move(map, 0); break;
				case SDLK_DOWN: player.move(map, 1); break;
				case SDLK_LEFT: player.move(map, 2); break;
				case SDLK_RIGHT: player.move(map, 3); break;
				case SDLK_SPACE: break;
				default: ;*/
			}
		}
	}
	
	SDL_Flip(screen);
}
	/*sleep(2);
	player.move(map, 1);
	uMap.draw_map(screen);
	player.refresh(screen);
	SDL_Flip(screen);
	sleep(4);*/
	
    uMap.~user_map();
	return 0;
}


