#include "DPlaya.h"
#include "funcs.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

SDL_Surface *screen;
SDL_Event event;

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
	if( event.type == SDL_KEYDOWN )
    	{
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_UP:
            case SDLK_DOWN:
            case SDLK_LEFT:
            case SDLK_RIGHT:
				player.move(uMap, 1);
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
        {
            case SDLK_DOWN: player.move(uMap, 1); break;
            case SDLK_SPACE: break;
            default: ;
        }
    	}
	player.refresh(screen);
	SDL_Flip(screen);
	sleep(100);

    	uMap.~user_map();
	return 0;
}


