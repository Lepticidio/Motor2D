#include "Collider.h"

float clamp(float n, float lower, float upper)
{
	n = (n > lower)* n + !(n > lower)* lower;
	return (n < upper) * n + !(n < upper) * upper;
}

bool Collider::collides(Collider& other) const
{
	return false;
}
bool Collider::collides(const Vec2& circlePos, float circleRadius)const
{
	return false;
}
bool Collider::collides(const Vec2& rectPos, const Vec2& rectSize)const
{
	return false;
}
bool Collider::collides(const Vec2& pixelsPos, const Vec2& pixelsSize,
	const uint8_t* pixels)const
{
	return false;
}
bool Collider::checkCircleCircle(const Vec2& pos1, float radius1,
	const Vec2& pos2, float radius2)const
{
	Vec2 vDifference(pos1.x - pos2.x, pos1.y - pos2.y);
	if (vDifference.Length() > radius1 + radius2)
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool Collider::checkCircleRect(const Vec2& circlePos, float circleRadius,
	const Vec2& rectPos, const Vec2& rectSize)const
{ 
	float closestX = clamp(circlePos.x, rectPos.x - rectSize.x/2, rectPos.x + rectSize.x/2);
	float closestY = clamp(circlePos.y, rectPos.y - rectSize.y/2, rectPos.y + rectSize.y/2);
	return (Vec2(closestX, closestY) - circlePos).Length() < circleRadius;
}
bool Collider::checkRectRect(const Vec2& rectPos1, const Vec2& rectSize1,
	const Vec2& rectPos2, const Vec2& rectSize2)const
{
	if (rectPos1.x > rectPos2.x - rectSize2.x / 2.  - rectSize1.x/2. && rectPos1.x < rectPos2.x + rectSize2.x / 2. + rectSize1.x / 2. &&
		rectPos1.y > rectPos2.y - rectSize2.y / 2. - rectSize1.y / 2. && rectPos1.y < rectPos2.y + rectSize2.y / 2. + rectSize1.y / 2.)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Collider::checkCirclePixels(const Vec2& circlePos, float circleRadius,
	const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels)const
{
	if (pixels != nullptr)
	{

		float minXPix = pixelsPos.x - pixelsSize.x / 2.f;
		float maxXPix = pixelsPos.x + pixelsSize.x / 2.f;
		float minYPix = pixelsPos.y - pixelsSize.y / 2.f;
		float maxYPix = pixelsPos.y + pixelsSize.y / 2.f;
		float minXCir = circlePos.x - circleRadius;
		float maxXCir = circlePos.x + circleRadius;
		float minYCir = circlePos.y - circleRadius;
		float maxYCir = circlePos.y + circleRadius;

		if (maxXPix > minXCir&& minXPix < maxXCir && maxYPix > minYCir&& minYPix < maxYCir)
		{

			int minOverlapX = 0;
			int maxOverlapX = pixelsSize.x;
			int minOverlapY = 0;
			int maxOverlapY = pixelsSize.y;

			if (minXPix < minXCir)
			{
				minOverlapX = minXCir - minXPix;
			}

			if (maxXPix > maxXCir)
			{
				maxOverlapX = maxXCir - minXPix;
			}

			if (minYPix < minYCir)
			{
				minOverlapY = minYCir - minYPix;
			}
			if (maxYPix > maxYCir)
			{
				maxOverlapY = maxYCir - minYPix;
			}

			int iWidthOverlap = maxOverlapX - minOverlapX;
			int iHeightOverlap = maxOverlapY - minOverlapY;


			bool bResult = false;
			for (int i = 0; i < iHeightOverlap; i++)
			{
				for (int j = 0; j < iWidthOverlap; j++)
				{

					if (
						*(pixels + (((i + minOverlapY) * (int)pixelsSize.x + j + minOverlapX) * 4 + 3)) > 0
						)
					{
						if ((Vec2(minXPix + minOverlapX + j, minYPix + minOverlapY + i) - circlePos).Length() <= circleRadius)
						{
							bResult = true;

						}
					}
				}

			}

			return bResult;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
bool Collider::checkPixelsPixels(
	const Vec2& pixelsPos1, const Vec2& pixelsSize1, const uint8_t* pixels1,
	const Vec2& pixelsPos2, const Vec2& pixelsSize2, const uint8_t* pixels2)const
{	
	if (pixels1 != nullptr && pixels2 != nullptr)
	{

		float minX1 = pixelsPos1.x - pixelsSize1.x / 2.f;
		float maxX1 = pixelsPos1.x + pixelsSize1.x / 2.f;
		float minY1 = pixelsPos1.y - pixelsSize1.y / 2.f;
		float maxY1 = pixelsPos1.y + pixelsSize1.y / 2.f;
		float minX2 = pixelsPos2.x - pixelsSize2.x / 2.f;
		float maxX2 = pixelsPos2.x + pixelsSize2.x / 2.f;
		float minY2 = pixelsPos2.y - pixelsSize2.y / 2.f;
		float maxY2 = pixelsPos2.y + pixelsSize2.y / 2.f;

		if (maxX1 > minX2&& minX1 < maxX2 && maxY1 > minY2&& minY1 < maxY2)
		{

			int minOverlapX1 = 0;
			int maxOverlapX1 = pixelsSize1.x;
			int minOverlapY1 = 0;
			int maxOverlapY1 = pixelsSize1.y;
			int minOverlapX2 = 0;
			int maxOverlapX2 = pixelsSize2.x;
			int minOverlapY2 = 0;
			int maxOverlapY2 = pixelsSize2.y;

			if (minX1 < minX2)
			{
				minOverlapX1 = minX2 - minX1;
			}
			else
			{
				minOverlapX2 = minX1 - minX2;
			}
			if (maxX1 > maxX2)
			{
				maxOverlapX1 = maxX2 - minX1;
			}
			else
			{
				maxOverlapX2 = maxX1 - minX2;
			}

			if (minY1 < minY2)
			{
				minOverlapY1 = minY2 - minY1;
			}
			else
			{
				minOverlapY2 = minY1 - minY2;
			}
			if (maxY1 > maxY2)
			{
				maxOverlapY1 = maxY2 - minY1;
			}
			else
			{
				maxOverlapY2 = maxY1 - minY2;
			}

			int iWidthOverlap = maxOverlapX1 - minOverlapX1;
			int iHeightOverlap = maxOverlapY1 - minOverlapY1;

			bool bResult = false;
			for (int i = 0; i < iHeightOverlap; i++)
			{
				for (int j = 0; j < iWidthOverlap; j++)
				{

					if (
							*(pixels1 + (((i + minOverlapY1) * (int)pixelsSize1.x + j + minOverlapX1) * 4 + 3)) > 0 &&
							*(pixels2 + (((i + minOverlapY2) * (int)pixelsSize2.x + j + minOverlapX2) * 4 + 3)) > 0
						)
					{
						bResult = true;
					}
				}
			}
			return bResult;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
bool Collider::checkPixelsRect(
	const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels,
	const Vec2& rectPos, const Vec2& rectSize)const
{
	if (pixels != nullptr)
	{

		float minXPix = pixelsPos.x - pixelsSize.x / 2.f;
		float maxXPix = pixelsPos.x + pixelsSize.x / 2.f;
		float minYPix = pixelsPos.y - pixelsSize.y / 2.f;
		float maxYPix = pixelsPos.y + pixelsSize.y / 2.f;
		float minXRec = rectPos.x - rectSize.x / 2.f;
		float maxXRec = rectPos.x + rectSize.x / 2.f;
		float minYRec = rectPos.y - rectSize.y / 2.f;
		float maxYRec = rectPos.y + rectSize.y / 2.f;

		if (maxXPix > minXRec&& minXPix < maxXRec && maxYPix > minYRec&& minYPix < maxYRec)
		{

			int minOverlapX = 0;
			int maxOverlapX = pixelsSize.x;
			int minOverlapY = 0;
			int maxOverlapY = pixelsSize.y;

			if (minXPix < minXRec)
			{
				minOverlapX = minXRec - minXPix;
			}

			if (maxXPix > maxXRec)
			{
				maxOverlapX = maxXRec - minXPix;
			}

			if (minYPix < minYRec)
			{
				minOverlapY = minYRec - minYPix;
			}
			if (maxYPix > maxYRec)
			{
				maxOverlapY = maxYRec - minYPix;
			}

			int iWidthOverlap = maxOverlapX - minOverlapX;
			int iHeightOverlap = maxOverlapY - minOverlapY;


			bool bResult = false;
			for (int i = 0; i < iHeightOverlap; i++)
			{
				for (int j = 0; j < iWidthOverlap; j++)
				{

					if (
						*(pixels + (((i + minOverlapY) * (int)pixelsSize.x + j + minOverlapX) * 4 + 3)) > 0 
						)
					{
						bResult = true;
					}
				}

			}

			return bResult;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
