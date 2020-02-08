#include "Tile.h"

Tile::Tile(const ltex_t* tex, int _id, int _x, int _y, int _width, int _height)
	: Sprite(tex, _width, _height)
{
	setCurrentFrame(_id);
}

void Tile::SetAsSolid()
{
	setCollisionType(COLLISION_RECT);
}
