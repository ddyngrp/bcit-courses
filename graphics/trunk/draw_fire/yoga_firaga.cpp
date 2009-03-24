#include "funcs.h"

extern SDL_Surface *screen;

bool draw_fire(fire f){
  draw_fire_center(f.center);
  draw_fire_arm_up(f.center, f.up);
  draw_fire_arm_down(f.center, f.down);
  draw_fire_arm_left(f.center, f.left);
  draw_fire_arm_right(f.center, f.right);
  return true;
}

void draw_fire_center(Point center){
  SDL_Surface *imgCenter;
 
  imgCenter 	  =  load_image("../images/fire/center.xcf");
  apply_surface((center.x*TILE), (center.y*TILE), imgCenter);
}

void draw_fire_arm_left(Point center, int left){
  SDL_Surface *imgLeftEnd;
  SDL_Surface *imgHorizontal;

  imgHorizontal =  load_image("../images/fire/horizontal.xcf");
  imgLeftEnd	  =  load_image("../images/fire/leftEnd.xcf");
  
  if(left != 0){
    apply_surface((center.x - left) * TILE, (center.y) * TILE, imgLeftEnd);
    left--;
  }
  for(int position = (center.x - left); position != center.x; position++)
    apply_surface((position * TILE), center.y * TILE, imgHorizontal);
}

void draw_fire_arm_right(Point center, int right){
  SDL_Surface *imgRightEnd;
  SDL_Surface *imgHorizontal;

  imgHorizontal =  load_image("../images/fire/horizontal.xcf");
  imgRightEnd	  =  load_image("../images/fire/rightEnd.xcf");
  	
  if(right != 0){
    apply_surface((center.x + right) * TILE, (center.y) * TILE, imgRightEnd);
    right--;
  }
  for(int position = (center.x + right); position != center.x; position--)
    apply_surface((position * TILE), center.y * TILE, imgHorizontal);
}

void draw_fire_arm_up(Point center, int up){
  SDL_Surface *imgVertical;
  SDL_Surface *imgTopEnd;

  imgVertical	  =  load_image("../images/fire/vertical.xcf");
  imgTopEnd	    =  load_image("../images/fire/topEnd.xcf");

  if(up != 0){
    apply_surface(center.x * TILE, (center.y - up) * TILE, imgTopEnd);
    up--;
  }
  for(int position = (center.y - up); position != center.y; position++)
    apply_surface(center.x * TILE, (position * TILE), imgVertical);
}

void draw_fire_arm_down(Point center, int direction){
  SDL_Surface *imgVertical;
  SDL_Surface *imgBottomEnd;

  imgVertical	  =  load_image("../images/fire/vertical.xcf");
  imgBottomEnd	=  load_image("../images/fire/bottomEnd.xcf");

  if(direction != 0){
    apply_surface(center.x * TILE, (center.y + direction) * TILE, imgBottomEnd);
    direction--;
  }
  for(int position = (center.y + direction); position != center.y; position--)
  	apply_surface(center.x * TILE, (position * TILE), imgVertical);
}

