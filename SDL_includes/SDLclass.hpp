
#ifndef SDLCLASS_HPP
#define SDLCLASS_HPP

#include "Interface.hpp"

#define MUS_PATH "./SDL_includes/chew.wav"

class SDLclass : public SDLinterface
{
	private:
	protected:
		SDLclass( void );
	public:
		SDLclass(int x, int y, Direction dir );
		SDLclass(SDLclass const & src);
		virtual ~SDLclass( void );
		SDLclass	const & operator=(SDLclass const & rhs);
		virtual Direction	getInput( void );
		virtual void		draw(int x, int y, int red, int green, int blue);
		virtual void		drawBorders(int x, int y, int score) const;
		virtual void		clearRender( void ) const;
		virtual void		render( void ) const;
		virtual void				playSound(Sound sound);
		void		drawGameOver(int x, int y, int score, int op_score) const;
};

extern "C" {
	SDLclass *maker(int x, int y, Direction dir);
}

#endif