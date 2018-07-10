
#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include <utility>
#include <iostream>
#include <string>

#include "main.hpp"
#include "SDLclass.hpp"

class Snake
{
	private:
		Direction _dir;
		std::vector< std::pair< int, int > > *_snake;
	protected:
		Snake( void );
	public:
		Snake( int x, int y );
		Snake( Snake const & src);
		~Snake( void );
		Snake const & operator=(Snake const & rhs);
		void addBody( int x, int y );
		void drawSnake( SDLinterface *sdl );
		void changeDirection(Direction dir);
		void moveSnake( void );
		int	getHeadX( void );
		int	getHeadY( void );
		void growSnake( void );
		int checkCollision( int x, int y);
};

#endif