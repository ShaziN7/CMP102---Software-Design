#pragma once

class Throw
{

public:
	Throw();
	~Throw();

	int throwInnerBull(int); // Throw of the inner bull
	int throwOuterBull(int); // Throw for the outer bull
	int throwSingle(int, int); // Throw for a 

	int throwTreble(int, int); // Throw for a treble
	int throwDouble(int, int); // Throw for a double

private:

	// Board neighbours ignoring slot zero
	int board[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
						 {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };
};