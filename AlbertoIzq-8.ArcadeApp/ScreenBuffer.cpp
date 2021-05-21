#include "ScreenBuffer.h"

#include <cassert>

uint32_t ScreenBuffer::getIndex(int r, int c) // Used to transform 2-D index into 1-D index
{
	assert(mSurface);
	if (mSurface) // A guard for release mode if mSurface is null
	{
		return r * mSurface->w + c; // w is width
	}
	return 0;
}

ScreenBuffer::ScreenBuffer() : mSurface(nullptr)
{
}

ScreenBuffer::ScreenBuffer(const ScreenBuffer& screenBuffer)// Copy constructor
{
	mSurface = SDL_CreateRGBSurfaceWithFormat(0, screenBuffer.mSurface->w, screenBuffer.mSurface->h, 0, screenBuffer.mSurface->format->format);

	SDL_BlitSurface(screenBuffer.mSurface, nullptr, mSurface, nullptr); // Copy all the pixels from one surface to another. nullptr means copying the entire surface
}

ScreenBuffer::~ScreenBuffer()
{
	if (mSurface)
	{
		SDL_FreeSurface(mSurface);
	}
}

ScreenBuffer& ScreenBuffer::operator=(const ScreenBuffer& screenBuffer)
{
	if (this == &screenBuffer) // If it's the same screenBuffer
	{
		return *this;
	}

	if (mSurface != nullptr) // If we have a surface, we free it first because it may not be the same format/size
	{
		SDL_FreeSurface(mSurface);
		mSurface = nullptr;
	}

	if (screenBuffer.mSurface != nullptr) // The same as the copy constructor
	{
		mSurface = SDL_CreateRGBSurfaceWithFormat(0, screenBuffer.mSurface->w, screenBuffer.mSurface->h, 0, screenBuffer.mSurface->format->format);
		SDL_BlitSurface(screenBuffer.mSurface, nullptr, mSurface, nullptr); // Copy all the pixels from one surface to another. nullptr means copying the entire surface
	}

	return *this;
}

void ScreenBuffer::init(uint32_t format, uint32_t width, uint32_t height)
{
	mSurface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 0, format);
	clear();
}

void ScreenBuffer::clear(const Color& c)
{
	assert(mSurface); // If we have a null surface, we want to assert because it means it's not been initialized yet
	if (mSurface)
	{
		SDL_FillRect(mSurface, nullptr, c.getPixelColor());
	}
}

void ScreenBuffer::setPixel(const Color& color, int x, int y) // Put a pixel with a color in a position
{
	assert(mSurface);
	
	if (mSurface && (y < mSurface->h && y >= 0 && x < mSurface->w && x >= 0)) // Check if x and y are within boundaries
	{
		SDL_LockSurface(mSurface); // Nobody else outside this block can access it

		uint32_t* pixels = (uint32_t*)mSurface->pixels; // Getting pixels of this surface, it's a 1-D array
		size_t index = getIndex(y, x);
		pixels[index] = color.getPixelColor();

		SDL_UnlockSurface(mSurface);
	}
}