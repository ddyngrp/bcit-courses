#include "../headers/mainHeader.h"


void textbox::handle_event(SDL_Event event, SDL_Surface *screen){

	char neW;
    if(event.key.keysym.sym == SDLK_BACKSPACE) {
        if(_message_position == 0)
          return;
        _message_position--;
        _text.erase(_text.length() - 1);
    }else {
        if(_message_position == _size)
          return;
        neW = *SDL_GetKeyName(event.key.keysym.sym);
        if((neW <= 'z' && neW >= 'a') || (neW <= 'Z' && neW >= 'A') || (neW <= '9' && neW >= '0') || (neW == '.')){
          _text += neW;
        }
        _message_position++;
    }
    fflush(stdout);
    refresh(screen);
}

void textbox::refresh(SDL_Surface *screen){
    int x;
    SDL_Surface *message;
    SDL_Color text_color = {BLACK};
    TTF_Font *font;

    if((font = TTF_OpenFont( FONT_PATH, FONT_SIZE2 )) == NULL){
      printf("Couldn't open desired font type: %s\n", SDL_GetError());
      exit(4);
    }

    apply_surface(_x_position, _y_position, _left, screen);

    for(x = 1; x < _size; x++)
        apply_surface(_x_position + x * TEXT_IMAGE_WIDTH, _y_position, _middle, screen);
    apply_surface(_x_position + x * TEXT_IMAGE_WIDTH, _y_position, _right, screen);

    if((message = TTF_RenderText_Solid( font, _text.c_str(), text_color)) == NULL){
        printf("Could not update text");
        return;
    }
    apply_surface(_x_position + TEXT_IMAGE_WIDTH, _y_position + 10, message, screen);
}

