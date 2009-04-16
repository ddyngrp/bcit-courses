#include "InputOkCancel.h"
using std::string;


InputOkCancel::InputOkCancel(std::string fileNames[], std::string mfilename, SDL_Surface* screen)
{
	printf("Creating Ok_Cancel menu!\n");
	int i;
	loaded_ = 0;
	this->screen_ = screen;
	for(i = 0; i < num_options_; i++)
	{
		this->fileNames_[i] = fileNames[i];
		if (!loadBackground(fileNames_[i], i))
		{
			printf("File %s did not load.\n", fileNames_[i].c_str());
			exit(1);
		}
	}
	this->setMusic(Mix_LoadWAV( mfilename.c_str() ));
        text = new textbox(210, 470, 10);
        text->refresh();
	printf("Done Ok_Cancel menu1\n");

}

InputOkCancel::~InputOkCancel() {
	for(int i =0; i< num_options_; i++)
	{
		SDL_FreeSurface(backgrounds_[i]);
	}
	Mix_FreeChunk( music_);
}

bool InputOkCancel::showLoaded()
{
	printf("Showing loaded Ok_Cancel\n");
	SDL_Rect offset;
	offset.x = 40;
	offset.y =  250;
	int i = SDL_BlitSurface( backgrounds_[loaded_],0, screen_, &offset );
        text->refresh();
	if (i == 0)
		return (SDL_Flip( screen_ ) != -1);
	else
		return false;
}

bool InputOkCancel::move(int xstep, int ystep)
{
	printf("Movin Ok_Cancel Menu\n");
	SDL_Rect offset;
	offset.x = 40;
	offset.y = ystep > 250? 250: ystep;
	int i = SDL_BlitSurface( backgrounds_[loaded_],0, screen_, &offset );
	return i == 0;
}

string InputOkCancel::start(SDL_Event event)
{
	printf("Starting Ok_Cancel Menu!\n");
	loaded_= 0;
	if(!this->showLoaded()) return 0;
	while(true)
	{
		SDL_WaitEvent(&event);
		if(event.type == SDL_KEYDOWN)
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_UP:
				case SDLK_RIGHT:
					if(loaded_ == num_options_ -1){
						break;
					}else{
						loaded_ = num_options_ -1;
						Mix_PlayChannel(-1, music_, 0 );
					}
					if(!this->showLoaded()) return 0;
					break;

				case SDLK_DOWN:
				case SDLK_LEFT:
					if(loaded_ == num_options_ - 2)
					{
						break;
					}else{
						loaded_ = num_options_ - 2;
						Mix_PlayChannel(-1, music_, 0 );
					}
					if(!this->showLoaded()) return 0;
					break;
				case SDLK_ESCAPE:
					return text->get_text();
				case SDLK_RETURN:
				{
					if(loaded_ != 0)
						return text->get_text();
					break;
				}
				default:
					text->handle_event(event);
					if(!this->showLoaded()) return 0;
					break;
			}
		}
		else if (event.type == SDL_MOUSEMOTION)
			{
				if((event.motion.x > 90) && (event.motion.x < 140) &&
						(event.motion.y > 470) && (event.motion.y < 510))
				{
					if (loaded_ == num_options_ - 2)
						continue;

					loaded_ = num_options_ - 2;
					Mix_PlayChannel(-1, music_, 0);
					if(!this->showLoaded()) return 0;
				}else
					if((event.motion.x > 400) && (event.motion.x < 550) &&
							(event.motion.y > 470) && (event.motion.y < 510))
					{
						if (loaded_ == num_options_ - 1)
							continue;

						loaded_ = num_options_ - 1;
						Mix_PlayChannel(-1, music_, 0);
						if(!this->showLoaded()) return 0;
					}
				else
				{
					if(loaded_ == 0)
						continue;

					loaded_ = 0;
					if(!this->showLoaded()) return 0;
				}
			}
			else if ((event.type == SDL_MOUSEBUTTONUP) && loaded_)
			{
				return text->get_text();
			}
	}
	return 0;

}
