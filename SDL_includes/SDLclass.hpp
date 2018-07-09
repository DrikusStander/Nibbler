
#ifndef SDLCLASS_HPP
#define SDLCLASS_HPP

#include <SDL.h>
#include <iostream>
#include "Interface.hpp"

class SDLclass
{
	private:
		SDL_Window		*_window;
		SDL_Renderer	*_renderer;
		SDL_Rect		_rect;
		SDL_Event 		_event;
		Direction		_dir;

	protected:
		SDLclass( void );
	public:
		SDLclass(int x, int y);
		SDLclass(SDLclass const & src);
		~SDLclass( void );
		SDLclass	const & operator=(SDLclass const & rhs);
		Direction	getInput( void );
		void		draw(int x, int y);
		void		drawBorders(int x, int y);
		void		clearRender( void );
		void		render( void );
};

#endif