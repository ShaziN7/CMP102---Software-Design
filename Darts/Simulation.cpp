#include "Simulation.h"


Simulation::Simulation()
{
	gameEnded = false;
}

Simulation::~Simulation()
{
}


#pragma region Simulation Functions

int Simulation::getSimNum()
{
	return simNum; // Number of matches to simulate
}

bool Simulation::getGameEnded()
{
	return gameEnded;
}

void Simulation::setGameEnded(bool e)
{
	gameEnded = e;
}

#pragma endregion Functions for the Interactive game


#pragma region Main Simulation Game Loop Functions

void Simulation::setUpGame(Player &player1, Player &player2, Display display, Player* &currentPlayer, Throw throws)
{
	getPlayerInfo(player1, player2, display); // Gets player names and success rates

	display.initialDisplay(); // Refreshes display

	getWhoStarts(currentPlayer, player1, player2, throws, display); // Gets which player will start

	std::cout << std::endl << "How many matches would you like to simulate? ";
	std::cin >> simNum;

	// Limits simulation to between 1 and 10,000 matches
	while (simNum <= 0 || simNum > 10000)
	{
		std::cout << "Sorry, please enter a number between 1 and 10,000: ";
		std::cin >> simNum;
	}
}

void Simulation::playGame(Player* &currentPlayer, CurrentThrow &currentThrow, Throw throws, Player &player1, Player &player2, Game game)
{
	bool won = checkWin(currentPlayer); // Checks if player has won

	while (!won) // While no-one has won
	{
		for (int i = 0; i < 3; i++) // For each dart this turn
		{
			currentPlayer->setThrowCounter(currentPlayer->getThrowCounter() + 1); // Increments the player's throw counter
			setUpThrow(currentPlayer, currentThrow); // Does a linear search through each score array to see if it contains the target
			playThrow(currentPlayer, throws, currentThrow); // Takes throw based on throw type and target
			updatePoints(currentPlayer, currentThrow); // Updates the player's points
			won = checkWin(currentPlayer); // Checks if the player has won

			if (won)
			{
				break; // If the player has won, stop throwing
			}
		}

		currentPlayer->setTurnPoints(0); // Reset player's turn points when their turn is over

		currentPlayer->setTurn(currentPlayer->getTurn() + 1); // Increment the player's turn number

		switchPlayers(currentPlayer, player1, player2); // It is now the other player's turn
	}

	incrementGamesWon(player1, player2); // Checks who has won and increments their Games Won counter

	setGameCounter(getGameCounter() + 1); // Increments the game counter

	if (player1.getGamesWon() == 3)
	{
		setWon(player1, game); // If player 1 has won 3 games, they win the set
	}

	else if (player2.getGamesWon() == 3)
	{
		setWon(player2, game); // If player 2 has won 3 games, they win the set
	}

	gameEnded = checkGameEnded(player1, player2); // Check if game has ended
}

void Simulation::playThrow(Player* player, Throw throws, CurrentThrow &currentThrow)
{
	// Plays throw based on optimal target and with no output

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

			player->setThrowPoints(throws.throwSingle(target, player->getSuccessRate())); // Throws for a single on the target based on player's success rate

			break;
		}

		case SINGLE20: // If throw type is Single-20
		{
			target = 20; // Overrides target to equal 20

			player->setThrowPoints(throws.throwSingle(target, player->getSuccessRate())); // Throws for a single 20 based on player's success rate

			break;
		}

		case DOUBLE: // If throw type is Double
		{
			target = player->getTarget() / 2; // Sets throw target to equal half of the player's points remaining

			player->setThrowPoints(throws.throwDouble(target, player->getSuccessRate())); // Throws for a double on the target based on player's success rate

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

			player->setThrowPoints(throws.throwTreble(target, player->getSuccessRate())); // Throws for a treble on the target based on player's success rate

			break;
		}

		case INNERBULL: // If throw type is Inner Bull
		{
			player->setThrowPoints(throws.throwInnerBull(player->getSuccessRate())); // Throws for a bullseye based on player's success rate

			if (player->getThrowPoints() == 50) // If player has hit target
			{
				player->setBullCounter(player->getBullCounter() + 1); // Increments the bull counter
			}

			break;
		}

		case OUTERBULL: // If throw type is Outer Bull
		{
			player->setThrowPoints(throws.throwOuterBull(player->getSuccessRate())); // Throws for an outer bull based on player's success rate

			break;
		}

		case 0: default:
			break;
		}
}

void Simulation::updatePoints(Player* player, CurrentThrow &currentThrow)
{
	player->setTurnPoints(player->getTurnPoints() + player->getThrowPoints()); // Adds this throw's points onto this turn's points

	 // If player has reduced their points below 0, they won't count
	if (player->getPoints() - player->getThrowPoints() < 0)
	{
		player->setPoints(player->getPoints() + player->getTurnPoints()); // Resets points to how they were before this turn
	}

	// If player has reduced their points to 0 but didn't end on a double or bull, it won't count
	else if (player->getPoints() - player->getThrowPoints() == 0 && player->getThrowPoints() % 2 != 0)
	{
		player->setPoints(player->getPoints() + player->getTurnPoints()); // Resets points to how they were before this turn
	}

	// If player reduces their points to 1 and cannot win, it won't count
	else if (player->getPoints() - player->getThrowPoints() == 1)
	{
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
		player->setThrowPoints(0); // Resets player's point for the next throw
		currentThrow = NONE; // Resets the throw type
	}
}

void Simulation::incrementScores(Player player1, Player player2)
{
	scores[0][player1.getSetsWon()] += 1; // Increments player 1's score in the array
	scores[1][player2.getSetsWon()] += 1; // Increments player 2's score in the array
}

void Simulation::incrementSets(Player &player1, Player &player2)
{
	player1.setSetsWon(0); // Resets player 1's sets won for the next match
	player2.setSetsWon(0); // Resets player 2's sets won for the next match
}

void Simulation::displayResults(Player player1, Player player2, Display display)
{
	display.simulationResults(player1, player2, scores, simNum); // Displays the simulation results at the end
}

#pragma endregion Functions used in the game loop