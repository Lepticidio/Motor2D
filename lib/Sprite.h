#pragma once

#include "Background.h"
#include "CircleCollider.h"
#include "RectCollider.h"
#include "PixelsCollider.h"



enum CollisionType
{
	COLLISION_NONE,
	COLLISION_CIRCLE,
	COLLISION_RECT,
	COLLISION_PIXELS
};

class Sprite : public Drawable
{
public:
	// Tpo de la función callback 
	typedef void (* CallbackFunc)(Sprite&, float);

	// Indicamos el número de frames en horizontal y vertical
	// que tendrá la imagen del sprite 
	Sprite(const ltex_t* tex, int hframes = 1, int vframes = 1); 

	// Establecemos puntero a la función callback 
	void setCallback(CallbackFunc func); 

	// Puntero genérico a datos (normalmente introducimos aquí los datos 
	// del sprite que se van a utilizar en la función callback) 
	void* getUserData(); 
	void setUserData(void* data); 

	int getHframes() const; 
	int getVframes() const;
	// Tamaño de un frame multiplicado por la escala 
	Vec2 getSize() const;
	// Veces por segundo que se cambia el frame de animación 
	int getFps() const; 
	void setFps(int fps); 
	// Frame actual de animación 
	float getCurrentFrame() const; 
	void setCurrentFrame(int frame);
	void setHorizontalFrames(int hf);
	void setVerticalFrames(int vf);

	virtual void update(float deltaTime);
	virtual void draw() const;

	void setCollisionType(CollisionType type);
	CollisionType getCollisionType() const;
	const Collider* getCollider() const;
	bool collides(Sprite& other);
	Vec2 getVelocity() const;
	void setVelocity(Vec2 _velocity);

private:
	int iCurrentFrame = 0;
	int iFps = 0;
	int iHorizontalFrames;
	int iVerticalFrames;
	float fcurrentAnimationTime = 0;
	void* pWorld;
	Vec2 vVelocity = Vec2(0, 0);
	CallbackFunc callbackFunc;
	CollisionType eType;
	Collider* pCollider;
public:
	inline void setWorld(void* _world) { pWorld = _world; };
	inline void* getWorld() {return pWorld;};
};

