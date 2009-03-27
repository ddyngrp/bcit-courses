/*
 * OkCancel.h
 *
 *  Created on: 25-Mar-2009
 *      Author: d3vil
 */

#ifndef OKCANCEL_H_
#define OKCANCEL_H_
#include "mainHeader.h"

/*
 *
 */
class OkCancel
{
public:
	explicit OkCancel(std::string fileNames[], std::string mfilename, SDL_Surface* screen);
	virtual ~OkCancel();

	static const int num_options_ = 3;  //number of options
	    int getNum_options() const
	    {
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

	    SDL_Surface *getScreen() const
	    {
	        return screen_;
	    }

	    void setScreen(SDL_Surface *screen_)
	    {
	        this->screen_ = screen_;
	    }


	    bool showLoaded();
	    int start(SDL_Event event);
	    Mix_Chunk *getMusic() const
	    {
	        return music_;
	    }

	    void setMusic(Mix_Chunk *music_)
	    {
	        this->music_ = music_;
	    }

	private:
		int loaded_;
		std::string fileNames_[num_options_]; // background files
		SDL_Surface* backgrounds_[num_options_];//the actual loaded backgrounds
		SDL_Surface* screen_;
		Mix_Chunk *music_;

};


#endif /* OKCANCEL_H_ */
