#include "Interactive.h"


Interactive::Interactive()
{
	gameCounter = 1;
	setCounter = 1;
	twoPlayer = false;
	gameEnded = false;
}

Interactive::~Interactive()
{
}


#pragma region Interactive Functions

void Interactive::getPlayerThrow(char &throwType, int &target, Player player)
{
	std::cout << player.getName() << ", it is your turn. What would you like to throw for?" << std::endl
		<< "Please enter 'S' for a Single, 'D' for a Double, 'T' for a Treble, 'I' for Inner Bull or 'O' for Outer Bull: ";

	std::cin >> throwType; // Stores what type of throw the player has chosen

	// Makes sure input is valid
	while (toupper(throwType) != 'S' && toupper(throwType) != 'D' && toupper(throwType) != 'T' && toupper(throwType) != 'I' && toupper(throwType) != 'O')
	{
		std::cout << "That input is invalid. Please enter 'S' for a Single, 'D' for a Double, 'T' for a Treble, 'I' for Inner Bull or 'O' for Outer Bull: ";
		std::cin >> throwType;
	}

	// If bull wasn't chosen, asks player what number to make their target
	if (toupper(throwType) != 'I' && toupper(throwType) != 'O')
	{
		std::cout << std::endl << "What number would you like to throw at? Please enter a number between 1 and 20: ";
		std::cin >> target;

		// Makes sure input is valid
		while (target < 1 || target > 20)
		{
			std::cout << "That input is invalid. Please enter a number between 1 and 20: ";
			std::cin >> target;
		}
	}

	else if (toupper(throwType) == 'I')
	{
		target = 50; // If throwing for a bullseye, target is 50
	}

	else if (toupper(throwType) == 'O')
	{
		target = 25; // If throwing for the outer bull, target is 25
	}
}

bool Interactive::getTwoPlayers()
{
	// Asks if player would like to play with two players

	int choice;

	std::cout << "Please enter '1' for One Player or '2' for Two Player: ";
	std::cin >> choice;

	// Makes sure input is valid
	while (choice != 1 && choice != 2)
	{
		std::cout << "Please enter '1' for One Player or '2' for Two Player: ";
		std::cin >> choice;
	}

	if (choice == 1)
	{
		return false; // If one player
	}

	else if (choice == 2)
	{
		return true; // If two players
	}
}

bool Interactive::getGameEnded()
{
	return gameEnded;
}

void Interactive::setGameEnded(bool e)
{
	gameEnded = e;
}

int Interactive::getGameCounter()
{
	return gameCounter;
}

int Interactive::getSetCounter()
{
	return setCounter;
}

#pragma endregion Functions for the Interactive game


#pragma region Main Interactive Game Loop Functions

void Interactive::setUpGame(Display display, Player &player1, Player &player2, Player* &currentPlayer, Throw throws)
{
	twoPlayer = getTwoPlayers(); // If game is two player

	display.initialDisplay(); // Refreshes display

	if (!twoPlayer)
	{
		getPlayerInfo(player1, display); // If game is one player, get info for one player
	}

	else if (twoPlayer)
	{
		getPlayerInfo(player1, player2, display);  // If game is two player, get info for two players
	}

	getWhoStarts(currentPlayer, player1, player2, throws, display); // Ask player who they would like to start
}

void Interactive::playGame(Player* &currentPlayer, Display display, Player &player1, Player &player2, Game game, CurrentThrow &currentThrow, Throw throws)
{
	bool won = checkWin(currentPlayer);

	while (!won) // While no-one has won
	{
		display.displayScreen(player1, player2, gameCounter, setCounter); // Display the main screen

		if (currentPlayer == &player2 && !twoPlayer) // If it is the AI's turn
		{
			std::cout << "It is now turn " << (currentPlayer->getTurn() + 1) << " for " << currentPlayer->getName() << "." << std::endl;

			system("pause");
		}

		for (int i = 0; i < 3; i++) // Loop for each dart
		{
			throwDart(currentPlayer, player1, player2, display, currentThrow, throws, i); // Plays a throw
			
			updatePoints(currentPlayer, currentThrow); // Updates the player's points

			system("pause");

			display.displayScreen(player1, player2, gameCounter, setCounter); // Refreshes the display

			won = checkWin(currentPlayer); // Checks if player has won

			if (won)
			{
				break; // If player has won, stop playing
			}
		}

		currentPlayer->setTurnPoints(0); // Reset player's turn points when their turn is over

		currentPlayer->setTurn(currentPlayer->getTurn() + 1); // Increment the player's turn number

		switchPlayers(currentPlayer, player1, player2); // It is the other player's turn
	}

	incrementGamesWon(player1, player2); // Checks who has won and increments their Games Won counter

	gameCounter += 1;

	checkSetWon(player1, player2, game); // Checks if player has won set and increments/resets appropriate variables

	gameEnded = checkGameEnded(player1, player2); // Check if game has ended
}


void Interactive::playThrow(Player* player, Throw throws, CurrentThrow &currentThrow)
{
	// Plays throw by working out the optimal target for the player

	switch (currentThrow)
	{
	case SINGLE: // If throw type is Single
	{
		if (player->getTarget() % 2 != 0)
		{
			target = 1; // If target is not even, throw for a single 1 to make it even
		}

		else
		{
			target = player->getTarget(); // If target is even, throw for the target
		}

		std::cout << player->getName() << " will throw for a single " << target << "..." << std::endl;

		player->setThrowPoints(throws.throwSingle(target, player->getSuccessRate())); // Throws for a single on the target based on player's success rate

		if (player->getThrowPoints() == target) // If player has hit target
		{
			std::cout << player->getName() << " has hit his target and scored " << player->getThrowPoints() << " points." << std::endl;
		}

		else // If player has not hit target
		{
			std::cout << player->getName() << " has missed his target and scored " << player->getThrowPoints() << " points." << std::endl;
		}

		break;
	}

	case SINGLE20: // If throw type is Single-20
	{
		target = 20; // Overrides target to equal 20

		std::cout << player->getName() << " will throw for a single " << target << "..." << std::endl;

		player->setThrowPoints(throws.throwSingle(target, player->getSuccessRate())); // Throws for a single 20 based on player's success rate

		if (player->getThrowPoints() == 20) // If player has hit target
		{
			std::cout << player->getName() << " has hit his target and scored " << player->getThrowPoints() << " points." << std::endl;
		}

		else // If player has not hit target
		{
			std::cout << player->getName() << " has missed his target and scored " << player->getThrowPoints() << " points." << std::endl;
		}

		break;
	}

	case DOUBLE: // If throw type is Double
	{
		target = player->getTarget() / 2; // Sets throw target to equal half of the player's points remaining

		std::cout << player->getName() << " will throw for a double " << target << "..." << std::endl;

		player->setThrowPoints(throws.throwDouble(target, player->getSuccessRate())); // Throws for a double on the target based on player's success rate

		if (player->getThrowPoints() == player->getTarget()) // If player has hit target
		{
			std::cout << player->getName() << " has hit his target and scored " << player->getThrowPoints() << " points." << std::endl;
		}

		else // If player has not hit target
		{
			std::cout << player->getName() << " has missed his target and scored " << player->getThrowPoints() << " points." << std::endl;
		}

		break;
	}

	case TREBLE: // If throw type is Treble
	{
		if (player->getTarget() > 60)
		{
			target = 20; // If player's points are over 60, aim for 20 which is the highest target possible
		}

		else
		{
			target = player->getTarget() / 3; // If player's points aren't above 60, aim for a third of the total points
		}

		std::cout << player->getName() << " will throw for a treble " << target << "..." << std::endl;

		player->setThrowPoints(throws.throwTreble(target, player->getSuccessRate())); // Throws for a treble on the target based on player's success rate

		if (player->getThrowPoints() == player->getTarget() || (target == 20 && player->getThrowPoints() == 60)) // If player has hit target
		{
			std::cout << player->getName() << " has hit his target and scored " << player->getThrowPoints() << " points." << std::endl;
		}

		else // If player has not hit target
		{
			std::cout << player->getName() << " has missed his target and scored " << player->getThrowPoints() << " points." << std::endl;
		}

		break;
	}

	case INNERBULL: // If throw type is Inner Bull
	{
		std::cout << player->getName() << " will throw for a Bull..." << std::endl;

		player->setThrowPoints(throws.throwInnerBull(player->getSuccessRate())); // Throws for a bullseye based on player's success rate

		if (player->getThrowPoints() == 50) // If player has hit target
		{
			std::cout << player->getName() << " has hit the Bull and scored " << player->getThrowPoints() << " points." << std::endl;
			player->setBullCounter(player->getBullCounter() + 1); // Increments the bull counter
		}

		else // If player has not hit target
		{
			std::cout << player->getName() << " has missed the Bull and scored " << player->getThrowPoints() << " points." << std::endl;
		}

		break;
	}

	case OUTERBULL: // If throw type is Outer Bull
	{
		std::cout << player->getName() << " will throw for the outer Bull..." << std::endl;

		player->setThrowPoints(throws.throwOuterBull(player->getSuccessRate())); // Throws for an outer bull based on player's success rate

		if (player->getThrowPoints() == 25) // If player has hit target
		{
			std::cout << player->getName() << " has hit the outer Bull and scored " << player->getThrowPoints() << " points." << std::endl;
		}

		else // If player has not hit target
		{
			std::cout << player->getName() << " has missed the outer Bull and scored " << player->getThrowPoints() << " points." << std::endl;
		}

		break;
	}

	case 0: default:
		break;
	}
}

void Interactive::playThrow(Player* player, Throw throws, int target, CurrentThrow &currentThrow)
{
	// Plays throw based on what the player chose to throw at

	switch (currentThrow)
	{

	case SINGLE:
	{
		std::cout << player->getName() << " will throw for a single " << target << "..." << std::endl;

		player->setThrowPoints(throws.throwSingle(target, player->getSuccessRate())); // Throws for a single on the target based on player's success rate

		if (player->getThrowPoints() == target) // If player has hit target
		{
			std::cout << player->getName() << " has hit their target and scored " << player->getThrowPoints() << " points." << std::endl;
		}

		else // If player has not hit target
		{
			std::cout << player->getName() << " has missed their target and scored " << player->getThrowPoints() << " points." << std::endl;
		}

		break;
	}


	case DOUBLE:
	{
		std::cout << player->getName() << " will throw for a double " << target << "..." << std::endl;

		player->setThrowPoints(throws.throwDouble(target, player->getSuccessRate())); // Throws for a double on the target based on player's success rate

		if (player->getThrowPoints() == target) // If player has hit target
		{
			std::cout << player->getName() << " has hit their target and scored " << player->getThrowPoints() << " points." << std::endl;
		}

		else // If player has not hit target
		{
			std::cout << player->getName() << " has missed their target and scored " << player->getThrowPoints() << " points." << std::endl;
		}

		break;
	}


	case TREBLE:
	{
		std::cout << player->getName() << " will throw for a treble " << target << "..." << std::endl;

		player->setThrowPoints(throws.throwTreble(target, player->getSuccessRate()));  // Throws for a treble on the target based on player's success rate

		if (player->getThrowPoints() == target) // If player has hit target
		{
			std::cout << player->getName() << " has hit their target and scored " << player->getThrowPoints() << " points." << std::endl;
		}

		else // If player has not hit target
		{
			std::cout << player->getName() << " has missed their target and scored " << player->getThrowPoints() << " points." << std::endl;
		}

		break;
	}


	case INNERBULL:
	{
		std::cout << player->getName() << " will throw for a Bull..." << std::endl;

		player->setThrowPoints(throws.throwInnerBull(player->getSuccessRate())); // Throws for a bullseye based on player's success rate

		if (player->getThrowPoints() == 50) // If player has hit target
		{
			std::cout << player->getName() << " has hit the Bull and scored " << player->getThrowPoints() << " points." << std::endl;
			player->setBullCounter(player->getBullCounter() + 1);
		}

		else // If player has not hit target
		{
			std::cout << player->getName() << " has missed the Bull and scored " << player->getThrowPoints() << " points." << std::endl;
		}

		break;
	}


	case OUTERBULL:
	{
		std::cout << player->getName() << " will throw for the outer Bull..." << std::endl;

		player->setThrowPoints(throws.throwOuterBull(player->getSuccessRate())); // Throws for an outer bull based on player's success rate

		if (player->getThrowPoints() == 25) // If player has hit target
		{
			std::cout << player->getName() << " has hit the outer Bull and scored " << player->getThrowPoints() << " points." << std::endl;
		}

		else // If player has not hit target
		{
			std::cout << player->getName() << " has missed the outer Bull and scored " << player->getThrowPoints() << " points." << std::endl;
		}

		break;
	}


	default:
	{
		break;
	}
	}
}

void Interactive::throwDart(Player* &currentPlayer, Player &player1, Player &player2, Display display, CurrentThrow &currentThrow, Throw throws, int i)
{
	if (currentPlayer == &player1 || (currentPlayer == &player2 && twoPlayer))
	{
		getPlayerThrow(throwType, target, *currentPlayer); // If current player is user-controlled, ask them what they would like to throw at
	}

	display.displayScreen(player1, player2, gameCounter, setCounter); // Refreshes display

	std::cout << "Throw " << i + 1 << "..." << std::endl;

	currentPlayer->setThrowCounter(currentPlayer->getThrowCounter() + 1); // Adds one to player's throw counter

	if (currentPlayer == &player1 || (currentPlayer == &player2 && twoPlayer)) // If current player is user-controlled
	{
		setUpThrow(throwType, currentThrow); // Sets the current throw variable to be what the player has chosen
		playThrow(currentPlayer, throws, target, currentThrow); // Plays the throw based on the player's chosen target and their success rate
	}

	else if (currentPlayer == &player2 && !twoPlayer) // If current player is the AI
	{
		setUpThrow(currentPlayer, currentThrow); // Sets the player's current throw based on the optimal target
		playThrow(currentPlayer, throws, currentThrow); // Plays the throw based on the player's target and success rate
	}
}


void Interactive::updatePoints(Player* player, CurrentThrow &currentThrow)
{
	player->setTurnPoints(player->getTurnPoints() + player->getThrowPoints()); // Adds this throw's points onto this turn's points

	// If player has reduced their points below 0, they won't count
	if (player->getPoints() - player->getThrowPoints() < 0)
	{
		std::cout << player->getName() << " has reduced his score below 0, therefore his points for this turn will not count." << std::endl;

		player->setPoints(player->getPoints() + player->getTurnPoints()); // Resets points to how they were before this turn
	}

	// If player has reduced their points to 0 but didn't end on a double or bull, it won't count
	else if (player->getPoints() - player->getThrowPoints() == 0 && player->getThrowPoints() % 2 != 0)
	{
		std::cout << player->getName() << " has reduced his score to 0 but has not ended with a Double or a Bull, therefore his points for this turn will not count." << std::endl;
		player->setPoints(player->getPoints() + player->getTurnPoints()); // Resets points to how they were before this turn
	}

	// If player reduces their points to 1 and cannot win, it won't count
	else if (player->getPoints() - player->getThrowPoints() == 1)
	{
		std::cout << player->getName() << " has reduced his score to 1 and cannot win on this score, therefore his points for this turn will not count." << std::endl;
		player->setPoints(player->getPoints() + player->getTurnPoints()); // Resets points to how they were before this turn
	}

	// If points can be safely deducted, they are
	else
	{
		player->setPoints(player->getPoints() - player->getThrowPoints());
	}

	gameWon = checkWin(player); // Checks if player has won

	if (!gameWon) // If player hasn't won
	{
		std::cout << player->getName() << " now has " << player->getPoints() << " points." << std::endl << std::endl;

		player->setThrowPoints(0); // Resets player's point for the next throw
		currentThrow = NONE; // Resets the throw type
	}

	else // If player has won
	{
		std::cout << player->getName() << " has reduced his points to 0 and won the game!" << std::endl << std::endl;
	}
}

void Interactive::checkSetWon(Player &player1, Player &player2, Game game)
{
	if (player1.getGamesWon() == 3) // If player 1 has won the set
	{
		setWon(player1, game); // Increments and resets the appropriate counters
		setCounter += 1; // Adds one to the set counter
		gameCounter = 1; // Resets the game counter for the next set
	}

	else if (player2.getGamesWon() == 3) // If player 2 has won the set
	{
		setWon(player2, game); // Increments and resets the appropriate counters
		setCounter += 1; // Adds one to the set counter
		gameCounter = 1; // Resets the game counter for the next set
	}
}

#pragma endregion Functions used in the game loop