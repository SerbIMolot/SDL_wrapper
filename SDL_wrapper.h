#ifndef SDL_WRAPPER
#define SDL_WRAPPER



//#include "stdafx.h"

#include <memory>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <chrono>
#include "sdl\include\SDL_platform.h"
#include "sdl\include\SDL_ttf.h"
#include "Box2D\Box2D.h"

#include "EventData.h"
#include <cstdint>
typedef uint32_t Uint32;
/*
#include "Rectangle.h"
#include "Mouse.h"
#include "Animation.h"
#include "TimerIns.h"
#include "ContactListener.h"

#include "TextureManager.h"
#include "TriggersManager.h"
#include "SoundManager.h"
#include "ButtonManager.h"
#include "BodyManager.h"
*/
class TextureManager;
class TriggersManager;
class SoundManager;
class ButtonManager;
class BodyManager;
class EventHandle;
class ContactListener;
class engRectangle;
class Mouse;
class Body;
class Scene;


class SDL_wrapper

{

	static SDL_wrapper* instance;
public:
	static std::map<std::string, std::shared_ptr<Scene>> Scenes;

public:
	static SDL_wrapper* Instance() {
		if (instance == nullptr) {
			instance = new SDL_wrapper();
		}
		return instance;
	}

	SDL_Window* gWindow = NULL;
	SDL_Surface* gWindowSurf = NULL;


	//std::shared_ptr< Body > botbox;
	//std::shared_ptr< Body > leftbox;
	//std::shared_ptr< Body > topbox;
	//std::shared_ptr< Body > rightbox;
	//std::shared_ptr< dynBody > dybox;
	//std::shared_ptr< dynBody > dybox2;
	//std::shared_ptr< Player > pl;

	//static std::unique_ptr< BodyManager > bodyManager;
	ContactListener* _contactListener;

	static std::vector< std::shared_ptr< Body > > GameBodys;
	static std::shared_ptr< EventHandle > eventHandler;
	b2ThreadPoolTaskExecutor threadPoolExecutor;
	//static std::unique_ptr<SDL_wrapper> Game;
	

	static b2World* world;
	std::shared_ptr< Mouse > cursor;
//	static std::shared_ptr< EventHandle > eventHandler;
	//static std::unique_ptr<SDL_wrapper> Game;
	//static std::shared_ptr<SDL_wrapper> hInstance;

	static bool init;
	static bool quit;
	//GPU_RendererID rendererID;
	std::shared_ptr< Mouse > mouse = nullptr;
	//GPU_Renderer* screen;

	static SDL_DisplayMode displayMode;



	//starts SDL and creates window
	//bool Init( std::string windowName = "Demo");

	static bool GameInit( std::string windowName = "Demo", int windowWidth = 800, int windowHeight = 600) ;
	int Run(int argc, const char* argv[]);
	void resizeWindow(int windowWidth, int windowHeight);
	void InputHandler();
	static void GamePreTick() {};
	void GameTick();
	static void GamePostTick() {};
	void doPhysicsStep(float deltaTime);
	void GameDraw();
	static void GameClose();
	//load media
	bool loadMedia();

	void drawOutlinedQuad( SDL_Rect& rect, SDL_Color color, SDL_BlendFactor blend = SDL_BLENDFACTOR_ZERO);

	static void drawFilledQuad( SDL_Rect& rect, SDL_Color color, SDL_BlendFactor blend = SDL_BLENDFACTOR_ZERO);

	void drawFilledQuad( engRectangle& rect, SDL_Color color, SDL_BlendFactor blend = SDL_BLENDFACTOR_ZERO);

	void drawOutlinedQuad(  float x, float y, float w, float h, SDL_Color color, SDL_BlendFactor blend = SDL_BLENDFACTOR_ZERO);

	//static void drawOutlinedQuad( SDL_Rect & rect, SDL_Color color = RED_COLOR, SDL_BlendMode blend = SDL_BLENDMODE_NONE );
	//
	//static void drawFilledQuad( SDL_Rect & rect, SDL_Color color, SDL_BlendMode blend = SDL_BLENDMODE_NONE );
	//
	//void drawFilledQuad(engRectangle & rect, SDL_Color color, SDL_BlendMode blend);
	//
	//static void drawOutlinedQuad( int x, int y, int w, int h, SDL_Color color = RED_COLOR, SDL_BlendMode blend = SDL_BLENDMODE_NONE );
	//
	//static void drawFilledQuad(int x, int y, int w, int h, SDL_Color color, SDL_BlendMode blend = SDL_BLENDMODE_NONE );
	//

	//static std::shared_ptr<SDL_wrapper> Instance();
	void AddScene(std::string name, std::shared_ptr<Scene> scene);
	void RemoveScene(std::string name);
	void onMouseButtonEvent( int x, int y, bool hold, int button );


	virtual void onKeyPress( std::shared_ptr< Event > event ) {};

	virtual void onKeyRelease( std::shared_ptr< Event > event ) {};


	void drawFilledQuad( float x, float y, float w, float h, SDL_Color color, SDL_BlendFactor blend = SDL_BLENDFACTOR_ZERO);

	//Frees media and shots down sdl
	void close();

	SDL_wrapper();
	~SDL_wrapper();
};


#endif // !SDL_WRAPPER