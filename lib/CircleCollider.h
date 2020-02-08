#pragma once
#include "Collider.h"
class CircleCollider :public Collider
{	
public:
	CircleCollider(float _fRadius, Vec2 _vPosition);
	virtual bool collides(Collider& other) const;
	virtual bool collides(const Vec2& circlePos, float circleRadius) const;
	virtual bool collides(const Vec2& rectPos, const Vec2& rectSize)const;
	virtual bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize,
		const uint8_t* pixels) const;
	float fRadius;
	Vec2 vPosition;
};

