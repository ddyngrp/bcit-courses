#include "../headers/InputOkCancel.h"
using std::string;
/******************************************************************************
 *  Constructor:    InputOkCancel
 *
 *  Date:        March 30, 2009
 *
 *  Revisions:		Colby Last
 *
 *  Designer:    Alin Albu
 *  Programmer:  Alin Albu
 *
 *  Interface:   InputOkCancel(std::string fileNames[], std::string mfilename, SDL_Surface* screen, int size)
 *								filenames - menu items paths
 *								mfilename - sound for loading item ( item click)
 *								screen 	  - the SDL_surface to draw on
 *								size      - the number of max characters in text box

 *
 *  Description:
	Construct an OK CANCEL dialog box with a text that can be used to retrieve and
	save user keyboard input.
 *
 *****************************************************************************/

InputOkCancel::InputOkCancel(std::string fileNames[], std::string mfilename, SDL_Surface* screen, int size) {
	printf("Creating Ok_Cancel menu!\n");
	int i;
	loaded_ = 0;
	this->screen_ = screen;
	for (i = 0; i < num_options_; i++) {
		this->fileNames_[i] = fileNames[i];
		if (!loadBackground(fileNames_[i], i)) {
			printf("File %s did not load.\n", fileNames_[i].c_str());
			exit(1);
		}
	}
	this->setMusic(Mix_LoadWAV( mfilename.c_str() ));
	text = new textbox(200, 470, size);
	text->refresh(screen);
	printf("Done Ok_Cancel menu1\n");

}

/******************************************************************************
 *  Destructor:    ~InputOkCancel()
 *
 *  Date:        March 30, 2009
 *
 *  Revisions:   Colby Last
 *
 *  Designer:    Alin Albu
 *  Programmer:  Alin Albu
 *
 *  Interface:   ~InputOkCancel()
 *
 *  Description: Frees the loaded pictures and music when the menu is destroyed.
 *
 *****************************************************************************/

InputOkCancel::~InputOkCancel() {
	for (int i = 0; i < num_options_; i++) {
		SDL_FreeSurface(backgrounds_[i]);
	}
	Mix_FreeChunk(music_);
}
/******************************************************************************
 *  Function:    showLoaded
 *
 *  Date:        March 30, 2009
 *
 *  Revisions:
 *
 *  Designer:    Alin Albu
 *  Programmer:  Alin Albu
 *
 *  Interface:   showLoaded()
 *  Returns:    true on success false on failure
 *
 *  Description: Show the currently selected option.
 *
 *****************************************************************************/

bool InputOkCancel::showLoaded() {
	printf("Showing loaded Ok_Cancel\n");
	SDL_Rect offset;
	offset.x = 40;
	offset.y = 250;
	int i = SDL_BlitSurface(backgrounds_[loaded_], 0, screen_, &offset);
	text->refresh(screen_);
	if (i == 0)
		return (SDL_Flip(screen_) != -1);
	else
		return false;
}
/******************************************************************************
 *  Function:    move
 *
 *  Date:        March 30, 2009
 *
 *  Revisions:
 *
 *  Designer:    Alin Albu
 *  Programmer:  Alin Albu
 *
 *  Interface:   move(int xstep, int ystep)
 *  				xstep - new x coordinate
 *  				ystep - new y coordinate
 *  Returns:    true on success false on failure
 *
 *  Description: moves the currently loaded background to the new location.
 *  			This function does not refresh the screen, it has to be done outside
 *  			the function.
 *
 *****************************************************************************/
bool InputOkCancel::move(int xstep, int ystep) {
	printf("Moving Ok_Cancel Menu\n");
	SDL_Rect offset;
	offset.x = 40;
	offset.y = ystep > 250 ? 250 : ystep;
	int i = SDL_BlitSurface(backgrounds_[loaded_], 0, screen_, &offset);
	return i == 0;
}
/******************************************************************************
 *  Function:    start
 *
 *  Date:        March 30, 2009
 *
 *  Revisions:
 *
 *  Designer:    Alin Albu
 *  Programmer:  Alin Albu
 *
 *  Interface:   start(SDL_Event event)
 *  Returns:    true on success false on failure
 *
 *  Description: Starts the menu loop, loads the menu backgrounds and
 *  return the result when user selects OK.
 *
 *****************************************************************************/
string InputOkCancel::start(SDL_Event event) {
	printf("Starting Ok_Cancel Menu!\n");
	loaded_ = 0;
	std::string tmpTxt = "";
	if (text->get_text().length() > 0) {
		tmpTxt = text->get_text();
	}
	if (!this->showLoaded())
		return 0;
	while (true) {
		SDL_WaitEvent(&event);
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_UP:
			case SDLK_RIGHT:
				if (loaded_ == num_options_ - 1) {
					break;
				} else {
					loaded_ = num_options_ - 1;
					Mix_PlayChannel(-1, music_, 0 );
				}
				if (!this->showLoaded())
					return 0;
				break;

			case SDLK_DOWN:
			case SDLK_LEFT:
				if (loaded_ == num_options_ - 2) {
					break;
				} else {
					loaded_ = num_options_ - 2;
					Mix_PlayChannel(-1, music_, 0 );
				}
				if (!this->showLoaded())
					return 0;
				break;
			case SDLK_ESCAPE:
				return text->get_text();
			case SDLK_RETURN: {
				if (loaded_ == 2)
					text->set_text(tmpTxt);
				return text->get_text();
				break;
			}
			default:
				text->handle_event(event, screen_);
				if (!this->showLoaded())
					return 0;
				break;
			}
		} else if (event.type == SDL_QUIT) {
			loaded_ = 1;
			exit(25);
		} else if (event.type == SDL_MOUSEMOTION) {
			if ((event.motion.x > 90) && (event.motion.x < 140)
					&& (event.motion.y > 470) && (event.motion.y < 510)) {
				if (loaded_ == num_options_ - 2)
					continue;

				loaded_ = num_options_ - 2;
				Mix_PlayChannel(-1, music_, 0);
				if (!this->showLoaded())
					return 0;
			} else if ((event.motion.x > 400) && (event.motion.x < 550)
					&& (event.motion.y > 470) && (event.motion.y < 510)) {
				if (loaded_ == num_options_ - 1)
					continue;

				loaded_ = num_options_ - 1;
				Mix_PlayChannel(-1, music_, 0);
				if (!this->showLoaded())
					return 0;
			} else {
				if (loaded_ == 0)
					continue;

				loaded_ = 0;
				if (!this->showLoaded())
					return 0;
			}
		} else if ((event.type == SDL_MOUSEBUTTONUP) && loaded_) {
			if (loaded_ == 2)
				text->set_text(tmpTxt);
			return text->get_text();
		}
	}
	return 0;

}
