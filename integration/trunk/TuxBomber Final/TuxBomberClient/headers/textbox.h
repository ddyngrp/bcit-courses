#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "mainHeader.h"

#define BLACK 0,0,0
#define TEXT_IMAGE_WIDTH 8
#define TEXT_IMAGE_HEIGHT 36
SDL_Surface *load_image(std::string filename);
class textbox {
public:
	textbox(int x_position, int y_position, int size) :
		_x_position(x_position), _y_position(y_position), _size(size) {
		_message_position = 0;
		_left = load_image(TBOX_LEFT);
		_middle = load_image(TBOX_CENTRE);
		_right = load_image(TBOX_RIGHT);
	}
	~textbox() {
		SDL_FreeSurface(_left);
		SDL_FreeSurface(_middle);
		SDL_FreeSurface(_right);
	}
	void handle_event(SDL_Event, SDL_Surface *);
	std::string get_text() {
		return _text;
	}
	void set_text(std::string txt) {
		_text = txt;
		_message_position = _text.length();
	}
	void refresh(SDL_Surface *);
private:
	int _x_position, _y_position;
	int _size;
	std::string _text;
	int _message_position;
	SDL_Surface *_left, *_middle, *_right;
};

#endif

