#pragma once
#include"GameBoard.h"
/*Structure to hold the user input data.*/
struct Input {
	int command;	//Command given by user, i.e. flag,assert,unflag.	
	int rowNumber;	//Row number given by the user.
	int columnNumber;//Column number given y the user.
};

/*
This class represents the gameplay. It contains a gameboard object, length of board, width of board,
number of bombs board will contain, and a boolean property to check if has player has made 
its first assertion.
*/
class Game
{
public:
	Game(int difficulty);
	Game(int rows, int columns, int bombs);
	~Game();
	Square* acceptInputs(Input& data);
	bool updateGameplay(Input&, Square*);
	void displayGamePlay();
private:
	GameBoard* board;	//Game board
	int difficultyLevel;	//Difficulty level
	int bombs;		//Number of bombs in the game
	int rows, columns;//Length and width of board
	bool firstAssertionPlayed;//Bool property to check if player has made first assertion or not.
	void printCommandMenu() const;
	bool validateCommand(int);
	bool validateRow(int);
	bool validateColumn(int);
	void removeNearbyBombs(Square*);
	void revealNeighbours(Square*);
	void firstTimeAssertion(Square*);
};

