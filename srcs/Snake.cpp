
#include "Snake.hpp"


Snake::Snake( void )
{
	return;
}

Snake::Snake( int x, int y)
{
	this->_dir = right;
	this->_snake = new std::vector<std::pair<int, int>>;
	this->_snake->push_back(std::pair<int, int>(x, y));
	for (int i = 1; i < 4; i++)
	{
		this->_snake->push_back(std::pair<int, int>(x - (i * 8), y));
	}
	return;
}

Snake::Snake( Snake const & src)
{
	this->_snake = src._snake;
	return;
}

Snake::~Snake( void )
{
	return;
}

Snake const & Snake::operator=(Snake const & rhs)
{
	this->_snake = rhs._snake;
	return(*this);
}

void Snake::addBody( int x, int y)
{
	this->_snake->push_back(std::pair<int, int>(x, y));
}

void Snake::drawSnake( SDLclass *sdl )
{
	sdl->clearRender();
	for (std::vector<std::pair<int, int>> ::iterator i = this->_snake->begin(); i != this->_snake->end(); i++)
	{
		sdl->draw(i->first, i->second);
		std::cout << i->first << std::endl;
		std::cout << i->second << std::endl;
	}
	sdl->render();
}

void Snake::changeDirection(Direction dir)
{
	this->_dir = dir;
	return;
}

void Snake::moveSnake( void )
{
	int x;
	int y;
	if (this->_dir == right)
	{
		x = this->_snake->begin()->first;
		y = this->_snake->begin()->second;
		this->_snake->pop_back();
		this->_snake->insert(this->_snake->begin(), std::pair<int, int>(x + 8, y));
	}
	if (this->_dir == left)
	{
		x = this->_snake->begin()->first;
		y = this->_snake->begin()->second;
		this->_snake->pop_back();
		this->_snake->insert(this->_snake->begin(), std::pair<int, int>(x - 8, y));
	}
	if (this->_dir == up)
	{
		x = this->_snake->begin()->first;
		y = this->_snake->begin()->second;
		this->_snake->pop_back();
		this->_snake->insert(this->_snake->begin(), std::pair<int, int>(x, y - 8));
	}
	if (this->_dir == down)
	{
		x = this->_snake->begin()->first;
		y = this->_snake->begin()->second;
		this->_snake->pop_back();
		this->_snake->insert(this->_snake->begin(), std::pair<int, int>(x, y + 8));
	}
}