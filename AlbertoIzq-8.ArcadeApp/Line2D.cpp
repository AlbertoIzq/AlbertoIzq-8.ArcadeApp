#include "Line2D.h"
#include "Utils.h"

Line2D::Line2D() 
	: Line2D(Vec2D::Zero, Vec2D::Zero) {}

Line2D::Line2D(float x0, float y0, float x1, float y1)
	: Line2D(Vec2D(x0, y0), Vec2D(x1, y1)) {}

Line2D::Line2D(const Vec2D& p0, const Vec2D& p1)
	: mP0(p0), mP1(p1) {}

bool Line2D::operator=(const Line2D& line) const
{
	return line.getP0() == mP0 && line.getP1() == mP1;
}

float Line2D::minDistanceFrom(const Vec2D& p, bool limitToSegment) const // Distance from the closest point
{
	return p.distance(closestPoint(p, limitToSegment));
}

Vec2D Line2D::closestPoint(const Vec2D& p, bool limitToSegment) const
{
	Vec2D p0ToP = p - mP0;
	Vec2D p0ToP1 = mP1 - mP0;

	float l2 = p0ToP1.mag2();
	float dot = p0ToP.dot(p0ToP1); // Projection
	float t = dot / l2;

	if (limitToSegment)
	{
		t = std::fmax(0, std::fmin(1.0f, t)); // We make sure that t < 1 and t >=
	}

	return mP0 + p0ToP1 * t; // Scaling the vector and adding point 0

}

Vec2D Line2D::midPoint() const
{
	return Vec2D((mP0.getX() + mP1.getX() / 2.0f), (mP0.getY() + mP1.getY() / 2.0f));
}

float Line2D::slope() const
{
	float dx = mP1.getX() - mP0.getX();
	
	if (fabsf(dx) < EPSILON) // If absolute value of dx is close to zero
	{
		return 0;
	}

	float dy = mP1.getY() - mP0.getY();

	return dy / dx;
}
float Line2D::length() const
{
	return mP1.distance(mP0);
}