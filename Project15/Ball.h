#pragma once

#include "Paddle.h"

class Ball
{
private:
	int Ball_X;
	int Ball_Y;

public:
	Ball();
	~Ball();
	void moveBallUp();
	void moveBallDown();
	void moveBallLeft();
	void moveBallRight();
	int ballLocation(char);
	void setBallLoc(int, int);
};