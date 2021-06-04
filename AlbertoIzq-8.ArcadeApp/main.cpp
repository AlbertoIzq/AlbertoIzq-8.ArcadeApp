#include <iostream>

#pragma warning(push, 0) // Quite the warnings coming from the SDL.h header file
#include "SDL.h"
#pragma warning(pop)
#undef main // To avoid error: external symbol _sdl_main referenced in function _main get cmdline

#include "Color.h"
#include "Screen.h"
#include "Line2D.h"

const int SCREEN_WIDTH = 224; // Pixel sizes for Pac-Man
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 1;

int main(int argc, const char* argv[])
{
	Screen screen;
	screen.init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);

	Line2D line = { Vec2D(0, 0), Vec2D(SCREEN_WIDTH, SCREEN_HEIGHT) };
	screen.draw(line, Color::Red());
	
	//screen.draw(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, Color::Yellow());
	
	screen.swapScreens();

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

	return 0;
}