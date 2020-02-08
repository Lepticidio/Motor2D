#include "Drawable.h"

Drawable::Drawable(const ltex_t* tex) : texture(*tex)
{

}
const ltex_t* Drawable::getTexture() const
{
	return &texture;
}
void Drawable::setTexture(const ltex_t* tex)
{
	texture = *tex;
}
lblend_t Drawable::getBlend() const
{
	return blend;
}
void Drawable::setBlend(lblend_t mode)
{
	blend = mode;
}
float Drawable::getRed() const
{
	return fRed;
}
float Drawable::getGreen() const
{
	return fGreen;
}
float Drawable::getBlue() const
{
	return fBlue;
}
float Drawable::getAlpha() const
{
	return fAlpha;
}
void Drawable::setColor(float r, float g, float b, float a)
{
	fRed = r;
	fGreen = g;
	fBlue = b;
	fAlpha = a;
}
const Vec2& Drawable::getPosition() const
{
	return vPosition;
}
void Drawable::setPosition(const Vec2& pos)
{
	vPosition = pos;
}
float Drawable::getAngle() const
{
	return fAngle;
}
void Drawable::setAngle(float angle)
{
	fAngle = angle;
}
const Vec2& Drawable::getScale() const
{
	return vScale;
}
void Drawable::setScale(const Vec2& scale)
{
	vScale = scale;
}
Vec2 Drawable::getSize() const
{
	return Vec2(vScale.x * texture.width, vScale.y * texture.height);
}
const Vec2& Drawable::getPivot() const
{
	return vPivot;
}
void Drawable::setPivot(const Vec2& pivot)
{
	vPivot = pivot;
}
void Drawable::update(float _deltaTime)
{
}
void Drawable::draw() const
{	
}