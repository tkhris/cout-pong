#include "Ball.h"

Ball::Ball()
{
	Ball_X = 40;
	Ball_Y = 12;
}


Ball::~Ball()
{
}

void Ball::moveBallUp()
{
	Ball_Y--;
}

void Ball::moveBallDown()
{
	Ball_Y++;
}

void Ball::moveBallLeft()
{
	Ball_X--;
}

void Ball::moveBallRight()
{
	Ball_X++;
}

int Ball::ballLocation(char plane)
{
	if (plane == 'x')
		return Ball_X;
	else
		return Ball_Y;
}

void Ball::setBallLoc(int x, int y)
{
	Ball_X = x;
	Ball_Y = y;
}