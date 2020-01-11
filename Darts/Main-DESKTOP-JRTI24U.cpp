#include <iostream>
#include <string>
#include <time.h>

#include "Player.h"
#include "Throw.h"
#include "Game.h"
#include "Display.h"


int main()
{
	//TODO: make target a player variable?
	//TODO: maybe do input without enter (getch)

	srand(time(0)); // seed for random number

	Player player1("Joe", 71, 501, 0, 0); // changed to player 1 and 2 in case players change
	Player player2("Sid", 73, 501, 0, 0);
	Throw throws;
	Game game;
	Display display;

	Player* currentPlayer = NULL;



	char newGameChoice = 'Y'; //TODO: maybe a menu class?
	int choice;
	int starts = 0;


	enum GameType { NONE, SIMULATION, INTERACTIVE };
	GameType gameType = NONE;
	int input;
	std::string name;
	char throwType;
	int target;



	display.initialDisplay();


	std::cout << "What type of game would you like to play? Please enter '1' for a Simulation or '2' for an Interactive Game: ";
	std::cin >> choice;

	while (choice != 1 && choice != 2)
	{
		std::cout << "That input is invalid. Please press '1' for a Simulation or '2' for an Interactive Game : ";
		std::cin >> choice;
	}

	if (choice == 1)
	{
		gameType = SIMULATION;
	}

	else if (choice == 2)
	{
		gameType = INTERACTIVE;
	}

	display.initialDisplay();


	if (gameType == SIMULATION)
	{
		
	}

	//TODO: maybe option for 2 players to play?

	else if (gameType == INTERACTIVE)
	{
		std::cout << std::endl << "Please enter the player's name: ";
		std::cin >> name;
		player1.setName(name);

		display.initialDisplay();

		std::cout << std::endl << "The default Success Rate is 71." << std::endl << "Please enter 0 to use the default or enter the success rate you would like to have : ";
		std::cin >> choice;

		while (choice < 0 || choice > 100)
		{
			std::cout << "That input is invalid. Please enter 0 to use the default or enter the Success Rate you would like to have: ";
			std::cin >> choice;
		}


		if (choice == 0)
		{
			player1.setSuccessRate(71);
		}

		else
		{
			player1.setSuccessRate(choice);
		}

		display.initialDisplay();


		//TODO: sort functions out


	}

	std::cout << std::endl << "Who would you like to start first? Please enter 1 for " << player1.getName() << " or 2 for " << player2.getName() << ": ";
	std::cin >> starts;

	while (starts != 1 && starts != 2)
	{
		std::cout << "That input is invalid. Who would you like to start first? Please enter 1 for " << player1.getName() << " or 2 for " << player2.getName() << ": ";
		std::cin >> starts;
	}

	if (starts == 1)
	{
		currentPlayer = &player1;
	}

	else if (starts == 2)
	{
		currentPlayer = &player2;
	}


	bool gameEnded = false;

	

	while (!gameEnded)
	{
		player1 = Player(player1.getName(), player1.getSuccessRate(), 501, player1.getGamesWon(), player1.getSetsWon()); // so i can keep track of games won after i reset
		player2 = Player(player2.getName(), player2.getSuccessRate(), 501, player2.getGamesWon(), player2.getSetsWon()); // so i can keep track of games won after i reset
		game = Game(game.getGameCounter(), game.getSetCounter());


		bool won = game.checkWin(currentPlayer);

		while (!won) // while noone has won
		{

			display.displayScreen(player1, player2, game);

			if (currentPlayer == &player2)
			{
				std::cout << "It is now turn " << (currentPlayer->getTurn() + 1) << " for " << currentPlayer->getName() << "." << std::endl;

				system("pause");
			}

			for (int i = 0; i < 3; i++)
			{

				if (currentPlayer == &player1)
				{
					std::cout << "It is your turn. What would you like to throw for?" << std::endl
						<< "Please enter 'S' for a Single, 'D' for a Double, 'T' for a Treble, 'I' for Inner Bull or 'O' for Outer Bull: ";

					std::cin >> throwType;

					while (toupper(throwType) != 'S' && toupper(throwType) != 'D' && toupper(throwType) != 'T' && toupper(throwType) != 'I' && toupper(throwType) != 'O')
					{
						std::cout << "That input is invalid. Please enter 'S' for a Single, 'D' for a Double, 'T' for a Treble, 'I' for Inner Bull or 'O' for Outer Bull : ";
						std::cin >> throwType;
					}

					if (toupper(throwType) != 'I' && toupper(throwType) != 'O')
					{
						std::cout << std::endl << "What number would you like to throw at? Please enter a number between 1 and 20: ";
						std::cin >> target;
					}

					else if (toupper(throwType) == 'I')
					{
						target = 50;
					}

					else if (toupper(throwType) == 'O')
					{
						target = 25;
					}
				}

				display.displayScreen(player1, player2, game);

				std::cout << "Throw " << i + 1 << "..." << std::endl;

				currentPlayer->setThrowCounter(currentPlayer->getThrowCounter() + 1);

				if (gameType == SIMULATION || gameType == INTERACTIVE && currentPlayer == &player2)
				{
					game.setUpThrow(currentPlayer);
					game.playThrow(currentPlayer, throws);
				}

				else if (gameType == INTERACTIVE && currentPlayer == &player1)
				{
					game.setUpThrow(currentPlayer, throwType);
					game.playThrow(currentPlayer, throws, target);
				}


				game.updatePoints(currentPlayer);

				system("pause");

				display.displayScreen(player1, player2, game);

				won = game.checkWin(currentPlayer);

				if (won)
				{
					break;
				}
			}

			currentPlayer->setTurnPoints(0);

			currentPlayer->setTurn(currentPlayer->getTurn() + 1);

			if (currentPlayer == &player1)
			{
				currentPlayer = &player2;
			}

			else if (currentPlayer == &player2)
			{
				currentPlayer = &player1;
			}
		}

		if (player1.getHasWon())
		{
			player1.setGamesWon(player1.getGamesWon() + 1);
		}

		else if (player2.getHasWon())
		{
			player2.setGamesWon(player2.getGamesWon() + 1);
		}

		//game.outputResults(player1, player2);

		game.setGameCounter(game.getGameCounter() + 1);

		if (player1.getGamesWon() == 3)
		{
			std::cout << player1.getName() << " has won this set!" << std::endl;
			system("pause");
			player1.setSetsWon(player1.getSetsWon() + 1);
			game.setSetCounter(game.getSetCounter() + 1);
			game.setGameCounter(0);
			player1.setGamesWon(0);
		}

		else if (player2.getGamesWon() == 3)
		{
			std::cout << player2.getName() << " has won this set!" << std::endl;
			system("pause");
			player2.setSetsWon(player2.getSetsWon() + 1);
			game.setSetCounter(game.getSetCounter() + 1);
			game.setGameCounter(0);
			player2.setGamesWon(0);
		}

		if (player1.getSetsWon() == 1 | player2.getSetsWon() == 1)
		{
			gameEnded = true;
		}

	}

	display.endScreen(player1, player2, game);

	return 0;
}