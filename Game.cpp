#include "Game.h"
#include<iostream>
using namespace std;

/*
This constructor accepts a difficulty level and initializes the game based on the level.
*/
Game::Game(int difficulty)
{
	this->difficultyLevel = difficulty;
	this->firstAssertionPlayed = false;
	if (this->difficultyLevel == 1)
	{
		rows = 10;
		columns = 10;
		bombs = 25;
		this->board = new GameBoard(rows, columns, bombs);
	}
	else if (this->difficultyLevel == 2)
	{
		rows = 15;
		columns = 15;
		bombs = 60;
		this->board = new GameBoard(rows, columns, bombs);
	}
	else if (this->difficultyLevel == 3)
	{
		rows = 20;
		columns = 20;
		bombs = 120;
		this->board = new GameBoard(rows, columns, bombs);
	}
	else if (this->difficultyLevel == 4)
	{
		rows = 24;
		columns = 24;
		bombs = 150;
		this->board = new GameBoard(rows, columns, bombs);
	}
	else
	{
		rows = 24;
		columns = 24;
		bombs = 300;
		this->board = new GameBoard(rows, columns, bombs);
	}
}

/*
This constructor is called when a user decides to create a custom board.
*/
Game::Game(int rows, int columns, int bombs)
{
	this->difficultyLevel = 0;
	this->firstAssertionPlayed = false;
	this->rows = rows;
	this->columns = columns;
	this->bombs = bombs;
	this->board = new GameBoard(rows, columns, bombs);
}

//Deletes the game board.
Game::~Game() 
{
	delete board;
}

/*
Method to accept and validate inputs from the user.
*/
Square* Game::acceptInputs(Input& data)
{
	//Print the command menu
	printCommandMenu();
	cin >> data.command;

	//Validate the command entered by the user
	while (!validateCommand(data.command))
	{
		cout << "\nInvalid Command!! Please Select Command Again!!\n";
		printCommandMenu();
		cin >> data.command;
	}

	//If user wants to quit.
	if (data.command == 5 || data.command == 4)
		return NULL;

	cout << "\nEnter Row Number: ";
	cin >> data.rowNumber;

	//Validate that the row number is whithin board range.
	while (!validateRow(data.rowNumber))
	{
		cout << "\nInvalid Row Number!! Please Select a Valid Row number from 0 to " << rows - 1 << " !!\n";
		cout << "Enter Row Number: ";
		cin >> data.rowNumber;
	}

	cout << "Enter Column Number: ";
	cin >> data.columnNumber;

	//Validate that the column number is whithin board range.
	while (!validateColumn(data.columnNumber))
	{
		cout << "\nInvalid Column Number!! Please Select a Valid Column number from 0 to " << columns - 1 << " !!\n";
		cout << "Enter Column Number: ";
		cin >> data.columnNumber;
	}

	//Return the square at the provided row and column number.
	Square* square = board->getSquare(data.rowNumber, data.columnNumber);
	return square;
}

//Validates the command given by user.
bool Game::validateCommand(int command)
{
	bool isValid = false;
	switch (command)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		isValid = true;
		break;
	default:
		isValid = false;
	}
	return isValid;
}

//Validates the row number
bool Game::validateRow(int row)
{
	return (row >= 0 && row < rows);
}

//Validates the column number.
bool Game::validateColumn(int column)
{
	return(column >= 0 && column < columns);
}

//Prinds the command menu
void Game::printCommandMenu() const
{
	cout << "\n1) Flag a Square as mine.\n";
	cout << "2) UnFlag a Square.\n";
	cout << "3) Assert that a Square is Mine Free.\n";
	cout << "4) Auto Complete.\n";
	cout << "5) Quit the Game.\n";
	cout << "\nEnter Command: ";
}

/*
This method is caaled only once at the time user asserts for the first time.
Since it is the rule of the game that the first square openend is never  bomb.
*/
void Game::removeNearbyBombs(Square* square)
{
	int row = square->getRow();
	int column = square->getColumn();

	//If square does not have surrounding bombs then just step out of the method.
	if (square->getNeighboringBombs() == 0)
		return;

	for (int row_offset = -1; row_offset <= 1; row_offset++)
	{
		for (int column_offset = -1; column_offset <= 1; column_offset++)
		{
			int rowToBeChecked = row + row_offset;
			int columnToBeChecked = column + column_offset;
			if (board->isValidRowAndColumn(rowToBeChecked,columnToBeChecked ))
			{
				Square* neighbor = board->getSquare(rowToBeChecked, columnToBeChecked);
				if (neighbor->hasBomb())
					neighbor->setBomb(false);
			}
		}
	}

}

/*
This method reveals the neighbors of the square.
Called only when a square is asserted that does not contain surrounding bombs.
*/
void Game::revealNeighbours(Square* square)
{
	int row = square->getRow();
	int column = square->getColumn();

	//If a square has surrounding bombs, then do not proceed
	if (square->getNeighboringBombs() != 0)
		return;

	for (int row_offset = -1; row_offset <= 1; row_offset++)
	{
		for (int column_offset = -1; column_offset <= 1; column_offset++)
		{
			int rowToBeChecked = row + row_offset;
			int columnToBeChecked = column + column_offset;
			if (board->isValidRowAndColumn(rowToBeChecked, columnToBeChecked))
			{
				Square* neighbor = board->getSquare(rowToBeChecked, columnToBeChecked);
				
				//Checks if the square/neighbor has not been revealed
				if (!neighbor->isRevealed())
				{
					//Reveal the square/neighbor
					neighbor->setRevealed(true);

					//If a neighbor further has zero surrounding bombs, then its neighbors are also 
					//revealed recursively using recursion. 
					if (neighbor->getNeighboringBombs() == 0)
						revealNeighbours(neighbor);
				}
			}
		}
	}
}

/*
This method is called only when user asserts a square for the first time. Since,
It it the rule of game that first square opened is never a bomb, so we have to ake sure of that.
There are 4 cases when a user opens a square for the first time.
Case 1: Square does not have bomb and square has neighboring bombs.
Case 2: Square has bomb but no surrounding bombs.
Case 3: Square has bomb and also surrounding bombs.
Case 4: Square has no bomb and no surrounding bombs.(Handled automatically)
*/
void Game::firstTimeAssertion(Square* square)
{
	firstAssertionPlayed = true;
	square->setRevealed(true);

	//Case 1
	if (!square->hasBomb() && square->getNeighboringBombs() != 0)
	{
		removeNearbyBombs(square);
		board->setBombCountAndDisplay();
	}
	//Case 2
	else if (square->hasBomb() && square->getNeighboringBombs() == 0)
	{
		square->setBomb(false);
		board->setBombCountAndDisplay();
	}
	//Case 3
	else if (square->hasBomb() && square->getNeighboringBombs() != 0 )
	{
		square->setBomb(false);
		removeNearbyBombs(square);
		board->setBombCountAndDisplay();
	}
	//If none then it is definitely case 4.

	//Reveal the neigbors
	revealNeighbours(square);
}

/*
This method updates the game play each time a user makes a move.
Returns true if user has not lost yet or not won yet.
Returns false if user has either wo or lost.
*/
bool Game::updateGameplay(Input& input, Square* square)
{
	//If user wants to flag a square
	if (input.command == 1)
	{
		//Flag the square
		square->setFlag(true);

		//Check if only bombs are flagged, then user has won the game
		if (board->allBombsFlagged())
		{
			cout << "\nCongratulations, You have Successfully Flagged all Squares only with bombs!!";
			return false;
		}
		return true;
	}
	//If user wants to unflag a square
	else if (input.command == 2)
	{
		if(square->isFlagged())
			square->setFlag(false);
		return true;
	}
	//If user wants to open a square
	else if(input.command == 3)
	{
		//User cannot open a flagged square, it must be unflagged first.
		if (square->isFlagged())
		{
			cout << "\nYou cannot Assert a Flagged Square. Please unflag it first.!!\n";
			return true;
		}
		//If user is asserting for the first time, call the first time assertion method.
		else if (!firstAssertionPlayed)
		{
			firstTimeAssertion(square);
			return true;
		}
		//If square user wants to open is a bomb, then user has lost the game.
		else if (square->hasBomb())
		{
			board->revealAllBombs();
			cout << "\n****BOOM You Lose****!!\n";
			return false;
		}
		//If none of the aove then
		else
		{
			//Reveal the square
			square->setRevealed(true);
			//If square has no surrounding bombs, then reveal the eighbors also
			if (square->getNeighboringBombs() == 0)
			{
				revealNeighbours(square);
			}

			//Check if user has opened all non bomb squares or not.
			if (board->allSquaresRevealed())
			{
				board->revealAllBombs();
				cout << "\nCongratulations, You opened all Squares!!\n";
				return false;
			}
			return true;
		}
	}
	//If user wants to auto complete the game
	else
	{
		board->revealAllSquares();
		return false;
	}
}

//Displays the board.
void Game::displayGamePlay()
{
	board->print();
}