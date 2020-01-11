#pragma once

#include <iostream>
#include <string>

#include "Player.h"


class Display
{

public:

	Display();
	~Display();


	void initialDisplay(); // The initial screen to be displayed with a title
	void displayScreen(Player, Player, int, int); // The main screen that will be displayed
	void endScreen(Player, Player, int, int); // Will be displayed once the game is over
	void simulationResults(Player, Player, int[2][8], int); // Will be used to show the results of the simulation
};
