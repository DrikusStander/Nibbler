
#include "SDLclass2.hpp"

int SCORE_AREA = 20;

SDLclass2 *maker( int x, int y, Direction dir)
{
	return new SDLclass2(x, y, dir);
}

SDLclass2::SDLclass2( void )
{
	return;
}

SDLclass2::SDLclass2(int x, int y, Direction dir)
{
	this->_window = new Fl_Window(x, y, "Nibler");
	this->_draw = new Draw(x, y, SNAKE_SIZE, SNAKE_SIZE);
	this->_draw->clear();
	this->_window->show();
	this->_dir = dir;
	return;
}

SDLclass2::SDLclass2(SDLclass2 const & src)
{
	// this->_rect = src._rect;
	// this->_renderer = src._renderer;
	this->_draw = src._draw;
	this->_window = src._window;
	this->_event = src._event;
	return;
}

SDLclass2::~SDLclass2( void )
{
	this->_window->hide();
	// TTF_Quit();
	// SDL_Quit();
	return;
}

SDLclass2	const & SDLclass2::operator=(SDLclass2 const & rhs)
{
	// this->_rect = rhs._rect;
	// this->_renderer = rhs._renderer;
	this->_draw = rhs._draw;
	this->_window = rhs._window;
	this->_event = rhs._event;
	return(*this);
}

Direction	SDLclass2::getInput( void )
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

void		SDLclass2::draw(int x, int y, int red, int green, int blue)
{

	fl_color(red - 10 , green - 10, blue - 10);
	this->_draw->update(x, y, SNAKE_SIZE);
}

void		SDLclass2::clearRender( void ) const
{
	this->_draw->clear();
}

void		SDLclass2::render( void ) const
{
	this->_window->show();
	Fl::redraw();
}

void		SDLclass2::drawBorders(int x, int y, int score) const
{
	this->_draw->updateBorder(SCORE_AREA, score);
}

void playChew()
{
	// Mix_Chunk *chew = NULL;
	// if( Mix_OpenAudio( 44100, AUDIO_S16SYS, 2, 1024 ) < 0 )
	// {
	// 	throw SDL_error("Unable to open Audio File");
	// }
	// if ((chew = Mix_LoadWAV("SDL_includes/chew.wav")) == NULL)
	// {
	// 	throw SDL_error("Unable to load Audio file");
	// }
	// Mix_VolumeChunk(chew, MIX_MAX_VOLUME/2);
	// Mix_PlayChannel( -1, chew, -1);
	// SDL_Delay(500);
	// Mix_FreeChunk(chew);
}

void playCrash()
{
	// Mix_Chunk *crash = NULL;
	// if( Mix_OpenAudio( 44100, AUDIO_S16SYS, 2, 1024 ) < 0 )
	// {
	// 	throw SDL_error("Unable to open Audio File");
	// }
	// if ((crash = Mix_LoadWAV("SDL_includes/crash.wav")) == NULL)
	// {
	// 	throw SDL_error("Unable to load Audio file");
	// }
	// Mix_VolumeChunk(crash, MIX_MAX_VOLUME/2);
	// Mix_PlayChannel( -1, crash, -1);
	// SDL_Delay(500);
	// Mix_FreeChunk(crash);
}

void	SDLclass2::playSound(Sound sound)
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

void		SDLclass2::drawGameOver(int x, int y, int score, int op_score) const
{
	// SDL_SetRenderDrawColor(this->_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	// SDL_Rect GameWrect;
	// GameWrect.x = 0;
	// GameWrect.y = 0;
	// GameWrect.w = x;
	// GameWrect.h = y - SCORE_AREA;
	// SDL_RenderDrawRect(this->_renderer,	&GameWrect);
	// SDL_Rect ScoreWrect;
	// ScoreWrect.x = 0;
	// ScoreWrect.y = y - SCORE_AREA + 1;
	// ScoreWrect.w = x;
	// ScoreWrect.h = SCORE_AREA - 1;
	// SDL_RenderDrawRect(this->_renderer,	&ScoreWrect);

	// TTF_Font* font = TTF_OpenFont("./SDL_includes/Arial.ttf", 50);
	// if (font == NULL)
	// 	throw SDL_error("Unable to open Font File");
	// SDL_Color foregroundColor = { 255, 255, 255, 255 };
	// SDL_Surface* artSurface = TTF_RenderText_Solid(font, "GAME OVER", foregroundColor);

	// if (artSurface == NULL)
	// 	throw SDL_error("Unable to Render textSurface");
	// SDL_Texture* artTexture = SDL_CreateTextureFromSurface(this->_renderer, artSurface);
	// if (artTexture == NULL)
	// 	throw SDL_error("Unable to Render textTexture");
	// SDL_Rect artLocation = { x / 4, (y - SCORE_AREA) / 4 , x / 2 , (y - SCORE_AREA) / 2 };
	// SDL_RenderCopy(this->_renderer, artTexture, NULL, &artLocation);
	
	// font = TTF_OpenFont("./SDL_includes/Arial.ttf", 20);

	// SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Score :", foregroundColor);
	// if (textSurface == NULL)
	// 	throw SDL_error("Unable to Render textSurface");
	// SDL_Texture* textTexture = SDL_CreateTextureFromSurface(this->_renderer, textSurface);
	// if (textTexture == NULL)
	// 	throw SDL_error("Unable to Render textTexture");
	// SDL_Rect textLocation = { 8, y - SCORE_AREA + 2 , 50, 19 };
	// SDL_RenderCopy(this->_renderer, textTexture, NULL, &textLocation);

	// std::stringstream strs;
	// strs << score;
	// SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, strs.str().c_str(), foregroundColor);
	// if (scoreSurface == NULL)
	// 	throw SDL_error("Unable to Render scoreSurface");
	// SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(this->_renderer, scoreSurface);
	// if (scoreTexture == NULL)
	// 	throw SDL_error("Unable to Render scoreTexture");
	// SDL_Rect scoreLocation = { 60, y - SCORE_AREA + 2 , 20, 19 };
	// SDL_RenderCopy(this->_renderer, scoreTexture, NULL, &scoreLocation);
	
	// SDL_Surface* opTextSurface = TTF_RenderText_Solid(font, "Opponent Score :", foregroundColor);
	// if (opTextSurface == NULL)
	// 	throw SDL_error("Unable to Render opTextSurface");
	// SDL_Texture* opTextTexture = SDL_CreateTextureFromSurface(this->_renderer, opTextSurface);
	// if (opTextTexture == NULL)
	// 	throw SDL_error("Unable to Render opTextTexture");
	// SDL_Rect opTextLocation = { x - 138, y - SCORE_AREA + 2 , 110, 19 };
	// SDL_RenderCopy(this->_renderer, opTextTexture, NULL, &opTextLocation);

	// std::stringstream op_strs;
	// op_strs << op_score;
	// SDL_Surface* opScoreSurface = TTF_RenderText_Solid(font, op_strs.str().c_str(), foregroundColor);
	// if (opScoreSurface == NULL)
	// 	throw SDL_error("Unable to Render opScoreSurface");
	// SDL_Texture* opScoreTexture = SDL_CreateTextureFromSurface(this->_renderer, opScoreSurface);
	// if (opScoreTexture == NULL)
	// 	throw SDL_error("Unable to Render opScoreTexture");
	// SDL_Rect opScoreLocation = { x - 28, y - SCORE_AREA + 2 , 20, 19 };
	// SDL_RenderCopy(this->_renderer, opScoreTexture, NULL, &opScoreLocation);

	// SDL_FreeSurface(artSurface);
	// SDL_FreeSurface(textSurface);
	// SDL_FreeSurface(scoreSurface);
	// SDL_FreeSurface(opTextSurface);
	// SDL_FreeSurface(opScoreSurface);
	// TTF_CloseFont(font);
}