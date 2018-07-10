
#ifndef SDLCLASS_HPP
#define SDLCLASS_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>
#include "Interface.hpp"

class SDLclass : public SDLinterface
{
	private:
		// SDL_Window		*_window;
		// SDL_Renderer	*_renderer;
		// SDL_Rect		_rect;
		// SDL_Event 		_event;
		// Direction		_dir;

	protected:
		SDLclass( void );
	public:
		SDLclass(int x, int y);
		SDLclass(SDLclass const & src);
		virtual ~SDLclass( void );
		SDLclass	const & operator=(SDLclass const & rhs);
		virtual Direction	getInput( void );
		virtual void		draw(int x, int y, int red, int green, int blue);
		virtual void		drawBorders(int x, int y, int score) const;
		virtual void		clearRender( void ) const;
		virtual void		render( void ) const;
};

extern "C" {
	SDLclass *maker(int x, int y);
}

#endif