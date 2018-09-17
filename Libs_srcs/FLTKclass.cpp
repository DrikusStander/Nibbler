
#include "FLTKclass.hpp"

int SCORE_AREA = 20;

FLTKclass *maker( int x, int y, Direction dir)
{
	return new FLTKclass(x, y, dir);
}

FLTKclass::FLTKclass( void )
{
	return;
}

FLTKclass::FLTKclass(int x, int y, Direction dir)
{
	this->_window = new Fl_Window(x, y, "Nibler");
	this->_draw = new Draw(x, y, SNAKE_SIZE, SNAKE_SIZE);
	this->_draw->clear();
	this->_window->show();
	this->_dir = dir;

	al_init();

	al_install_audio();
	return;
}

FLTKclass::FLTKclass(FLTKclass const & src)
{
	this->_draw = src._draw;
	this->_window = src._window;
	this->_event = src._event;
	return;
}

FLTKclass::~FLTKclass( void )
{
	this->_window->hide();
	return;
}

FLTKclass	const & FLTKclass::operator=(FLTKclass const & rhs)
{
	this->_draw = rhs._draw;
	this->_window = rhs._window;
	this->_event = rhs._event;
	return(*this);
}

Direction	FLTKclass::getInput( void )
{
	usleep(40000);	
	Fl::wait(0);
	if ((this->_event = Fl::event_key() ) != 0)
	{
		if (Fl::get_key(this->_event) == true)
		{
			switch(this->_event)
			{
				case '1':
					return(lib1);
				case '2':
					return(lib2);
				case '3':
					return(lib3);
				case FL_Up:
					this->_dir = up;
					return(up);
				case FL_Down:
					this->_dir = down;
					return(down);
				case FL_Right:
					this->_dir = right;
					return(right);
				case FL_Left:
					this->_dir = left;
					return(left);
				case FL_Escape:
					this->_dir = quit;
					return(quit);
				case 'q':
					this->_dir = quit;
					return(quit);
			}
		}
	}
	return(this->_dir);
}

void		FLTKclass::draw(int x, int y, int red, int green, int blue)
{

	fl_color(red - 10 , green - 10, blue - 10);
	this->_draw->update(x, y, SNAKE_SIZE);
}

void		FLTKclass::clearRender( void ) const
{
	this->_draw->clear();
}

void		FLTKclass::render( void ) const
{
	Fl::redraw();
	Fl::wait(0);
}

void		FLTKclass::drawBorders(int x, int y, int score) const
{
	this->_draw->updateBorder(SCORE_AREA, score);
}

void playChew()
{
	ALLEGRO_SAMPLE *sample=NULL;

	al_init_acodec_addon();
	al_reserve_samples(1);
	sample = al_load_sample( "./Libs_includes/chew.wav" );
	if(!sample)
	{
		std::cout << "Unable to load Audio file" << std::endl;
		return;
	}
	al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
	usleep(4000000);
	al_destroy_sample(sample);
}

void playCrash()
{
	ALLEGRO_SAMPLE *sample=NULL;

	al_init_acodec_addon();
	al_reserve_samples(1);
	sample = al_load_sample( "./Libs_includes/crash.wav" );
	if(!sample)
	{
		std::cout << "Unable to load Audio file" << std::endl;
		return;
	}
	al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
	usleep(4000000);
	al_destroy_sample(sample);
}

void	FLTKclass::playSound(Sound sound)
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

void		FLTKclass::drawGameOver(int x, int y, int score, int op_score) const
{
	this->_draw->twoPGameover(score, op_score, SCORE_AREA);
}