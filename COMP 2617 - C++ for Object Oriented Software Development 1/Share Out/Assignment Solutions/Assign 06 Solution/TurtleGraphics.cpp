// Assignment 7 Solution: TurtleGraphics.cpp
// Member-function definitions for class TurtleGraphics.
// Author: Bob Langelaan 
// Date: March 6th, 2006

#include ".\turtlegraphics.h"

// include and using statments

#include <iostream>
using std::cout;
using std::endl;

// init. floor to all zeros
TurtleGraphics::TurtleGraphics(void)
{
	for (int r = 0; r < NROWS; ++r){
		for (int c = 0; c < NCOLS; ++c){
			floor [r][c] = 0;
		}
	}
}

void TurtleGraphics::processTurtleMoves( const int cmds[])
{

   int dir = STARTING_DIRECTION; // used to represent current direction that the turtle is moving
                                 //   The possible values for dir are 3,6,9 and 12 o'clock

   int row = STARTING_ROW;  // used to represent current row that turtle is at
   int col = STARTING_COL;  // used to represent current column that turtle is at

   int pen = STARTING_PEN_POSITION; // starting position of pen (up or down)
                                    // 0 is up, 1 is down

   int cmdNo = 0; // The current position we are processing in the cmds[] array
               
   int ii;        // will be used in for loop as counter

   // The following while loop is the main loop of this program
   // We will stay in this loop as long as we are processing commands from the cmds[] array

   while ( cmds[cmdNo] != 9 ) { // 9 is the sentinel value indicating we are done

	   switch ( cmds[cmdNo] ) {  // main switch statment
           case 1: // Pen up
			   pen = 0;
			   break;

		   case 2: // Pen down
			   pen = 1;
			   break;

		   case 3: // Turn right
			   dir += 3; // for example, change from 3 o'clock to 6 o'clock
			   if (dir > 12)   // in case we turn right at 12 o'clock
				   dir -= 12;  
			   break;

		   case 4: // Turn left
			   dir -= 3; // for example, change from 6 o'clock to 3 o'clock
			   if (dir <= 0)    // in case we turn left at 3 o'clock
				   dir += 12; 
			   break;
		   
		   case 5: // Move forward 

			   ++cmdNo;  // point to next command in the command array
			             //   we need next value to know how any spaces to move

			   if (cmds[cmdNo] < 1) // not valid if move is less than 1
				   break;  // go process next command

			   switch (dir) { // move depends on current direction
				              //   so we use a switch statement inside our switch statement

		           case 3: // moving in direction 3 o'clock
					   
					   for ( ii = 1; ii <= cmds[cmdNo]; ++col, ++ii ){
						   if(col >= (NCOLS-1))
							   break;  //can't move further in this direction
						   if (pen)
							   floor[row][col] = 1;
					   }
					   break;

				   case 6: // moving in direction 6 o'clock
					   for ( ii = 1; ii <= cmds[cmdNo]; ++row, ++ii ){
						   if(row >= (NROWS-1))
							   break;  //can't move further in this direction
						   if (pen)
							   floor[row][col] = 1;
					   }
					   break;

				   case 9: // moving in direction 9 o'clock
					   for ( ii = 1; ii <= cmds[cmdNo]; --col, ++ii ){
						   if(col <= 0)
							   break;  //can't move further in this direction
						   if (pen)
							   floor[row][col] = 1;
					   }
					   break;

				   case 12: // moving in direction 12 o'clock
					   for ( ii = 1; ii <= cmds[cmdNo]; --row, ++ii ){
						   if(row <= 0)
							   break;  //can't move further in this direction
						   if (pen)
							   floor[row][col] = 1;
					   }
					   break;

				   default: // should never get here!!!
					   cout << "\n\nERROR - invalid direction in a inner switch statement.\n\n";
					   return; //major error, so go home

			   }
			   break; // end of case 5

		   case 6: // display the floor matrix
			   displayFloor();
			   break;

		   default: // should never get here !!!
			   cout << "\n\nERROR - invalid command encountered in outer switch statement.\n\n";
			   return;  // major error, so go home

	   } // end of outer switch statment

	   ++cmdNo;   // move to next command

   }  //  End of main while loop
}
	                   
void TurtleGraphics::displayFloor()
{
   int k;		// counter for outer loop
   int j;       // counter for inner loop
  
   for ( k = 0; k < NROWS; k++ ){

	   for (j = 0; j < NCOLS; j++){

		   if (floor [k][j] == 0) // if turtle did not draw on this cell
			   cout << ' ';       // then display a blank

		   else
			   cout << '*';       // else display a '*'
	   } // end of inner for loop

	   cout << endl; // move to next line

   } // end of outer for loop

   cout << endl << endl;  // a couple of blank lines for good measure

} // end of displayFloor()