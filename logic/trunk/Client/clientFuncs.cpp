//Movement:
void updatePlayer();
void redrawPlayer();

//Bomb:
void drawBomb();

//Explosion:
void updateMap();
void redrawMap();
void updatePlayerlist();

//Quit:
void quit();

void updatePlayer() {
	
}

void redrawPlayer() {
}

//Receive input
void Player::handle_input()
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_UP:
            case SDLK_DOWN:
            case SDLK_LEFT:
            case SDLK_RIGHT:
				//request_move(direction, playerID);
				break;
            case SDLK_SPACE:
				//Send bomb request
				break;
			case SDLK_QUIT:
				exit(1);
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
            case SDLK_UP: yVel += 35; break;
            case SDLK_DOWN: yVel -= 35; break;
            case SDLK_LEFT: xVel += 35; break;
            case SDLK_RIGHT: xVel -= 35; break;
            case SDLK_SPACE: break;
            default: ;
        }
    }
}

