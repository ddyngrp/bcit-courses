#include "../headers/mainHeader.h"
using namespace std;

/*------------------------------------------------------------------------------------------------------------------
--       FUNCTION: 					draw_status_bar
--
--       DATE:                      March 16, 2009
--
--       REVISIONS:                 March 31, 2009
--										Hard coded font and background.
--
--       DESIGNER:                  Brendan Neva & Mitesh Lad
--
--       PROGRAMMER: 			    Mitesh Lad & Brendan Neva
--
--       INTERFACE:                 void draw_status_bar(std::string players[],SDL_Surface *tux[],SDL_Surface *screen,SDL_Color textColor)
--										players[] : A list of all players.
--									    tux[]	  : A list of all tux images.
--										screen    : the window in which the player names and images will go
--										textColor : Text color
--
--       RETURNS:                   void.
--
--       NOTES:
--				The purpose of this function is to load the necessary files such as the background image and font.
				It displays the player name and character choice at the location specified by the for loop.  It has a maximum of
				2 players per column and 8 players in total.
----------------------------------------------------------------------------------------------------------------------*/
bool draw_status_bar(std::string players[], SDL_Surface *tux[],SDL_Surface *screen,SDL_Color textColor )
{
	SDL_Surface *hud = NULL;
	SDL_Surface *background = NULL;
	TTF_Font *font = NULL;
	SDL_Surface *message;
	int x = X_POS,y=1, i = 0;

	if((hud = load_image("snowback.png")) == NULL )
            return false;

    //apply_surface(0,0,background,hud);

	if((font = TTF_OpenFont( FONT, FONT_SIZE)) == NULL )
    	    return false;


	for(i =0; i < PLAYERCOUNT; i++)
	{
		if(i % 2 == 0 && i != 0)
		{
			x += INC_X;
			y = RESET_Y;
		}
		message = TTF_RenderText_Solid( font,players[i].c_str() , textColor);

		apply_surface(x,y ,message, hud );
		apply_surface(x-X_POS,y,tux[i],hud);
		y *= INC_Y;
	}

	apply_surface(0,600,hud,screen);

	SDL_FreeSurface( background );
	SDL_FreeSurface( message );

	return true;
}
