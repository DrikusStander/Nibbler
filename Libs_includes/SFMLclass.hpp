
#ifndef SFMLCLASS_HPP
#define SFMLCLASS_HPP


#include "Interface.hpp"
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <unistd.h>


class SFMLclass : public SDLinterface
{
	private:
		sf::RenderWindow *_window;
		
	protected:
		SFMLclass( void );
	public:
		SFMLclass(int x, int y, Direction dir);
		SFMLclass(SFMLclass const & src);
		virtual ~SFMLclass( void );
		SFMLclass	const & operator=(SFMLclass const & rhs);
		virtual Direction	getInput( void );
		virtual void		draw(int x, int y, int red, int green, int blue);
		virtual void		drawBorders(int x, int y, int score) const;
		virtual void		clearRender( void ) const;
		virtual void		render( void ) const;
		virtual void				playSound(Sound sound);
		void		drawGameOver(int x, int y, int score, int op_score) const;

};

extern "C" {
	SFMLclass *maker(int x, int y, Direction dir);
}

#endif