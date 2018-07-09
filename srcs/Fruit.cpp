#include "Fruit.hpp"

Fruit::Fruit( void )
{
	return;
}

Fruit::Fruit( int win_x, int win_y )
{
	this->_win_max_x = win_x;
	this->_win_max_y = win_y;
	this->_x = rand() % win_x;
	this->_y = rand() % win_y;
	if (this->_x % 4 != 0 || this->_y % 4 != 0)
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
	this->_x = rand() % this->_win_max_x;
	this->_y = rand() % this->_win_max_y;
	if (this->_x % SNAKE_SIZE != 0 || this->_y % SNAKE_SIZE != 0)
		this->newFruit();
	return;
}

void Fruit::drawFruit( SDLclass *sdl )
{
	sdl->draw(this->_x, this->_y);
	return;
}

int Fruit::CheckFruitEaten(int x, int y)
{
	if (x == this->_x && y == this->_y)
		return(1);
	return(0);
}