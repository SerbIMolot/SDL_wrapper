#include "SDL_wrapper.h"


GPU_Target* SDL_wrapper::gRenderer = nullptr;

SDL_DisplayMode SDL_wrapper::displayMode;
std::shared_ptr<SDL_wrapper> SDL_wrapper::hInstance = nullptr;

bool SDL_wrapper::quit = false;

SDL_wrapper::SDL_wrapper()
{

}


SDL_wrapper::~SDL_wrapper()
{
}


void SDL_wrapper::onMouseButtonEvent(int x, int y, bool hold, int button)
{
	mouse->UpdateStats( x, y, hold, button );
	if ( button == SDL_BUTTON_LEFT)
	{
		GPU_Log("LMB PRESS\n");
		//	BodyManager::Instance()->getDynBody("Box1")->applyForce( b2Vec2( 100.0f, 0.0f ) );
		//	BodyManager::Instance()->BodyDebug( );

	}

}

void SDL_wrapper::onKeyPress(SDL_Scancode key)
{
	if (key == SDL_SCANCODE_LEFT)
	{
		Metronome::bpm += 5;
		Metronome::Instance()->UpdateInterval();
	}

	if (key == SDL_SCANCODE_B)
	{
	}
	//if ( !KEYS[ SDL_SCANCODE_LEFT ] )
	//{
	//	SDL_wrapper::Instance()->pl->move( b2Vec2( 0, 1 ) );
	//}
	if (key == SDL_SCANCODE_RIGHT)
	{
		Metronome::bpm += 5;
		Metronome::Instance()->UpdateInterval();
	}
	if (key == SDL_SCANCODE_SPACE)
	{
		Metronome::stop = true;
	}
	if ( key == SDL_SCANCODE_E )
	{
		Metronome::Instance()->button->Press();
	}
	//if ( key == SDL_SCANCODE_LEFT  )
	//{
	//	GPU_Log("Left arrow press \n");
	//	pl->move( b2Vec2( 0, 1 ) );		
	//}
	/*if ( key[ SDL_SCANCODE_LEFT ] )
	{
		GPU_Log("Left arrow press \n");
		pl->move( b2Vec2( 0, 1 ) );
	}
	if ( key[ SDL_SCANCODE_RIGHT ] )
	{
		GPU_Log("Right arrow press \n");
		pl->move( b2Vec2( 0, -1 ) );

	}
	if ( key[ SDL_SCANCODE_SPACE ] )
	{
		GPU_Log("SPACE pressed\n");
		pl->jump();
	}*/
}

void SDL_wrapper::onKeyRelease(SDL_Scancode key)
{
	if (key == SDL_SCANCODE_E)
	{
		Metronome::Instance()->button->Release();
	}
	//if ( key == SDL_SCANCODE_LEFT )
	//{
	//	GPU_Log("Left arrow release \n");
	//	pl->move( b2Vec2_zero );
	//}
	//if ( key == SDL_SCANCODE_RIGHT )
	//{
	//	SDL_Log("Right arrow release \n");
	//	pl->move( b2Vec2_zero );
	//
	//}

}


std::shared_ptr<SDL_wrapper> SDL_wrapper::Instance()
{
	if (!hInstance)
	{
		hInstance = std::make_unique< SDL_wrapper >();
		hInstance->Init();
	}
	return hInstance;
}


bool SDL_wrapper::Init( std::string windowName )
{
	bool success = true;

	GPU_RendererID rendererID = GPU_MakeRendererID( windowName.c_str(), GPU_ReserveNextRendererEnum(), 1, 0 );
	GPU_RegisterRenderer(rendererID, &create_dummy_renderer, &free_dummy_renderer);


	// Request this specific renderer
	gRenderer = GPU_InitRenderer(rendererID.renderer, 800, 600, GPU_DEFAULT_INIT_FLAGS);
	//gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		success = false;
	}


	int imgFlags = IMG_INIT_PNG;

	if ( !( IMG_Init(imgFlags) & imgFlags ) )
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		success = false;
	}

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf error: %s\n", TTF_GetError());
		success = false;

	}
	
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	GPU_SetDebugLevel( GPU_DEBUG_LEVEL_1 );

	TimerIns::Instance();
	TextureManager::Initialize();
	mouse = std::make_shared< Mouse >();






	return success;
}


bool SDL_wrapper::loadMedia()
{
	bool success = true;

	return success;
}

void SDL_wrapper::drawOutlinedQuad( GPU_Rect& rect, SDL_Color color, GPU_BlendPresetEnum blend )
{
	GPU_SetShapeBlendMode( blend );

	GPU_Rectangle2( gRenderer, rect, color );
}

void SDL_wrapper::drawFilledQuad( GPU_Rect& rect, SDL_Color color, GPU_BlendPresetEnum blend )
{
	GPU_SetShapeBlendMode( blend );

	GPU_RectangleFilled2( gRenderer, rect, color );
}

void SDL_wrapper::drawFilledQuad( engRectangle& rect, SDL_Color color, GPU_BlendPresetEnum blend )
{
	GPU_SetShapeBlendMode( blend );

	GPU_RectangleFilled2( gRenderer, rect.convertToGPURect(), color );
}

void SDL_wrapper::drawOutlinedQuad( float x, float y, float w, float h, SDL_Color color, GPU_BlendPresetEnum blend )
{
	GPU_SetShapeBlendMode( blend );

	GPU_Rectangle( gRenderer, x, y, w, h, color );
}



void SDL_wrapper::drawFilledQuad( float x, float y, float w, float h, SDL_Color color, GPU_BlendPresetEnum blend )
{
	GPU_SetShapeBlendMode( blend );

	GPU_Rectangle( gRenderer, x, y, w, h, color );
}

void SDL_wrapper::close()
{
	Metronome::stop = true;

	delete TextureManager::Initialize();
	delete TriggersManager::Instance();
	GPU_FreeTarget( gRenderer );

	SDL_DestroyWindow( gWindow );
	gRenderer = NULL;
	gWindow = NULL;

	GPU_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}



