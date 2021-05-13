#include <iostream>

#include "SDL.h"
#undef main // To avoid error: external symbol _sdl_main referenced in function _main get cmdline

const int SCREEN_WIDTH = 224; // Pixel sizes for Pac-Man
const int SCREEN_HEIGHT = 288;

void setPixel(SDL_Surface* noptr_window_surface, uint32_t color, int x, int y);
size_t getIndex(SDL_Surface* noptr_window_surface, int r, int c);

int main(int argc, const char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << "Error SDL_Init failed" << std::endl;
		return 1;
	}

	// Creates window and does memory allocation
	SDL_Window* optr_window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	if (optr_window == nullptr) {
		std::cout << "Could not create the window, got error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Surface* noptr_window_surface = SDL_GetWindowSurface(optr_window);

	SDL_PixelFormat* pixel_format = noptr_window_surface->format;
	std::cout << "The window pixel format is " << SDL_GetPixelFormatName(pixel_format->format);

	uint32_t color = 0XFF0000;
	setPixel(noptr_window_surface, color, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	SDL_UpdateWindowSurface(optr_window);

	SDL_Event sdl_event;
	bool running = true;

	while (running) {
		while (SDL_PollEvent(&sdl_event)) {
			switch (sdl_event.type) {
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

void setPixel(SDL_Surface* noptr_window_surface, uint32_t color, int x, int y) { // Put a pixel with a color in a position
	SDL_LockSurface(noptr_window_surface); // Nobody else outside this block can access it

	uint32_t* pixels = (uint32_t*)noptr_window_surface->pixels; // Getting pixels of this surface, it's a 1-D array
	size_t index = getIndex(noptr_window_surface, y, x);
	pixels[index] = color;

	SDL_UnlockSurface(noptr_window_surface);
}

size_t getIndex(SDL_Surface* noptr_window_surface, int r, int c) // Used to transform 2-D index into 1-D index
{
	return r * noptr_window_surface->w + c; // w is width
}