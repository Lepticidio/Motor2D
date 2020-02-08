#pragma once
#include "Sprite.h"
class Tile :
	public Sprite
{
public:
	Tile(const ltex_t* tex, int _id, int _x, int _y, int _width, int _height);
	void SetAsSolid();
};

