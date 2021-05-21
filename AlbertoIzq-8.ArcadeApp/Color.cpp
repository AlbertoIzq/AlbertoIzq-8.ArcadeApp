#include "Color.h"

const SDL_PixelFormat* Color::mFormat = nullptr;

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	setRGBA(r, g, b, a);
}

void Color::initColorFormat(const SDL_PixelFormat* format)
{
	Color::mFormat = format;
}

void Color::setRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	mColor = SDL_MapRGBA(mFormat, r, g, b, a);
}

void Color::setRed(uint8_t red)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	SDL_GetRGBA(mColor, mFormat, &r, &g, &b, &a);
	setRGBA(red, g, b, a);
}

void Color::setGreen(uint8_t green)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	SDL_GetRGBA(mColor, mFormat, &r, &g, &b, &a);
	setRGBA(r, green, b, a);
}

void Color::setBlue(uint8_t blue)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	SDL_GetRGBA(mColor, mFormat, &r, &g, &b, &a);
	setRGBA(r, g, blue, a);
}

void Color::setAlpha(uint8_t alpha)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	SDL_GetRGBA(mColor, mFormat, &r, &g, &b, &a);
	setRGBA(r, g, b, alpha);
}

uint8_t Color::getRed() const
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	SDL_GetRGBA(mColor, mFormat, &r, &g, &b, &a);
	return r;
}

uint8_t Color::getGreen() const
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	SDL_GetRGBA(mColor, mFormat, &r, &g, &b, &a);
	return g;
}

uint8_t Color::getBlue() const
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	SDL_GetRGBA(mColor, mFormat, &r, &g, &b, &a);
	return b;
}

uint8_t Color::getAlpha() const
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	SDL_GetRGBA(mColor, mFormat, &r, &g, &b, &a);
	return a;
}