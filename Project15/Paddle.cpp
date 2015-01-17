#include "Paddle.h"

Paddle::Paddle(int player): playerNumber(player)
{
	if (playerNumber == 1)
	{
		Paddle_X = 4;
		Paddle_Y = 11;
		Score = 0;
	}
	else
	{
		Paddle_X = 77;
		Paddle_Y = 11;
		Score = 0;
	}
}

Paddle::~Paddle()
{
}

void Paddle::movePaddleUp()
{
	if (Paddle_Y > 3)
		Paddle_Y--;
}

void Paddle::movePaddleDown()
{
	if (Paddle_Y < 18)
		Paddle_Y++;
}

int Paddle::paddleLocation(char plane)
{
	if (plane == 'y')
		return Paddle_Y;
	else
		return Paddle_X;
}

void Paddle::playerScored()
{
	Score++;
}

int Paddle::getScore()
{
	return Score;
}