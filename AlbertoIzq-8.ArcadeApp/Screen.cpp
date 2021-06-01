#include "Screen.h"

#include <cassert>

void Screen::clearScreen()
{
	assert(moptrWindow);
	if (moptrWindow)
	{
		SDL_FillRect(mnoptrWindowSurface, nullptr, mClearColor.getPixelColor());
	}
	
}

Screen::Screen() : mWidth(0), mHeight(0), moptrWindow(nullptr), mnoptrWindowSurface(nullptr)
{
}

Screen::~Screen()
{
	if (moptrWindow)
	{
		SDL_DestroyWindow(moptrWindow); // Destroys window and frees memory
		moptrWindow = nullptr;
	}
	SDL_Quit(); // Cleans the SDL_Init()
}

SDL_Window* Screen::init(uint32_t w, uint32_t h, uint32_t mag)
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		std::cout << "Error SDL_Init failed" << std::endl;
		return nullptr;
	}

	mWidth = w;
	mHeight = h;

	// Creates window and does memory allocation
	moptrWindow = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth * mag, mHeight * mag, 0);

	if (moptrWindow)
	{
		mnoptrWindowSurface = SDL_GetWindowSurface(moptrWindow);
		SDL_PixelFormat* pixel_format = mnoptrWindowSurface->format;
		Color::initColorFormat(pixel_format);
		mClearColor = Color::Black();
		mBackBuffer.init(pixel_format->format, mWidth, mHeight);
		mBackBuffer.clear(mClearColor);
	}

	return moptrWindow;	
}

void Screen::swapScreens()
{
	assert(moptrWindow);
	if (moptrWindow) // Make sure nothing bad happens if init() isn't been called
	{
		clearScreen(); // Clears the current front facing surface, not the backBuffer

		SDL_BlitScaled(mBackBuffer.getSurface(), nullptr, mnoptrWindowSurface, nullptr); // Copies content to another surface. SDL_BlitScaled instead of SDL_BlitSurface to take magnification into account

		SDL_UpdateWindowSurface(moptrWindow);

		mBackBuffer.clear(mClearColor);
	}
}

void Screen::draw(int x, int y, const Color& color)
{
	assert(moptrWindow);
	if (moptrWindow) // Make sure nothing bad happens if init() isn't been called
	{
		mBackBuffer.setPixel(color, x, y);
	}
}

void Screen::draw(const Vec2D& point, const Color& color)
{
	assert(moptrWindow);
	if (moptrWindow) // Make sure nothing bad happens if init() isn't been called
	{
		mBackBuffer.setPixel(color, point.getX(), point.getY());
	}
}

