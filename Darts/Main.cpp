#include <iostream>
#include <string>
#include <time.h>

//#include "Player.h"
//#include "Throw.h"
//#include "Display.h"
#include "Interactive.h"
#include "Simulation.h"
//#include "States.h"


#pragma region Function Prototypes

void getGameType(Display display, GameType &gameType); // Asks user what type of game they would like to play
void resetClasses(Player &player1, Player &player2, Game &game); // Resets classes for new game

#pragma endregion Declarations of the functions used


int main()
{
#pragma region Class object instantiations

	Player player1("Joe", 71, 501, 0, 0); // Sets default details for player 1 in case these are not changed
	Player player2("Sid", 73, 501, 0, 0); // Sets default details for player 2 in case these are not changed
	Throw throws; // Creates an object of the throw class
	Game game; // Creates an object of the game class
	Display display; // Creates an object of the display class
	Interactive interactive; // Creates an object of the interactive class
	Simulation simulation; // Creates an object of the simulation class

#pragma endregion Instances of the classes used


#pragma region Variable initialisations

	Player* currentPlayer = NULL; // A pointer which will point to the current player playing their turn
	GameType gameType = MENU; // An enunm storing which game type is playing
	CurrentThrow currentThrow = NONE; // An enum storing which throw the player will play

	srand(time(0)); // Seeds for a random number based on time

#pragma endregion Variables to be used throughout the main function



	getGameType(display, gameType); // Asks user what type of game they would like to play



#pragma region Simulation Game

	if (gameType == SIMULATION) // If the user has chosen to play a Simulation Game
	{
		simulation.setUpGame(player1, player2, display, currentPlayer, throws); // Gets pre-game info such as the player information and who starts

		for (int j = 0; j < simulation.getSimNum(); j++) // Repeats for however many matches the player has chosen to simulate
		{
			while (simulation.getGameEnded() == false) // Repeat while the game has not ended
			{
				resetClasses(player1, player2, game); // Resets classes for new game

				simulation.playGame(currentPlayer, currentThrow, throws, player1, player2, game); // Plays the Simulation Game

				currentThrow = NONE; // Resets the Current Throw variable
			}

			simulation.incrementScores(player1, player2); // Increments the scores array to keep track of player scores

			simulation.incrementSets(player1, player2); // Increments the sets variable to keep track of how many sets have been played

			simulation.setGameEnded(false); // Reset Game Ended variable
		}

		simulation.displayResults(player1, player2, display); // Once all of the simulations have played, displays the results
	}

#pragma endregion The game loop for the Simulation Game



#pragma region Interactive Game

	else if (gameType == INTERACTIVE) // If the user has chosen to play an Interactive Game
	{
		interactive.setUpGame(display, player1, player2, currentPlayer, throws); // Gets pre-game info such as the player information and who starts

		while (interactive.getGameEnded() == false) // Repeat while the game has not ended
		{
			resetClasses(player1, player2, game); // Resets classes for new game

			interactive.playGame(currentPlayer, display, player1, player2, game, currentThrow, throws); // Plays the Interactive Game

			currentThrow = NONE; // Resets the Current Throw variable
		}

		display.endScreen(player1, player2, interactive.getGameCounter(), interactive.getSetCounter()); // Once the match has ended, displays the end screen
	}

	system("pause");
	return 0;
}

#pragma endregion The game loop for the Interactive Game



#pragma region Main functions

void getGameType(Display display, GameType &gameType)
{
	char choice;

	display.initialDisplay(); // Displays the initial title screen

	std::cout << "What type of game would you like to play? Please enter 'S' for a Simulation or 'I' for an Interactive Game: ";
	std::cin >> choice;

	// Ensures input is valid
	while (toupper(choice) != 'S' && toupper(choice) != 'I')
	{
		std::cout << "That input is invalid. Please enter 'S' for a Simulation or 'I' for an Interactive Game: ";
		std::cin >> choice;
	}

	if (toupper(choice) == 'S')
	{
		gameType = SIMULATION; // User has chosen to play a Simulation Game
	}

	else if (toupper(choice) == 'I')
	{
		gameType = INTERACTIVE; // User has chosen to play an Interactive Game
	}

	display.initialDisplay(); // Refreshes the display
}

void resetClasses(Player &player1, Player &player2, Game &game)
{
	// Resets classes, passing in relevant info which needs to be stored for future games

	player1 = Player(player1.getName(), player1.getSuccessRate(), 501, player1.getGamesWon(), player1.getSetsWon()); // so i can keep track of games won after i reset
	player2 = Player(player2.getName(), player2.getSuccessRate(), 501, player2.getGamesWon(), player2.getSetsWon()); // so i can keep track of games won after i reset
	game = Game(game.getGameCounter(), game.getSetCounter());
}

#pragma endregion Functions needed in main file