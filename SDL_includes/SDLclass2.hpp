
#ifndef SDLCLASS2_HPP
#define SDLCLASS2_HPP


#include "Interface.hpp"
#include "Draw.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Device.H>
#include <FL/Fl_Copy_Surface.H>


#include <unistd.h>


class SDLclass2 : public SDLinterface
{
	private:
		// SDL_Window		*_window;
		// SDL_Renderer	*_renderer;
		// SDL_Rect		_rect;
		// SDL_Event 		_event;

		Draw *_draw;
		Fl_Window *_window;
		int _event;
	protected:
		SDLclass2( void );
	public:
		SDLclass2(int x, int y, Direction dir);
		SDLclass2(SDLclass2 const & src);
		virtual ~SDLclass2( void );
		SDLclass2	const & operator=(SDLclass2 const & rhs);
		virtual Direction	getInput( void );
		virtual void		draw(int x, int y, int red, int green, int blue);
		virtual void		drawBorders(int x, int y, int score) const;
		virtual void		clearRender( void ) const;
		virtual void		render( void ) const;
		virtual void				playSound(Sound sound);
		void		drawGameOver(int x, int y, int score, int op_score) const;
		
};

extern "C" {
	SDLclass2 *maker(int x, int y, Direction dir);
}

#endif