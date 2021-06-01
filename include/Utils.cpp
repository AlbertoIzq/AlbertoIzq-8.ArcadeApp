// Needed for static library functionality
#include "pch.h"
#include "framework.h"

#include "Utils.h"
#include <cmath> // Used for fabs

namespace Game2DUtils
{
	bool isEqual(float x, float y)
	{
		return fabs(x - y) < EPSILON;
	}

	bool isGreaterThanOrEqual(float x, float y)
	{
		return x > y || isEqual(x, y);
	}

	bool isLessThanOrEqual(float x, float y)
	{
		return x < y || isEqual(x, y);
	}
}