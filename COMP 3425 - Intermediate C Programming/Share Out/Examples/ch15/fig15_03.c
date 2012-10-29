/* Fig. 15.3: fig15_03.c
   Displaying a bitmap on the screen. */
#include <allegro.h>

int main( void )
{
    BITMAP *bmp; /* pointer to the bitmap */
    
    allegro_init(); /* initialize Allegro */
    install_keyboard(); /* allow Allegro to recieve keyboard input */
    set_color_depth( 16 ); /* set the color depth to 16-bit */
    set_gfx_mode( GFX_AUTODETECT, 640, 480, 0, 0 ); /* set graphics mode */
    bmp = load_bitmap( "picture.bmp", NULL ); /* load the bitmap file */
    blit( bmp, screen, 0, 0, 0, 0, bmp->w, bmp->h ); /* draw the bitmap */
    readkey(); /* wait for a keypress */
    destroy_bitmap( bmp ); /* free the memory allocated to bmp */
    return 0;
} /* end function main */
END_OF_MAIN() /* Allegro-specific macro */
