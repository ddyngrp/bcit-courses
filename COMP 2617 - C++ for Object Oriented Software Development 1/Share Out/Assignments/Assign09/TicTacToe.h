// Exercise 9.15 Solution: TicTacToe.h
#ifndef TICTACTOE_H
#define TICTACTOE_H

class TicTacToe 
{
private:  
   enum Status { WIN, DRAW, CONTINUE }; // enumeration constants
           // The above line declares enum type "Status" but does
           // _NOT_ declare a data member of the class !!!
   int board[ 3 ][ 3 ];  // only data member of this class
public:
   TicTacToe(); // default constructor
   void makeMove(); // make move
   void printBoard(); // print board
   bool validMove( int, int ); // validate move
   bool xoMove( int ); // x o move 
   Status gameStatus(); // game status
}; // end class TicTacToe

#endif
