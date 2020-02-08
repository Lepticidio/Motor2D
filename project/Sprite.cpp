#include "Sprite.h"


unsigned char* generateUCharArray(const int _size)
{
	return new unsigned char[_size];
}
Sprite::Sprite(const ltex_t* tex, int hframes, int vframes)
	: Drawable(tex), iHorizontalFrames(hframes), iVerticalFrames(vframes)
{

}
void Sprite::setCallback(CallbackFunc func)
{
	callbackFunc = func;
}
int Sprite::getHframes() const
{
	return iHorizontalFrames;
}
int Sprite::getVframes() const
{
	return iVerticalFrames;
}
int Sprite::getFps() const
{
	return iFps;
}
void Sprite::setFps(int fps)
{
	iFps = fps;
}
void Sprite::setHorizontalFrames(int hf)
{
	iHorizontalFrames = hf;
}
void Sprite::setVerticalFrames(int vf)
{
	iVerticalFrames = vf;
}
Vec2 Sprite::getSize() const
{
	return Vec2(vScale.x * texture.width /iHorizontalFrames, vScale.y * texture.height/iVerticalFrames);
}
float Sprite::getCurrentFrame() const
{
	return iCurrentFrame;
}
void Sprite::setCurrentFrame(int frame)
{
	iCurrentFrame = frame;
}
void Sprite::update(float _deltaTime)
{
	Vec2 vAbsSize = getSize();
	if (vAbsSize.x < 0)
	{
		vAbsSize = Vec2(-vAbsSize.x, vAbsSize.y);
	}
	switch (getCollisionType())
	{
	case COLLISION_CIRCLE:
	{
		const Collider* pCollider = getCollider();
		CircleCollider* pCircle = static_cast<CircleCollider*>( const_cast<Collider*>(pCollider));
		pCircle->vPosition = vPosition;
		pCircle->fRadius = vAbsSize.x / 2;
	}
	break;
	case COLLISION_RECT:
	{
		const Collider* pCollider = getCollider();		
		RectCollider* pRect = static_cast<RectCollider*>(const_cast<Collider*>(pCollider));
		pRect->vPosition = vPosition + vAbsSize*0.5f - vPivot*vAbsSize;
		pRect->vSize = vAbsSize;
	}
	break;
	case COLLISION_PIXELS:
	{
		const Collider* pCollider = getCollider();
		PixelsCollider* pPixels = static_cast<PixelsCollider*>(const_cast<Collider*>(pCollider));
		pPixels->vPosition = vPosition;
		pPixels->vSize = vAbsSize;
	}
	break;
	default:
	{
	}
	}
	if (iFps != 0)
	{
		callbackFunc(*this, _deltaTime);
		fcurrentAnimationTime += _deltaTime;
		float fTotalAnimationTime = (iHorizontalFrames * iVerticalFrames) / iFps;
		if (fcurrentAnimationTime > fTotalAnimationTime)
		{
			fcurrentAnimationTime -= fTotalAnimationTime;
		}
		iCurrentFrame = iVerticalFrames * iHorizontalFrames * (fcurrentAnimationTime / fTotalAnimationTime);
	}
}
void Sprite::draw() const
{
	Vec2 vSize = getSize();
	Vec2 vPositionInArray(iCurrentFrame % iHorizontalFrames, iCurrentFrame / iHorizontalFrames);
	lgfx_setblend(blend);
	lgfx_setcolor(fRed, fGreen, fBlue, fAlpha);
	ltex_drawrotsized(&texture, vPosition.x, vPosition.y, fAngle, vPivot.x, vPivot.y, vSize.x, vSize.y, 
		vPositionInArray.x /(float)iHorizontalFrames, vPositionInArray.y / (float) iVerticalFrames, (vPositionInArray.x + 1.)/(float)iHorizontalFrames, (vPositionInArray.y + 1.)/(float)iVerticalFrames);
	lgfx_setcolor(1, 1, 1, 1);
}

void Sprite::setCollisionType(CollisionType type)
{
	Vec2 vAbsSize = getSize();
	if (vAbsSize.x < 0)
	{
		vAbsSize = Vec2(-vAbsSize.x, vAbsSize.y);
	}
	eType = type;
	switch (type)
	{
		case COLLISION_CIRCLE:
		{
			Vec2 size = getSize();
			float radius = size.x / 2;
			if (size.y > size.x)
			{
				radius = size.y/2;
			}
			pCollider = new CircleCollider(radius, vPosition);
		}
		break;
		case COLLISION_RECT:
		{
			pCollider = new RectCollider(vAbsSize, vPosition + vAbsSize * 0.5f - vPivot * vAbsSize);
		}
		break;
		case COLLISION_PIXELS:
		{
			int iNumberChars = vAbsSize.x * vAbsSize.y * 4;
			uint8_t* sTextureChars = generateUCharArray(iNumberChars);
			ltex_getpixels(&texture, sTextureChars);

			pCollider = new PixelsCollider(vAbsSize, vPosition, sTextureChars);
		}
		break;
		default:
		{

		}
	}
}
CollisionType Sprite::getCollisionType() const
{
	if (pCollider == nullptr)
	{
		return COLLISION_NONE;
	}
	else
	{
		return eType;
	}
}
const Collider* Sprite::getCollider() const
{
	return pCollider;
}
bool Sprite::collides(Sprite& other)
{
	if (pCollider != nullptr && other.pCollider != nullptr)
	{
		bool bResult = pCollider->collides(*(other.pCollider));
		if (bResult)
		{
		}
		return bResult;
	}
	else
	{
		return false;
	}
}
void Sprite::setVelocity(Vec2 _velocity)
{
	vVelocity = _velocity;
}
Vec2 Sprite::getVelocity() const
{
	return vVelocity;
}