/* Fig. 15.14: fig15_14.c
   Adding timers to the Pong game. */
#include <allegro.h>

/* symbolic constants for the ball’s possible directions */
#define DOWN_RIGHT 0
#define UP_RIGHT 1
#define DOWN_LEFT 2
#define UP_LEFT 3

/* function prototypes */
void moveBall( void );
void respondToKeyboard( void );
void reverseVerticalDirection( void );
void reverseHorizontalDirection( void );

volatile int ball_x; /* the ball’s x-coordinate */
volatile int ball_y; /* the ball’s y-coordinate */
volatile int barL_y; /* y-coordinate of the left paddle */
volatile int barR_y; /* y-coordinate of the right paddle */
volatile int scoreL; /* score of the left player */
volatile int scoreR; /* score of the right player */
volatile int direction; /* the ball’s direction */
BITMAP *ball; /* pointer to ball’s image bitmap */
BITMAP *bar; /* pointer to paddle’s image bitmap */
BITMAP *buffer; /* pointer to the buffer */
SAMPLE *boing; /* pointer to sound file */
FONT *pongFont; /* pointer to font file */

int main( void )
{
   int depth;   /* represents color depth */

   /* first, set up Allegro and the graphics mode */
   allegro_init(); /* initialize Allegro */
   install_keyboard(); /* install the keyboard for Allegro to use */
   install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT, NULL );
   install_timer(); /* install the timer handler */
   
   depth = desktop_color_depth();  /* find out what color depth is on our computer */
   if (depth == 0)
	   depth = 32;
   set_color_depth( depth ); /* set the color depth to depth used by our computer */

   set_gfx_mode( GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0 ); /* set graphics mode */
   ball = load_bitmap( "ball.bmp", NULL ); /* load the ball bitmap */
   bar = load_bitmap( "bar.bmp", NULL); /* load the bar bitmap */
   buffer = create_bitmap(SCREEN_W, SCREEN_H);/* create buffer */
   boing = load_sample( "boing.wav" ); /* load the sound file */
   pongFont = load_font( "pongfont.pcx", NULL, NULL ); /* load the font */
   ball_x = SCREEN_W / 2; /* give ball its initial x-coordinate */
   ball_y = SCREEN_H / 2; /* give ball its initial y-coordinate */
   barL_y = SCREEN_H / 2; /* give left paddle its initial y-coordinate */
   barR_y = SCREEN_H / 2; /* give right paddle its initial y-coordinate */
   scoreL = 0; /* set left player’s score to 0 */
   scoreR = 0; /* set right player’s score to 0 */
   srand( time( NULL ) ); /* seed the random function ... */
   direction = rand() % 4; /* and then make a random initial direction */
   /* add timer that calls moveBall every 5 milliseconds */
   install_int( moveBall, 5 );
   /* add timer that calls respondToKeyboard every 10 milliseconds */
   install_int( respondToKeyboard, 10 );

   while ( !key[KEY_ESC] )/* until the escape key is pressed ... */
   {
      /* now, perform double buffering */
      clear_to_color( buffer, makecol( 255, 255, 255 ) );
      blit( ball, buffer, 0, 0, ball_x, ball_y, ball->w, ball->h );
      blit( bar, buffer, 0, 0, 0, barL_y, bar->w, bar->h );  
      blit( bar, buffer, 0, 0, 620, barR_y, bar->w, bar->h );
      line( buffer, 0, 30, 640, 30, makecol( 0, 0, 0 ) );
      /* draw text onto the buffer */
      textprintf_ex( buffer, pongFont, 75, 0, makecol( 0, 0, 0 ),
                     -1, "Left Player Score: %d", scoreL );             
      textprintf_ex( buffer, pongFont, 400, 0, makecol( 0, 0, 0 ),
                     -1, "Right Player Score: %d", scoreR );            
      blit( buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h );    
      clear_bitmap( buffer );                                      
   } /* end while */
   
   remove_int( moveBall ); /* remove moveBall timer */
   remove_int( respondToKeyboard ); /* remove respondToKeyboard timer */
   destroy_bitmap( ball ); /* destroy the ball bitmap */
   destroy_bitmap( bar ); /* destroy the bar bitmap */
   destroy_bitmap( buffer ); /* destroy the buffer bitmap */
   destroy_sample( boing ); /* destroy the boing sound file */
   destroy_font( pongFont ); /* destroy the font */
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

   /* if the ball is going off the top or bottom ... */
   if ( ball_y <= 30 || ball_y >= 440 ) 
      reverseVerticalDirection(); /* make it go the other way */

   /* if the ball is in range of the left paddle ... */                   
   if (ball_x < 20 && (direction == DOWN_LEFT || direction == UP_LEFT))   
   {                                                                      
      /* is the left paddle in the way? */                                
      if ( ball_y > ( barL_y - 39 ) && ball_y < ( barL_y + 99 ) )         
         reverseHorizontalDirection();                                    
      else if ( ball_x <= -20 ) { /* if the ball goes off the screen */   
         ++scoreR; /* give right player a point */                        
         ball_x = SCREEN_W / 2; /* place the ball in the ... */           
         ball_y = SCREEN_H / 2; /* ... center of the screen  */           
         direction = rand() % 4; /* give the ball a random direction */   
      } /* end else */                                                    
   } /* end if */                                                         
                                                                          
   /* if the ball is in range of the right paddle ... */                  
   if (ball_x > 580 && (direction == DOWN_RIGHT || direction == UP_RIGHT))
   {                                                                      
      /* is the right paddle in the way? */                               
      if ( ball_y > ( barR_y - 39 ) && ball_y < ( barR_y + 99 ) )         
         reverseHorizontalDirection();                                    
      else if ( ball_x >= 620 ) { /* if the ball goes off the screen */   
         ++scoreL; /* give left player a point */                         
         ball_x = SCREEN_W / 2; /* place the ball in the ... */           
         ball_y = SCREEN_H / 2; /* ... center of the screen  */           
         direction = rand() % 4; /* give the ball a random direction */   
      } /* end else */                                                    
   } /* end if */                                                         
} /* end function moveBall */

void respondToKeyboard() /* responds to keyboard input */                  
{                                                                          
   if ( key[KEY_A] ) /* if A is being pressed... */                        
      barL_y -= 3; /* ... move the left paddle up */                       
   if ( key[KEY_Z] ) /* if Z is being pressed... */                        
      barL_y += 3; /* ... move the left paddle down */                     
                                                                           
   if ( key[KEY_UP] ) /* if the up arrow key is being pressed... */        
      barR_y -= 3; /* ... move the right paddle up */                      
   if ( key[KEY_DOWN] ) /* if the down arrow key is being pressed... */    
      barR_y += 3; /* ... move the right paddle down */                    
                                                                           
   /* make sure the paddles don’t go offscreen */                          
   if ( barL_y < 30 ) /* if left paddle is going off the top */            
      barL_y = 30;                                                         
   else if ( barL_y > 380 ) /* if left paddle is going off the bottom */   
      barL_y = 380;                                                        
   if ( barR_y < 30 ) /* if right paddle is going off the top */           
      barR_y = 30;                                                         
   else if ( barR_y > 380 ) /* if right paddle is going off the bottom */  
      barR_y = 380;                                                        
} /* end function respondToKeyboard */                                 

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
