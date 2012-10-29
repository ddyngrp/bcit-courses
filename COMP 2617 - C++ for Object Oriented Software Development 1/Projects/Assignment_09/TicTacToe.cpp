// Assignment 9: TicTacToe.cpp
// Author: Steffen L. Norgren
// Date: April 4, 2007

#include <iostream>
using namespace std; // using the entire std namespace

#include <iomanip>

#include "TicTacToe.h" // include definiton of class TicTacToe

TicTacToe::TicTacToe()
{
	// Initialize board to all zeros
	for ( int i = 0; i < 3; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			board[ i ][ j ] = 0;
		} // end inner for loop
	} // end outer for loop
}

void TicTacToe::makeMove()
{	
	int move = 1;
	
	printBoard();
	
	while ( xoMove( move ) == false )
	{
		move++;
	} // end while loop
}

bool TicTacToe::validMove( int row, int column )
{
	bool isValid;
	
	if ( board[ row - 1 ][ column - 1 ] == 0 )
		isValid = true;
	else
		isValid = false;
		
	return isValid;
}

bool TicTacToe::xoMove( int move )
{
	bool isOver = false;
	int row;
	int column;

	cout << "Player " << 2 - move % 2 << " it is your turn!\n";
	cout << "Choose a row for your move: ";
	cin >> row;
	cout << "Choose a column for your move: ";
	cin >> column;
	
	while ( validMove( row, column ) == false )
	{
		cout << "I am sorry, but that is an invalid move." <<
			" Please try again.\n";
		cout << "Choose a row for your move: ";
		cin >> row;
		cout << "Choose a column for your move: ";
		cin >> column;
	}
	
	board[ row - 1 ][ column - 1 ] = 2 - move % 2;

	printBoard();

	if ( gameStatus() == WIN || gameStatus() == DRAW )
	{
		if ( gameStatus() == WIN )
			cout << "\nPlayer " << 2 - move % 2 << " has won!\n";
		else
			cout << "The game is a draw!\n";
		isOver = true;
	}

	return isOver;
}

TicTacToe::Status TicTacToe::gameStatus()
{
	int gameStat = CONTINUE;
	int filledSpots = 0;
	
	// Checking if player 1 has won
	if ( board[ 0 ][ 0 ] == 1 && board[ 0 ][ 1 ] == 1 && board[ 0 ][ 2 ] == 1 )
		gameStat = WIN;
	if ( board[ 1 ][ 0 ] == 1 && board[ 1 ][ 1 ] == 1 && board[ 1 ][ 2 ] == 1 )
		gameStat = WIN;
	if ( board[ 2 ][ 0 ] == 1 && board[ 2 ][ 1 ] == 1 && board[ 2 ][ 2 ] == 1 )
		gameStat = WIN;

	if ( board[ 0 ][ 0 ] == 1 && board[ 1 ][ 0 ] == 1 && board[ 2 ][ 0 ] == 1 )
		gameStat = WIN;
	if ( board[ 0 ][ 1 ] == 1 && board[ 1 ][ 1 ] == 1 && board[ 2 ][ 1 ] == 1 )
		gameStat = WIN;
	if ( board[ 0 ][ 2 ] == 1 && board[ 1 ][ 2 ] == 1 && board[ 2 ][ 2 ] == 1 )
		gameStat = WIN;

	if ( board[ 0 ][ 0 ] == 1 && board[ 1 ][ 1 ] == 1 && board[ 2 ][ 2 ] == 1 )
		gameStat = WIN;
	if ( board[ 2 ][ 0 ] == 1 && board[ 1 ][ 1 ] == 1 && board[ 0 ][ 2 ] == 1 )
		gameStat = WIN;

	// Checking if player 2 has won
	if ( board[ 0 ][ 0 ] == 2 && board[ 0 ][ 1 ] == 2 && board[ 0 ][ 2 ] == 2 )
		gameStat = WIN;
	if ( board[ 1 ][ 0 ] == 2 && board[ 1 ][ 1 ] == 2 && board[ 1 ][ 2 ] == 2 )
		gameStat = WIN;
	if ( board[ 2 ][ 0 ] == 2 && board[ 2 ][ 1 ] == 2 && board[ 2 ][ 2 ] == 2 )
		gameStat = WIN;

	if ( board[ 0 ][ 0 ] == 2 && board[ 1 ][ 0 ] == 2 && board[ 2 ][ 0 ] == 2 )
		gameStat = WIN;
	if ( board[ 0 ][ 1 ] == 2 && board[ 1 ][ 1 ] == 2 && board[ 2 ][ 1 ] == 2 )
		gameStat = WIN;
	if ( board[ 0 ][ 2 ] == 2 && board[ 1 ][ 2 ] == 2 && board[ 2 ][ 2 ] == 2 )
		gameStat = WIN;

	if ( board[ 0 ][ 0 ] == 2 && board[ 1 ][ 1 ] == 2 && board[ 2 ][ 2 ] == 2 )
		gameStat = WIN;
	if ( board[ 2 ][ 0 ] == 2 && board[ 1 ][ 1 ] == 2 && board[ 0 ][ 2 ] == 2 )
		gameStat = WIN;
		
	// Checking if the game is a draw
	if ( gameStat != WIN )
	{
		for ( int i = 0; i < 3; i++ )
		{
			for ( int j = 0; j < 3; j++ )
			{
				if ( board[ i ][ j ] != 0 )
				{
					filledSpots++;
				} // end inner if
			} // end inner for loop
		} // end outer for loop
		if ( filledSpots == 9 )
			gameStat = DRAW;
	} // end outer if
	
	return Status( gameStat );
}

// I had no access to a PC, as such I am guessing
// as to what the proper output should be.
void TicTacToe::printBoard()
{
	cout << '\n';
	for ( int i = 0; i < 3; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			if ( j == 1 || j == 2 )
				cout << "  |";
				
			if ( board[ i ][ j ] == 0 )
				cout << setw( 3 ) << " ";
			else
				cout << setw( 3 ) << board[ i ][ j ];
		} // end inner for loop
		if ( i < 2 )
			cout << "\n-----------------\n";
	} // end outer for loop
	cout << '\n';
}