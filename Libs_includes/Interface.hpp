#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "main.hpp"

#include <iostream>
#include <sstream>
#include <thread>
#include "Exceptions.hpp"

extern int SCORE_AREA;

enum Sound
{
	Chew = 0,
	Colide
};

class SDLinterface
{
	private:
	protected:
		Direction		_dir;

	public:
		virtual ~SDLinterface( void ) {};
		virtual Direction	getInput( void ) = 0;
		virtual void		draw(int x, int y, int red, int green, int blue) = 0;
		virtual void		drawBorders(int x, int y, int score) const = 0;
		virtual void		clearRender( void ) const = 0;
		virtual void		render( void ) const = 0;
		virtual void		playSound(Sound sound) = 0;
		virtual void		drawGameOver(int x, int y, int score, int op_score) const =0;

};




#endif