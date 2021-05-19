#pragma once

#include  <stdint.h> // More options for integer variables
#include "SDL.h"

class Color {
private:
	uint32_t mColor;
public:
	static const SDL_PixelFormat* mFormat;

	Color() : Color{ 0 } {}
	Color(uint32_t color) : mColor(color) {}
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	static void initColorFormat(const SDL_PixelFormat* format);

	inline bool operator==(const Color& c) const { return mColor == c.mColor; }
	inline bool operator!=(const Color& c) const { return not(*this == c); }
	inline uint32_t getPixelColor() const { return mColor; }

	void setRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void setRed(uint8_t red);
	void setGreen(uint8_t green);
	void setBlue(uint8_t blue);
	void setAlpha(uint8_t alpha);

	uint8_t getRed() const;
	uint8_t getGreen() const;
	uint8_t getBlue() const;
	uint8_t getAlpha() const;

	// Predefined colors
	static Color Black() { return Color(0, 0, 0, 255); }
	static Color White() { return Color(255, 255, 255, 255); }
	static Color Red() { return Color(255, 0, 0, 255); }
	static Color Green() { return Color(0, 255, 0, 255); }
	static Color Blue() { return Color(0, 0, 255, 255); }
	static Color Yellow() { return Color(255, 255, 0, 255); }
	static Color Magenta() { return Color(255, 0, 255, 255); }
	static Color Cyan() { return Color(37, 240, 217, 255); }
	static Color Pink() { return Color(252, 197, 224, 255); }
	static Color Orange() { return Color(245, 190, 100, 255); }
};