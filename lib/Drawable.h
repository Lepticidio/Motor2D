
#include <glfw3.h>
#include <litegfx.h>
#include "Vec2.h"


class Drawable abstract
{
public:
	Drawable(const ltex_t* tex);
	const ltex_t* getTexture() const;
	void setTexture(const ltex_t* tex);
	lblend_t getBlend() const;
	void setBlend(lblend_t mode);
	float getRed() const;
	float getGreen() const;
	float getBlue() const;
	float getAlpha() const;
	void setColor(float r, float g, float b, float a);
	const Vec2& getPosition() const;
	void setPosition(const Vec2& pos);
	float getAngle() const;
	void setAngle(float angle);
	const Vec2& getScale() const;
	void setScale(const Vec2& scale);
	virtual void update(float _deltaTime);
	virtual void draw() const;

	// Tamaño de la textura multiplicado por la escala 
	Vec2 getSize() const;
	// Este valor se pasa a ltex_drawrotsized en el pintado 
	// para indicar el pivote de rotación 
	const Vec2& getPivot() const;
	void setPivot(const Vec2& pivot);

protected:
	ltex_t texture;
	lblend_t blend = BLEND_ALPHA;
	float fRed = 1;
	float fGreen = 1;
	float fBlue = 1;
	float fAlpha = 1;
	float fAngle = 0;
	Vec2 vPosition = Vec2(0, 0);
	Vec2 vScale = Vec2(1, 1);
	Vec2 vPivot = Vec2(0, 0);
};