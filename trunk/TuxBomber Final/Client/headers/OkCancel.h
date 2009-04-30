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
  explicit
  OkCancel(std::string fileNames[], std::string mfilename, SDL_Surface* screen);
  virtual
  ~OkCancel();

  static const int num_options_ = 3; //number of options
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
  Mix_Chunk *
  getMusic() const;
  void
  setMusic(Mix_Chunk *music_);

private:
  int loaded_;
  std::string fileNames_[num_options_]; // background files
  SDL_Surface* backgrounds_[num_options_];//the actual loaded backgrounds
  SDL_Surface* screen_;
  Mix_Chunk *music_;

};

#endif /* OKCANCEL_H_ */
