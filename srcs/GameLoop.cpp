
#include "GameLoop.hpp"


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

void	gameLoop( int x_max, int y_max, int lib)
{
	int score = 0;
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
				delete sdl;
				sdl = loadLib("lib1.so", hndl, x_max, y_max, oldDir);
				dir = oldDir;
				break;
			case lib2:
				delete sdl;
				sdl = loadLib("lib2.so", hndl, x_max, y_max, oldDir);
				dir = oldDir;
				break;
			case lib3:
				delete sdl;
				sdl = loadLib("lib3.so", hndl, x_max, y_max, oldDir);
				dir = oldDir;
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