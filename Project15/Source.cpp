#include <iostream>
#include <conio.h>
#include <ctime>
#include <Windows.h>
#include <iomanip>
#include <stdio.h>
#include "Paddle.h"
#include "Ball.h"

void drawGame(Paddle &Player1, Paddle &Player2, Ball &Ball);
void movePaddle(Paddle &Player1, Paddle &Player2);
void moveBall(Paddle &Player1, Paddle &Player2, Ball &Ball);

int main()
{
	Paddle Player1(1);
	Paddle Player2(2);
	Ball Ball;

	const int FRAMES_PER_SEC = 8;
	double time_counter = 0;
	bool gameIsRunning = true;

	clock_t this_time = clock();
	clock_t last_time = this_time;

	while (gameIsRunning)
	{
		this_time = clock();
		time_counter += (double)(this_time - last_time);
		last_time = this_time;

		if (time_counter > (double)(CLOCKS_PER_SEC / FRAMES_PER_SEC))
		{
			time_counter -= (double)(CLOCKS_PER_SEC / FRAMES_PER_SEC);
			// game code, screen refreshes everytime this area is reached
			// screen size is 80 x 25
			drawGame(Player1, Player2, Ball);
		}

		if (Player1.getScore() == 10 || Player2.getScore() == 10)
		{
			system("CLS");
			std::cout << (Player1.getScore() == 10) ? "Player 1 WINS\n" : "Player 2 Wins\n";
			system("PAUSE");
			gameIsRunning = 0;
		}
	}
	return 0;
}

void drawGame(Paddle &Player1, Paddle &Player2, Ball &Ball)
{
	int Cusor_Row = 0;
	bool player1Drawn = 0;
	bool ballDrawn = 0;

	static int time = 0;
	static int timeDisplay = 0;

	if (time % 8 == 0)
		timeDisplay++;
	
	time++;

	system("CLS");
	
	std::cout << " " << timeDisplay;
	std::cout << std::endl << "PLAYER 1 : " << Player1.getScore() << std::setw(60) << "PLAYER 2 : " << Player2.getScore();

	while (Cusor_Row < 22)
	{
		if (Player1.paddleLocation('y') == Cusor_Row ||
			 Player1.paddleLocation('y') + 1 == Cusor_Row ||
			 Player1.paddleLocation('y') + 2 == Cusor_Row ||
			 Player1.paddleLocation('y') + 3 == Cusor_Row)
		{
			std::cout << std::setw(Player1.paddleLocation('x')) << "|]";
			player1Drawn = 1;
		}

		if (Ball.ballLocation('y') == Cusor_Row)
		{
			std::cout << (player1Drawn ? std::setw(Ball.ballLocation('x') - Player1.paddleLocation('x'))
									   : std::setw(Ball.ballLocation('x'))) << "0";
			ballDrawn = 1;
		}
		
		if	(Player2.paddleLocation('y') == Cusor_Row ||
				  Player2.paddleLocation('y') + 1 == Cusor_Row || 
				  Player2.paddleLocation('y') + 2 == Cusor_Row || 
				  Player2.paddleLocation('y') + 3 == Cusor_Row)
		{
			if (!ballDrawn)
				std::cout << (player1Drawn ? std::setw(Player2.paddleLocation('x') - Player1.paddleLocation('x'))
				: std::setw(Player2.paddleLocation('x'))) << "[|";
			else
				std::cout << (std::setw(Player2.paddleLocation('x') - Ball.ballLocation('x'))) << "[|";
		}
		
		
			std::cout << std::endl;
			Cusor_Row++;
			player1Drawn = 0;
			ballDrawn = 0;
			if (Cusor_Row == 1 || Cusor_Row == 22)
			{
				std::cout << " ";
				for (int i = 0; i < 78; i++)
					std::cout << "_";
			}
	}
	static int count = 1;
	
	moveBall(Player1, Player2, Ball);

	if (count >= 3)
	{
		movePaddle(Player1, Player2);
		count = 1;
	}

	count++;
}

void movePaddle(Paddle &Player1, Paddle &Player2)
{
	if (GetAsyncKeyState(VK_UP))
	{
		Player2.movePaddleUp();
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		Player2.movePaddleDown();
	}
	else if (GetAsyncKeyState(VK_SHIFT))
	{
		Player1.movePaddleUp();
	}
	else if (GetAsyncKeyState(VK_CONTROL))
	{
		Player1.movePaddleDown();
	}
	/*else if (GetAsyncKeyState(VK_UP) && GetAsyncKeyState(VK_SHIFT)) // Up and SHIFT
	{
	Player2.movePaddleUp();
	Player1.movePaddleUp();
	}
	else if (GetAsyncKeyState(VK_UP) && GetAsyncKeyState(VK_CONTROL)) // Up and CONTROL
	{
	Player2.movePaddleUp();
	Player1.movePaddleDown();
	}
	else if (GetAsyncKeyState(VK_DOWN) && GetAsyncKeyState(VK_SHIFT)) // Down and SHIFT
	{
	Player2.movePaddleDown();
	Player1.movePaddleUp();
	}
	else if (GetAsyncKeyState(VK_DOWN) && GetAsyncKeyState(VK_CONTROL)) // Down and CONTROL
	{
	Player2.movePaddleDown();
	Player1.movePaddleDown();
	}*/
}

void moveBall(Paddle &Player1, Paddle &Player2, Ball &Ball)
{
	static bool xRight = 0;
	static bool yUp = 0;

	if (Ball.ballLocation('x') <= 4) // ball scores left
	{
		Player2.playerScored();
		Ball.setBallLoc(40, 12);
		yUp = !yUp;
	}
	else if (Ball.ballLocation('x') >= 76) // ball scores right
	{
		Player1.playerScored();
		Ball.setBallLoc(40, 12);
		yUp = !yUp;
	}
	else if ((Ball.ballLocation('x') == 5) &&
			((Ball.ballLocation('y') >= Player1.paddleLocation('y')) &&
			 (Ball.ballLocation('y') <= (Player1.paddleLocation('y') + 3)))) // ball hits left paddle
	{
		xRight = 1;
	}
	else if ((Ball.ballLocation('x') == 75) &&
			((Ball.ballLocation('y') >= Player2.paddleLocation('y')) &&
			 (Ball.ballLocation('y') <= (Player2.paddleLocation('y') + 3)))) // ball hits right paddle
	{
		xRight = 0;
	}

	if (Ball.ballLocation('y') <= 2) // ball hits top
	{
		yUp = 0;
	}
	else if (Ball.ballLocation('y') >= 21) // ball hits bottom
	{
		yUp = 1;
	}
	
	if (xRight == 0 && yUp == 0)
	{
		Ball.moveBallLeft();
		Ball.moveBallDown();
	}
	else if (xRight == 0 && yUp == 1)
	{
		Ball.moveBallLeft();
		Ball.moveBallUp();
	}
	else if (xRight == 1 && yUp == 0)
	{
		Ball.moveBallRight();
		Ball.moveBallDown();
	}
	else if (xRight == 1 && yUp == 1)
	{
		Ball.moveBallRight();
		Ball.moveBallUp();
	}
}