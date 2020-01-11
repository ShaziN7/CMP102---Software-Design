#include "Game.h"
#include "Display.h"


Game::Game()
{
	gameCounter = 1;
	setCounter = 1;
}

Game::Game(int gc, int sc)
{
	// For keeping count of how many games and sets have been won after resetting the class object

	gameCounter = gc;
	setCounter = sc;
}

Game::~Game()
{
}


#pragma region Player Functions

void Game::getPlayerInfo(Player &player1, Display display)
{
	// Gets player's name and stores in player class
	std::cout << std::endl << "Please enter the player's name: ";
	std::cin >> name;
	player1.setName(name);

	display.initialDisplay(); // Refreshes display

	// Gets success rate of player
	std::cout << std::endl << "The default Success Rate is 71." << std::endl << "Please enter 0 to use the default or enter the success rate you would like to have: ";
	std::cin >> choice;

	// Makes sure input is valid
	while (choice < 0 || choice > 100)
	{
		std::cout << "That input is invalid. Please enter 0 to use the default or enter the Success Rate you would like to have: ";
		std::cin >> choice;
	}

	if (choice == 0)
	{
		player1.setSuccessRate(71); // Sets success rate to default
	}

	else
	{
		player1.setSuccessRate(choice); // Sets success rate to player's choice
	}

	display.initialDisplay();
}

void Game::getPlayerInfo(Player &player1, Player &player2, Display display)
{
	// Gets player 1's name and stores in player class
	std::cout << std::endl << "Please enter Player 1's name: ";
	std::cin >> name;
	player1.setName(name);

	// Gets success rate of player 1
	std::cout << std::endl << "Please enter Player 1's success rate or 0 to keep default of 71: ";
	std::cin >> choice;

	// Makes sure input is valid
	while (choice < 0 || choice > 100)
	{
		std::cout << "That input is invalid. Please enter 0 to use the default or enter the Success Rate you would like to have: ";
		std::cin >> choice;
	}

	if (choice == 0)
	{
		player1.setSuccessRate(71); // Sets success rate to default
	}

	else
	{
		player1.setSuccessRate(choice); // Sets success rate to player's choice
	}

	display.initialDisplay(); // Refreshes display

	// Gets player 2's name and stores in player class
	std::cout << std::endl << "Please enter Player 2's name: ";
	std::cin >> name;
	player2.setName(name);

	// Gets success rate of player 2
	std::cout << std::endl << "Please enter Player 2's success rate or 0 to keep default of 73: ";
	std::cin >> choice;

	// Makes sure input is valid
	while (choice < 0 || choice > 100)
	{
		std::cout << "That input is invalid. Please enter 0 to use the default or enter the Success Rate you would like to have: ";
		std::cin >> choice;
	}


	if (choice == 0)
	{
		player2.setSuccessRate(73); // Sets success rate to default
	}

	else
	{
		player2.setSuccessRate(choice); // Sets success rate to player's choice
	}

	display.initialDisplay(); // Refreshes display
}

void Game::getWhoStarts(Player* &currentPlayer, Player &player1, Player &player2, Throw throws, Display display)
{
	std::cout << std::endl << "Who would you like to start first? Please enter 1 for " << player1.getName() << ", 2 for " << player2.getName() << " or 3 to throw for first: ";
	std::cin >> starts;

	// Makes sure input is valid
	while (starts != 1 && starts != 2 && starts != 3)
	{
		std::cout << "That input is invalid. Who would you like to start first? Please enter 1 for " << player1.getName() << " or 2 for " << player2.getName() << " or 3 to throw for first: ";
		std::cin >> starts;
	}


	switch (starts)
	{
		// If player 1 will start
	case 1:
	{
		currentPlayer = &player1; // Sets player 1 as the current player using the pointer
		break;
	}

	// If player 2 will start
	case 2:
	{
		currentPlayer = &player2; // Sets player 2 as the current player using the pointer
		break;
	}

	// If players will throw to see who will start
	case 3:
	{
		p1Throw = throwForFirst(player1, throws); // Stores player 1's score
		p2Throw = throwForFirst(player2, throws); // Stores player 2's score

		display.initialDisplay();

		// Displays what player 1 scored
		std::cout << player1.getName() << " will throw..." << std::endl;
		std::cout << player1.getName() << " has scored a " << p1Throw << "." << std::endl << std::endl;

		system("pause");
		display.initialDisplay();

		// Displays what player 2 scored
		std::cout << player2.getName() << " will throw..." << std::endl;
		std::cout << player2.getName() << " has scored a " << p2Throw << "." << std::endl << std::endl;

		system("pause");

		// While the player's threw the same score
		while (p1Throw == p2Throw)
		{
			display.initialDisplay();

			std::cout << "The throws were a draw so will be taken again." << std::endl;
			system("pause");

			// Each player throws again
			p1Throw = throwForFirst(player1, throws);
			p2Throw = throwForFirst(player2, throws);

			display.initialDisplay();

			std::cout << player1.getName() << " will throw..." << std::endl;
			std::cout << player1.getName() << " has scored a " << p1Throw << "." << std::endl << std::endl;

			system("pause");
			display.initialDisplay();

			std::cout << player2.getName() << " will throw..." << std::endl;
			std::cout << player2.getName() << " has scored a " << p2Throw << "." << std::endl << std::endl;
			system("pause");
		}

		// If player 1 threw higher than player 2
		if (p1Throw > p2Throw)
		{
			display.initialDisplay();
			std::cout << player1.getName() << " has scored higher and will start first." << std::endl << std::endl;
			currentPlayer = &player1; // Sets player 1 to be the current player
			system("pause");
		}

		// If player 2 threw higher than player 1
		else if (p2Throw > p1Throw)
		{
			display.initialDisplay();
			std::cout << player2.getName() << " has scored higher and will start first." << std::endl << std::endl;
			currentPlayer = &player2; // Sets player 2 to be the current player
			system("pause");
		}

		break;
	}

	default:
		break;
	}
}

void Game::switchPlayers(Player* &currentPlayer, Player &player1, Player &player2)
{
	if (currentPlayer == &player1)
	{
		currentPlayer = &player2; // If it was player 1's turn, it is now player 2's turn
	}

	else if (currentPlayer == &player2)
	{
		currentPlayer = &player1; // If it was player 2's turn, it is now player 1's turn
	}
}

void Game::setWon(Player &player, Game &game)
{
	// If a set has been won

	player.setSetsWon(player.getSetsWon() + 1); // Increments how many sets the player has won by 1
	game.setSetCounter(game.getSetCounter() + 1); // Increments the number of sets played by 1
	game.setGameCounter(1); // Resets the game counter for the new set
	player.setGamesWon(0); // Resets the player's games won for the new set
}

#pragma endregion Functions dealing with players in the game


#pragma region Throw Functions

void Game::setUpThrow(Player* player, CurrentThrow &currentThrow)
{
	// Does a linear search through each array to see if it contains the target, if so the player will throw at that

	for (int i = 0; i < 20; i++) // 20 is the size of each array
	{
		if (currentThrow == NONE) // If throw type has not yet been set
		{

			if (player->getTarget() > 61)
			{
				currentThrow = TREBLE; // If player needs more than 61 points, they will throw for a treble
			}

			else if (player->getTarget() >= 50)
			{
				currentThrow = INNERBULL; // If player needs more 50 or more points, they will throw for a bull
			}

			else if (player->getTarget() == 25)
			{
				currentThrow = OUTERBULL; // If player needs 25 points, they will throw for an outer bull
			}

			else if (player->getTarget() < 60 && player->getTarget() % 2 != 0 || player->getTarget() == 61)
			{
				currentThrow = SINGLE; // If player's score is less than 60 and not even, or if they have 61 points, they will throw for a single
			}

			else if (player->getTarget() == treblesArray[i] && player->getTarget() > 40)
			{
				currentThrow = TREBLE; // If player's target is in the trebles array and is higher than 40
			}

			else if (player->getTarget() == doublesArray[i])
			{
				currentThrow = DOUBLE; // If player's target is in the doubles array
			}

			else if (player->getTarget() == singlesArray[i])
			{
				currentThrow = SINGLE; // If player's target is in the singles array
			}
		}

	}

	if (currentThrow == NONE)
	{
		currentThrow = SINGLE20; // In case the above criteria didn't work, throw for a single 20 as this should bring the points to something in an array
	}
}

void Game::setUpThrow(char throwType, CurrentThrow &currentThrow)
{
	// Sets throw type based on what the player has chosen

	switch (throwType)
	{

	case 'S': case 's':
		currentThrow = SINGLE;
		break;

	case 'D': case 'd':
		currentThrow = DOUBLE;
		break;

	case 'T': case 't':
		currentThrow = TREBLE;
		break;

	case 'I': case 'i':
		currentThrow = INNERBULL;
		break;

	case 'O': case 'o':
		currentThrow = OUTERBULL;
		break;

	default:
		currentThrow = NONE;
		break;
	}
}

int Game::throwForFirst(Player player, Throw throws)
{
	int firstThrow = throws.throwInnerBull(player.getSuccessRate()); // Throws at the bull to see who goes first

	return firstThrow;
}

#pragma endregion Functions dealing with throws in the game


#pragma region Point Functions

bool Game::checkWin(Player* player)
{
	if (player->getPoints() == 0)
	{
		return true; // If player has 0 points, they have won
	}

	else
	{
		return false; // If player doesn't have 0 points, they have not won
	}
}

bool Game::checkGameEnded(Player &player1, Player &player2)
{
	if (player1.getSetsWon() == 7 || player2.getSetsWon() == 7)
	{
		return true; // If a player has won 7 sets, the game has been won and has ended
	}

	else
	{
		return false; // If no-one has won 7 sets, the game has not ended yet
	}
}

#pragma endregion Functions dealing with points in the game


#pragma region Counter Functions

int Game::getGameCounter()
{
	return gameCounter;
}

void Game::setGameCounter(int gc)
{
	gameCounter = gc;
}

int Game::getSetCounter()
{
	return setCounter;
}

void Game::setSetCounter(int sc)
{
	setCounter = sc;
}

void Game::incrementGamesWon(Player &player1, Player &player2)
{
	if (player1.getHasWon())
	{
		player1.setGamesWon(player1.getGamesWon() + 1); // If player 1 has won, adds 1 to their games won counter
	}

	else if (player2.getHasWon())
	{
		player2.setGamesWon(player2.getGamesWon() + 1); // If player 2 has won, adds 1 to their games won counter
	}
}

#pragma endregion Functions dealing with counters in the game