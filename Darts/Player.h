#pragma once

#include <iostream>


class Player
{

public:

	Player(std::string, int, int, int, int);
	~Player();



#pragma region Getters

	std::string getName(); // Gets the player's name
	int getSuccessRate(); // Gets the player's success rate
	int getPoints(); // Gets the player's points
	int getThrowPoints(); // Gets the player's points for this throw
	int getTurnPoints(); // Gets the player's points for this turn
	int getTarget(); // Gets the player's target
	int getTurn(); // Gets what turn the player is on
	bool getHasWon(); // Gets if the player has won
	int getThrowCounter(); // Gets the player's throw counter
	int getBullCounter(); // Gets the player's bull counter
	int getGamesWon(); // Gets how many games the player has won
	int getSetsWon(); // Gets how many sets the player has won

#pragma endregion Functions to allow the program to access private player variables


#pragma region Setters

	void setName(std::string); // Sets the player's name
	void setSuccessRate(int); // Sets the player's success rate
	void setPoints(int); // Sets the player's points
	void setThrowPoints(int); // Sets the player's points for this throw
	void setTurnPoints(int); // Sets the player's points for this turn
	void setTurn(int); // Sets what turn the player is on
	void setThrowCounter(int); // Sets the player's throw counter
	void setBullCounter(int); // Sets the player's bull counter
	void setGamesWon(int); // Sets how many games the player has won
	void setSetsWon(int); // Sets how many sets the player has won

#pragma endregion Functions to allow the program to edit private player variables


private:

	std::string name; // Player's name
	int successRate; // Player's success rate, how likely they are to hit their target
	int points; // Player's points
	int throwPoints; // Player's points for this throw
	int turnPoints; // Player's points for this turn
	int target; // Player's target
	int turn; // What turn the player is on
	bool hasWon; // If the player has won
	int throwCounter; // How many throws the player has had
	int bullCounter; // How many bullseyes the player has scored
	int gamesWon; // How many games the player has won
	int setsWon; // How many sets the player has won
};

