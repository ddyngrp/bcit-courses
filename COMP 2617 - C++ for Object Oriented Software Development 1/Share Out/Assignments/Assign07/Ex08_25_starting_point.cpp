// Exercise 8.25 Solution: Ex08_25.cpp
// This solution assumes that there is only one
// entrance and one exit for a given maze, and
// these are the only two zeroes on the borders.
#include <iostream> 
using std::cin; 
using std::cout;  

enum Direction { DOWN, RIGHT, UP, LEFT };

// function prototypes
void mazeTraversal( char [][ 12 ], const int, const int, int, int, int );
void printMaze( const char[][ 12 ] );
bool validMove( const char [][ 12 ], int, int );
bool coordsAreEdge( int, int );

int main()
{
   char maze[ 12 ][ 12 ] =
      { {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
      {'#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#'},
      {'.', '.', '#', '.', '#', '.', '#', '#', '#', '#', '.', '#'},
      {'#', '#', '#', '.', '#', '.', '.', '.', '.', '#', '.', '#'},
      {'#', '.', '.', '.', '.', '#', '#', '#', '.', '#', '.', '.'},
      {'#', '#', '#', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
      {'#', '.', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
      {'#', '#', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
      {'#', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '#'},
      {'#', '#', '#', '#', '#', '#', '.', '#', '#', '#', '.', '#'},
      {'#', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#'},
      {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'} };

   int xStart = 2; // starting X and Y coordinates for maze
   int yStart = 0;
   int x = xStart; // current X and Y coordinates
   int y = yStart;

   mazeTraversal( maze, xStart, yStart, x, y, RIGHT );
   return 0;
} // end main
