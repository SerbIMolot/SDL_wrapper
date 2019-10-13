#ifndef SDL_WRAPPER
#define SDL_WRAPPER

class SDL_wrapper;

#include "stdafx.h"

const SDL_Color BLACK_COLOR{ 0, 0, 0, 255 };
const SDL_Color RED_COLOR{ 255, 0, 0, 255 };
const SDL_Color GREEN_COLOR{ 0, 255, 0, 255 };
const SDL_Color BLUE_COLOR{ 0, 0, 255, 255 };
const SDL_Color WHITE_COLOR{ 255, 255, 255, 255 };

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

class SDL_wrapper
{
public:


//	static std::shared_ptr< EventHandle > eventHandler;
	//static std::unique_ptr<SDL_wrapper> Game;
	static std::shared_ptr<SDL_wrapper> hInstance;
	SDL_Window* gWindow = NULL;
	static bool quit;

	std::shared_ptr< Mouse > mouse = nullptr;

	static GPU_Target* gRenderer;

	static SDL_DisplayMode displayMode;



	//starts SDL and creates window
	bool Init( std::string windowName = "Demo");
	//load media
	bool loadMedia();

	void drawOutlinedQuad( GPU_Rect& rect, SDL_Color color, GPU_BlendPresetEnum blend = GPU_BLEND_NORMAL );

	void drawFilledQuad( GPU_Rect& rect, SDL_Color color, GPU_BlendPresetEnum blend = GPU_BLEND_NORMAL );

	void drawFilledQuad( engRectangle& rect, SDL_Color color, GPU_BlendPresetEnum blend = GPU_BLEND_NORMAL );

	void drawOutlinedQuad(  float x, float y, float w, float h, SDL_Color color, GPU_BlendPresetEnum blend = GPU_BLEND_NORMAL );

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

	static std::shared_ptr<SDL_wrapper> Instance();

	void onMouseButtonEvent( int x, int y, bool hold, int button );


	void onKeyPress( SDL_Scancode key = SDL_SCANCODE_UNKNOWN );

	void onKeyRelease( SDL_Scancode key = SDL_SCANCODE_UNKNOWN );



	void drawFilledQuad( float x, float y, float w, float h, SDL_Color color, GPU_BlendPresetEnum blend = GPU_BLEND_NORMAL );

	//Frees media and shots down sdl
	void close();

	SDL_wrapper();
	~SDL_wrapper();
};



#endif // !SDL_WRAPPER