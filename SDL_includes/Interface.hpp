#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "main.hpp"
extern int SCORE_AREA;

class SDLinterface
{
	private:
	protected:

		SDL_Window		*_window;
		SDL_Renderer	*_renderer;
		SDL_Rect		_rect;
		SDL_Event 		_event;
		Direction		_dir;

	public:
		virtual ~SDLinterface( void ) {};
		virtual Direction	getInput( void ) = 0;
		virtual void		draw(int x, int y, int red, int green, int blue) = 0;
		virtual void		drawBorders(int x, int y, int score) const = 0;
		virtual void		clearRender( void ) const = 0;
		virtual void		render( void ) const = 0;
};

#endif