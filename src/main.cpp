#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#ifdef _WIN32
#include "glut.h"
#pragma comment(linker,"/SUBSYSTEM:CONSOLE")
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __EMSCRIPTEN__
#include <GL/glut.h>
#include <GLES3/gl32.h>
#include <emscripten/html5.h>
#endif

#ifdef __linux__
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#ifdef _MSC_VER
#define UNUSED_ARGS(...) (void)(true ? (void)0 : ((void)(__VA_ARGS__)))
#else
#define UNUSED_ARGS(...)
#endif


#include <NsRender/GLFactory.h>
#include <NsGui/IntegrationAPI.h>
#include <NsGui/IRenderer.h>
#include <NsGui/IView.h>
#include <NsGui/Grid.h>


static Noesis::IView* _view;

#include "World.h"
#include "AudioListener.h"

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


void LogHandler(const char* filename, uint32_t line, uint32_t level, const char* channel,
	const char* message)
{
	if (strcmp(channel, "") == 0)
	{
		// [TRACE] [DEBUG] [INFO] [WARNING] [ERROR]
		const char* prefixes[] = { "T", "D", "I", "W", "E" };
		const char* prefix = level < NS_COUNTOF(prefixes) ? prefixes[level] : " ";
		fprintf(stderr, "[NOESIS/%s] %s\n", prefix, message);
	}
}


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

	Noesis::GUI::Init(nullptr, LogHandler, nullptr);
	// For simplicity purposes we are not using resource providers in this sample. ParseXaml() is
	// enough if there is no extra XAML dependencies
	Noesis::Ptr<Noesis::Grid> xaml(Noesis::GUI::ParseXaml<Noesis::Grid>(R"(
        <Grid xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation">
            <Grid.Background>
                <LinearGradientBrush StartPoint="0,0" EndPoint="0,1">
                    <GradientStop Offset="0" Color="#FF123F61"/>
                    <GradientStop Offset="0.6" Color="#FF0E4B79"/>
                    <GradientStop Offset="0.7" Color="#FF106097"/>
                </LinearGradientBrush>
            </Grid.Background>
            <Viewbox>
                <StackPanel Margin="50">
                    <Button Content="Hello World!" Margin="0,30,0,0"/>
                    <Rectangle Height="5" Margin="-10,20,-10,0">
                        <Rectangle.Fill>
                            <RadialGradientBrush>
                                <GradientStop Offset="0" Color="#40000000"/>
                                <GradientStop Offset="1" Color="#00000000"/>
                            </RadialGradientBrush>
                        </Rectangle.Fill>
                    </Rectangle>
                </StackPanel>
            </Viewbox>
        </Grid>
    )"));

	// View creation to render and interact with the user interface
	// We transfer the ownership to a global pointer instead of a Ptr<> because there is no way
	// in GLUT to do shutdown and we don't want the Ptr<> to be released at global time
	_view = Noesis::GUI::CreateView(xaml).GiveOwnership();
	_view->SetIsPPAAEnabled(true);

	// Renderer initialization with an OpenGL device
	_view->GetRenderer()->Init(NoesisApp::GLFactory::CreateDevice());

	//2) Creamos una ventana
	GLFWwindow* pWindow = glfwCreateWindow(iWidth, iHeight, "", nullptr, nullptr);

	//3) Asociamos el contexto de OpenGL a la ventana
	glfwMakeContextCurrent(pWindow);

	//4) Iniciamos la librería LiteGFX
	lgfx_setup2d(iWidth, iHeight);

	bool bOpen = true;

	int iWidthClouds = 0;
	int iHeightClouds = 0;
	double deltaTime = 0;
	double previousTime = glfwGetTime();

	double dXMouse = 0;
	double dYMouse = 0;
	double* pXMouse = &dXMouse;
	double* pYMouse = &dYMouse;


	unsigned char* sCloudsBytes = stbi_load("data//clouds.png", &iWidthClouds, &iHeightClouds, nullptr, 4);
	ltex_t* pTextureClouds = nullptr;
	pTextureClouds = ltex_alloc(iWidthClouds, iHeightClouds, 1);
	ltex_setpixels(pTextureClouds, sCloudsBytes);
	stbi_image_free(sCloudsBytes);

	World world(0.8f, 0.8f, 0.8f, pTextureClouds, "data//map.tmx");

	//Audio
	ALCdevice* pDevice = alcOpenDevice(NULL);
	ALCcontext* pContext = alcCreateContext(pDevice, NULL);
	ALCboolean contextCurrent = alcMakeContextCurrent(pContext);

	//AudioListener* pListener;
	//pListener->getInstance();
	AudioListener*    pAudioListener = new AudioListener();
	ALenum auxError = alGetError();
	if (auxError != AL_NO_ERROR)
	{

		return 0;
	}
	AudioBuffer* pMusic;
	pMusic = pMusic->load("data//music.wav");
	
	auxError = alGetError();
	if (auxError != AL_NO_ERROR)
	{

		return 0;
	}
	AudioSource source = AudioSource(pMusic);
	
	auxError = alGetError();
	if (auxError != AL_NO_ERROR)
	{

		return 0;
	}

	source.play();

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




		if (GetAsyncKeyState(VK_UP))
		{
			source.increasePitch();
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			source.decreasePitch();
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			source.moveRight();
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			source.moveLeft();
		}

		//5.3) Actualizamos lógica de juego
		world.update(deltaTime);
		if(source.isPlaying())
		{
			printf("is Playing\n");
		}
		else
		{
			printf("is NOT Playing\n");

		}

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