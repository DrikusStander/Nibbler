
#include "GameLoop.hpp"


void	ServerGameLoop( int x_max, int y_max, int lib)
{
	TCP server;
	
	server.send(x_max);
	server.send(y_max);
	
	int score = 0;
	int op_score = 0;
	Direction dir = right;
	Direction oldDir = right;
	int recv = 0;
	
	Snake snake(x_start(x_max), y_start(y_max));
	Fruit fruit(x_max, y_max - SCORE_AREA);
	int fruit_x = fruit.getX();
	int fruit_y = fruit.getY();
	server.send(fruit_x);
	server.send(fruit_y);
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
		if (recv == -2)
		{
			gameover = -2;
			break;
		}
		else if (recv == -1)
		{
			fruit.newFruit();
			fruit_x = fruit.getX();
			server.send(fruit_x);
			fruit_y = fruit.getY();
			server.send(fruit_y);
		}
		dir = sdl->getInput();
		switch(dir)
		{
			case lib1:
				delete sdl;
				sdl = loadLib("lib1.so", hndl, x_max, y_max, oldDir);
				break;
			case lib2:
				delete sdl;
				sdl = loadLib("lib2.so", hndl, x_max, y_max, oldDir);
				break;
			case lib3:
				delete sdl;
				sdl = loadLib("lib3.so", hndl, x_max, y_max, oldDir);
				break;
			case quit:
				gameover = -2;
				break;
			case up:
			case down:
			case left:
			case right:
				oldDir = dir;
				snake.changeDirection(dir);
				break;
		}
		server.send(gameover);
		if (gameover)
			break;
		snake.moveSnake();
		if (snake.checkCollision(x_max, y_max - SCORE_AREA) == 1)
		{
			gameover = -1;
			server.send(gameover);
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
			fruit_x = fruit.getX();
			server.send(fruit_x);
			fruit_y = fruit.getY();
			server.send(fruit_y);
			snake.growSnake();
			score++;
		}
		server.recv(&recv);

	}
	sleep(1);
	server.send(score);
	while (1)
	{
		server.recv(&op_score);
		if (op_score)
			break;
	}
	sdl->clearRender();
	sdl->drawGameOver(x_max, y_max, score, op_score);
	sdl->render();
	sleep(4);
	if (sdl)
		delete sdl;
}


void	ClientGameLoop(int lib, std::string ip)
{
	(void)lib;

	TCP client(ip);
	int x_max;
	int y_max;
	int fruit_x;
	int fruit_y;
	int ate_fruit = -1;
	int died = -2;
	
	client.recv(&x_max);
	client.recv(&y_max);
	
	int score = 0;
	int op_score = 0;
	Direction dir = right;
	Direction oldDir = right;
	
	Snake snake(x_start(x_max), y_start(y_max));
	Fruit fruit;
	fruit.setXY(client.recv(&fruit_x), client.recv(&fruit_y));
	fruit_x = 0;
	fruit_y = 0;
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
		if (fruit_x < 0)
		{
			gameover = -2;
			break;
		}
		else if (fruit_x > 0)
		{
			client.recv(&fruit_y);
			fruit.setXY(fruit_x, fruit_y);
			fruit_x = 0;
			fruit_y = 0;
		}


		dir = sdl->getInput();

		switch(dir)
		{
			case lib1:
				delete sdl;
				sdl = loadLib("lib1.so", hndl, x_max, y_max, oldDir);
				break;
			case lib2:
				delete sdl;
				sdl = loadLib("lib2.so", hndl, x_max, y_max, oldDir);
				break;
			case lib3:
				delete sdl;
				sdl = loadLib("lib3.so", hndl, x_max, y_max, oldDir);
				break;
			case quit:
				gameover = -2;
				break;
			case up:
			case down:
			case left:
			case right:
				oldDir = dir;
				snake.changeDirection(dir);
				break;
		}
		client.send(gameover);
		if (gameover)
			break;
		snake.moveSnake();


		if (snake.checkCollision(x_max, y_max - SCORE_AREA) == 1)
		{
			gameover = -1;
			sdl->playSound(Colide);
			client.send(died);
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
			client.send(ate_fruit);
			fruit.setXY(fruit_x, fruit_y);
			fruit_x = 0;
			fruit_y = 0;
			snake.growSnake();
			score++;
		}
		client.recv(&fruit_x);
	}
	sleep(1);
	client.send(score);
	while (1)
	{
		client.recv(&op_score);
		if (op_score)
			break;
	}
	sdl->clearRender();
	sdl->drawGameOver(x_max, y_max, score, op_score);
	sdl->render();
	sleep(4);
	if (sdl)
		delete sdl;
}