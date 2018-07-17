
#include "GameLoop.hpp"

void	testfunc(TCP *server, int *val)
{
	server->recv(val);
}

void	ServerGameLoop( int x_max, int y_max, int lib)
{
	TCP server;
	
	server.send(x_max);
	server.send(y_max);
	
	int score = 0;
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
		// std::cout << "start of loop" << std::endl;
		server.send(gameover);
		// std::thread thread(testfunc, &server, &recv);
		// thread.detach();
		
		std::cout << recv << std::endl;
		if (recv == -2)
		{
			gameover = 1;
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
				sdl = loadLib("lib1.so", hndl, x_max, y_max, oldDir);
				break;
			case lib2:
				sdl = loadLib("lib2.so", hndl, x_max, y_max, oldDir);
				break;
			case lib3:
				sdl = loadLib("lib3.so", hndl, x_max, y_max, oldDir);
				break;
			case quit:
				gameover = -1;
				server.send(gameover);
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
			fruit_x = fruit.getX();
			server.send(fruit_x);
			fruit_y = fruit.getY();
			server.send(fruit_y);
			snake.growSnake();
			score++;
		}
		server.recv(&recv);
	}
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
	
	// test = client.recv();
	// std::string str(test);
	// if (!str.empty())
	// 	std::cout << str << std::endl;
	
	int score = 0;
	Direction dir = right;
	Direction oldDir = right;
	// int x_max;
	// int y_max;
	
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

		client.send(gameover);
		// std::thread thread(testfunc, &client, &fruit_x);
		// thread.join();
		std::cout << fruit_x << std::endl;
		if (fruit_x < 0)
		{
			gameover = 1;
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
				sdl = loadLib("lib1.so", hndl, x_max, y_max, oldDir);
				break;
			case lib2:
				sdl = loadLib("lib2.so", hndl, x_max, y_max, oldDir);
				break;
			case lib3:
				sdl = loadLib("lib3.so", hndl, x_max, y_max, oldDir);
				break;
			case quit:
				gameover = -1;
				client.send(gameover);
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
			// fruit.newFruit();
			client.send(ate_fruit);
			fruit.setXY(fruit_x, fruit_y);
			fruit_x = 0;
			fruit_y = 0;
			snake.growSnake();
			score++;
		}
		client.recv(&fruit_x);
	}
	if (sdl)
		delete sdl;
}