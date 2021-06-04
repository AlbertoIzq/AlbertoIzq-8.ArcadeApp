#include "Screen.h"

#include <cassert>
#include <cmath> // For line drawing

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

void Screen::draw(const Line2D& line, const Color& color)
{
	assert(moptrWindow);

	if (moptrWindow)
	{
		int dx, dy;

		// We have to round up points because Bresenham's algorithm deals only with integers
		int x0 = roundf(line.getP0().getX());
		int y0 = roundf(line.getP0().getY());
		int x1 = roundf(line.getP1().getX());
		int y1 = roundf(line.getP1().getY());
		
		dx = x1 - x0;
		dy = y1 - y0;

		signed const char ix((dx > 0) - (dx < 0)); // Evaluates to 1 or -1
		signed const char iy((dy > 0) - (dy < 0));

		dx = abs(dx) * 2;
		dy = abs(dy) * 2;

		draw(x0, y0, color); // First point of the line

		if (dx >= dy) // Go along in the x
		{
			int d = dy - dx / 2;
			while (x0 != x1)
			{
				if (d >= 0)
				{
					d -= dx;
					y0 += iy;
				}
				d += dy;
				x0 += ix;
				draw(x0, y0, color);
			}
		}
		else // Go along in the y
		{
			int d = dx - dy / 2;
			while (y0 != y1)
			{
				if (d >= 0)
				{
					d -= dy;
					x0 += ix;
				}
				d += dx;
				y0 += iy;
				draw(x0, y0, color);
			}
		}
	}
}