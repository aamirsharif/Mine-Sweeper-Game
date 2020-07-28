#pragma once
#include"Square.h"
/*
This class represents the game board. Board is made up of dynamic 2D array of squares.
*/
class GameBoard
{
public:
	GameBoard();
	GameBoard(int rows,int columns,int bombs);
	~GameBoard();
	Square* getSquare(int& row, int& column);
	bool isValidRowAndColumn(int row, int column) const;
	int getBombCountOfSquare(Square* square);
	void setBombCountAndDisplay();
	void revealAllBombs();
	void revealAllSquares();
	bool allBombsFlagged();
	bool allSquaresRevealed();
	void print();
private:
	Square** board;	//Board of squares
	int rows, columns;	//Numbr of rows and columns of board
	int bombs;		//Number of bombs in board.
	void initializeSquares();
	void placeBombs(int bombs);
};

