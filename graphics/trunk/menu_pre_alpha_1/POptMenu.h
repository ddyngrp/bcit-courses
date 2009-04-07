/*
 * POptMenu.h
 *
 *  Created on: 27-Mar-2009
 *      Author: d3vil
 */

#ifndef POPTMENU_H_
#define POPTMENU_H_
#include "mainHeader.h"

class POptMenu {
public:
	POptMenu(std::string modelNames[], std::string fileNames[], std::string mfilename, std::string smfilename, SDL_Surface* screen);
	virtual ~POptMenu();

	static const int num_options_ = 5;  //number of options
	static const int num_models_ = 8;
	static const int colorTopX = 300;
	static const int colorTopY = 200;

	int getNum_models() const{
	        return num_models_;
	    }

    int getNum_options() const{
        return num_options_;
    }

    std::string getFileNames(int index) const
    {
    	if (index >= num_options_ || index < 0)
		{
			return "";
		}
        return fileNames_[index];
    }

    void setFileNames(std::string fileName, int index)
    {
    	if (index >= num_options_ || index < 0)
		{
			return ;
		}
        this->fileNames_[index] = fileName;
    }

    SDL_Surface *getBackground(int index) const
    {
    	if (index >= num_options_ || index < 0)
		{
			return NULL;
		}
        return backgrounds_[index];
    }

    void setBackground(SDL_Surface *background,int index)
    {
    	if (index >= num_options_ || index < 0)
		{
			return ;
		}
        this->backgrounds_[index] = background;
    }

    bool loadBackground(std::string filename,int index)
    {
    	if (index >= num_options_ || index < 0)
    	{
    		return false;
    	}
    	backgrounds_[index]= load_image(filename.c_str());
    	return backgrounds_[index] != NULL;
    }

    bool loadModel(std::string filename, int index)
   {
	if (index >= num_models_ || index < 0)
	{
		return false;
	}
	models_[index]= load_image(filename.c_str());
	return models_[index] != NULL;
   }

    SDL_Surface *getScreen() const
    {
        return screen_;
    }

    void setScreen(SDL_Surface *screen_)
    {
        this->screen_ = screen_;
    }

    Mix_Chunk *getNexMusic() const
    {
        return nexMusic_;
    }

    void setNexMusic(Mix_Chunk *nexMusic_)
    {
        this->nexMusic_ = nexMusic_;
    }

    Mix_Music *getMusic() const
    {
        return music_;
    }

    void setMusic(Mix_Music *music_)
    {
        this->music_ = music_;
    }


    bool showModels();
    bool showloaded();
    bool showColors(int x, int y);
    bool showColors();
    bool move(int xStep, int yStep);
    int start();
    SDL_Surface *getColors() const
    {
        return colors_;
    }

    void setColors(SDL_Surface *colors)
    {
        this->colors_ = colors;
    }

    int getLoaded() const
    {
        return loaded_;
    }

    void setLoaded(int loaded)
    {
        this->loaded_ = loaded;
    }

    int getModelLoaded() const
    {
        return modelLoaded_;
    }

    void setModelLoaded(int modelLoaded)
    {
    	if (modelLoaded < 0){
    		this->modelLoaded_ = 0;
    		return;
    	}
		if (modelLoaded >= num_models_ ){
			this->modelLoaded_ = num_models_ -1;
			return;
		}

        this->modelLoaded_ = modelLoaded;
    }

    std::string getModelNames(int index) const
    {
        return modelNames_[index];
    }

    void setModelNames(std::string modelName, int index)
    {
        this->modelNames_[index] = modelName;
    }

private:
	int loaded_;
	int modelLoaded_;
	int colour_;
	std::string fileNames_[num_options_]; // background files
	std::string modelNames_[num_models_]; // model files
	SDL_Surface* backgrounds_[num_options_];//the actual loaded backgrounds
	SDL_Surface* models_[num_models_];
	SDL_Surface* zoomed_[7];	//shrink image of models
	SDL_Surface* screen_;
	SDL_Surface* colors_; //name colors
	SDL_Surface* cselect_;
	Mix_Music *music_;
	Mix_Chunk *nexMusic_;

};


#endif /* POPTMENU_H_ */
