#pragma once

#include "Game.h"
#include "Display.h"


class Simulation: public Game
{

public:

	Simulation();
	~Simulation();


#pragma region Simulation Functions

	int getSimNum(); // Gets how many matches to simulate
	bool getGameEnded(); // Gets if game has ended
	void setGameEnded(bool); // Sets if game has ended

#pragma endregion Functions for the Interactive game


#pragma region Main Simulation Game Loop Functions

	void setUpGame(Player &player1, Player &player2, Display display, Player* &currentPlayer, Throw throws); // Gets pre-game info such as the player information and who starts
	void playGame(Player* &currentPlayer, CurrentThrow &currentThrow, Throw throws, Player &player1, Player &player2, Game game); // Plays the main game loop
	void playThrow(Player*, Throw, CurrentThrow &currentThrow); // Plays throw based on optimal target and with no output
	void updatePoints(Player*, CurrentThrow &currentThrow); // Updates points
	void incrementScores(Player player1, Player player2); // Increments the scores array
	void incrementSets(Player &player1, Player &player2); // Increments the sets variable
	void displayResults(Player player1, Player player2, Display display); // Displays the results of the simulation

#pragma endregion Functions used in the game loop


private:

	int scores[2][8] = { 0 }; // 2D array to store all of the results of the simulation, makes it easy to calculate results and frequencies in the end
	int simNum; // How many matches to simulate
	bool gameEnded; // If the game has ended
};
