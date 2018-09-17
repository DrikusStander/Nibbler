
#ifndef OBSTACLS_HPP
#define OBSTACLS_HPP

#include <vector>
#include <utility>
#include <iostream>
#include <string>

#include "main.hpp"
#include "SDLclass.hpp"

class Obstacles
{
	private:
        int _win_max_x;
        int _win_max_y;
		int _x;
        int _y;

	protected:
	public:
        Obstacles( void );	
        Obstacles( int win_x, int win_y );
		Obstacles( Obstacles const & src);
		~Obstacles( void );
		Obstacles const & operator=(Obstacles const & rhs);
		void newObstacle( void );
		void drawObstacle( SDLinterface *sdl );
        int CheckObstacles(int x, int y);
		void	setXY(int x, int y);
		int		getX( void );
		int		getY( void );
};

#endif