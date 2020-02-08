#include "World.h"
#include "pugixml.hpp"
#include "pugiconfig.hpp"

float Clamp(float n, float lower, float upper)
{
	n = (n > lower)* n + !(n > lower)* lower;
	return (n < upper) * n + !(n < upper) * upper;
}

World::World
(
	float clearRed, float clearGreen, float clearBlue,
	const ltex_t* back0
) : fClearRed(clearRed), fClearGreen(clearGreen), fClearBlue(clearBlue), pBackgrounds{new Background(back0) }
{
	for (int i = 0; i < 1; i++)
	{
		Background* pBackground = const_cast<Background*>(pBackgrounds[i]);
		//if (vLevelSize.x < pBackground->getTexture()->width)
		//{
		//	vLevelSize = Vec2(pBackground->getTexture()->width, pBackground->getTexture()->height);
		//}
		vLevelSize = Vec2(800, 800);
	}
	for (int i = 0; i < 1; i++)
	{
		Background* pBackground = const_cast<Background*>(pBackgrounds[i]);
		pBackground->setScale(vLevelSize / pBackground->getSize());
	}
	const_cast<Background*>(pBackgrounds[0])->SetScrollRatio(0.4f);
	const_cast<Background*>(pBackgrounds[0])->SetScrollSpeed(Vec2(-16.f, -8.f));
}

World::World
(
	float clearRed, float clearGreen, float clearBlue,
	const ltex_t* back0, const char* sMap
) : fClearRed(clearRed), fClearGreen(clearGreen), fClearBlue(clearBlue), pBackgrounds{ new Background(back0) }
{

	loadMap(sMap, 1);
	for (int i = 0; i < 1; i++)
	{
		Background* pBackground = const_cast<Background*>(pBackgrounds[i]);
		//if (vLevelSize.x < pBackground->getTexture()->width)
		//{
		//	vLevelSize = Vec2(pBackground->getTexture()->width, pBackground->getTexture()->height);
		//}
	}
	for (int i = 0; i < 1; i++)
	{
		Background* pBackground = const_cast<Background*>(pBackgrounds[i]);
		pBackground->setScale(vLevelSize / pBackground->getSize());
	}
	const_cast<Background*>(pBackgrounds[0])->SetScrollRatio(0.4f);
	const_cast<Background*>(pBackgrounds[0])->SetScrollSpeed(Vec2(-16.f, -8.f));
}
int World::getSpriteFollowing() const
{
	return iSpriteFollowing;
}
int World::getNumberSprites() const
{
	return tSprites.size();
}
float World::getClearRed() const
{
	return fClearRed;
}
float World::getClearGreen() const
{
	return fClearGreen;
}
float World::getClearBlue() const
{
	return fClearBlue;
}
float World::getScrollRatio(size_t layer)
{
	Background background = *(pBackgrounds[layer]);
	return background.GetScrollRatio();
}
const Vec2& World::getScrollSpeed(size_t layer) const
{
	Background background = *(pBackgrounds[layer]);
	return background.GetScrollSpeed();
}
const Vec2& World::getCameraPosition() const
{
	return vCameraPosition;
}
const ltex_t* World::getBackground(size_t layer) const
{
	return pBackgrounds[layer]->getTexture();
}
void World::setSpriteFollowing(int _index)
{
	iSpriteFollowing = _index;
}
void World::setScrollRatio(size_t layer, float ratio)
{
	Background background = *(pBackgrounds[layer]);
	background.SetScrollRatio(ratio);
}
void World::setScrollSpeed(size_t layer, const Vec2& speed)
{
	Background background = *(pBackgrounds[layer]);
	background.SetScrollSpeed(speed);
}
void World::setCameraPosition(const Vec2& pos)
{
	vCameraPosition = pos;
}
void World::addSprite(Sprite& sprite)
{
	tSprites.push_back(sprite);
}
void World::removeSprite(Sprite& sprite)
{
	int iCounter = 0;
	while (iCounter < tSprites.size() && &(tSprites[iCounter]) != &sprite)
	{
		iCounter++;
	}
	if (iCounter < tSprites.size())
	{
		tSprites.erase(tSprites.begin() + iCounter);
	}
}
void World::update(float deltaTime)
{
	
	for (int i = 0; i < tSprites.size(); i++)
	{
		tSprites[i].update(deltaTime);
	}
	for each (const Background * background in pBackgrounds)
	{
		Background* pBackground = const_cast<Background*>(background);
		pBackground->update(deltaTime);
	}

	for (int i = 0; i < tSprites.size() - 1; i++)
	{
		bool bCollides = false;
		for (int j = i + 1; j < tSprites.size(); j++)
		{
			tSprites[i].collides(tSprites[j]);
		}
	}
}
void World::draw(const Vec2& screenSize)
{
	//Clear screen with color
	lgfx_clearcolorbuffer(fClearRed, fClearGreen, fClearBlue);

	//Center camera on first sprite
	vCameraPosition = Vec2(tSprites[iSpriteFollowing].getPosition().x - screenSize.x/2, tSprites[iSpriteFollowing].getPosition().y - screenSize.y/2);
	vCameraPosition = Vec2(Clamp(vCameraPosition.x, 0, vLevelSize.x - screenSize.x), Clamp(vCameraPosition.y, 0, vLevelSize.y - screenSize.y));
	lgfx_setorigin(vCameraPosition.x, vCameraPosition.y);

	//Draw backgrounds and sprites
	for each (const Background* background in pBackgrounds)
	{
		background->draw(vLevelSize, vCameraPosition);
	}
	for (int i = 0; i < tSprites.size(); i++)
	{
		Vec2 siz = tSprites[i].getSize();
		Vec2 pos = tSprites[i].getPosition();
		Vec2 piv = tSprites[i].getPivot();
		tSprites[i].draw();
	}
}
Vec2 World::getMapSize() const
{
	return vLevelSize;
}
bool World::moveSprite(Sprite& sprite, const Vec2& amount)
{
	bool bResult = false;
	Vec2 vCurrentPosition = sprite.getPosition();
	Vec2 vRealAmount = amount;

	Vec2 vAbsSize = sprite.getSize();
	if (vAbsSize.x < 0)
	{
		vAbsSize = Vec2(-vAbsSize.x, vAbsSize.y);
	}
	Vec2 vPivot = sprite.getPivot();

	const Collider* pCollider = sprite.getCollider();
	RectCollider* pRect = static_cast<RectCollider*>(const_cast<Collider*>(pCollider));
	pRect->vSize = vAbsSize;
	
	//Check collision x
	pRect->vPosition = vCurrentPosition + Vec2(vRealAmount.x, 0) + vAbsSize * 0.5f - vPivot * vAbsSize;
	for (int i = 0; i < tSprites.size() - 1; i++)
	{
		if (tSprites[i].collides(sprite))
		{
			bResult = true;
			vRealAmount.x = 0;
		}
	}

	//Check collision y
	pRect->vPosition = vCurrentPosition + Vec2(0, vRealAmount.y) + vAbsSize * 0.5f - vPivot * vAbsSize;
	if (vRealAmount.y > 0)
	{
		for (int i = 0; i < tSprites.size() - 1; i++)
		{
			while (tSprites[i].collides(sprite))
			{
				bResult = true;
				pRect->vPosition = vCurrentPosition + Vec2(0, --vRealAmount.y) + vAbsSize * 0.5f - vPivot * vAbsSize;
			}
		}
	}
	else if(vRealAmount.y < 0)
	{
		for (int i = 0; i < tSprites.size() - 1; i++)
		{
			if (tSprites[i].collides(sprite))
			{
				bResult = true;
				vRealAmount.y = 0;
			}
		}
	}

	sprite.setPosition(vCurrentPosition + vRealAmount);
	return bResult;
}
bool World::spriteIsOnGround(Sprite& sprite)
{
	bool bResult = false;
	Vec2 vCurrentPosition = sprite.getPosition();

	Vec2 vAbsSize = sprite.getSize();
	if (vAbsSize.x < 0)
	{
		vAbsSize = Vec2(-vAbsSize.x, vAbsSize.y);
	}
	Vec2 vPivot = sprite.getPivot();

	const Collider* pCollider = sprite.getCollider();
	RectCollider* pRect = static_cast<RectCollider*>(const_cast<Collider*>(pCollider));
	pRect->vSize = vAbsSize;

	//Check collision y
	pRect->vPosition = vCurrentPosition + Vec2(0, 1) + vAbsSize * 0.5f - vPivot * vAbsSize;
	for (int i = 0; i < tSprites.size() - 1; i++)
	{
		if (tSprites[i].collides(sprite))
		{
			bResult = true;
		}
	}
	return bResult;

}
bool World::loadMap(const char* filename, uint16_t firstColId)
{
	bool bResult = false;
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filename);
	if (result) 
	{
		// Cargado correctamente, podemos analizar su contenido ...
		pugi::xml_node mapNode = doc.child("map");
		pugi::xml_node tileset = mapNode.child("tileset");
		pugi::xml_node imageInfo = tileset.child("image");
		pugi::xml_node layer = mapNode.child("layer");
		int iWidthSet = tileset.attribute("columns").as_int();
		if (iWidthSet == 0)
		{
			iWidthSet = 1;
		}
		int iHeightSet = tileset.attribute("tilecount").as_int() / iWidthSet;
		int iWidthTile = tileset.attribute("tilewidth").as_int();
		int iHeightTile = tileset.attribute("tileheight").as_int();
		int iNHorizontalTiles = layer.attribute("width").as_int();
		int iNVerticalTiles = layer.attribute("height").as_int();

		std::string sPath = "data//";
		std::string sPath2 = imageInfo.attribute("source").as_string();
		sPath.append(sPath2);
		const int iSizeString = sPath.size() + 1;

		char* sPathChar = new char [iSizeString];
		sPath.copy(sPathChar, iSizeString);
		sPathChar[sPath.size()] = '\0';


		int iImageWidth = imageInfo.attribute("width").as_int();
		int iImageHeight = imageInfo.attribute("height").as_int();

		unsigned char* sTilesetBytes = stbi_load(sPathChar, &iImageWidth, &iImageHeight, nullptr, 4);
		ltex_t* pTextureMap = nullptr;
		pTextureMap = ltex_alloc(iImageWidth, iImageHeight, 1);
		ltex_setpixels(pTextureMap, sTilesetBytes);
		stbi_image_free(sTilesetBytes);
			
		// Iteramos por todos los tiles
		int iCounter = 0;
		vLevelSize = Vec2(iNHorizontalTiles * iWidthTile, iNVerticalTiles*iHeightTile);
		for (pugi::xml_node tileNode = layer.child("data").child("tile");
			tileNode; tileNode = tileNode.next_sibling("tile")) 
		{
			int gid = tileNode.attribute("gid").as_int();
			if (gid > 0)
			{
				int iXTile = iCounter % iNHorizontalTiles;
				int iYTile = iCounter / iNHorizontalTiles;
				Tile tile(pTextureMap, gid - 1, iXTile, iYTile, iWidthSet, iHeightSet);
				tile.setPosition(Vec2(iXTile * iWidthTile, iYTile * iHeightTile));
				tile.setCollisionType(COLLISION_RECT);
				addSprite(tile);
			}
			iCounter++;
			
		}

		bResult = true;
	}
	else 
	{
		// No se ha podido cargar
		std::cout << result.description() << std::endl;
	}
	return bResult;
}