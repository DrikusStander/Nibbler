
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
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	TTF_Init();

	SDL_CreateWindowAndRenderer(x, y, 0, &this->_window, &this->_renderer);
	this->_rect.w = SNAKE_SIZE;
	this->_rect.h = SNAKE_SIZE;
	this->_dir = dir;
	return;
}

SDLclass2::SDLclass2(SDLclass2 const & src)
{
	this->_rect = src._rect;
	this->_renderer = src._renderer;
	this->_window = src._window;
	this->_event = src._event;
	return;
}

SDLclass2::~SDLclass2( void )
{
	TTF_Quit();
	SDL_Quit();
	return;
}

SDLclass2	const & SDLclass2::operator=(SDLclass2 const & rhs)
{
	this->_rect = rhs._rect;
	this->_renderer = rhs._renderer;
	this->_window = rhs._window;
	this->_event = rhs._event;
	return(*this);
}

Direction	SDLclass2::getInput( void )
{
	SDL_Delay(50);
	if (SDL_PollEvent(&this->_event)) 
	{
		switch (this->_event.type) 
		{
			case SDL_QUIT:
				this->_dir = quit;
				return (quit);
			case SDL_KEYDOWN:
				switch (this->_event.key.keysym.sym) 
				{
					case SDLK_1:
						return(lib1);
					case SDLK_2:
						return(lib2);
					case SDLK_3:
						return(lib3);
					case SDLK_LEFT:
						this->_dir = left;
						return (left);
					case SDLK_RIGHT:
						this->_dir = right;
						return (right);
					case SDLK_DOWN:
						this->_dir = down;
						return (down);
					case SDLK_UP:
						this->_dir = up;
						return (up);
					case SDLK_ESCAPE:
					case SDLK_q:
						this->_dir = quit;
						return (quit);
				}
		}
	}
	return(this->_dir);
}

void		SDLclass2::draw(int x, int y, int red, int green, int blue)
{
	this->_rect.x = x;
	this->_rect.y = y;
	SDL_SetRenderDrawColor(this->_renderer, red - 10, green - 10, blue - 10, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(this->_renderer,	&this->_rect);
	SDL_RenderFillRect(this->_renderer,	&this->_rect);
}

void		SDLclass2::clearRender( void ) const
{
	SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(this->_renderer);
}

void		SDLclass2::render( void ) const
{
	SDL_RenderPresent(this->_renderer);
}

void		SDLclass2::drawBorders(int x, int y, int score) const
{
	SDL_SetRenderDrawColor(this->_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_Rect GameWrect;
	GameWrect.x = 0;
	GameWrect.y = 0;
	GameWrect.w = x;
	GameWrect.h = y - SCORE_AREA;
	SDL_RenderDrawRect(this->_renderer,	&GameWrect);
	SDL_Rect ScoreWrect;
	ScoreWrect.x = 0;
	ScoreWrect.y = y - SCORE_AREA + 1;
	ScoreWrect.w = x;
	ScoreWrect.h = SCORE_AREA - 1;
	SDL_RenderDrawRect(this->_renderer,	&ScoreWrect);

	TTF_Font* font = TTF_OpenFont("./SDL_includes/Arial.ttf", 12);
	SDL_Color foregroundColor = { 255, 255, 255, 255 };
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Score :", foregroundColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(this->_renderer, textSurface);
	SDL_Rect textLocation = { 8, y - SCORE_AREA + 2 , 50, 19 };

	SDL_RenderCopy(this->_renderer, textTexture, NULL, &textLocation);
	std::stringstream strs;
	strs << score;
	SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, strs.str().c_str(), foregroundColor);
	SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(this->_renderer, scoreSurface);
	SDL_Rect scoreLocation = { 60, y - SCORE_AREA + 2 , 20, 19 };
	SDL_RenderCopy(this->_renderer, scoreTexture, NULL, &scoreLocation);
	
	SDL_FreeSurface(textSurface);
	SDL_FreeSurface(scoreSurface);
	TTF_CloseFont(font);
}

void playChew()
{
	Mix_Chunk *chew = NULL;
	if( Mix_OpenAudio( 44100, AUDIO_S16SYS, 2, 1024 ) < 0 )
    {
		std::cout << "audio error: unable to open Audio" << std::endl;
        return;    
    }
	if ((chew = Mix_LoadWAV("SDL_includes/chew.wav")) == NULL)
	{
		std::cout << "audio error: unable to load file" << std::endl;
		return;
	}
	Mix_VolumeChunk(chew, MIX_MAX_VOLUME/2);
	Mix_PlayChannel( -1, chew, -1);
	SDL_Delay(500);
	Mix_FreeChunk(chew);
}

void playCrash()
{
	Mix_Chunk *crash = NULL;
	if( Mix_OpenAudio( 44100, AUDIO_S16SYS, 2, 1024 ) < 0 )
    {
		std::cout << "audio error: unable to open Audio" << std::endl;
        return;    
    }
	if ((crash = Mix_LoadWAV("SDL_includes/crash.wav")) == NULL)
	{
		std::cout << "audio error: unable to load file" << std::endl;
		return;
	}
	Mix_VolumeChunk(crash, MIX_MAX_VOLUME/2);
	Mix_PlayChannel( -1, crash, -1);
	SDL_Delay(500);
	Mix_FreeChunk(crash);
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