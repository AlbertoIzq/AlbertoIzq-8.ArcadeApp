#include <iostream>

#pragma warning(push, 0) // Quite the warnings coming from the SDL.h header file
#include "SDL.h"
#pragma warning(pop)
#undef main // To avoid error: external symbol _sdl_main referenced in function _main get cmdline

#include "Color.h"
#include "ScreenBuffer.h"

const int SCREEN_WIDTH = 224; // Pixel sizes for Pac-Man
const int SCREEN_HEIGHT = 288;

int main(int argc, const char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		std::cout << "Error SDL_Init failed" << std::endl;
		return 1;
	}

	// Creates window and does memory allocation
	SDL_Window* optr_window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	if (optr_window == nullptr)
	{
		std::cout << "Could not create the window, got error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Surface* noptr_window_surface = SDL_GetWindowSurface(optr_window);

	SDL_PixelFormat* pixel_format = noptr_window_surface->format;

	Color::initColorFormat(pixel_format);
	
	ScreenBuffer screenBuffer;
	screenBuffer.init(pixel_format->format, noptr_window_surface->w, noptr_window_surface->h);
	screenBuffer.setPixel(Color::Red(), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	SDL_BlitSurface(screenBuffer.getSurface(), nullptr, noptr_window_surface, nullptr);

	SDL_UpdateWindowSurface(optr_window);

	SDL_Event sdl_event;
	bool running = true;

	while (running)
	{
		while (SDL_PollEvent(&sdl_event))
		{
			switch (sdl_event.type)
			{
			case SDL_QUIT: // X button in window
				running = false;
				break;
			}
		}
	}

	SDL_DestroyWindow(optr_window); // Destroys window and frees memory
	SDL_Quit(); // Cleans the SDL_Init()

	return 0;
}