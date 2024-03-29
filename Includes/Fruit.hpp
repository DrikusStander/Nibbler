
#ifndef FRUIT_HPP
#define FRUIT_HPP

#include <vector>
#include <utility>
#include <iostream>
#include <string>

#include "main.hpp"
#include "SDLclass.hpp"

class Fruit
{
	private:
        int _win_max_x;
        int _win_max_y;
		int _x;
        int _y;

	protected:
	public:
        Fruit( void );	
        Fruit( int win_x, int win_y );
		Fruit( Fruit const & src);
		~Fruit( void );
		Fruit const & operator=(Fruit const & rhs);
		void newFruit( void );
		void drawFruit( SDLinterface *sdl );
        int CheckFruitEaten(int x, int y);
		void	setXY(int x, int y);
		int		getX( void );
		int		getY( void );
};

#endif