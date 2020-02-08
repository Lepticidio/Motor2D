#pragma once

#include "Drawable.h"

class Background : public Drawable
{
private:
	float fScrollRatio = 1;
	Vec2 vScrollSpeed = Vec2(0,0);
	Vec2 vScrollPosition = Vec2(0, 0);
public:
	Background(const ltex_t* tex);
	void SetScrollRatio(float _fScrollRatio);
	void SetScrollSpeed(Vec2 _vScrollSpeed);
	float GetScrollRatio();
	Vec2 GetScrollSpeed();
	virtual void update(float _deltaTime);
	virtual void draw(Vec2 _vLevelSize, Vec2 _vCameraPosition) const;
};

