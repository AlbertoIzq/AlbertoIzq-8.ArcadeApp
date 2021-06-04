#pragma once

#include  <stdint.h> // More options for integer variables

#include "SDL.h"
#include "ScreenBuffer.h"
#include "Color.h"
#include "Line2D.h"

#include "Vec2D.h"
using namespace Game2DUtils;

class Screen
{
private:
	uint32_t mWidth;
	uint32_t mHeight;

	Color mClearColor;
	ScreenBuffer mBackBuffer;

	SDL_Window* moptrWindow;
	SDL_Surface* mnoptrWindowSurface;

	void clearScreen();

	Screen(const Screen& screen); // Private copy constructor to avoid the object being copied
	Screen& operator=(const Screen& screen);
public:
	Screen();
	~Screen();

	SDL_Window* init(uint32_t w, uint32_t h, uint32_t mag);
	void swapScreens();

	inline void setClearColor(const Color& clearColor) { mClearColor = clearColor; }
	inline uint32_t width() const { return mWidth; }
	inline uint32_t height() const { return mHeight; }

	// Draw methods
	void draw(int x, int y, const Color& color);
	void draw(const Vec2D& point, const Color& color);
	void draw(const Line2D& line, const Color& color);
};