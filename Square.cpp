#include "Square.h"
#include<iostream>
using namespace std;

/*
Initializes Square to its default values
*/
Square::Square()
{
	display = "";
	containsBomb = false;
	revealed = false;
	flagged = false;
	neighboursWithBombs = 0;
	row = 0;
	column = 0;
}

Square::~Square()
{}

//Returns true if square has bomb
bool Square::hasBomb() const
{
	return containsBomb;
}

//Returns true if square has been asserted
bool Square::isRevealed() const
{
	return revealed;
}

//Returns true if square is flagged
bool Square::isFlagged() const
{
	return flagged;
}

/*
This method returns the number of bombs surrounding it
*/
int Square::getNeighboringBombs() const
{
	return neighboursWithBombs;
}

//Returns the row no of square
int Square::getRow() const
{
	return row;
}

//Returns the column number of square
int Square::getColumn() const
{
	return column;
}

//Sets bomb in the square
void Square::setBomb(bool value)
{
	this->containsBomb = value;
}

//Flags the square
void Square::setFlag(bool value)
{
	this->flagged = value;
}

//Reveals the square
void Square::setRevealed(bool value)
{
	this->revealed = value;
}

//Sets the number of bombs surrounding
void Square::setNeighborsWithBombs(int value)
{
	this->neighboursWithBombs = value;
}

//Sets the row and column number of square
void Square::setPosition(int row, int column)
{
	this->row = row;
	this->column = column;
}

//Sets the display of square
void Square::setDisplay(string value)
{
	this->display = value;
}

//Returns the display of square
string Square::getDisplay()
{
	return this->display;
}