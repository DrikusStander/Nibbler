
#include <SDL.h>
#include <iostream>
#define POINTS_COUNT 5

static SDL_Point points[POINTS_COUNT] = {
    {320, 200},
    {320, 240},
    {340, 240},
    {340, 200},
	{320, 200}
};




void	initGraphics(int window_x, int window_y)
{

}

int main()
{
	SDL_Window *window;                    // Declare a pointer

	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

	// Create an application window with the following settings:
	// window = SDL_CreateWindow(
	// 	"An SDL2 window",                  // window title
	// 	SDL_WINDOWPOS_UNDEFINED,           // initial x position
	// 	SDL_WINDOWPOS_UNDEFINED,           // initial y position
	// 	640,                               // width, in pixels
	// 	480,                               // height, in pixels
	// 	SDL_WINDOW_OPENGL                  // flags - see below
	// );
	SDL_Rect srcrect;
	Direction Dir;
	Dir = right;
	srcrect.x = 10;
	srcrect.y = 10;
	srcrect.w = 4;
	srcrect.h = 4;
	SDL_Renderer* renderer = NULL;
	// Check that the window was successfully created
	if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) != 0) 
	{
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Event event;
	int gameover = 0;
	

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer); 
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(renderer, points, POINTS_COUNT);
	SDL_RenderDrawRect(renderer, &srcrect);
	SDL_RenderPresent(renderer);


	// The window is open: could enter program loop here (see SDL_PollEvent())

	while (!gameover)
	{
		/* look for an event */
		if (SDL_PollEvent(&event)) 
		{
			/* an event was found */
			switch (event.type) 
			{
				/* close button clicked */
				case SDL_QUIT:
					gameover = 1;
					break;

				/* handle the keyboard */
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) 
					{
						case SDLK_LEFT:
							Dir = left;
							break;
						case SDLK_RIGHT:
							Dir = right;
							break;
						case SDLK_DOWN:
							Dir = down;
							break;
						case SDLK_UP:
							Dir = up;
							break;
						case SDLK_ESCAPE:
						case SDLK_q:
							gameover = 1;
							break;
					}
					break;
			}
		}
		
		switch (Dir)
			{
				case right:
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
					SDL_RenderClear(renderer);
					srcrect.x += 1 ;
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
					SDL_RenderDrawRect(renderer, &srcrect);
					SDL_RenderPresent(renderer);
					break;
				case left:
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
					SDL_RenderClear(renderer);
					srcrect.x -= 1 ;
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
					SDL_RenderDrawRect(renderer, &srcrect);
					SDL_RenderPresent(renderer);
					break;
				case up:
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
					SDL_RenderClear(renderer);
					srcrect.y -= 1 ;
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
					SDL_RenderDrawRect(renderer, &srcrect);
					SDL_RenderPresent(renderer);
					break;
				case down:
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
					SDL_RenderClear(renderer);
					srcrect.y += 1 ;
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
					SDL_RenderDrawRect(renderer, &srcrect);
					SDL_RenderPresent(renderer);
					break;
			}
			SDL_Delay(10);
	}

	SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

		if (renderer) {
            SDL_DestroyRenderer(renderer);
        }

	// Close and destroy the window
	if (window)
		SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
	return 0;
}

// int main ( int argc, char *argv[] )
// {

// 	/* initialize SDL */
// 	SDL_Init(SDL_INIT_VIDEO);

// 	/* set the title bar */
// 	//SDL_WM_SetCaption("SDL Test", "SDL Test");

// 	/* create window */
// 	SDL_Surface* screen = SDL_SetVideoMode(640, 480, 0, 0);

// 	/* load bitmap to temp surface */
// 	SDL_Surface* temp = SDL_LoadBMP("sdl_logo.bmp");

// 	/* convert bitmap to display format */
// 	SDL_Surface* bg = SDL_DisplayFormat(temp);

// 	/* free the temp surface */
// 	SDL_FreeSurface(temp);

// 	SDL_Event event;
// 	int gameover = 0;

// 	/* message pump */
// 	while (!gameover)
// 	{
// 		/* look for an event */
// 		if (SDL_PollEvent(&event)) 
// 		{
// 			/* an event was found */
// 			switch (event.type) 
// 			{
// 				/* close button clicked */
// 				case SDL_QUIT:
// 					gameover = 1;
// 					break;

// 				/* handle the keyboard */
// 				case SDL_KEYDOWN:
// 					switch (event.key.keysym.sym) 
// 					{
// 						case SDLK_ESCAPE:
// 						case SDLK_q:
// 							gameover = 1;
// 							break;
// 					}
// 					break;
// 			}
// 		}
// 		/* draw the background */
// 		SDL_BlitSurface(bg, NULL, screen, NULL);

// 		/* update the screen */
// 		SDL_UpdateRect(screen, 0, 0, 0, 0);
// 	}

// 	/* free the background surface */
// 	SDL_FreeSurface(bg);

// 	/* cleanup SDL */
// 	SDL_Quit();

// 	return 0;
// }