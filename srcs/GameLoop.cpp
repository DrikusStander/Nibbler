
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

	switch (lib)
	{
		case 1:
			sdl = loadLib("lib1.so", hndl, x_max, y_max, dir);
			break;
		case 2:
			sdl = loadLib("lib2.so", hndl, x_max, y_max, dir);
			break;
		case 3:
			sdl = loadLib("lib3.so", hndl, x_max, y_max, dir);
			break;
	}
	int countNum = 50;
	Obstacles obs[countNum];
	for (int i = 0; i < countNum; i++)
		obs[i] = Obstacles(x_max, y_max - SCORE_AREA);

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
		for (int i = 0; i < countNum; i++)
		{
			obs[i].drawObstacle(sdl);
			if (obs[i].CheckObstacles(snake.getHeadX(), snake.getHeadY()))
			{
				sdl->playSound(Colide);
				usleep(400000);
				gameover = 1;
			}
		}
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
	sdl->clearRender();
	sdl->drawGameOver(x_max, y_max, score, -22);
	sdl->render();
	sleep(4);
	if (sdl)
		delete sdl;
}