
#include "main.hpp"
#include "Snake.hpp"
#include "Interface.hpp"
#include "Fruit.hpp"
#include <unistd.h>

int SCORE_AREA = 20;

SDLinterface * loadLib(std::string str, void *hndl , int x_max, int y_max, Direction dir)
{
	if (hndl)
	{
		if (dlclose(hndl))
		{
			std::cerr << dlerror() << std::endl;
			exit(-1);
		}
	}
	hndl = dlopen(str.c_str(), RTLD_NOW);
	if (hndl == NULL)
	{
		std::cerr << dlerror() << std::endl;
		exit(-1);
	}
	void *mkr = dlsym(hndl, "maker");
	typedef SDLinterface *(*fptr)(int, int, Direction);
	fptr func = reinterpret_cast<fptr>(reinterpret_cast<long>(mkr));
	return(func(x_max, y_max, dir));
}

int x_start(int x_max)
{
	int start_x = x_max / 2;
	while (start_x % SNAKE_SIZE)
	{
		start_x++;
	}
	return(start_x);
}

int y_start(int y_max)
{
	int start_y = y_max / 2;
	while ((y_max - SCORE_AREA) % SNAKE_SIZE)
	{
		SCORE_AREA++;
	}

	while (start_y % SNAKE_SIZE)
	{
		start_y++;
	}
	return(start_y);
}

int main(int ac, char **av)
{
	if ( ac != 4)
	{
		std::cout << "usage: ./Nibler <int x> <int y> <int 1-3 [lib]>" << std::endl;
		return(-1);
	}
	else
	{
		int x_max;
		int y_max;
		int score = 0;
		int lib;
		try
		{
			x_max = std::stoi(av[1], NULL, 10);
			y_max = std::stoi(av[2], NULL, 10);
			lib = std::stoi(av[3], NULL, 10);
		}
		catch (...)
		{
			std::cout << "usage: ./Nibler <int x> <int y> <int 1-3 [lib]>" << std::endl;
		}
		if (x_max > X_MAX || y_max > Y_MAX )
		{
			std::cout << "Map size to Big" << std::endl;
			std::cout << "X max val: " << X_MAX << std::endl;
			std::cout << "Y max val: " << Y_MAX << std::endl;
			return(-1);
		}
		else if (x_max < X_MIN || y_max < Y_MIN )
		{
			std::cout << "Map size to small" << std::endl;
			std::cout << "X min val: " << X_MIN << std::endl;
			std::cout << "Y min val: " << Y_MIN << std::endl;
			return(-1);
		}
		else if (lib < 1 || lib > 3)
		{
			std::cout << "Invalid Library selected" << std::endl;
			std::cout << "usage: ./Nibler <int x> <int y> <int 1-3 [lib]>" << std::endl;
		}

		srand(time(NULL));
		Direction dir = right;
		Direction oldDir = right;
		
		Snake snake(x_start(x_max), y_start(y_max));
		Fruit fruit(x_max, y_max - SCORE_AREA);
		int gameover = 0;
		void *hndl = NULL;
		SDLinterface *sdl;
		if (lib == 1)
			sdl = loadLib("lib1.so", hndl, x_max, y_max, dir);
		else if (lib == 2)
			sdl = loadLib("lib2.so", hndl, x_max, y_max, dir);
		else
			sdl = loadLib("lib3.so", hndl, x_max, y_max, dir);
		while (!gameover)
		{
			dir = sdl->getInput();
			switch(dir)
			{
				case lib1:
					sdl = loadLib("lib1.so", hndl, x_max, y_max, oldDir);
					break;
				case lib2:
					sdl = loadLib("lib2.so", hndl, x_max, y_max, oldDir);
					break;
				case lib3:
					sdl = loadLib("lib3.so", hndl, x_max, y_max, oldDir);
					break;
				case quit:
					gameover = 1;
					break;
				case up:
				case down:
				case left:
				case right:
					oldDir = dir;
					snake.changeDirection(dir);
					break;
			}
			snake.moveSnake();
			if (snake.checkCollision(x_max, y_max - SCORE_AREA) == 1)
			{
				sdl->playSound(Colide);
				usleep(400000);
				break;
			}
			sdl->clearRender();
			snake.drawSnake(sdl);
			fruit.drawFruit(sdl);
			sdl->drawBorders(x_max, y_max, score);
			sdl->render();

			if (fruit.CheckFruitEaten(snake.getHeadX(), snake.getHeadY()))
			{
				sdl->playSound(Chew);
				fruit.newFruit();
				snake.growSnake();
				score++;
			}
		}
		if (sdl)
			delete sdl;
	}
	return(0);
}