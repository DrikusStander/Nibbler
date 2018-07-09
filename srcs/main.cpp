
#include "main.hpp"
#include "Snake.hpp"
#include "SDLclass.hpp"
#include "Fruit.hpp"
#include <unistd.h>

int main(int ac, char **av)
{
	if ( ac != 3)
	{
		std::cout << "usage: ./Nibler <int x> <int y> " << std::endl;
		return(-1);
	}
	else
	{
		int x_max;
		int y_max;
		try
		{
			x_max = std::stoi(av[1], NULL, 10);
			y_max = std::stoi(av[2], NULL, 10);
		}
		catch (...)
		{
			std::cout << "usage: ./Nibler <int x> <int y>" << std::endl;
		}
		if (x_max < X_MIN || x_max > X_MAX || y_max < Y_MIN || y_max > Y_MAX )
		{
			std::cout << "X min val: " << X_MIN << std::endl;
			std::cout << "X max val: " << X_MAX << std::endl;
			std::cout << "Y min val: " << Y_MIN << std::endl;
			std::cout << "Y max val: " << Y_MAX << std::endl;
			return(-1);
		}
		srand(time(NULL));
		Direction dir;
		Snake snake(x_max / 2, (y_max -SCORE_AREA) / 2);
		Fruit fruit(x_max, y_max - SCORE_AREA);
		int gameover = 0;
		SDLclass sdl(x_max, y_max);
		while (!gameover)
		{
			dir = sdl.getInput();
			if (dir == quit)
				gameover = 1;
			snake.changeDirection(dir);

			snake.moveSnake();
			
			// clears the canvas draws new items to canvas and renders canvas to screen
			sdl.clearRender();
			snake.drawSnake(&sdl);
			fruit.drawFruit(&sdl);
			sdl.drawBorders(x_max, y_max);
			sdl.render();

			if (fruit.CheckFruitEaten(snake.getHeadX(), snake.getHeadY()))
			{
				fruit.newFruit();
				snake.growSnake();
			}
			if (snake.checkCollision(x_max, y_max - SCORE_AREA) == 1)
			{
				break;
				return(0);
			}
			
		}
	}
	sleep(3);
	return(0);
}