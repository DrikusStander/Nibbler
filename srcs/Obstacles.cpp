#include "Obstacles.hpp"

Obstacles::Obstacles( void )
{
	this->_win_max_x = 0;
	this->_win_max_y = 0;
	this->_x = 0;
	this->_y = 0;
	return;
}

Obstacles::Obstacles( int win_x, int win_y )
{
	this->_win_max_x = win_x;
	this->_win_max_y = win_y;
	this->newObstacle();
	return;
}

Obstacles::Obstacles( Obstacles const & src)
{
	this->_win_max_x = src._win_max_x;
	this->_win_max_y = src._win_max_y;
	this->_x = src._x;
	this->_y = src._y;
	return;
}

Obstacles::~Obstacles( void )
{

	return;
}

Obstacles const & Obstacles::operator=(Obstacles const & rhs)
{
	this->_win_max_x = rhs._win_max_x;
	this->_win_max_y = rhs._win_max_y;
	this->_x = rhs._x;
	this->_y = rhs._y;
	return(*this);
}

void Obstacles::newObstacle( void )
{
	this->_x = rand() % (this->_win_max_x - SNAKE_SIZE) + SNAKE_SIZE ;
	this->_y = rand() % (this->_win_max_y - SNAKE_SIZE) + SNAKE_SIZE;
	if (this->_x % SNAKE_SIZE != 0 || this->_y % SNAKE_SIZE != 0 || this->_y >= this->_win_max_y - SNAKE_SIZE || this->_x >= this->_win_max_x - SNAKE_SIZE)
		this->newObstacle();
	return;
}

void Obstacles::drawObstacle( SDLinterface *sdl )
{
	sdl->draw(this->_x, this->_y, 255, 255, 255);
	return;
}

int Obstacles::CheckObstacles(int x, int y)
{
	if (x == this->_x && y == this->_y)
		return(1);
	return(0);
}

void	Obstacles::setXY(int x, int y)
{
	this->_x = x;
	this->_y = y;
	return;
}

int		Obstacles::getX( void )
{
	return(this->_x);
}

int		Obstacles::getY( void )
{
	return(this->_y);
}