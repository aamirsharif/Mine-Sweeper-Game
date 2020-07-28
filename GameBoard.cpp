#include "GameBoard.h"
#include<iostream>
#include<time.h>
#include<string.h>
#include<string>
using namespace std;

//Initializes a default GameBoard
GameBoard::GameBoard()
{
	rows = 10;
	columns = 10;
	bombs = 20;
	
	//Create the dynamic board of squares
	this->board = new Square*[rows];
	for (int i = 0; i < rows; i++)
		this->board[i] = new Square[columns];
	
	//Initialize Squares
	initializeSquares();

	//Place bombs in the board
	placeBombs(bombs);

	//Set neighboring bomb count and display of each square
	setBombCountAndDisplay();
}

/*
Accepts as parameter number of rows, columns and number of bombs.
Creates a custom board.
*/
GameBoard::GameBoard(int numberOfRows,int numberOfColumns,int numberOfBombs)
{
	rows = numberOfRows;
	columns = numberOfColumns;
	bombs = numberOfBombs;

	//Create the dynamic board
	board = new Square*[rows];
	for (int i = 0; i < rows; i++)
		board[i] = new Square[columns];
	//Initialize the squares
	initializeSquares();

	//Place bombs in the board
	placeBombs(bombs);

	//Set neighboring bomb count and display of each square
	setBombCountAndDisplay();
}

/*Frees the memory occupied by the board*/
GameBoard::~GameBoard()
{
	for (int i = 0; i < rows; i++)
		delete[] board[i];
}

//Returns the square at the given row and column number
Square* GameBoard::getSquare(int& row,int& column)
{
	Square* square = &board[row][column];
	return square;
}

/*Checks whether the given row and column number are valid in the board.
I.E. the row and column number are whithin board range.*/
bool GameBoard::isValidRowAndColumn(int row,int column) const
{
	return(row >= 0 && row < rows  && column >= 0 && column < columns);
}

/*
This method places bombs at random positions in the board.
We first get a random square from board and check if it has bomb or not.
If it has bomb, then the loop is skipped, else a bomb is placed in it.
*/
void GameBoard::placeBombs(int bombs)
{
	//Randomizes the seeder
	srand(time(0));		

	//Counter to keep track of number of bombs placed
	int counter = 0;

	while (counter < bombs)
	{
		//Get random row number
		int randomRow = rand() % rows;	
		//Get random column number
		int randomColumn = rand() % columns;		
		
		//Get the random square
		Square* square = getSquare(randomRow, randomColumn);

		//If bomb already placed, skip the iteration
		if (square->hasBomb())		
			continue;
		
		//Else place bomb in it and set the display as "*" character.
		square->setBomb(true);
		square->setDisplay("*");

		counter++;
	}//end while
}

/*
This method checks how many bombs are present in the adjacent neighbors of square.
Returns the number of bombs in the neighbors.
*/
int GameBoard::getBombCountOfSquare(Square* square)
{
	int noOfBombs = 0;
	int row = square->getRow();
	int column = square->getColumn();

	for (int row_offset = -1; row_offset <= 1; row_offset++) 
	{
		for (int column_offset = -1; column_offset <= 1; column_offset++) 
		{
			int rowToBeChecked = row + row_offset;
			int columnToBeChecked = column + column_offset;
			//Checks if square is whithin the board range
			if (isValidRowAndColumn(rowToBeChecked, columnToBeChecked)) 
			{		
				Square* neighborSquare = getSquare(rowToBeChecked,columnToBeChecked);
				
				//If square is a bomb
				if (neighborSquare->hasBomb())		
					noOfBombs++;

			}//end if
		}//end for column loop
	}//end for row loop
	return noOfBombs;
}

/*
This method sets the bomb count of each square and sets the display of each square.
*/
void GameBoard::setBombCountAndDisplay()
{
	for (int row = 0; row < rows; row++) 
	{
		for (int column = 0; column < columns; column++) 
		{
			Square* square = getSquare(row,column);
			
			//Get the number of bombs
			int numberOfbombs = getBombCountOfSquare(square);		
			square->setNeighborsWithBombs(numberOfbombs);

			//If square is not a bomb
			if (!square->hasBomb())
				square->setDisplay(to_string(numberOfbombs));		//Sets the display value to bomb count
		}//end for column loop
	}//end for row loop
}

/*
This method reveals all the bombs of the game board.
This method is called only when a user loses the game.
*/
void GameBoard::revealAllBombs()
{
	for (int row = 0; row < rows; row++) 
	{
		for (int column = 0; column < columns; column++) 
		{
			Square* square = getSquare(row,column);

			//If square is a bomb, then it is revealed
			if (square->hasBomb())
				square->setRevealed(true);

		}//end for column loop
	}//end for row loop
}

/*
This method checks if user has flagged only bombs in the game board.
If a non bomb square is flagged, then false is returned.
*/
bool GameBoard::allBombsFlagged()
{
	for (int row = 0; row < rows; row++) 
	{
		for (int column = 0; column < columns; column++) 
		{
			Square* square = getSquare(row,column);

			//If a bomb square is left unflagged,then false is returned
			if (square->hasBomb() && !square->isFlagged())		
				return false;

			//If a square is not a bomb and it is flagged
			if (!square->hasBomb() && square->isFlagged())
				return false;

		}//end for column loop
	}//end for row loop

	//Returns true if only bombs are flagged
	return true;		
}

/*
This method checks if all non bomb square are revealed or not.
*/
bool GameBoard::allSquaresRevealed()
{
	for (int row = 0; row < rows; row++) 
	{
		for (int column = 0; column < columns; column++) 
		{
			Square* square = getSquare(row,column);

			//If non-bomb square is left un-revealed,then false is returned
			if (!square->hasBomb() && !square->isRevealed())		
				return false;
		}
	}
	return true;
}

/*
This method prints the game board.
*/
void GameBoard::print()
{
	cout << "\n     ";
	for (int i = 0; i < columns; i++)
	{
		if (i < 10)
			cout << i << "   ";
		else
			cout << i << "  ";
	}
	
	cout << "\n\n";
	
	for (int row = 0; row < rows; row++)
	{
		if (row < 10)
			cout << row << "   ";
		else
			cout << row << "  ";
		for (int column = 0; column < columns; column++)
		{
			Square* square = &board[row][column];

			if (square->isRevealed())
				cout << " " << square->getDisplay() << "  ";
			else if (square->isFlagged())
				cout << " |^ ";
			else
				cout << " [] ";
		}
		cout << endl;
	}
	cout << "\n";
}

//Initializes the row and column numbr of all board squares
void GameBoard::initializeSquares()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			board[i][j].setPosition(i, j);
		}
	}
}

//This method reveals all the squares
void GameBoard::revealAllSquares()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			board[i][j].setRevealed(true);
		}
	}
}