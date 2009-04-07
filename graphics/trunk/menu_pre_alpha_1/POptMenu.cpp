/*
 * POptMenu.cpp
 *
 *  Created on: 25-Mar-2009
 *      Author: d3vil
 */

#include "POptMenu.h"

POptMenu::POptMenu(std::string modelNames[], std::string fileNames[], std::string mfilename, std::string smfilename, SDL_Surface* screen)
{
	printf("Creating Option Menu!\n");
	int i;
	loaded_ = 0;
	modelLoaded_ = 0;
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
	for(i = 0; i < num_models_; i++)
	{

		this->modelNames_[i] = modelNames[i];
		if (!loadModel(modelNames_[i], i))
		{
			printf("File %s did not load.\n", modelNames_[i].c_str());
			exit(1);
		}
	}
	this->setMusic(Mix_LoadMUS( mfilename.c_str()));
	this->setNexMusic(Mix_LoadWAV(smfilename.c_str()));
	this->colour_ = 0;
	printf("Option Menu Created!\n");

}

POptMenu::~POptMenu() {
	for(int i =0; i< num_options_; i++)
	{
		SDL_FreeSurface(backgrounds_[i]);
	}
	Mix_FreeMusic( music_);
	Mix_FreeChunk(nexMusic_);
}

bool POptMenu::showModels()
{
	printf("Loading Models:");
	SDL_Rect offset;
	int i, toLoad, result;
	double center, left1, left2, left3, right1, right2, right3;
	offset.y = screen_->h - 300;

	center = screen_->w / 2;
	left1  = 0.75 * center;
	left2  = 0.50 * center;
	left3  = 0.25 * center;

	right1 = center + left3;
	right2 = center + left2;
	right3 = center + left1;

	for(i = 0; i < 3; i++ )
	{
		toLoad = (modelLoaded_ - 3) + i;
		printf(".");
		if (toLoad  <  0)
		{
			continue;
		}

		switch (i){
			case 0:
			{
				zoomed_[i] = zoomSurface(models_[toLoad], 0.7, 0.7, 1);
				optimizeImg(&zoomed_[i]);
				offset.x = (int) left3 - (zoomed_[i]->w / 2);
				result = SDL_BlitSurface( zoomed_[i],0, screen_, &offset );
				break;

			}

			case 1:
			{
				zoomed_[i] = zoomSurface(models_[toLoad], 0.8, 0.8, 1);
				optimizeImg(&zoomed_[i]);
				offset.x = (int)left2 - (zoomed_[i]->w / 2) ;
				result = SDL_BlitSurface( zoomed_[i],0, screen_, &offset );
				break;

			}
			case 2:
			{
				zoomed_[i] = zoomSurface(models_[toLoad], 0.9, 0.9, 1);
				optimizeImg(&zoomed_[i]);
				offset.x = (int)left1 - (zoomed_[i]->w / 2);
				result = SDL_BlitSurface( zoomed_[i],0, screen_, &offset );
				break;

			}
		}
	}

		for(i = 6; i > 3; i-- )
		{
			toLoad = (modelLoaded_ - 3) + i;
			if (toLoad >= num_models_)
			{
				continue;
			}

		switch (i){
			case 4:
			{
				zoomed_[i] = zoomSurface(models_[toLoad], 0.9, 0.9, 1);
				optimizeImg(&zoomed_[i]);
				offset.x = (int)right1 - (zoomed_[i]->w / 2);;
				result = SDL_BlitSurface( zoomed_[i],0, screen_, &offset );
				break;

			}
			case 5:
			{
				zoomed_[i]= zoomSurface(models_[toLoad], 0.8, 0.8, 1);
				optimizeImg(&zoomed_[i]);
				offset.x = (int)right2 - (zoomed_[i]->w / 2);
				result = SDL_BlitSurface( zoomed_[i],0, screen_, &offset );
				break;

			}
			case 6:
			{
				zoomed_[i] = zoomSurface(models_[toLoad], 0.7, 0.7, 1);
				optimizeImg(&zoomed_[i]);
				offset.x = (int)right3 - (zoomed_[i]->w / 2);
				result = SDL_BlitSurface( zoomed_[i],0, screen_, &offset );
				break;
			}
		}
	}


	offset.x= (int)center -(int) (models_[modelLoaded_]->w / 2);
	result = SDL_BlitSurface( models_[modelLoaded_],0, screen_, &offset );

	 if (result == 0)
			return (SDL_Flip( screen_ ) != -1);
		else
			return false;
}
bool POptMenu::showloaded()
{
	printf("Loading backgrounds\n");
	bool result = false;
	result = move(0,0);
	if(result){
		printf("Background Loaded\n");
		showColors();
		result = showModels();
	}
	return 	result;
	}

bool POptMenu::move(int xStep, int yStep)
{
	printf("Moving Option Menu");
	SDL_Rect offset;
	offset.x = xStep;
	offset.y = yStep;
	int i = SDL_BlitSurface( backgrounds_[loaded_],0, screen_, &offset );
	return i == 0;
}

bool POptMenu::showColors(int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(colors_, 0,screen_, &offset);
}
bool POptMenu::showColors()
{
	if(loaded_ != num_options_ - 2)
		return false;

	SDL_Rect offset;
	offset.x = colorTopX;
	offset.y = colorTopY;
	SDL_BlitSurface(colors_, 0,screen_, &offset);
	offset.x = offset.x + 50 * colour_ % 300;
	offset.y = offset.y + 50 * colour_ / 300;
	SDL_BlitSurface(cselect_, 0,screen_, &offset);

	return true;
}
int POptMenu::start()
{
	printf("Option menu execution started\n");
	SDL_Event event;
	loaded_ = 0;
	if(!this->showloaded()) return 0;
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
					if(!this->showloaded()) return 0;
					break;

				case SDLK_DOWN:
					Mix_PlayChannel(-1, nexMusic_, 0);
					if(loaded_ < 2)
					{
						loaded_ = num_options_ -1;
					}else{
						--loaded_;
					}
					if(!this->showloaded()) return 0;
					break;
				case SDLK_LEFT:
					 if(loaded_ == 2)
					 {
						 if(!this->move(0,0)) return 0;
						 this->setModelLoaded(this->getModelLoaded() - 1);
						 this->showModels();
						 break;
					 }
					 break;
				case SDLK_RIGHT:
					if(loaded_ == 2)
					{
						if(!this->move(0,0)) return 0;
						this->setModelLoaded(this->getModelLoaded() + 1);
						this->showModels();
						break;
					}
					break;
				case SDLK_F11:
					return 'f';
				case SDLK_ESCAPE:
					Mix_PlayChannel(-1, nexMusic_, 0);
					return 1;
				case SDLK_RETURN:
					if(loaded_ == 1){
						Mix_PlayChannel(-1, nexMusic_, 0);
						return loaded_;
					}
						break;
				default:
				break;
			}
		}
		else if (event.type == SDL_MOUSEMOTION)
			{
				if((event.motion.x > 40) && (event.motion.x < 112) && (event.motion.y > 110) && (event.motion.y < 160))
				{
					if(loaded_ == num_options_ - 1)
						continue;
					loaded_ = num_options_ - 1;
					Mix_PlayChannel(-1, nexMusic_, 0);
					if(!this->showloaded()) return 0;
				}else
					if((event.motion.x > 40) && (event.motion.y > 210) && (event.motion.y < 260))
				{

					if(loaded_ == num_options_ - 2)
						continue;

					loaded_ = num_options_ - 2;
					Mix_PlayChannel(-1, nexMusic_, 0);
					if(!this->showloaded()) return 0;

				}else
					if((event.motion.x > 40) && (event.motion.x < 235) && (event.motion.y > 310) && (event.motion.y < 360))
				{

					if(loaded_ == num_options_ - 3)
						continue;

					loaded_ = num_options_ - 3;
					Mix_PlayChannel(-1, nexMusic_, 0);
					if(!this->showloaded()) return 0;

				}else
					if((event.motion.x > 40) && (event.motion.x < 135) && (event.motion.y > 710) && (event.motion.y < 760))
				{

					if (loaded_ == num_options_ - 4)
						continue;
					loaded_ = num_options_ - 4;
					Mix_PlayChannel(-1, nexMusic_, 0);
					if(!this->showloaded()) return 0;

				}else if(loaded_ != 0)
				{
					loaded_ = 0;
					if(!this->showloaded()) return 0;
				}
			}
		else if ((event.type == SDL_MOUSEBUTTONUP) && loaded_ == 1)
		{
			return loaded_;
		}
	}
	return 0;

}
