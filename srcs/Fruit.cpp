#include "Fruit.hpp"

Fruit::Fruit( void )
{
	return;
}

Fruit::Fruit( int win_x, int win_y )
{
	this->_win_max_x = win_x;
	this->_win_max_y = win_y;
	this->newFruit();
	return;
}

Fruit::Fruit( Fruit const & src)
{
	this->_win_max_x = src._win_max_x;
	this->_win_max_y = src._win_max_y;
	this->_x = src._x;
	this->_y = src._y;
	return;
}

Fruit::~Fruit( void )
{

	return;
}

Fruit const & Fruit::operator=(Fruit const & rhs)
{
	this->_win_max_x = rhs._win_max_x;
	this->_win_max_y = rhs._win_max_y;
	this->_x = rhs._x;
	this->_y = rhs._y;
	return(*this);
}

void Fruit::newFruit( void )
{
	this->_x = rand() % (this->_win_max_x - SNAKE_SIZE) + SNAKE_SIZE ;
	this->_y = rand() % (this->_win_max_y - SNAKE_SIZE) + SNAKE_SIZE;
	if (this->_x % SNAKE_SIZE != 0 || this->_y % SNAKE_SIZE != 0 || this->_y >= this->_win_max_y - SNAKE_SIZE || this->_x >= this->_win_max_x - SNAKE_SIZE)
		this->newFruit();
	return;
}

void Fruit::drawFruit( SDLinterface *sdl )
{
	sdl->draw(this->_x, this->_y, 200, 100, 150);
	return;
}

int Fruit::CheckFruitEaten(int x, int y)
{
	if (x == this->_x && y == this->_y)
		return(1);
	return(0);
}

void	Fruit::setXY(int x, int y)
{
	this->_x = x;
	this->_y = y;
	return;
}