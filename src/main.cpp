#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "World.h"
#include "AudioSource.h"

using namespace std;

int iWidth = 800;
int iHeight = 800;

Vec2 vMousePos;
HKL kbl = GetKeyboardLayout(0);
ltex_t* pTextureRun = nullptr;
ltex_t* pTextureIdle = nullptr;




#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <sstream>
#include <vector>

#include <fstream>     
#include <iterator>

bool GetKeyInput(char _cInput)
{
	return (GetAsyncKeyState(VkKeyScanEx(_cInput, kbl)));
}

void SpriteCallback(Sprite& _sprite, float _deltaTime)
{
	Vec2 vVelocity(0, 0);
	
	//Player control
	if (GetAsyncKeyState(VK_RIGHT) || GetKeyInput('d'))
	{
		vVelocity = Vec2(128 * _deltaTime, 0);
	}
	if (GetAsyncKeyState(VK_LEFT) || GetKeyInput('a'))
	{
		vVelocity = Vec2(-128 * _deltaTime, 0);
	}


	if (vVelocity.x == 0 && _sprite.getTexture() != pTextureIdle)
	{
		_sprite.setTexture(pTextureIdle);
		_sprite.setHorizontalFrames(1);
		_sprite.setFps(1);
	}
	else if (vVelocity.x != 0 && _sprite.getTexture() != pTextureRun)
	{

		_sprite.setTexture(pTextureRun);
		_sprite.setHorizontalFrames(6);
		_sprite.setFps(6);

	}
	if (vVelocity.x < 0 && _sprite.getScale().x > 0)
	{
		_sprite.setScale(Vec2(-_sprite.getScale().x, _sprite.getScale().y));
	}
	else if (vVelocity.x > 0 && _sprite.getScale().x < 0)
	{
		_sprite.setScale(Vec2(-_sprite.getScale().x, _sprite.getScale().y));
	}
	World _world = *static_cast<World*>(_sprite.getWorld());
	if(! _world.spriteIsOnGround(_sprite))
	{
		Vec2 vGravityVelocity = _sprite.getVelocity() + Vec2(0, 8.f);
		_sprite.setVelocity(vGravityVelocity);
		vVelocity = vVelocity + vGravityVelocity * _deltaTime;
	}
	else
	{

		if (GetAsyncKeyState(VK_SPACE) || GetAsyncKeyState(VK_UP) || GetKeyInput('W'))
		{
			vVelocity = Vec2(vVelocity.x, -8);
			_sprite.setVelocity(Vec2(0, -300));
		}
		else
		{
			vVelocity.y = 0;
			_sprite.setVelocity(Vec2(0, 0));
		}
	}
	_world.moveSprite(_sprite, vVelocity);
}

int main()
{
	//1) Iniciamos la librería GFWX
	glfwInit();

	//2) Creamos una ventana
	GLFWwindow* pWindow = glfwCreateWindow(iWidth, iHeight, "", nullptr, nullptr);

	//3) Asociamos el contexto de OpenGL a la ventana
	glfwMakeContextCurrent(pWindow);

	//4) Iniciamos la librería LiteGFX
	lgfx_setup2d(iWidth, iHeight);

	bool bOpen = true;
	int iWidthRun = 0;
	int iHeighRun = 0;
	int iWidthIdle = 0;
	int iHeightIdle = 0;
	int iWidthClouds = 0;
	int iHeightClouds = 0;
	double deltaTime = 0;
	double previousTime = glfwGetTime();

	double dXMouse = 0;
	double dYMouse = 0;
	double* pXMouse = &dXMouse;
	double* pYMouse = &dYMouse;

	unsigned char* sRunBytes = stbi_load("data//run.png", &iWidthRun, &iHeighRun, nullptr, 4);	
	pTextureRun = ltex_alloc(iWidthRun, iHeighRun, 1);
	ltex_setpixels(pTextureRun, sRunBytes);
	stbi_image_free(sRunBytes);

	unsigned char* sIdleBytes = stbi_load("data//idle.png", &iWidthIdle, &iHeightIdle, nullptr, 4);
	pTextureIdle = ltex_alloc(iWidthIdle, iHeightIdle, 1);
	ltex_setpixels(pTextureIdle, sIdleBytes);
	stbi_image_free(sIdleBytes);

	Sprite player(pTextureIdle, 1, 1);
	player.setPivot(Vec2(0.5f, 0.5f));
	player.setFps(1);
	player.setPosition(Vec2(400, 372));
	player.setCollisionType(COLLISION_RECT);
	player.setCallback(SpriteCallback);


	unsigned char* sCloudsBytes = stbi_load("data//clouds.png", &iWidthClouds, &iHeightClouds, nullptr, 4);
	ltex_t* pTextureClouds = nullptr;
	pTextureClouds = ltex_alloc(iWidthClouds, iHeightClouds, 1);
	ltex_setpixels(pTextureClouds, sCloudsBytes);
	stbi_image_free(sCloudsBytes);

	World world(0.8f, 0.8f, 0.8f, pTextureClouds, "data//map.tmx");
	world.setSpriteFollowing(world.getNumberSprites());
	player.setWorld(&world);
	world.addSprite(player);

	//Audio


	ALCdevice* pDevice = alcOpenDevice(NULL);
	ALCcontext* pContext = alcCreateContext(pDevice, NULL);
	ALCboolean contextCurrent = alcMakeContextCurrent(pContext);


	//5) Bucle principal
	while (!glfwWindowShouldClose(pWindow) && bOpen)
	{
		//5.1) Actualizamos delta de tiempo
		deltaTime = glfwGetTime() - previousTime;
		previousTime = glfwGetTime();
		//5.2) Leemos input del usuario
		if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			bOpen = false;
		}
		glfwGetCursorPos(pWindow, pXMouse, pYMouse);
		vMousePos = Vec2(dXMouse, dYMouse);
		vMousePos = vMousePos + world.getCameraPosition();

		//5.3) Actualizamos lógica de juego
		world.update(deltaTime);

		//5.4-5) Limpiamos el backbuffer y renderizamos la escena.
		world.draw(Vec2(iWidth, iHeight));

		//5.6) Cambiamos el backbuffer por el frontbuffer
		glfwSwapBuffers(pWindow);

		//5.7) Procesamos eventos
		glfwPollEvents();
	}
	//6) Liberamos los recursos.
	alcDestroyContext(pContext);
	alcCloseDevice(pDevice);
	glfwTerminate();

	return 0;
}