#include "Player.h"


Player::Player(std::string n, int r, int p, int g, int s)
{
	// Initialises variables

	name = n;
	successRate = r;
	points = p;
	gamesWon = g;
	setsWon = s;

	throwPoints = 0;
	target = 0;
	turn = 0;
	hasWon = false;
	throwCounter = 0;
	bullCounter = 0;
	turnPoints = 0; 
}

Player::~Player()
{
}


std::string Player::getName()
{
	return name;
}

void Player::setName(std::string n)
{
	name = n;
}

int Player::getSuccessRate()
{
	return successRate;
}

void Player::setSuccessRate(int r)
{
	successRate = r;
}

int Player::getPoints()
{
	return points;
}

void Player::setPoints(int p)
{
	points = p;
}

int Player::getThrowPoints()
{
	return throwPoints;
}

void Player::setThrowPoints(int p)
{
	throwPoints = p;
}

int Player::getTurnPoints()
{
	return turnPoints;
}

void Player::setTurnPoints(int p)
{
	turnPoints = p;
}

int Player::getTarget()
{
	target = points; // Sets target to equal the points the player has left

	return target;
}

int Player::getTurn()
{
	return turn;
}

void Player::setTurn(int t)
{
	turn = t;
}

bool Player::getHasWon()
{
	if (points == 0)
	{
		return true; // If player's points are 0, they have won
	}

	else
	{
		return false; // If player's points are not 0, they have not won
	}
}

int Player::getThrowCounter()
{
	return throwCounter;
}

void Player::setThrowCounter(int t)
{
	throwCounter = t;
}

int Player::getBullCounter()
{
	return bullCounter;
}

void Player::setBullCounter(int b)
{
	bullCounter = b;
}

int Player::getGamesWon()
{
	return gamesWon;
}

void Player::setGamesWon(int g)
{
	gamesWon = g;
}

int Player::getSetsWon()
{
	return setsWon;
}

void Player::setSetsWon(int s)
{
	setsWon = s;
}
