#pragma once

// Needed for static library functionality
#include "pch.h"
#include "framework.h"

#include <iostream>

namespace Game2DUtils
{
	class Vec2D
	{
	private:
		float mX, mY;

	public:
		static const Vec2D Zero;

		Vec2D() : Vec2D(0, 0) {}
		Vec2D(float x, float y) : mX{ x }, mY{ y } {}

		inline void setX(float x) { mX = x; }
		inline void setY(float x) { mX = x; }
		inline float getX() const { return mX; }
		inline float getY() const { return mY; }

		friend std::ostream& operator<<(std::ostream& consoleOut, const Vec2D& vec);

		bool operator==(const Vec2D& vec2) const;
		bool operator!=(const Vec2D& vec2) const;

		Vec2D operator-() const;
		Vec2D operator*(float scale) const;
		Vec2D operator/(float scale) const;
		Vec2D& operator*=(float scale);
		Vec2D& operator/=(float scale);
		friend Vec2D operator*(float scalar, const Vec2D& vec);

		Vec2D operator+(const Vec2D& vec) const;
		Vec2D operator-(const Vec2D& vec) const;
		Vec2D& operator+=(const Vec2D& vec);
		Vec2D& operator-=(const Vec2D& vec);

		float mag2() const; // Square magnitude
		float mag() const; // Magnitude

		Vec2D getUnitVec() const;
		Vec2D& normalize();

		float distance(const Vec2D& vec) const;

		float dot(const Vec2D& vec) const;

		Vec2D projectOnto(const Vec2D& vec2) const;

		float angleBetween(const Vec2D& vec2) const;

		Vec2D reflect(const Vec2D& normal) const;

		void rotate(float angle, const Vec2D& around_point);
		Vec2D rotationResult(float angle, const Vec2D& around_point) const;
	};
}