/* Fig. 15.9: fig15_09.c
   Utilizing sound files */
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
BITMAP *ball; /* pointer to ball's image bitmap */
BITMAP *buffer; /* pointer to the buffer */
SAMPLE *boing; /* pointer to sound file */

int main( void )
{
   /* first, set up Allegro and the graphics mode */
   allegro_init(); /* initialize Allegro */
   install_keyboard(); /* install the keyboard for Allegro to use */
   install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT, NULL );
   set_color_depth( 16 ); /* set the color depth to 16-bit */
   set_gfx_mode( GFX_AUTODETECT, 640, 480, 0, 0 ); /* set graphics mode */
   ball = load_bitmap( "ball.bmp", NULL ); /* load the ball bitmap */
   buffer = create_bitmap(SCREEN_W, SCREEN_H);/* create buffer */
   boing = load_sample( "boing.wav" ); /* load the sound file */
   ball_x = SCREEN_W / 2; /* give the ball its initial x-coordinate */
   ball_y = SCREEN_H / 2; /* give the ball its initial y-coordinate */
   srand( time( NULL ) ); /* seed the random function ... */
   direction = rand() % 4; /* and then make a random initial direction */
   
   while ( !key[KEY_ESC] )/* until the escape key is pressed ... */
   {
      moveBall(); /* move the ball */
      /* now, perform double buffering */
      clear_to_color( buffer, makecol( 255, 255, 255 ) );
      blit( ball, buffer, 0, 0, ball_x, ball_y, ball->w, ball->h );
      blit( buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h );    
      clear_bitmap( buffer );                                      
   } /* end while */
   
   destroy_bitmap( ball ); /* destroy the ball bitmap */
   destroy_bitmap( buffer ); /* destroy the buffer bitmap */
   destroy_sample( boing ); /* destroy the boing sound file */
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

   /* make sure the ball doesn’t go off screen */

   /* if the ball is going off the top or bottom ... */
   if ( ball_y <= 30 || ball_y >= 440 ) 
      reverseVerticalDirection();

   /* if the ball is going off the left or right ... */
   if ( ball_x <= 0 || ball_x >= 600 )
      reverseHorizontalDirection();
} /* end function moveBall */

void reverseVerticalDirection() /* reverse the ball’s up-down direction */
{
   if ( ( direction % 2 ) == 0 ) /* "down" directions are even numbers */
      ++direction; /* make the ball start moving up */
   else /* "up" directions are odd numbers */
      --direction; /* make the ball start moving down */
   play_sample( boing, 255, 128, 1000, 0 ); /* play "boing" sound once */
} /* end function reverseVerticalDirection */

void reverseHorizontalDirection() /* reverses the horizontal direction */
{
   direction = ( direction + 2 ) % 4; /* reverse horizontal direction */
   play_sample( boing, 255, 128, 1000, 0 ); /* play "boing" sound once */
} /* end function reverseHorizontalDirection */
