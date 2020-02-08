#include "Background.h"
Background::Background(const ltex_t* tex) : Drawable(tex)
{

}
void Background::SetScrollRatio(float _fScrollRatio)
{
	fScrollRatio = _fScrollRatio;
}
void Background::SetScrollSpeed(Vec2 _vScrollSpeed)
{
	vScrollSpeed = _vScrollSpeed;
}
float Background::GetScrollRatio()
{
	return fScrollRatio;
}
Vec2 Background::GetScrollSpeed()
{
	return vScrollSpeed;
}
void Background::update(float _deltaTime)
{
	vScrollPosition = vScrollPosition + vScrollSpeed * _deltaTime;
}
void Background::draw(Vec2 _vLevelSize, Vec2 _vCameraPosition) const
{
	Vec2 vSize = getSize();
	Vec2 vOffset = Vec2(- vScale.x*(_vCameraPosition.x / _vLevelSize.x - fScrollRatio * _vCameraPosition.x/  (_vLevelSize.x)), -vScale.y*(_vCameraPosition.y/_vLevelSize.y - fScrollRatio * _vCameraPosition.y / (_vLevelSize.y)));
	vOffset = vOffset - Vec2( vScrollPosition.x / texture.width, vScrollPosition.y / texture.height);
	lgfx_setblend(blend);
	lgfx_setcolor(fRed, fGreen, fBlue, fAlpha);
	ltex_drawrotsized(&texture, vPosition.x, vPosition.y, fAngle, vPivot.x, vPivot.y, vSize.x, vSize.y, 
		vOffset.x, vOffset.y, vScale.x + vOffset.x, vScale.y + vOffset.y);
	lgfx_setcolor(1, 1, 1, 1);
}