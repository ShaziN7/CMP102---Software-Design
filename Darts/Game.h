#pragma once


#include <iostream>
#include <string>

#include "Player.h"
#include "Throw.h"
#include "States.h"
#include "Display.h"


//class Display; // Forward declaration of Display class so it can be used


class Game
{

public:

	Game();
	Game(int, int); // Overloaded constructor receiving game and set counters
	~Game();


#pragma region Player Functions

	void getPlayerInfo(Player &player1, Display display); // For getting player details when there is a single player
	void getPlayerInfo(Player &player1, Player &player2, Display display); // For getting player details when there are two players
	void getWhoStarts(Player* &currentPlayer, Player &player1, Player &player2, Throw throws, Display display); // Asks who starts the game
	void switchPlayers(Player* &currentPlayer, Player &player1, Player &player2); // Switches players based on the current turn
	void setWon(Player &player, Game &game); // Increments and resets appropriate counters when someone has won a set

#pragma endregion Functions dealing with players in the game


#pragma region Throw Functions

	void setUpThrow(Player*, CurrentThrow &currentThrow); // Sets up throw when throw type is not yet known
	void setUpThrow(char, CurrentThrow &currentThrow); // Overloaded to set up throw when player is choosing a throw type
	int throwForFirst(Player, Throw); // Used when players are throwing to see who will go first

#pragma endregion Functions dealing with throws in the game


#pragma region Point Functions

	bool checkWin(Player*); // Checks if there has been a win
	bool checkGameEnded(Player &player1, Player &player2); // Checks if the game has ended

#pragma endregion Functions dealing with points in the game
	

#pragma region Counter Functions

	int getGameCounter(); // Gets how many games have played
	void setGameCounter(int); // Sets how many games have played
	int getSetCounter(); // Gets how many sets have played
	void setSetCounter(int); // Sets how many sets have played
	void incrementGamesWon(Player &player1, Player &player2); // Checks who has won and increments their Games Won counter

#pragma endregion Functions dealing with counters in the game
	


protected:

	int p1Throw; // For outputting what player 1 scored
	int p2Throw; // For outputting what player 2 scored
	int starts; // For storing input for who starts
	int choice; // For temporarily storing input from player
	std::string name; // For storing input for player's name


#pragma region Throw Variables

	int target; // Target to throw at

#pragma endregion Variables dealing with throws in the game


#pragma region Counter And Point Variables

	bool gameWon; // If game has been won
	int gameCounter; // How many games have played
	int setCounter; // How many sets have played

#pragma endregion Variables dealing with counters and points in the game


#pragma region Score Arrays

	int treblesArray[20] = { 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48, 51, 54, 57, 60 }; // Array storing all values that a Treble Throw might score
	int doublesArray[20] = { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40 }; // Array storing all values that a Double Throw might score
	int singlesArray[20] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 }; // Array storing all values that a Single Throw might score

#pragma endregion Arrays holding the possible scores of each type of throw
};

