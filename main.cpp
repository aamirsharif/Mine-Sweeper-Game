#include"Game.h"
#include<iostream>
#include<iomanip>
#include<conio.h>
using namespace std;
//Create a game object, and other variables required as global.
Game* game;
int difficulty,rows, columns, bombs, lowerBound,upperBound;

void printMainMenu();	//Prints the main menu.
void validateAndProceedMainChoice(int& choice);	//Validate and proceeds the choice of main menu.
void printDifficultyMenu();	//Prints the difficulty menu to select the difficulty.
void validateDifficulty();	//Validates the difficulty selected by user
void validateRows();	//Validates the number of rows given by user
void validateColumns();	//Validates the number of columns given by user.
void validateBombs();	//Validates the number of bombs given y user.
void startGame(bool &wantToPlay);	//Starts the game play.

int main()
{
	//Create a bool property to decide whether user still wants to play or not.
	bool wantToPlay = true;
	while (wantToPlay)
	{
		system("cls");
		cout << "***********Minesweeper Game************\n\n";

		//Print the main menu and get users choice.
		printMainMenu();
		int choice = 0;
		cin >> choice;

		//Validate and proceed with the choice
		validateAndProceedMainChoice(choice);

		//If user selected a predefined difficuly
		if (choice == 1)
			game = new Game(difficulty);

		//If user wants to create a custom board
		else if (choice == 2)
			game = new Game(rows, columns, bombs);
		
		//If user wants to know the rules first, then skip the rest of iteration.
		else
			continue;

		//Start the game play
		startGame(wantToPlay);

		//Delete the previous game and create a new game if user wants to play a new one.
		delete game;
	}

	cout << "\n\nThank You For Playing Minesweeper!!";
	cout << "\n\n";
	return 0;
}

//Prints the main menu.
void printMainMenu() 
{
	cout << "1) Select Difficulty.\n";
	cout << "2) Create Custom Board.\n";
	cout << "3) Display rules of game.\n";
	cout << "4) Quit Game.";
	cout << "\n\nEnter Choice: ";
}

//Prints the difficulty menu to select the difficulty.
void printDifficultyMenu() 
{
	cout << "--Please Select Difficulty Level--\n\n";
	cout << "1)Easy   10 x 10 Board, 20 Bombs.";
	cout << "\n2)Medium 15 x 15 Board, 60 Bombs.";
	cout << "\n3)Hard   20 x 20 Board, 120 Bombs.";
	cout << "\n4)Pro    24 x 24 Board, 150 Bombs.";
	cout << "\n5)Legend 24 x 24 Board, 300 Bombs.";
	cout << "\n\nEnter Choice: ";
}

//Validates the difficulty selected by user
void validateDifficulty()
{
	while (difficulty < 1 || difficulty >5)
	{
		cout << "\nInvalid Choice!! Please Select a Valid Choice\n";
		cout << "\nEnter Choice Again: ";
		cin >> difficulty;
	}
}

//Validates the number of rows given by user
void validateRows()
{
	while (rows < 10 || rows > 24)
	{
		cout << "\nError!! Rows cannot be less than 10 or rows cannot be greater than 24!!\n";
		cout << "\nPlease Enter Rows Again: ";
		cin >> rows;
	}
}

//Validates the number of columns given by user.
void validateColumns()
{
	while (columns < 10 || columns > 24)
	{
		cout << "\nError!! Columns cannot be less than 10 or rows cannot be greater than 24!!\n";
		cout << "\nPlease Enter Columns Again: ";
		cin >> columns;
	}
}

//Validates the number of bombs given y user.
void validateBombs()
{
	while (bombs < lowerBound || bombs > upperBound)
	{
		cout << "\nError! Bombs cannot be less than " << lowerBound << " or cannot be greater than " << upperBound << " !!\n";
		cout << "\nPlease Enter Bombs Again: ";
		cin >> bombs;
	}
}

//Validate and proceeds the choice of main menu.
void validateAndProceedMainChoice(int& choice)
{
	while (choice < 1 || choice >4)
	{
		cout << "\nInvalid Choice!! Please Select a Valid Choice!!\n";
		cout << "\nEnter Choice Again: ";
		cin >> choice;
	}

	system("cls");
	cout << "***********Minesweeper Game************\n\n";

	switch (choice)
	{
		//User wants to select a pregiven difficulty
	case 1:
		printDifficultyMenu();
		cin >> difficulty;
		validateDifficulty();
		break;
		//User wants to select a custom board
	case 2:
		cout << "Enter number of rows: ";
		cin >> rows;
		validateRows();
		cout << "Enter number of columns: ";
		cin >> columns;
		validateColumns();

		/*
		Bombs are selected within a given range based on the board size.
		The lower bound and upper bound is calculated first.
		*/

		lowerBound = (rows * columns) / 5;
		upperBound = floor(((double)(rows * columns)) / 2.5);
		cout << "Enter number of bombs between " << lowerBound << " and " << upperBound << " : ";
		cin >> bombs;
		validateBombs();
		break;
		//User wants to know the game rules.
	case 3:
		cout << "-- You are provided a board of squares. Some squares contain a bomb and some dont.\n";
		cout << "-- You have to open all the non bomb squares or flag all bomb only squares.\n";
		cout << "-- Opening a bomb will result in losing a game.\n";
		cout << "-- A square displays how many bombs are surrounding it.\n";
		cout << "-- If a square has no surrounding bomb, then its neighbors are revealed.\n";
		cout << "-- First square opened is never a bomb.\n\n";
		cout << "Press any key to go back.";
		_getch();
		break;
		//User wants to quit.
	case 4:
		cout << "Thank you for Playing!!\n\n";
		exit(0);
		break;
	}
}

/*
This method starts the main gameplay.
It recieves a boolean property to keep track whether user wants to play a new game again or not.
*/
void startGame(bool &wantToPlay)
{
	system("cls");
	//Bool property to check whether user has won/lost or not.
	bool gamePlay = true;

	//Create a square pointer.
	Square* square;
	game->displayGamePlay();

	while (gamePlay)
	{
		Input input;

		//Get the desired square based on the given input.
		square = game->acceptInputs(input);

		//If user wants to quit the game.
		if (input.command == 5)
			break;
		system("cls");

		//Update the game play based on the user input.
		gamePlay = game->updateGameplay(input,square);

		//Display the game state.
		game->displayGamePlay();
	}
	
	int option = 0;
	cout << "\nDo You Want To Play Again?\n";
	cout << "1) Yes\n";
	cout << "2) No\n";
	cout << "Enter Choice: ";
	cin >> option;
	while (option <= 0 || option > 2)
	{
		cout << "\nInvalid Option!!\n\n Please Select Again: ";
		cin >> option;
	}

	if (option == 1)
		wantToPlay = true;
	else
		wantToPlay = false;
	return;
}