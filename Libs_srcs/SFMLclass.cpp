
#include "SFMLclass.hpp"

int SCORE_AREA = 20;

SFMLclass *maker( int x, int y, Direction dir)
{
	return new SFMLclass(x, y, dir);
}

SFMLclass::SFMLclass( void )
{
	return;
}

SFMLclass::SFMLclass(int x, int y, Direction dir)
{
	this->_window = new sf::RenderWindow(sf::VideoMode(x * 2, y * 2), "Nibler");
	return;
}

SFMLclass::SFMLclass(SFMLclass const & src)
{
	this->_window = src._window;
	return;
}

SFMLclass::~SFMLclass( void )
{
	this->_window->close();
	return;
}

SFMLclass	const & SFMLclass::operator=(SFMLclass const & rhs)
{
	this->_window = rhs._window;
	return(*this);
}

Direction	SFMLclass::getInput( void )
{
	usleep(50000);
	if (this->_window->isOpen())
	{
		sf::Event event;
		if (this->_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				this->_dir = quit;
						return(quit);
			}
			if (event.type == sf::Event::KeyPressed)
				switch(event.key.code)
				{					
					case sf::Keyboard::Num1:
						return(lib1);
					case sf::Keyboard::Num2:
						return(lib2);
					case sf::Keyboard::Num3:
						return(lib3);
					case sf::Keyboard::Up:
						this->_dir = up;
						return (up);
					case sf::Keyboard::Down:
						this->_dir = down;
						return (down);
					case sf::Keyboard::Left:
						this->_dir = left;
						return (left);
					case sf::Keyboard::Right:
						this->_dir = right;
						return (right);
					case sf::Keyboard::Escape:
					case sf::Keyboard::Q:
						this->_dir = quit;
						return(quit);
					default:
						break;
				}
		}
	}
	return(this->_dir);
}

void		SFMLclass::draw(int x, int y, int red, int green, int blue)
{
	sf::RectangleShape rectangle(sf::Vector2f(SNAKE_SIZE * 2, SNAKE_SIZE * 2));
	rectangle.setFillColor(sf::Color(red - 100,green - 200 ,blue ));
	rectangle.setPosition(x * 2, y * 2);
	this->_window->draw(rectangle);
}

void		SFMLclass::clearRender( void ) const
{
	this->_window->clear(sf::Color::Black);
}

void		SFMLclass::render( void ) const
{
		this->_window->display();
}

void		SFMLclass::drawBorders(int x, int y, int score) const
{
	sf::RectangleShape rectangle(sf::Vector2f((x * 2) - 6 , (y * 2) - (SCORE_AREA * 2) - 6 ));
	sf::RectangleShape scoreAreaRect(sf::Vector2f((x * 2) - 6 , (SCORE_AREA * 2) - 6 ));
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineThickness(3);
	rectangle.setOutlineColor(sf::Color(255,0,0));
	rectangle.setPosition(3, 3);

	scoreAreaRect.setFillColor(sf::Color::Transparent);
	scoreAreaRect.setOutlineThickness(3);
	scoreAreaRect.setOutlineColor(sf::Color(255,0,0));
	scoreAreaRect.setPosition(3, (y * 2) + 3 - (SCORE_AREA * 2));
	this->_window->draw(rectangle);
	this->_window->draw(scoreAreaRect);

	std::stringstream strs;
	strs << score;
	sf::Text text;
	sf::Font font;
	if (!font.loadFromFile("./Libs_includes/Arial.ttf"))
		throw SDL_error("Unable to open Font File");
	text.setFont(font);
	text.setString("Score: " + strs.str());
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setPosition(3, (y * 2) - (SCORE_AREA * 2) + 6);
	this->_window->draw(text);
}


void playChew()
{
	sf::SoundBuffer buffer;
 	if (!buffer.loadFromFile("Libs_includes/chew.wav"))
		return;
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();
	usleep(500000);
}

void playCrash()
{
	sf::SoundBuffer buffer;
	if(!buffer.loadFromFile("Libs_includes/crash.wav"))
		return;

	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();
	usleep(500000);
}

void	SFMLclass::playSound(Sound sound)
{
	switch (sound)
	{
		case Chew:
		{
			std::thread chew_thread(playChew);
			chew_thread.detach();
			break;
		}
		case Colide:
		{
			std::thread chew_thread(playCrash);
			chew_thread.detach();
			break;
		}
	}
}

void		SFMLclass::drawGameOver(int x, int y, int score, int op_score) const
{
	

	this->drawBorders(x, y, score);
	sf::Text text;
	sf::Font font;
	font.loadFromFile("./Libs_includes/Arial.ttf");
	text.setFont(font);

	if (op_score != -22)
	{
		std::stringstream strs;
		strs << op_score;
		
		text.setString("Opponent Score: " + strs.str());
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::Red);
		text.setPosition((x * 2) - 225, (y * 2) - (SCORE_AREA * 2) + 6);
		this->_window->draw(text);
	}

	text.setFont(font);
	text.setString("GAME OVER");
	text.setCharacterSize(72);
	text.setFillColor(sf::Color::Red);
	text.setPosition((x * 2) / 3, y - (SCORE_AREA * 2));
	this->_window->draw(text);
	
}