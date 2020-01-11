#include <cstdlib>    // random numbers header file
#include <ctime>	// used to get date and time information

#include "Throw.h"


Throw::Throw()
{
}

Throw::~Throw()
{
}


int Throw::throwInnerBull(int accuracy)
{
	// Throw for the inner bull based on player's success rate (accuracy)

	int r = rand() % 100; // Gets random number between 0 and 100

	if (r < (accuracy - 20))
	{
		return 50; // Player has hit the bull
	}

	else if (r < accuracy)
	{
		return 25; // Player has missed and hit the outer bull
	}

	else
	{
		return 1 + rand() % 20; // Player has missed and hit something else
	}
}

int Throw::throwOuterBull(int accuracy)
{
	// Throw for the inner bull based on player's success rate (accuracy)

	int r = rand() % 100; // Gets random number between 0 and 100

	if (r < (accuracy - 20))
	{
		return 25; // Player has hit the outer bull
	}

	else if (r < accuracy)
	{
		return 50; // Player has missed and hit the inner bull
	}

	else
	{
		return 1 + rand() % 20; // Player has missed and hit something else
	}
}

int Throw::throwSingle(int target, int accuracy) {

	// Throw for a single based on player's success rate (accuracy) and target

	int r = rand() % 100; // Gets random number between 0 and 100

		// 1 to 20 single
	if (r < accuracy)
	{
		return target; // Player has hit their target
	}

	else if (r < (accuracy - 4))
	{
		return board[0][target]; // Player has missed their target and hit its board neighbour
	}

	else if (r < (accuracy - 8))
	{
		return board[1][target]; // Player has missed their target and hit its board neighbour
	}

	else if (r < (accuracy - 10))
	{
		return 3 * target; // Player has missed their target and hit a treble of their target
	}

	else
	{
		return 2 * target; // Player has missed their target and hit a double of their target
	}
}

int Throw::throwTreble(int target, int accuracy)
{
	// Throw for a treble based on player's success rate (accuracy) and target

	int r = rand() % 100; // Gets random number between 0 and 100

	if (r < accuracy)
	{
		return 3 * target; // Player has hit their target
	}

	else if (r < 90)
	{
		return target; // Player has missed their target and hit a single of their target
	}

	else if (r < 93)
	{
		return 3 * board[0][target]; // Player has missed their target and hit its board neighbour
	}

	else if (r < 96)
	{
		return 3 * board[1][target]; // Player has missed their target and hit its board neighbour
	}

	else if (r < 98)
	{
		return board[0][target]; // Player has missed their target and hit a single of its board neighbour
	}

	else
	{
		return board[1][target]; // Player has missed their target and hit a single of its board neighbour
	}
}

int Throw::throwDouble(int target, int accuracy)
{
	// Throw for a double based on player's success rate (accuracy) and target

	int r = rand() % 100; // Gets random number between 0 and 100

	if (r < accuracy) // has hit target
	{
		return 2 * target; // Player has hit their target
	}

	else if (r < target + 5)
	{
		return 0; // Player has completely missed
	}

	else if (r < target + 10)
	{
		return target; // Player has missed their target and hit a single of their target
	}

	else if (r < target + 13)
	{
		return 2 * board[0][target]; // Player has missed their target and hit a double of its board neighbour
	}

	else if (r < target + 16)
	{
		return 2 * board[1][target]; // Player has missed their target and hit a double of its board neighbour
	}

	else if (r < target + 18)
	{
		return board[0][target]; // Player has missed their target and hit a single of its board neighbour
	}
		
	else
	{
		return board[1][target]; // Player has missed their target and hit a single of its board neighbour
	}
}
