#include "../headers/OkCancel.h"

/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION: 		    OkCancel Constructor
 --
 --       DATE:                      April 15, 2009
 --
 --       DESIGNER:                  Alin Albu
 --
 --       PROGRAMMER: 		    Alin Albu
 --
 --       INTERFACE:                 OkCancel::OkCancel(std::string fileNames[], std::string mfilename, SDL_Surface* screen)
 --
 --       NOTES:
 --       Creates an OkCancel menu, loading the background images and song
 ----------------------------------------------------------------------------------------------------------------------*/
OkCancel::OkCancel(std::string fileNames[], std::string mfilename,
    SDL_Surface* screen)
{
  printf("Creating Ok_Cancel menu!\n");
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
  this->setMusic(Mix_LoadWAV( mfilename.c_str() ));
  printf("Done Ok_Cancel menu1\n");

}

/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION: 		    OkCancel Destructor
 --
 --       DATE:                      April 15, 2009
 --
 --       DESIGNER:                  Alin Albu
 --
 --       PROGRAMMER: 		    Alin Albu
 --
 --       INTERFACE:                 OkCancel::~OkCancel()
 --
 --       NOTES:
 --       Frees the background images and song
 ----------------------------------------------------------------------------------------------------------------------*/
OkCancel::~OkCancel()
{
  for (int i = 0; i < num_options_; i++)
    {
      SDL_FreeSurface(backgrounds_[i]);
    }
  Mix_FreeChunk(music_);
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
 --       INTERFACE:                 bool OkCancel::showLoaded()
 --
 --	 RETURNS:		    bool
 --
 --       NOTES:
 --       Blits the menu and flips the screen
 ----------------------------------------------------------------------------------------------------------------------*/
bool
OkCancel::showLoaded()
{
  printf("Showing loaded Ok_Cancel\n");
  SDL_Rect offset;
  offset.x = 40;
  offset.y = 250;
  int i = SDL_BlitSurface(backgrounds_[loaded_], 0, screen_, &offset);
  if (i == 0)
    return (SDL_Flip(screen_) != -1);
  else
    return false;
}
/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION: 		    move
 --
 --       DATE:                      April 15, 2009
 --
 --       DESIGNER:                  Alin Albu
 --
 --       PROGRAMMER: 		    Alin Albu
 --
 --       INTERFACE:                 bool OkCancel::move(int xstep, int ystep)
 --
 --	 	RETURNS:		    bool
 --
 --       NOTES:
 --       Allows us to be able to move the menu on the screen.
 ----------------------------------------------------------------------------------------------------------------------*/

bool
OkCancel::move(int xstep, int ystep)
{
  printf("Movin Ok_Cancel Menu\n");
  SDL_Rect offset;
  offset.x = 40;
  offset.y = ystep > 250 ? 250 : ystep;
  int i = SDL_BlitSurface(backgrounds_[loaded_], 0, screen_, &offset);
  return i == 0;
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
 --       INTERFACE:                 int OkCancel::start(SDL_Event event)
 --
 --	 RETURNS:		    int
 --
 --       NOTES:
 --       This function waits for events such as keyboard or mouse input.  The mouse input checks where the mouse click
 --	 is on the screen to check if the user clicked an item.  The keyboard input switches between the menu items.
 ----------------------------------------------------------------------------------------------------------------------*/
int
OkCancel::start(SDL_Event event)
{
  printf("Starting Ok_Cancel Menu!\n");
  loaded_ = 0;
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
          case SDLK_RIGHT:
            if (loaded_ == num_options_ - 1)
              {
                break;
              }
            else
              {
                loaded_ = num_options_ - 1;
                Mix_PlayChannel(-1, music_, 0 );
              }
            if (!this->showLoaded())
              return 0;
            break;

          case SDLK_DOWN:
          case SDLK_LEFT:
            if (loaded_ == num_options_ - 2)
              {
                break;
              }
            else
              {
                loaded_ = num_options_ - 2;
                Mix_PlayChannel(-1, music_, 0 );
              }
            if (!this->showLoaded())
              return 0;
            break;
          case SDLK_ESCAPE:
            return 2;
          case SDLK_RETURN:
          case SDLK_SPACE:
            {
              if (loaded_ != 0)
                return loaded_;
              break;
            }
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
          if ((event.motion.x > 90) && (event.motion.x < 140)
              && (event.motion.y > 470) && (event.motion.y < 510))
            {
              if (loaded_ == num_options_ - 2)
                continue;

              loaded_ = num_options_ - 2;
              Mix_PlayChannel(-1, music_, 0);
              if (!this->showLoaded())
                return 0;
            }
          else if ((event.motion.x > 400) && (event.motion.x < 550)
              && (event.motion.y > 470) && (event.motion.y < 510))
            {
              if (loaded_ == num_options_ - 1)
                continue;

              loaded_ = num_options_ - 1;
              Mix_PlayChannel(-1, music_, 0);
              if (!this->showLoaded())
                return 0;
            }
          else
            {
              if (loaded_ == 0)
                continue;

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
OkCancel::getNum_options() const
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
OkCancel::getFileNames(int index) const
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
OkCancel::setFileNames(std::string fileName, int index)
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
OkCancel::getBackground(int index) const
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
OkCancel::setBackground(SDL_Surface *background, int index)
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
OkCancel::loadBackground(std::string filename, int index)
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
OkCancel::getScreen() const
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
OkCancel::setScreen(SDL_Surface *screen_)
{
  this->screen_ = screen_;
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

Mix_Chunk *
OkCancel::getMusic() const
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
OkCancel::setMusic(Mix_Chunk *music_)
{
  this->music_ = music_;
}

