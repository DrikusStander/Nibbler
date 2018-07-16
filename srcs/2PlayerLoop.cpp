
#include "GameLoop.hpp"

void	ServerGameLoop( int x_max, int y_max, int lib)
{
	TCP server;
	server.send("Server running");
	char *test;

	test = server.recv();
	std::cout << test << std::endl;
	(void)x_max;
	(void)y_max;
	(void)lib;
	// int score = 0;
	// Direction dir = right;
	// Direction oldDir = right;
	
	// Snake snake(x_start(x_max), y_start(y_max));
	// Fruit fruit(x_max, y_max - SCORE_AREA);
	// int gameover = 0;
	// void *hndl = NULL;
	// SDLinterface *sdl;
	// if (lib == 1)
	// 	sdl = loadLib("lib1.so", hndl, x_max, y_max, dir);
	// else if (lib == 2)
	// 	sdl = loadLib("lib2.so", hndl, x_max, y_max, dir);
	// else
	// 	sdl = loadLib("lib3.so", hndl, x_max, y_max, dir);
	// while (!gameover)
	// {
	// 	dir = sdl->getInput();
	// 	switch(dir)
	// 	{
	// 		case lib1:
	// 			sdl = loadLib("lib1.so", hndl, x_max, y_max, oldDir);
	// 			break;
	// 		case lib2:
	// 			sdl = loadLib("lib2.so", hndl, x_max, y_max, oldDir);
	// 			break;
	// 		case lib3:
	// 			sdl = loadLib("lib3.so", hndl, x_max, y_max, oldDir);
	// 			break;
	// 		case quit:
	// 			gameover = 1;
	// 			break;
	// 		case up:
	// 		case down:
	// 		case left:
	// 		case right:
	// 			oldDir = dir;
	// 			snake.changeDirection(dir);
	// 			break;
	// 	}
	// 	snake.moveSnake();
	// 	if (snake.checkCollision(x_max, y_max - SCORE_AREA) == 1)
	// 	{
	// 		sdl->playSound(Colide);
	// 		usleep(400000);
	// 		break;
	// 	}
	// 	sdl->clearRender();
	// 	snake.drawSnake(sdl);
	// 	fruit.drawFruit(sdl);
	// 	sdl->drawBorders(x_max, y_max, score);
	// 	sdl->render();

	// 	if (fruit.CheckFruitEaten(snake.getHeadX(), snake.getHeadY()))
	// 	{
	// 		sdl->playSound(Chew);
	// 		fruit.newFruit();
	// 		snake.growSnake();
	// 		score++;
	// 	}
	// }
	// if (sdl)
	// 	delete sdl;
}


void	ClientGameLoop(int lib, std::string ip)
{
	(void)lib;

	TCP client(ip);
	client.send("Client Connected");
	char *test;

	test = client.recv();
	std::cout << test << std::endl;
	// int score = 0;
	// Direction dir = right;
	// Direction oldDir = right;
	// int x_max;
	// int y_max;
	
	// Snake snake(x_start(x_max), y_start(y_max));
	// Fruit fruit(x_max, y_max - SCORE_AREA);
	// int gameover = 0;
	// void *hndl = NULL;
	// SDLinterface *sdl;
	// if (lib == 1)
	// 	sdl = loadLib("lib1.so", hndl, x_max, y_max, dir);
	// else if (lib == 2)
	// 	sdl = loadLib("lib2.so", hndl, x_max, y_max, dir);
	// else
	// 	sdl = loadLib("lib3.so", hndl, x_max, y_max, dir);
	
	// while (!gameover)
	// {
	// 	dir = sdl->getInput();
	// 	switch(dir)
	// 	{
	// 		case lib1:
	// 			sdl = loadLib("lib1.so", hndl, x_max, y_max, oldDir);
	// 			break;
	// 		case lib2:
	// 			sdl = loadLib("lib2.so", hndl, x_max, y_max, oldDir);
	// 			break;
	// 		case lib3:
	// 			sdl = loadLib("lib3.so", hndl, x_max, y_max, oldDir);
	// 			break;
	// 		case quit:
	// 			gameover = 1;
	// 			break;
	// 		case up:
	// 		case down:
	// 		case left:
	// 		case right:
	// 			oldDir = dir;
	// 			snake.changeDirection(dir);
	// 			break;
	// 	}
	// 	snake.moveSnake();
	// 	if (snake.checkCollision(x_max, y_max - SCORE_AREA) == 1)
	// 	{
	// 		sdl->playSound(Colide);
	// 		usleep(400000);
	// 		break;
	// 	}
	// 	sdl->clearRender();
	// 	snake.drawSnake(sdl);
	// 	fruit.drawFruit(sdl);
	// 	sdl->drawBorders(x_max, y_max, score);
	// 	sdl->render();

	// 	if (fruit.CheckFruitEaten(snake.getHeadX(), snake.getHeadY()))
	// 	{
	// 		sdl->playSound(Chew);
	// 		// fruit.newFruit();
	// 		snake.growSnake();
	// 		score++;
	// 	}
	// }
	// if (sdl)
	// 	delete sdl;
}