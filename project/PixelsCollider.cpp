#include "PixelsCollider.h"

PixelsCollider::PixelsCollider(Vec2 _vSize, Vec2 _vPosition, uint8_t* _pixels) : vSize(_vSize), vPosition(_vPosition), m_pixels(_pixels)
{
}
bool PixelsCollider::collides(Collider& other) const
{
	return other.collides(vPosition, vSize, m_pixels);
}
bool PixelsCollider::collides(const Vec2& circlePos, float circleRadius)const
{
	return checkCirclePixels(circlePos, circleRadius, vPosition, vSize, m_pixels);
}
bool PixelsCollider::collides(const Vec2& rectPos, const Vec2& rectSize)const
{
	return checkPixelsRect(vPosition, vSize, m_pixels, rectPos, rectSize);
}
bool PixelsCollider::collides(const Vec2& pixelsPos, const Vec2& pixelsSize,
	const uint8_t* pixels)const
{
	return checkPixelsPixels(vPosition, vSize, m_pixels, pixelsPos, pixelsSize, pixels);
}

