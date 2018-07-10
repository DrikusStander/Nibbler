
#include "main.hpp"
#include "Snake.hpp"
#include "Interface.hpp"
#include "Fruit.hpp"
#include <unistd.h>

int SCORE_AREA = 20;

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
		int score = 0;
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
		int start_x = x_max / 2;
		int start_y = y_max / 2;
		while ((y_max - SCORE_AREA) % SNAKE_SIZE)
		{
			SCORE_AREA++;
		}
		srand(time(NULL));
		Direction dir;
		while (start_y % SNAKE_SIZE)
		{
			start_y++;
		}
		while (start_x % SNAKE_SIZE)
		{
			start_x++;
		}
		Snake snake(start_x, start_y);
		Fruit fruit(x_max, y_max - SCORE_AREA);
		int gameover = 0;

		// SDLclass sdl(x_max, y_max);
		
		void *hndl = dlopen("lib1.so", RTLD_NOW);
		if (hndl == NULL)
		{
			std::cerr << dlerror() << std::endl;
			exit(-1);
		}
		void *mkr = dlsym(hndl, "maker");
		typedef SDLinterface *(*fptr)(int, int);
		fptr func = reinterpret_cast<fptr>(reinterpret_cast<long>(mkr));
		SDLinterface *sdl = func(x_max, y_max);
		while (!gameover)
		{
			dir = sdl->getInput();
			if (dir == lib1)
			{
				if (dlclose(hndl))
				{
					std::cerr << dlerror() << std::endl;
					exit(-1);
				}
				hndl = dlopen("lib1.so", RTLD_NOW);
				if (hndl == NULL)
				{
					std::cerr << dlerror() << std::endl;
					exit(-1);
				}
				mkr = dlsym(hndl, "maker");
				fptr func = reinterpret_cast<fptr>(reinterpret_cast<long>(mkr));
				sdl = func(x_max, y_max);
			}
			else if (dir == lib2)
			{
				if (dlclose(hndl))
				{
					std::cerr << dlerror() << std::endl;
					exit(-1);
				}
				hndl = dlopen("lib2.so", RTLD_NOW);
				if (hndl == NULL)
				{
					std::cerr << dlerror() << std::endl;
					exit(-1);
				}
				mkr = dlsym(hndl, "maker");
				fptr func = reinterpret_cast<fptr>(reinterpret_cast<long>(mkr));
				sdl = func(x_max, y_max);
			}
			else if (dir == lib3)
			{
				if (dlclose(hndl))
				{
					std::cerr << dlerror() << std::endl;
					exit(-1);
				}
				hndl = dlopen("lib3.so", RTLD_NOW);
				if (hndl == NULL)
				{
					std::cerr << dlerror() << std::endl;
					exit(-1);
				}
				mkr = dlsym(hndl, "maker");
				fptr func = reinterpret_cast<fptr>(reinterpret_cast<long>(mkr));
				sdl = func(x_max, y_max);
			}
			else if (dir == quit)
				gameover = 1;
			snake.changeDirection(dir);

			snake.moveSnake();
			
			// clears the canvas draws new items to canvas and renders canvas to screen
			sdl->clearRender();
			snake.drawSnake(sdl);
			fruit.drawFruit(sdl);
			sdl->drawBorders(x_max, y_max, score);
			sdl->render();

			if (fruit.CheckFruitEaten(snake.getHeadX(), snake.getHeadY()))
			{
				fruit.newFruit();
				snake.growSnake();
				score++;
			}
			if (snake.checkCollision(x_max, y_max - SCORE_AREA) == 1)
			{
				break;
				return(0);
			}
			
		}
	}
	// delete sdl;
	sleep(3);
	return(0);
}