// Assignment 6 Solution: TurtleGraphics.h
// Declaration of class TurtleGraphics.
// Member functions are defined in TurtleGraphics.cpp.
// Author: Bob Langelaan 
// Date: March 6th, 2006
#pragma once

class TurtleGraphics
{
private:
	const static int NROWS = 22;  // number of rows in floor
	const static int NCOLS = 70;  // number of colums in floor
	short floor [NROWS][NCOLS]; // floor on which turtle will draw

	const static int STARTING_ROW = 0;    // row that turtle will start in
	const static int STARTING_COL = 0;    // column that turtle will start in

	const static int STARTING_DIRECTION = 6; // direction that turtle 
	                      // will be facing at the start
                          // 6 as in 6 o'clock on an analog clock
                          // The other 3 possible values are 3,9 and 12 o'clock

	const static int STARTING_PEN_POSITION = 0; // Pen will be up when 
	                            // program starts
                                // 0 means pen up, 1 means pen down
public:
	TurtleGraphics(void); //ctor will init. floor to all zeros
	void processTurtleMoves( const int commands[]);  // will process
	                   // the commands contained in array "commands"
	void displayFloor();  // will display floor on the screen
};
