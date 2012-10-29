/* Fig. 15.1: fig15_01.c
   A simple Allegro program. */
#include <allegro.h>

int main( void )
{
   allegro_init(); /* initialize Allegro */
   allegro_message( "Welcome to Allegro!" ); /* display a message */
   return 0;
} /* end function main */
END_OF_MAIN() /* Allegro-specific macro */
