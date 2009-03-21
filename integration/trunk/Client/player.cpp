/*---------------------------------------------------------------------------------------------
--      SOURCE FILE:	player.cpp - Functions used by the player class
--            
--      PROGRAM:        TuxBomber 
--
--      FUNCTIONS:      int main(int argc, char *argv[])           
--
--      DATE:           March 18, 2009
--
--      DESIGNER:       Whoever contributed to this write your names here
--      PROGRAMMER:		
---------------------------------------------------------------------------------------------*/
#include "player.h"

//Player::Player(const Player& old): x_(old.x_), y_(old.y_), image_(old.image_),
					//	w_(old.w_), h_(old.h_){}
						
void Player::paint(Player player, int newX , int newY, SDL_Surface* screen)
{
	player.setX(newX);
	player.setY(newY);
	refresh(screen);
}
void Player::refresh(SDL_Surface * screen)
{
	SDL_Rect  position;
	position.x = getX();
	position.y = getY();
	
	SDL_BlitSurface(getImage(), NULL, screen, &position );	
}

void Player::dropBomb()
{
	int i;
	for(i = 0; i < numBombs_; i++)
	{
		//if(bombs[i] == 0)
			break;
	}
	
	//bombs[i] = new Bomb();
	droppedBombs_++;
}

void Player::explodeBomb(int i)
{
	//bombs[i] = 0;
	droppedBombs_--;
}

//Player::Player(const int x, const int y, const int w, const int h , const string pic) :
//				 x_(x),  y_(y), w_(w), h_(h),
//					image_(loadImage(pic)){}
					
/*void Player::handle_input()
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: yVel -= 35; break;
            case SDLK_DOWN: yVel += 35; break;
            case SDLK_LEFT: xVel -= 35; break;
            case SDLK_RIGHT: xVel += 35; break;
            case SDLK_SPACE:	
            		    if(bombCount > 4)
            			{
            				break;
            			}
            			else
            			{
            				myBomb[bombCount].setRect(box.x, box.y);
            				setBombStatus(bombCount, 1);
                            plantBomb();	
                            break;
                        }
            default: ;
        }
    }
    //If a key was released
    else if( event.type == SDL_KEYUP )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: yVel += 35; break;
            case SDLK_DOWN: yVel -= 35; break;
            case SDLK_LEFT: xVel += 35; break;
            case SDLK_RIGHT: xVel -= 35; break;
            case SDLK_SPACE: break;
            default: ;
        }
    }
}*/

