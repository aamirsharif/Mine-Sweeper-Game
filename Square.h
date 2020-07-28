#pragma once
#include<string.h>
#include<iostream>
using namespace std;
/*
This class represents a single square which makes up the whole game board.
*/
class Square
{
public:
	Square();
	~Square();
	bool hasBomb() const;
	bool isRevealed() const;
	bool isFlagged() const;
	int getNeighboringBombs() const;
	int getRow() const;
	int getColumn() const;
	string getDisplay();
	void setBomb(bool);
	void setRevealed(bool);
	void setFlag(bool);
	void setNeighborsWithBombs(int);
	void setPosition(int row, int column);
	void setDisplay(string);
protected:
	string display;				//String to be displayed on board
	bool containsBomb;			//Does the square have a bomb?
	bool revealed;				//Is the square revealed?
	bool flagged;				//Has the square been flagged?
	int neighboursWithBombs;	//Neighbouring squares with bombs
	int row;					//Row number of square
	int column;					//Column number of square
};

