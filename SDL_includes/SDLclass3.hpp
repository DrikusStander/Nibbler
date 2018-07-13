
#ifndef SDLCLASS3_HPP
#define SDLCLASS3_HPP


#include "Interface.hpp"

class SDLclass3 : public SDLinterface
{
	private:
	protected:
		SDLclass3( void );
	public:
		SDLclass3(int x, int y, Direction dir);
		SDLclass3(SDLclass3 const & src);
		virtual ~SDLclass3( void );
		SDLclass3	const & operator=(SDLclass3 const & rhs);
		virtual Direction	getInput( void );
		virtual void		draw(int x, int y, int red, int green, int blue);
		virtual void		drawBorders(int x, int y, int score) const;
		virtual void		clearRender( void ) const;
		virtual void		render( void ) const;
		virtual void				playSound(Sound sound);

};

extern "C" {
	SDLclass3 *maker(int x, int y, Direction dir);
}

#endif