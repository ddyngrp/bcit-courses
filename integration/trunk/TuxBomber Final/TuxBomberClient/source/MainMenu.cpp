/*
 * MainMenu2.cpp
 *
 *  Created on: 25-Mar-2009
 *      Author: d3vil
 */

#include "../headers/MainMenu.h"

/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION: 		    MainMenu2 Constructor
 --
 --       DATE:                      April 15, 2009
 --
 --       DESIGNER:                  Alin Albu
 --
 --       PROGRAMMER: 		         Alin Albu
 --
 --       INTERFACE:                 MainMenu2(std::string fileNames[], std::string mfilename, std::string smfilename, SDL_Surface* screen)
 --
 --       NOTES:
 --       Creates a new menu loading the background images and setting the music
 ----------------------------------------------------------------------------------------------------------------------*/

MainMenu2::MainMenu2(std::string fileNames[], std::string mfilename,
    std::string smfilename, SDL_Surface* screen)
{
  printf("Creating main menu\n");
  int i;
  loaded_ = 0;
  this->screen_ = screen;
  for (i = 0; i < num_options_; i++)
    {
      this->fileNames_[i] = fileNames[i];
      if (!loadBackground(fileNames_[i], i))
        {
          printf("File %s did not load.\n", fileNames_[i].c_str());
          exit(1);
        }
    }
  this->setMusic(Mix_LoadMUS(mfilename.c_str()));
  this->setNexMusic(Mix_LoadWAV(smfilename.c_str()));
  printf("Creating main menu -- Done\n");

}

/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION: 		    MainMenu2 Deconstructor
 --
 --       DATE:                      April 15, 2009
 --
 --       DESIGNER:                  Alin Albu
 --
 --       PROGRAMMER: 		    	Alin Albu
 --
 --       INTERFACE:                 MainMenu2(std::string fileNames[], std::string mfilename, std::string smfilename, SDL_Surface* screen)
 --
 --       NOTES:
 --       Free's all the background images and music
 ----------------------------------------------------------------------------------------------------------------------*/

MainMenu2::~MainMenu2()
{
  for (int i = 0; i < num_options_; i++)
    {
      SDL_FreeSurface(backgrounds_[i]);
    }
  Mix_FreeMusic(music_);
  Mix_FreeChunk(nexMusic_);
}

/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION: 		    showLoaded
 --
 --       DATE:                      April 15, 2009
 --
 --       DESIGNER:                  Alin Albu
 --
 --       PROGRAMMER: 		    Alin Albu
 --
 --       INTERFACE:                 bool MainMenu2::showLoaded()
 --
 --	 	  RETURNS:		    true if succeeds, false otherwise
 --
 --       NOTES:
 --       Loads the current opiton onto the screen and checks to see if music is playing.
		 It also flips the screen to draw the new surface.
 ----------------------------------------------------------------------------------------------------------------------*/

bool
MainMenu2::showLoaded()
{
  printf("Showing loaded Menu!\n");
  int i = SDL_BlitSurface(backgrounds_[loaded_], 0, screen_, 0);
  if (!Mix_PlayingMusic())
    Mix_PlayMusic(music_, -1);
  if (i == 0)
    {
      return (SDL_Flip(screen_) != -1);
    }
  else
    {
      printf("Showing loaded Menu -- Failed!\n");
      return false;
    }
}

/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION: 		    move
 --
 --       DATE:                      April 15, 2009
 --
 --       DESIGNER:                  Alin Albu
 --
 --       PROGRAMMER: 		    	Alin Albu
 --
 --       INTERFACE:                 bool MainMenu2::move(int xStep, int yStep)
 --
 --	 	  RETURNS:		    true if succeeds, false otherwise
 --
 --       NOTES:
 --       Moves the menu to a new place on the screen.
 ----------------------------------------------------------------------------------------------------------------------*/

bool
MainMenu2::move(int xStep, int yStep)
{
  printf("Moving menu!\n");
  SDL_Rect offset;
  offset.x = xStep;
  offset.y = yStep;
  int i = SDL_BlitSurface(backgrounds_[loaded_], 0, screen_, &offset);
  return i == 0;
  printf("Moving menu! -- Done\n");
}

/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION: 		    start
 --
 --       DATE:                      April 15, 2009
 --
 --       DESIGNER:                  Alin Albu
 --
 --       PROGRAMMER: 		    Alin Albu
 --
 --       INTERFACE:                 int MainMenu2::start(SDL_Event event)
 --
 --	 	  RETURNS:		    the index of the selected option.
 --
 --       NOTES:
 --       This function waits for events such as keyboard or mouse input.  The mouse input checks where the mouse click
 --	 is on the screen to check if the user clicked an item.  The keyboard input switches between the menu items.
 ----------------------------------------------------------------------------------------------------------------------*/

int
MainMenu2::start(SDL_Event event)
{
  loaded_ = 0;
  printf("Main menu execution Started\n");
  if (!this->showLoaded())
    return 0;
  while (true)
    {
      SDL_WaitEvent(&event);
      if (event.type == SDL_KEYDOWN)
        {
          switch (event.key.keysym.sym)
            {
          case SDLK_UP:
            Mix_PlayChannel(-1, nexMusic_, 0);
            if (loaded_ == num_options_ - 1)
              {
                loaded_ = 1;
              }
            else
              {
                ++loaded_;
              }
            if (!this->showLoaded())
              return 0;
            break;

          case SDLK_DOWN:
            Mix_PlayChannel(-1, nexMusic_, 0);
            if (loaded_ < 2)
              {
                loaded_ = num_options_ - 1;
              }
            else
              {
                --loaded_;
              }
            if (!this->showLoaded())
              return 0;
            break;
          case SDLK_F11:
            return 'f';
          case SDLK_ESCAPE:
            Mix_PlayChannel(-1, nexMusic_, 0);
            return 1;
          case SDLK_RETURN:
            if (loaded_ == 0)
              break;
            Mix_PlayChannel(-1, nexMusic_, 0);
            return loaded_;
          default:
            break;
            }
        }
      else if (event.type == SDL_QUIT)
        {
          loaded_ = 1;
          exit(25);
        }
      else if (event.type == SDL_MOUSEMOTION)
        {
          if ((event.motion.x > 300) && (event.motion.y < 150))
            {
              if (loaded_ == num_options_ - 1)
                continue;
              loaded_ = num_options_ - 1;
              Mix_PlayChannel(-1, nexMusic_, 0);
              if (!this->showLoaded())
                return 0;
            }
          else if ((event.motion.x < 400) && (event.motion.y < 300)
              && (event.motion.y > 150))
            {

              if (loaded_ == num_options_ - 2)
                continue;

              loaded_ = num_options_ - 2;
              Mix_PlayChannel(-1, nexMusic_, 0);
              if (!this->showLoaded())
                return 0;
            }
          else if ((event.motion.x > 200) && (event.motion.y > 300)
              && (event.motion.y < 650))
            {

              if (loaded_ == num_options_ - 3)
                continue;

              loaded_ = num_options_ - 3;
              Mix_PlayChannel(-1, nexMusic_, 0);
              if (!this->showLoaded())
                return 0;
            }
          else if ((event.motion.x < 200) && (event.motion.y > 700))
            {

              if (loaded_ == num_options_ - 4)
                continue;
              loaded_ = num_options_ - 4;
              Mix_PlayChannel(-1, nexMusic_, 0);
              if (!this->showLoaded())
                return 0;
            }
          else if (loaded_ != 0)
            {
              loaded_ = 0;
              if (!this->showLoaded())
                return 0;
            }
        }
      else if ((event.type == SDL_MOUSEBUTTONUP) && loaded_)
        {
          return loaded_;
        }
    }
  return 0;

}
/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION: 		    getNum_options
 --
 --       DATE:                      April 15, 2009
 --
 --       DESIGNER:                  Alin Albu
 --
 --       PROGRAMMER: 		    Alin Albu
 --
 --       INTERFACE:                 int MainMenu2::getNum_options() const
 --
 --	 	  RETURNS:		    the number of options in the menu

 ----------------------------------------------------------------------------------------------------------------------*/

int
MainMenu2::getNum_options() const
{
  return num_options_;
}
/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION: 		    getFileNames
 --
 --       DATE:                      April 15, 2009
 --
 --       DESIGNER:                  Alin Albu
 --
 --       PROGRAMMER: 		    Alin Albu
 --
 --       INTERFACE:                 int MainMenu2::getFileNames(int index) const
 --
 --	 	  RETURNS:		    the path of the background at option "index"

 ----------------------------------------------------------------------------------------------------------------------*/

std::string
MainMenu2::getFileNames(int index) const
{
  if (index >= num_options_ || index < 0)
    {
      return "";
    }
  return fileNames_[index];
}
/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION: 		    setFileNames
 --
 --       DATE:                      April 15, 2009
 --
 --       DESIGNER:                  Alin Albu
 --
 --       PROGRAMMER: 		    Alin Albu
 --
 --       INTERFACE:                 void MainMenu2::setFileNames(std::string fileName, int index)
 --
 --	 	  RETURNS:				void

		 Description:
		Sets the path for the background at index "index" to the path "filename"
 ----------------------------------------------------------------------------------------------------------------------*/

void
MainMenu2::setFileNames(std::string fileName, int index)
{
  if (index >= num_options_ || index < 0)
    {
      return;
    }
  this->fileNames_[index] = fileName;
}
/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION: 		    getBackground
 --
 --       DATE:                      April 15, 2009
 --
 --       DESIGNER:                  Alin Albu
 --
 --       PROGRAMMER: 		    Alin Albu
 --
 --       INTERFACE:                 SDL_Surface * MainMenu2::getBackground(int index) const
 --
 --	 	  RETURNS:				returns a pointer to the background at index "index", or NULL if invalid index


 ----------------------------------------------------------------------------------------------------------------------*/

SDL_Surface *
MainMenu2::getBackground(int index) const
{
  if (index >= num_options_ || index < 0)
    {
      return NULL;
    }
  return backgrounds_[index];
}
/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION: 		    setBackground
 --
 --       DATE:                      April 15, 2009
 --
 --       DESIGNER:                  Alin Albu
 --
 --       PROGRAMMER: 		    Alin Albu
 --
 --       INTERFACE:                 void MainMenu2::setBackground(SDL_Surface *background, int index)
 --
 --	 	  RETURNS:				void

		 Description:
		Sets the  background at index "index" to the  "background"
 ----------------------------------------------------------------------------------------------------------------------*/

void
MainMenu2::setBackground(SDL_Surface *background, int index)
{
  if (index >= num_options_ || index < 0)
    {
      return;
    }
  this->backgrounds_[index] = background;
}
/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION: 		    loadBackground
 --
 --       DATE:                      April 15, 2009
 --
 --       DESIGNER:                  Alin Albu
 --
 --       PROGRAMMER: 		    Alin Albu
 --
 --       INTERFACE:                 bool MainMenu2::loadBackground(std::string filename, int index)
 --
 --	 	  RETURNS:				true if loaded, false otherwise

		 Description:
		Loads the picture at path "filename" as background at index "index"
 ----------------------------------------------------------------------------------------------------------------------*/

bool
MainMenu2::loadBackground(std::string filename, int index)
{
  if (index >= num_options_ || index < 0)
    {
      return false;
    }
  backgrounds_[index] = load_image(filename.c_str());
  return backgrounds_[index] != NULL;
}

/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION: 		    getScreen
 --
 --       DATE:                      April 15, 2009
 --
 --       DESIGNER:                  Alin Albu
 --
 --       PROGRAMMER: 		    Alin Albu
 --
 --       INTERFACE:             MainMenu2::getScreen() const
 --
 --	 	  RETURNS:				returns a pointer to the screen (main draw surface)


 ----------------------------------------------------------------------------------------------------------------------*/

SDL_Surface *
MainMenu2::getScreen() const
{
  return screen_;
}

/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION: 		    setScreen
 --
 --       DATE:                      April 15, 2009
 --
 --       DESIGNER:                  Alin Albu
 --
 --       PROGRAMMER: 		    Alin Albu
 --
 --       INTERFACE:             void MainMenu2::setScreen(SDL_Surface *screen_)
 --
 --	 	  RETURNS:				void

		  Description:
		  Set a new pointer to the screen.

 ----------------------------------------------------------------------------------------------------------------------*/

void
MainMenu2::setScreen(SDL_Surface *screen_)
{
  this->screen_ = screen_;
}

/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION: 		    getLoaded
 --
 --       DATE:                      April 15, 2009
 --
 --       DESIGNER:                  Alin Albu
 --
 --       PROGRAMMER: 		    Alin Albu
 --
 --       INTERFACE:             int MainMenu2::getLoaded() const
 --
 --	 	  RETURNS:				the index of the loaded background



 ----------------------------------------------------------------------------------------------------------------------*/

int
MainMenu2::getLoaded() const
{
  return loaded_;
}
/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION: 		    setLoaded
 --
 --       DATE:                      April 15, 2009
 --
 --       DESIGNER:                  Alin Albu
 --
 --       PROGRAMMER: 		    Alin Albu
 --
 --       INTERFACE:             void MainMenu2::setLoaded(int loaded)
 --
 --	 	  RETURNS:				void

		  Description:
		  Set a new value to save as the loaded background.

 ----------------------------------------------------------------------------------------------------------------------*/

void
MainMenu2::setLoaded(int loaded)
{
  this->loaded_ = loaded;
}
/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION: 		    getNexMusic
 --
 --       DATE:                      April 15, 2009
 --
 --       DESIGNER:                  Alin Albu
 --
 --       PROGRAMMER: 		    Alin Albu
 --
 --       INTERFACE:             Mix_Chunk * MainMenu2::getNexMusic() const
 --
 --	 	  RETURNS:				a pinter to the opened music chunk
 ----------------------------------------------------------------------------------------------------------------------*/

Mix_Chunk *
MainMenu2::getNexMusic() const
{
  return nexMusic_;
}
/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION: 		    setNexMusic
 --
 --       DATE:                      April 15, 2009
 --
 --       DESIGNER:                  Alin Albu
 --
 --       PROGRAMMER: 		    Alin Albu
 --
 --       INTERFACE:             MainMenu2::setNexMusic(Mix_Chunk *nexMusic_)
 --
 --	 	  RETURNS:				void

		  Description:
		  Set a new pointer to the music chunk that shalbe played when new a new item is loaded.

 ----------------------------------------------------------------------------------------------------------------------*/

void
MainMenu2::setNexMusic(Mix_Chunk *nexMusic_)
{
  this->nexMusic_ = nexMusic_;
}
/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION: 		    getMusic
 --
 --       DATE:                      April 15, 2009
 --
 --       DESIGNER:                  Alin Albu
 --
 --       PROGRAMMER: 		    Alin Albu
 --
 --       INTERFACE:             Mix_Chunk * MainMenu2::getMusic() const
 --
 --	 	  RETURNS:				a pointer to the opened main music
 ----------------------------------------------------------------------------------------------------------------------*/

Mix_Music *
MainMenu2::getMusic() const
{
  return music_;
}
/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION: 		    setMusic
 --
 --       DATE:                      April 15, 2009
 --
 --       DESIGNER:                  Alin Albu
 --
 --       PROGRAMMER: 		    Alin Albu
 --
 --       INTERFACE:             MainMenu2::setMusic(Mix_Chunk *nexMusic_)
 --
 --	 	  RETURNS:				void

		  Description:
		  Set a new pointer to the music that shall be played when menu is created.

 ----------------------------------------------------------------------------------------------------------------------*/

void
MainMenu2::setMusic(Mix_Music *music_)
{
  this->music_ = music_;
}

