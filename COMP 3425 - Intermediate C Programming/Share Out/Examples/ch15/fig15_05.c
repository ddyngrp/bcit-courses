/* Fig. 15.5: fig15_05.c
   Creating the bouncing ball. */
#include <allegro.h>

/* symbolic constants for the ball’s possible directions */
#define DOWN_RIGHT 0
#define UP_RIGHT 1
#define DOWN_LEFT 2
#define UP_LEFT 3

/* function prototypes */
void moveBall( void );
void reverseVerticalDirection( void );
void reverseHorizontalDirection( void );

int ball_x; /* the ball’s x-coordinate */
int ball_y; /* the ball’s y-coordinate */
int direction; /* the ball’s direction */
BITMAP *ball; /* pointer to the ball's image bitmap */

int main( void )
{
   /* first, set up Allegro and the graphics mode */
   allegro_init(); /* initialize Allegro */
   install_keyboard(); /* install the keyboard for Allegro to use */
   set_color_depth( 16 ); /* set the color depth to 16-bit */
   set_gfx_mode( GFX_AUTODETECT, 640, 480, 0, 0 ); /* set graphics mode */
   ball = load_bitmap( "ball.bmp", NULL ); /* load the ball bitmap */
   ball_x = SCREEN_W / 2; /* give the ball its initial x-coordinate */
   ball_y = SCREEN_H / 2; /* give the ball its initial y-coordinate */
   srand( time( NULL ) ); /* seed the random function */
   direction = rand() % 4; /* and then make a random initial direction */
   
   while( !key[KEY_ESC] )/* until the escape key is pressed ... */
   {
      moveBall(); /* move the ball */
      clear_to_color( screen, makecol( 255, 255, 255 ) ); /* clear the screen */
      /* now draw the bitmap onto the screen */
      blit( ball, screen, 0, 0, ball_x, ball_y, ball->w, ball->h );
   } /* end while */
   
   destroy_bitmap( ball ); /* destroy the ball bitmap */
   return 0;
} /* end function main */
END_OF_MAIN() /* don’t forget this! */

void moveBall() /* moves the ball */
{
   switch ( direction ) {
      case DOWN_RIGHT:
         ++ball_x; /* move the ball to the right */
         ++ball_y; /* move the ball down */
         break;
      case UP_RIGHT:
         ++ball_x; /* move the ball to the right */
         --ball_y; /* move the ball up */
         break;
      case DOWN_LEFT:
         --ball_x; /* move the ball to the left */
         ++ball_y; /* move the ball down */
         break;
      case UP_LEFT:
         --ball_x; /* move the ball to the left */
         --ball_y; /* move the ball up */
         break;
   } /* end switch */

   /* make sure the ball doesn’t go off the screen */

   /* if the ball is going off the top or bottom... */
   if ( ball_y <= 30 || ball_y >= 440 )
      reverseVerticalDirection(); /* make it go the other way */

   /* if the ball is going off the left or right... */
   if ( ball_x <= 0 || ball_x >= 600 )
      reverseHorizontalDirection(); /* make it go the other way */
} /* end function moveBall */

void reverseVerticalDirection() /* reverse the ball’s up-down direction */
{
   if ( ( direction % 2 ) == 0 ) /* "down" directions are even numbers */
      ++direction; /* make the ball start moving up */
   else /* "up" directions are odd numbers */
      --direction; /* make the ball start moving down */
} /* end function reverseVerticalDirection */                            

void reverseHorizontalDirection() /* reverses the horizontal direction */
{
    direction = ( direction + 2 ) % 4; /* reverse horizontal direction */
} /* end function reverseHorizontalDirection */
