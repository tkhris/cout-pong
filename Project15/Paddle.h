#pragma once

#include "Ball.h"

class Paddle
{
private:
	const int playerNumber;
	int Paddle_X;
	int Paddle_Y;
	int Score;

public:
	Paddle(int);
	~Paddle();
	void movePaddleUp();
	void movePaddleDown();
	int paddleLocation(char);
	void playerScored();
	int getScore();
};

