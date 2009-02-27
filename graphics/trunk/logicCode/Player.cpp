#include "bombHeader.h"

Player::Player()
{
    //Initialize the offsets
    box.x = 0;
    box.y = 0;

    //Set the Player's dimentions
    box.w = SQUARE_WIDTH;
    box.h = SQUARE_HEIGHT;

    //Initialize the velocity
    xVel = 0;
    yVel = 0;
    
    bombCount = 0;
}


void Player::setBombStatus(int bombNo, bool status)
{
    isPlanted[bombNo] = status;
}

void Player::handle_input()
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: yVel -= SQUARE_HEIGHT / 2; break;
            case SDLK_DOWN: yVel += SQUARE_HEIGHT / 2; break;
            case SDLK_LEFT: xVel -= SQUARE_WIDTH / 2; break;
            case SDLK_RIGHT: xVel += SQUARE_WIDTH / 2; break;
            case SDLK_SPACE:	if(bombCount > 4)
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
            case SDLK_UP: yVel += SQUARE_HEIGHT / 2; break;
            case SDLK_DOWN: yVel -= SQUARE_HEIGHT / 2; break;
            case SDLK_LEFT: xVel += SQUARE_WIDTH / 2; break;
            case SDLK_RIGHT: xVel -= SQUARE_WIDTH / 2; break;
            case SDLK_SPACE: break;
            default: ;
        }
    }
}

void Player::move()
{
    //Move the Player left or right
    box.x += xVel;

    //If the Player went too far to the left or right or has collided with the wall
    if( ( box.x < 0 ) || ( box.x + SQUARE_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        box.x -= xVel;
    }

    //Move the Player up or down
    box.y += yVel;

    //If the Player went too far up or down or has collided with the wall
    if( ( box.y < 0 ) || ( box.y + SQUARE_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        box.y -= yVel;
    }
}

void Player::show()
{
    //Show the Player
    apply_surface( box.x, box.y, square, screen );
    for(int i = 0; isPlanted[i] != 0; i++)
    {
        apply_surface( myBomb[i].getRectX(), myBomb[i].getRectY(), bomb, screen );
    }
}
