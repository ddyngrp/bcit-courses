/*
 * OkCancel.cpp
 *
 *  Created on: 25-Mar-2009
 *      Author: d3vil
 */

#include "OkCancel.h"

OkCancel::OkCancel(std::string fileNames[], std::string mfilename, SDL_Surface* screen)
{
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

}

OkCancel::~OkCancel() {
	for(int i =0; i< num_options_; i++)
	{
		SDL_FreeSurface(backgrounds_[i]);
	}
	Mix_FreeChunk( music_);
}

bool OkCancel::showLoaded()
{
	SDL_Rect offset;
	offset.x = 40;
	offset.y =  250;
	int i = SDL_BlitSurface( backgrounds_[loaded_],0, screen_, &offset );
	if (i == 0)
		return (SDL_Flip( screen_ ) != -1);
	else
		return false;
}

bool OkCancel::move(int xstep, int ystep)
{
	SDL_Rect offset;
	offset.x = 40;
	offset.y = ystep > 250? 250: ystep;
	int i = SDL_BlitSurface( backgrounds_[loaded_],0, screen_, &offset );
	return i == 0;
}

int OkCancel::start(SDL_Event event)
{
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
					return 2;
				case SDLK_RETURN:
				case SDLK_SPACE:
				{
					if(loaded_ != 0)
						return loaded_;
					break;
				}
				default:
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
				return loaded_;
			}
	}
	return 0;

}
