#pragma once

#include  <stdint.h> // More options for integer variables

#include "SDL.h"
#include "Color.h"

class ScreenBuffer
{
private:
	SDL_Surface* mSurface;

	uint32_t getIndex(int r, int c);
public:
	ScreenBuffer();
	ScreenBuffer(const ScreenBuffer& screenBuffer); // Copy constructor
	~ScreenBuffer();

	ScreenBuffer& operator=(const ScreenBuffer& screenBuffer);

	void init(uint32_t format, uint32_t width, uint32_t height);
	inline SDL_Surface* getSurface() { return mSurface; } // Not const method because it could be changed
	void clear(const Color& c = Color::Black());
	void setPixel(const Color& color, int x, int y);
};