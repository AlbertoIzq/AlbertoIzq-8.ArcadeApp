#include "pch.h"
#include "framework.h"

#include "Vec2D.h"
#include "Utils.h"
#include <cassert> // Used for assert
#include <cmath> // Used for epsilon value, sqrt and acosf

namespace Game2DUtils
{
	const Vec2D Vec2D::Zero;

	// Friend functions
	std::ostream& operator<<(std::ostream& consoleOut, const Vec2D& vec)
	{
		std::cout << "X: " << vec.mX << ", Y: " << vec.mY << std::endl;
		return consoleOut;
	}

	Vec2D operator*(float scalar, const Vec2D& vec)
	{
		return vec * scalar;
	}

	// Operator overloading
	bool Vec2D::operator==(const Vec2D& vec2) const
	{
		return isEqual(mX, vec2.mX) && isEqual(mY, vec2.mY);
	}
	bool Vec2D::operator!=(const Vec2D& vec2) const
	{
		return !(*this == vec2);
	}

	Vec2D Vec2D::operator-() const
	{
		return Vec2D(-mX, -mY);
	}

	Vec2D Vec2D::operator*(float scale) const
	{
		return Vec2D(scale * mX, scale * mY);
	}

	Vec2D Vec2D::operator/(float scale) const
	{
		assert(fabs(scale) > EPSILON); // Used to make sure that this condition is true. If not, program crashes

		return Vec2D(mX / scale, mY / scale);
	}

	Vec2D& Vec2D::operator*=(float scale)
	{
		*this = *this * scale;
		return *this;
	}

	Vec2D& Vec2D::operator/=(float scale)
	{
		assert(fabs(scale) > EPSILON);
		*this = *this / scale;
		return *this;
	}

	Vec2D Vec2D::operator+(const Vec2D& vec) const
	{
		return Vec2D(mX + vec.mX, mY + vec.mY);
	}

	Vec2D Vec2D::operator-(const Vec2D& vec) const
	{
		return Vec2D(mX - vec.mX, mY - vec.mY);
	}
	Vec2D& Vec2D::operator+=(const Vec2D& vec)
	{
		*this = *this + vec;
		return *this;
	}

	Vec2D& Vec2D::operator-=(const Vec2D& vec)
	{
		*this = *this - vec;
		return *this;
	}

	// Magnitude
	float Vec2D::mag2() const
	{
		return mX * mX + mY * mY;
	}

	float Vec2D::mag() const
	{
		return sqrt(mag2());
	}

	Vec2D Vec2D::getUnitVec() const
	{
		float mag_value = mag();

		if (mag_value > EPSILON)
		{
			return *this / mag_value;
		}

		return Vec2D::Zero;
	}

	Vec2D& Vec2D::normalize()
	{
		float mag_value = mag();

		if (mag_value > EPSILON)
		{
			*this /= mag_value;
		}

		return *this;
	}

	float Vec2D::distance(const Vec2D& vec) const
	{
		return (vec - *this).mag();
	}

	float Vec2D::dot(const Vec2D& vec) const
	{
		return mX * vec.mX + mY * vec.mY;
	}

	Vec2D Vec2D::projectOnto(const Vec2D& vec2) const
	{
		Vec2D vec2_unit = vec2.getUnitVec();

		float dot_value = dot(vec2_unit);

		return vec2_unit * dot_value;
	}

	float Vec2D::angleBetween(const Vec2D& vec2) const
	{
		return acosf(getUnitVec().dot(vec2.getUnitVec()));
	}

	Vec2D Vec2D::reflect(const Vec2D& normal) const
	{
		// v - 2vparallel = v - 2(v dot n)n
		return *this - 2 * projectOnto(normal);
	}

	void Vec2D::rotate(float angle, const Vec2D& around_point)
	{
		float cosine = cosf(angle);
		float sine = sinf(angle);

		Vec2D thisVec(mX, mY);

		thisVec -= around_point; // Go to origin first to rotate

		float x_rot = thisVec.mX * cosine - thisVec.mY * sine;
		float y_rot = thisVec.mX * sine + thisVec.mY * cosine;

		Vec2D rot = Vec2D(x_rot, y_rot);
		*this = rot + around_point; // Back to original location
	}

	Vec2D Vec2D::rotationResult(float angle, const Vec2D& around_point) const
	{
		float cosine = cosf(angle);
		float sine = sinf(angle);

		Vec2D thisVec(mX, mY);

		thisVec -= around_point; // Go to origin first to rotate

		float x_rot = thisVec.mX * cosine - thisVec.mY * sine;
		float y_rot = thisVec.mX * sine + thisVec.mY * cosine;

		Vec2D rot = Vec2D(x_rot, y_rot);
		return rot + around_point; // Back to original location
	}
}