
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
		this->_snake->push_back(std::pair<int, int>(x - (i * SNAKE_SIZE), y));
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
	for (std::vector<std::pair<int, int>> ::iterator i = this->_snake->begin(); i != this->_snake->end(); i++)
	{
		sdl->draw(i->first, i->second);
	}
}

void Snake::changeDirection(Direction dir)
{
	if ((this->_dir == left || this->_dir == right) && (dir == up || dir == down))
		this->_dir = dir;
	else if ((this->_dir == up || this->_dir == down) && (dir == left || dir == right))
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
		this->_snake->insert(this->_snake->begin(), std::pair<int, int>(x + SNAKE_SIZE, y));
	}
	if (this->_dir == left)
	{
		x = this->_snake->begin()->first;
		y = this->_snake->begin()->second;
		this->_snake->pop_back();
		this->_snake->insert(this->_snake->begin(), std::pair<int, int>(x - SNAKE_SIZE, y));
	}
	if (this->_dir == up)
	{
		x = this->_snake->begin()->first;
		y = this->_snake->begin()->second;
		this->_snake->pop_back();
		this->_snake->insert(this->_snake->begin(), std::pair<int, int>(x, y - SNAKE_SIZE));
	}
	if (this->_dir == down)
	{
		x = this->_snake->begin()->first;
		y = this->_snake->begin()->second;
		this->_snake->pop_back();
		this->_snake->insert(this->_snake->begin(), std::pair<int, int>(x, y + SNAKE_SIZE));
	}
}

int	Snake::getHeadX( void )
{
	return(this->snake[0]->first);
}

int	Snake::getHeadY( void );
{
	return(this->snake[0]->second);
}

void Snake::growSnake( void )
{
	this->addBody(this->snake.end().first, this->snake.end().second)
}