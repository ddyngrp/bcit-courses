/*
 * Assignment 5: Assign05.h
 * Author: Steffen L. Norgren
 * Student ID: A00683006
 * Date: March 24, 2008
 */

#include <allegro.h>
#include "Assign05.h"

/* symbolic constants for the ball's possible directions */
#define DOWN_RIGHT 0
#define UP_RIGHT 1
#define DOWN_LEFT 2
#define UP_LEFT 3

/* default ball & keyboard speed */
#define BALL_SPEED 5
#define KEYBOARD_SPEED 10

/* default number of bounces before a rally is determined */
#define RALLY_BOUNCES 10

/* default lead before player's paddle is handicapped */
#define POINT_LEAD 5

/* function prototypes */
void moveBall( void );
void respondToKeyboard_Left( void );
void respondToKeyboard_Right( void );
void reverseVerticalDirection( void );
void reverseHorizontalDirection( void );
void determineRally(int reset);
void playerHandicap();
void pauseGame();
void resumeGame();

volatile int ball_x; /* the ball's x-coordinate */
volatile int ball_y; /* the ball's y-coordinate */
volatile int barL_y; /* y-coordinate of the left paddle */
volatile int barR_y; /* y-coordinate of the right paddle */
volatile int scoreL; /* score of the left player */
volatile int scoreR; /* score of the right player */
volatile int direction; /* the ball's direction */
volatile float ballSpeed; /* the ball's speed in milliseconds */
volatile int rallyBounces; /* how many times the ball is hit without scoring */
volatile float keyboard_left, keyboard_right; /* how fast each player's paddles will move */
volatile int paused; /* whether the game is paused */
BITMAP *buffer; /* pointer to the buffer */
DATAFILE *pongData; /* pointer to the datafile */

int main( void ) {
	/* set the ball & keyboard speed variable */
	ballSpeed = BALL_SPEED;
	keyboard_left = KEYBOARD_SPEED;
	keyboard_right = KEYBOARD_SPEED;
	
	paused = 0; /* the game doesn't start paused */
	
	/* first, set up Allegro and the graphics mode */
	allegro_init(); /* initialize Allegro */
	install_keyboard(); /* install the keyboard for Allegro to use */
	install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT, NULL );
	install_timer(); /* install the timer handler */
	set_color_depth( 16 ); /* set the color depth to 16-bit */
	set_gfx_mode( GFX_AUTODETECT, 640, 480, 0, 0 ); /* set graphics mode */
	buffer = create_bitmap(SCREEN_W, SCREEN_H);/* create buffer */
	pongData = load_datafile( "pongdatafile.dat" ); /* load the datafile */
	ball_x = SCREEN_W / 2; /* give ball its initial x-coordinate */
	ball_y = SCREEN_H / 2; /* give ball its initial y-coordinate */
	barL_y = SCREEN_H / 2; /* give left paddle its initial y-coordinate */
	barR_y = SCREEN_H / 2; /* give right paddle its initial y-coordinate */
	scoreL = 0; /* set left player's score to 0 */
	scoreR = 0; /* set right player's score to 0 */
	srand( time( NULL ) ); /* seed the random function ... */
	direction = rand() % 4; /* and then make a random initial direction */
	/* add timer that calls moveBall every 5 milliseconds */
	install_int( moveBall, BALL_SPEED );
	/* add timer that calls respondToKeyboard_Left every 10 milliseconds */
	install_int( respondToKeyboard_Left, KEYBOARD_SPEED );
	/* add timer that calls respondToKeyboard_Right every 10 milliseconds */
	install_int( respondToKeyboard_Right, KEYBOARD_SPEED );
	
	while(!key[KEY_ESC]) { /* until the escape key is pressed ... */
		if(key[KEY_P]) /* pause the game */
			pauseGame();
		
		while(paused && !key[KEY_ESC]) {
			if(key[KEY_R]) /* resume the game */
				resumeGame();
		}
		
		/* now, perform double buffering */
		clear_to_color( buffer, makecol( 255, 255, 255 ) );
		blit( pongData[BALL].dat, buffer, 0, 0, ball_x, ball_y, 40, 40 );
		blit( pongData[BAR].dat, buffer, 0, 0, 0, barL_y, 20, 100 ); 
		blit( pongData[BAR].dat, buffer, 0, 0, 620, barR_y, 20, 100 );
		line( buffer, 0, 30, 640, 30, makecol( 0, 0, 0 ) );
		/* draw text onto the buffer */
		textprintf_ex( buffer, pongData[PONGFONT].dat, 75, 0, makecol( 0, 0, 0 ),
					  -1, "Left Player Score: %d", scoreL );
		textprintf_ex( buffer, pongData[PONGFONT].dat, 400, 0, makecol( 0, 0, 0 ),
					  -1, "Right Player Score: %d", scoreR ); 
		blit( buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h ); 
		clear_bitmap( buffer );
	} /* end while */
	
	remove_int( moveBall ); /* remove moveBall timer */
	remove_int( respondToKeyboard_Left ); /* remove respondToKeyboard_Left timer */
	remove_int( respondToKeyboard_Right ); /* remove respondToKeyboard_Right timer */
	destroy_bitmap( buffer ); /* destroy the buffer bitmap */
	unload_datafile( pongData ); /* unload the datafile */
	return 0;
} /* end function main */
END_OF_MAIN() /* don't forget this! */

void moveBall() { /* moves the ball */
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
	if ( ball_y <= 30 || ball_y >= 440 ) {
		reverseVerticalDirection(); /* make it go the other way */
	}
	
	/* if the ball is in range of the left paddle ... */
	if (ball_x < 20 && (direction == DOWN_LEFT || direction == UP_LEFT)) {
		/* is the left paddle in the way? */
		if ( ball_y > ( barL_y - 39 ) && ball_y < ( barL_y + 99 ) ) {
			reverseHorizontalDirection();
			determineRally(0);
		}
		else if ( ball_x <= -20 ) { /* if the ball goes off the screen */ 
			++scoreR; /* give right player a point */
			playerHandicap(); /* handicap player if lead exceeds POINT_LEAD */
			determineRally(1); /* reset the bounce count */
			ball_x = SCREEN_W / 2; /* place the ball in the ... */ 
			ball_y = SCREEN_H / 2; /* ... center of the screen */ 
			direction = rand() % 4; /* give the ball a random direction */ 
		} /* end else */ 
	} /* end if */ 
	
	/* if the ball is in range of the right paddle ... */ 
	if (ball_x > 580 && (direction == DOWN_RIGHT || direction == UP_RIGHT)) {
		/* is the right paddle in the way? */ 
		if ( ball_y > ( barR_y - 39 ) && ball_y < ( barR_y + 99 ) ) {
			reverseHorizontalDirection();
			determineRally(0);
		}
		else if ( ball_x >= 620 ) { /* if the ball goes off the screen */ 
			++scoreL; /* give left player a point */
			playerHandicap(); /* handicap player if lead exceeds POINT_LEAD */
			determineRally(1); /* reset the bounce count */
			ball_x = SCREEN_W / 2; /* place the ball in the ... */ 
			ball_y = SCREEN_H / 2; /* ... center of the screen */ 
			direction = rand() % 4; /* give the ball a random direction */ 
		} /* end else */ 
	} /* end if */ 
} /* end function moveBall */

void respondToKeyboard_Left() { /* responds to keyboard input for left player */ 
	if ( key[KEY_A] ) /* if A is being pressed... */ 
		barL_y -= 3; /* ... move the left paddle up */ 
	if ( key[KEY_Z] ) /* if Z is being pressed... */ 
		barL_y += 3; /* ... move the left paddle down */ 
	
	/* make sure the paddles don't go offscreen */ 
	if ( barL_y < 30 ) /* if left paddle is going off the top */ 
		barL_y = 30; 
	else if ( barL_y > 380 ) /* if left paddle is going off the bottom */ 
		barL_y = 380; 
}

void respondToKeyboard_Right() { /* responds to keyboard input for right player*/ 
	if ( key[KEY_UP] ) /* if the up arrow key is being pressed... */ 
		barR_y -= 3; /* ... move the right paddle up */ 
	if ( key[KEY_DOWN] ) /* if the down arrow key is being pressed... */ 
		barR_y += 3; /* ... move the right paddle down */ 
	
	/* make sure the paddles don't go offscreen */ 
	if ( barR_y < 30 ) /* if right paddle is going off the top */ 
		barR_y = 30; 
	else if ( barR_y > 380 ) /* if right paddle is going off the bottom */ 
		barR_y = 380; 
}

void reverseVerticalDirection() { /* reverse the ball's up-down direction */
	if ( ( direction % 2 ) == 0 ) /* "down" directions are even numbers */
		++direction; /* make the ball start moving up */
	else /* "up" directions are odd numbers */
		--direction; /* make the ball start moving down */
	play_sample( pongData[BOING].dat, 255, 128, 1000, 0 ); /* play sound */
} /* end function reverseVerticalDirection */

void reverseHorizontalDirection() { /* reverses the horizontal direction */
	direction = ( direction + 2 ) % 4; /* reverse horizontal direction */
	play_sample( pongData[BOING].dat, 255, 128, 1000, 0 ); /* play sound */
} /* end function reverseHorizontalDirection */

/* Handicap a player if their point lead becomes too great */
void playerHandicap() {
	int scoreDifference = scoreL - scoreR;
	
	/* Determine whether a lead of POINT_LEAD exists */
	if(scoreDifference >= POINT_LEAD && scoreDifference % POINT_LEAD == 0) {
		keyboard_left *= 1.2; /* paddle moves 20% slower */
		remove_int(respondToKeyboard_Left);
		install_int(respondToKeyboard_Left, keyboard_left);
	}
	else if(scoreDifference <= (POINT_LEAD * -1) && scoreDifference % POINT_LEAD == 0) {
		keyboard_right *= 1.2; /* paddle moves 20% slower */
		remove_int(respondToKeyboard_Right);
		install_int(respondToKeyboard_Right, keyboard_right);
	}
	/* no 5 point lead exists */
	else if(scoreDifference >= POINT_LEAD && scoreDifference <= (POINT_LEAD * -1)) {
		if(keyboard_left != KEYBOARD_SPEED) { /* don't change timers unless needed */
			keyboard_left = KEYBOARD_SPEED;
			remove_int(respondToKeyboard_Left);
			install_int(respondToKeyboard_Left, KEYBOARD_SPEED);
		}
		
		if(keyboard_right != KEYBOARD_SPEED) { /* don't change timers unless needed */
			keyboard_right = KEYBOARD_SPEED;
			remove_int(respondToKeyboard_Right);
			install_int(respondToKeyboard_Right, KEYBOARD_SPEED);
		}
	}
}

/* Determine if a rally exists and increase or decrease ball speed */
void determineRally(int reset) {
	if(reset == 0) {
		rallyBounces++; /* increment the bounce counter */		
		/* increase ball speed by 20% every RALLY_BOUNCES */
		if(rallyBounces % RALLY_BOUNCES == 0 && rallyBounces != 0) {
			ballSpeed *= 0.8;
			remove_int(moveBall); /* remove the timer before creating a new one */
			install_int(moveBall, ballSpeed);
		}
	}
	else {
		rallyBounces = 0; /* reset the bounce counter */
		ballSpeed = BALL_SPEED;
		remove_int(moveBall); /* remove the timer before creating a new one */
		install_int(moveBall, BALL_SPEED);
	}
}

/* Pause the game */
void pauseGame() {
	paused = 1;
	/* remove timers */
	remove_int(moveBall);
	remove_int(respondToKeyboard_Left);
	remove_int(respondToKeyboard_Right);
	textout_centre_ex(screen, font, "PAUSED", SCREEN_W / 2, SCREEN_H / 2, makecol(0, 0, 0), -1);
}

/* Resume the game */
void resumeGame() {
	paused = 0;
	/* reinstall timers with previous settings */
	install_int( moveBall, ballSpeed );
	install_int( respondToKeyboard_Left, keyboard_left );
	install_int( respondToKeyboard_Right, keyboard_right );
}