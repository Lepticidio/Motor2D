#include "CircleCollider.h"

CircleCollider::CircleCollider(float _fRadius, Vec2 _vPosition) : fRadius(_fRadius), vPosition(_vPosition)
{
}
bool CircleCollider::collides(Collider& other) const
{
	return other.collides(vPosition, fRadius);
}
bool CircleCollider::collides(const Vec2& circlePos, float circleRadius)const
{
	return checkCircleCircle(vPosition, fRadius, circlePos, circleRadius);
}
bool CircleCollider::collides(const Vec2& rectPos, const Vec2& rectSize)const
{
	return checkCircleRect(vPosition, fRadius, rectPos, rectSize);
}
bool CircleCollider::collides(const Vec2& pixelsPos, const Vec2& pixelsSize,
	const uint8_t* pixels) const
{
	return checkCirclePixels(vPosition, fRadius, pixelsPos, pixelsSize, pixels);
}