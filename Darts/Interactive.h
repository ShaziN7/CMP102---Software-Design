#pragma once

#include "Game.h"
#include "Display.h"


class Interactive: public Game
{

public:

	Interactive();
	~Interactive();


#pragma region Interactive Functions

	void getPlayerThrow(char &throwType, int &target, Player player); // Asks player what they would like to throw at
	bool getTwoPlayers(); // Asks if player wants to play by themselves or 2 player
	bool getGameEnded(); // Gets if game has ended
	void setGameEnded(bool); // Sets if game has ended
	int getGameCounter(); // Gets the game counter
	int getSetCounter(); // Sets the game counter

#pragma endregion Functions for the Interactive game


#pragma region Main Interactive Game Loop Functions

	void setUpGame(Display display, Player &player1, Player &player2, Player* &currentPlayer, Throw throws); // Gets pre-game info such as the player information and who starts
	void playGame(Player* &currentPlayer, Display display, Player &player1, Player &player2, Game game, CurrentThrow &currentThrow, Throw throws); // Plays the main game loop
	void playThrow(Player*, Throw, CurrentThrow &currentThrow); // Plays throw for the AI, working out the optimal target
	void playThrow(Player*, Throw, int, CurrentThrow &currentThrow); // Plays throw when throw type is chosen by the player
	void throwDart(Player* &currentPlayer, Player &player1, Player &player2, Display display, CurrentThrow &currentThrow, Throw throws, int i); // Throws and deals with the dart for one throw
	void updatePoints(Player*, CurrentThrow &currentThrow); // Updates points
	void checkSetWon(Player &player1, Player &player2, Game game); // Checks if player has won set and increments/resets appropriate variables
	
#pragma endregion Functions used in the game loop


private:

	char throwType; // Stores what type of throw the player has chosen
	int target; // Stores that target that the player has chosen
	bool twoPlayer; // If the game will be two player
	bool gameEnded; // If the game has ended
	int gameCounter; // How many games have played
	int setCounter; // How many sets have played
};

