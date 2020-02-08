#pragma once
#include "Tile.h"
#include <vector>
#include <stb_image.h>

class World
{
private:
	int iSpriteFollowing = 0;
	float fClearRed;
	float fClearGreen;
	float fClearBlue;
	Vec2 vCameraPosition;
	Vec2 vLevelSize;
	const Background* pBackgrounds[1];
	std::vector<Sprite> tSprites;

public:
	World
	(
		float clearRed = 0.15f, float clearGreen = 0.15f, float clearBlue = 0.15f,
		const ltex_t* back0 = nullptr
	);
	World
	(
		float clearRed = 0.15f, float clearGreen = 0.15f, float clearBlue = 0.15f,
		const ltex_t* back0 = nullptr, const char* sMap = nullptr
	);
	int getSpriteFollowing() const;
	int getNumberSprites() const;
	float getClearRed() const;
	float getClearGreen() const;
	float getClearBlue() const;
	const ltex_t* getBackground(size_t layer) const;
	float getScrollRatio(size_t layer);
	void setScrollRatio(size_t layer, float ratio);
	const Vec2& getScrollSpeed(size_t layer) const;
	void setScrollSpeed(size_t layer, const Vec2& speed);
	const Vec2& getCameraPosition() const;
	void setSpriteFollowing(int _index);
	void setCameraPosition(const Vec2& pos);
	void addSprite(Sprite& sprite);
	void removeSprite(Sprite& sprite);
	void update(float deltaTime);
	void draw(const Vec2& screenSize);
	bool loadMap(const char* filename, uint16_t firstColId);
	Vec2 getMapSize() const;
	bool moveSprite(Sprite& sprite, const Vec2& amount);
	bool spriteIsOnGround(Sprite& sprite);

};

