
#ifndef SDLCLASS2_HPP
#define SDLCLASS2_HPP


#include "Interface.hpp"
#include "Draw.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Device.H>
#include <FL/Fl_Copy_Surface.H>
#include <SDL_mixer.h>


#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


#include <unistd.h>


class FLTKclass : public SDLinterface
{
	private:
		Draw *_draw;
		Fl_Window *_window;
		int _event;
	protected:
		FLTKclass( void );
	public:
		FLTKclass(int x, int y, Direction dir);
		FLTKclass(FLTKclass const & src);
		virtual ~FLTKclass( void );
		FLTKclass	const & operator=(FLTKclass const & rhs);
		virtual Direction	getInput( void );
		virtual void		draw(int x, int y, int red, int green, int blue);
		virtual void		drawBorders(int x, int y, int score) const;
		virtual void		clearRender( void ) const;
		virtual void		render( void ) const;
		virtual void				playSound(Sound sound);
		void		drawGameOver(int x, int y, int score, int op_score) const;
		
};

extern "C" {
	FLTKclass *maker(int x, int y, Direction dir);
}

#endif