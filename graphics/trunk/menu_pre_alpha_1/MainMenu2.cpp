/*
 * MainMenu2.cpp
 *
 *  Created on: 25-Mar-2009
 *      Author: d3vil
 */

#include "MainMenu2.h"

MainMenu2::MainMenu2(std::string fileNames[], std::string mfilename, std::string smfilename, SDL_Surface* screen)
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
	this->setMusic(Mix_LoadMUS( mfilename.c_str()));
	this->setNexMusic(Mix_LoadWAV(smfilename.c_str()));

}

MainMenu2::~MainMenu2() {
	for(int i =0; i< num_options_; i++)
	{
		SDL_FreeSurface(backgrounds_[i]);
	}
	Mix_FreeMusic( music_);
	Mix_FreeChunk(nexMusic_);
}

bool MainMenu2::showLoaded()
{
	int i = SDL_BlitSurface( backgrounds_[loaded_],0, screen_, 0 );
	if(!Mix_PlayingMusic())
		Mix_PlayMusic( music_, -1 );
	if (i == 0)
			return (SDL_Flip( screen_ ) != -1);
		else
			return false;
}

bool MainMenu2::move(int xStep, int yStep)
{
	SDL_Rect offset;
	offset.x = xStep;
	offset.y = yStep;
	int i = SDL_BlitSurface( backgrounds_[loaded_],0, screen_, &offset );
	return i == 0;
}

int MainMenu2::start(SDL_Event event)
{
	loaded_ = 0;
	if(!this->showLoaded()) return 0;
	while(true)
	{
		SDL_WaitEvent(&event);
		if(event.type == SDL_KEYDOWN)
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_UP:
					Mix_PlayChannel(-1, nexMusic_, 0);
					if(loaded_ == num_options_ -1){
						loaded_ = 1;
					}else{
						++loaded_;
					}
					if(!this->showLoaded()) return 0;
					break;

				case SDLK_DOWN:
					Mix_PlayChannel(-1, nexMusic_, 0);
					if(loaded_ < 2)
					{
						loaded_ = num_options_ -1;
					}else{
						--loaded_;
					}
					if(!this->showLoaded()) return 0;
					break;
				case SDLK_F11:
					return 'f';
				case SDLK_ESCAPE:
					Mix_PlayChannel(-1, nexMusic_, 0);
					return 1;
				case SDLK_RETURN:
					if(loaded_ == 0)
						break;
					Mix_PlayChannel(-1, nexMusic_, 0);
					return loaded_;
				default:
				break;
			}
		}
		else if (event.type == SDL_MOUSEMOTION)
			{
				if((event.motion.x >300) && (event.motion.y < 150))
				{
					if(loaded_ == num_options_ - 1)
						continue;
					loaded_ = num_options_ - 1;
					Mix_PlayChannel(-1, nexMusic_, 0);
					if(!this->showLoaded()) return 0;
				}else
				if((event.motion.x < 400) && (event.motion.y < 300) && (event.motion.y > 150))
				{

					if(loaded_ == num_options_ - 2)
						continue;

					loaded_ = num_options_ - 2;
					Mix_PlayChannel(-1, nexMusic_, 0);
					if(!this->showLoaded()) return 0;
				}else
				if((event.motion.x > 200) && (event.motion.y > 300) && (event.motion.y < 650))
				{

					if(loaded_ == num_options_ - 3)
						continue;

					loaded_ = num_options_ - 3;
					Mix_PlayChannel(-1, nexMusic_, 0);
					if(!this->showLoaded()) return 0;
				}else
				if((event.motion.x < 200) && (event.motion.y > 700))
				{

					if (loaded_ == num_options_ - 4)
						continue;
					loaded_ = num_options_ - 4;
					Mix_PlayChannel(-1, nexMusic_, 0);
					if(!this->showLoaded()) return 0;
				}else
				{
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
