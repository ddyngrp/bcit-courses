/*
 * MainMenu2.h
 *
 *  Created on: 25-Mar-2009
 *      Author: d3vil
 */

#ifndef MAINMENU2_H_
#define MAINMENU2_H_
#include "mainHeader.h"
/*
 *
 */
class MainMenu2
{
public:
  MainMenu2(std::string fileNames[], std::string mfilename,
      std::string smfilename, SDL_Surface* screen);
  virtual
  ~MainMenu2();

  static const int num_options_ = 5; //number of options
  int
  getNum_options() const;
  std::string
  getFileNames(int index) const;
  void
  setFileNames(std::string fileName, int index);
  SDL_Surface *
  getBackground(int index) const;
  void
  setBackground(SDL_Surface *background, int index);
  bool
  loadBackground(std::string filename, int index);
  SDL_Surface *
  getScreen() const;
  void
  setScreen(SDL_Surface *screen_);
  bool
  showLoaded();
  bool
  move(int xStep, int yStep);
  int
  start(SDL_Event event);
  int
  getLoaded() const;
  void
  setLoaded(int loaded);
  Mix_Chunk *
  getNexMusic() const;
  void
  setNexMusic(Mix_Chunk *nexMusic_);
  Mix_Music *
  getMusic() const;
  void
  setMusic(Mix_Music *music_);

private:
  int loaded_;
  std::string fileNames_[num_options_]; // background files
  SDL_Surface* backgrounds_[num_options_];//the actual loaded backgrounds
  SDL_Surface* screen_;
  Mix_Music *music_;
  Mix_Chunk *nexMusic_;

};

#endif /* MAINMENU2_H_ */
