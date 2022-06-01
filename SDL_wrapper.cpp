
#include <string>
#include "SDL_wrapper.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Constants.h"
#include "TextureManager.h"
#include "EventHandle.h"
#include "SoundManager.h"
#include "TriggersManager.h"
#include "TimerIns.h"
#include "Box2D.h"
#include "ContactListener.h"
#include "Mouse.h"
#include "Scene.h"
#include "Log.h"
//#include "Level1.h"
#include "BodyManager.h" 
#include "SceneManager.h" 
#undef NFONT_USE_SDL_GPU
#undef FC_USE_SDL_GPU

SDL_DisplayMode SDL_wrapper::displayMode;
//std::shared_ptr<SDL_wrapper> SDL_wrapper::hInstance = nullptr;
bool SDL_wrapper::init = false;
SDL_wrapper* SDL_wrapper::instance = nullptr;
bool SDL_wrapper::quit = false;
std::shared_ptr< EventHandle > SDL_wrapper::eventHandler = std::make_shared< EventHandle >();
b2World* SDL_wrapper::world = new b2World(b2Vec2(0.0f, 10.0f));
SDL_wrapper::SDL_wrapper()
{

}


SDL_wrapper::~SDL_wrapper()
{
	//delete instance;
	TimerIns::Instance()->Release();
	TextureManager::Instance()->Close("all");
	//TriggersManager::Instance()->;
	SoundManager::Instance()->Close("all");
	//OUT IF RANGE___________________________________
	SDL_wrapper::Instance()->GameClose();
	//OUT IF RANGE-------------------------------------
}

void printRenderers(void)
{
	SDL_version compiled;
	SDL_version linked;
	//GPU_RendererID* renderers;
	int i;
	int order_size;
	//GPU_RendererID order[GPU_RENDERER_ORDER_MAX];

	//GPU_SetDebugLevel(GPU_DEBUG_LEVEL_MAX);

	//compiled = GPU_GetCompiledVersion();
	//linked = GPU_GetLinkedVersion();
	//if (compiled.major != linked.major || compiled.minor != linked.minor || compiled.patch != linked.patch)
	//	//GPU_Log("SDL_gpu v%d.%d.%d (compiled with v%d.%d.%d)\n", linked.major, linked.minor, linked.patch, compiled.major, compiled.minor, compiled.patch);
	//else
		//GPU_Log("SDL_gpu v%d.%d.%d\n", linked.major, linked.minor, linked.patch);

	////renderers /*= (GPU_RendererID*)malloc(sizeof(GPU_RendererID) * GPU_GetNumRegisteredRenderers());
	//GPU_GetRegisteredRendererList(renderers);*/

	//GPU_Log("\nAvailable renderers:\n");
	////for (i = 0; i < GPU_GetNumRegisteredRenderers(); i++)
	//{
	//	//GPU_Log("* %s (%d.%d)\n", renderers[i].name, renderers[i].major_version, renderers[i].minor_version);
	//}
	////GPU_Log("Renderer init order:\n");

	//GPU_GetRendererOrder(&order_size, order);
	//for (i = 0; i < order_size; i++)
	//{
	//	//GPU_Log("%d) %s (%d.%d)\n", i + 1, order[i].name, order[i].major_version, order[i].minor_version);
	//}
	////GPU_Log("\n");

	//free(renderers);
}

void printCurrentRenderer(void)
{
	//.GPU_Renderer* renderer = GPU_GetCurrentRenderer();
//GPU_RendererID id = renderer->id;

	////GPU_Log("Using renderer: %s (%d.%d)\n", id.name, id.major_version, id.minor_version);
	////GPU_Log(" Shader versions supported: %d to %d\n\n", renderer->min_shader_version, renderer->max_shader_version);
}
void SDL_wrapper::AddScene(std::string name, std::shared_ptr<Scene> scene) {

	SDL_wrapper::Scenes.insert(std::pair<std::string, std::shared_ptr<Scene>>(name, scene));


}
void SDL_wrapper::RemoveScene(std::string name) {
	auto foundScene = SDL_wrapper::Scenes.find(name);
	if (foundScene == SDL_wrapper::Scenes.end()) {
		return;
	}
	SDL_wrapper::Scenes.erase(foundScene);


}
std::map<std::string, std::shared_ptr<Scene>> SDL_wrapper::Scenes = std::map<std::string, std::shared_ptr<Scene>>();

GPU_Target* initialize_demo( Uint16 w, Uint16 h)
{
	//GPU_Target* screen;
	printRenderers();

	//GPU_RendererEnum renderer = GPU_RENDERER_OPENGL_2;
	// Parse command line args
	/*
	{
		
		for (int i = 1; i < argc; i++)
		{
			char* s = argv[i];

			if (s[0] == '-')
			{
				if (strcmp(s, "-r") == 0 || strcmp(s, "--renderer") == 0)
				{
					i++;
					if (i >= argc)
						break;

					s = argv[i];
					if (SDL_strcasecmp(s, "BASE") == 0 || SDL_strcasecmp(s, "OpenGL_BASE") == 0 || SDL_strcasecmp(s, "OpenGL_1_BASE") == 0)
						renderer = GPU_RENDERER_OPENGL_1_BASE;
					else if (SDL_strcasecmp(s, "OpenGL_1") == 0)
						renderer = GPU_RENDERER_OPENGL_1;
					else if (SDL_strcasecmp(s, "OpenGL_2") == 0)
						renderer = GPU_RENDERER_OPENGL_2;
					else if (SDL_strcasecmp(s, "OpenGL_3") == 0)
						renderer = GPU_RENDERER_OPENGL_3;
					else if (SDL_strcasecmp(s, "OpenGL_4") == 0)
						renderer = GPU_RENDERER_OPENGL_4;
				}
			}
		}
	}
	*/
	//if (renderer == GPU_RENDERER_UNKNOWN)
	//	screen = GPU_Init(w, h, GPU_DEFAULT_INIT_FLAGS);
	//else
	//	screen = GPU_InitRenderer(renderer, w, h, GPU_DEFAULT_INIT_FLAGS);

	/*if (screen == NULL)
		return NULL;*/

	//printCurrentRenderer();
	return NULL;
}


// Loads a shader and prepends version/compatibility info before compiling it.
// Normally, you can just use GPU_LoadShader() for shader source files or GPU_CompileShader() for strings.
// However, some hardware (certain ATI/AMD cards) does not let you put non-#version preprocessing at the top of the file.
// Therefore, I need to prepend the version info here so I can support both GLSL and GLSLES with one shader file.
//Uint32 load_shader(GPU_ShaderEnum shader_type, const char* filename)
//{
//	SDL_RWops* rwops;
//	Uint32 shader;
//	char* source;
//	int header_size, file_size;
//	const char* header = "";
//	GPU_Renderer* renderer = GPU_GetCurrentRenderer();
//
//	// Open file
//	rwops = SDL_RWFromFile(filename, "rb");
//	if (rwops == NULL)
//	{
//		GPU_PushErrorCode("load_shader", GPU_ERROR_FILE_NOT_FOUND, "Shader file \"%s\" not found", filename);
//		return 0;
//	}
//
//	// Get file size
//	file_size = static_cast< int > ( SDL_RWseek(rwops, 0, SEEK_END) );
//	SDL_RWseek(rwops, 0, SEEK_SET);
//
//	// Get size from header
//	if (renderer->shader_language == GPU_LANGUAGE_GLSL)
//	{
//		if (renderer->max_shader_version >= 120)
//			header = "#version 120\n";
//		else
//			header = "#version 110\n";  // Maybe this is good enough?
//	}
//	else if (renderer->shader_language == GPU_LANGUAGE_GLSLES)
//		header = "#version 100\nprecision mediump int;\nprecision mediump float;\n";
//
//	header_size = ( int )strlen(header);
//
//	// Allocate source buffer
//	source = (char*)malloc(sizeof(char) * (header_size + file_size + 1));
//
//	// Prepend header
//	strcpy_s(source, strlen( source ), header);
//
//	// Read in source code
//	SDL_RWread(rwops, source + strlen(source), 1, file_size);
//	source[header_size + file_size] = '\0';
//
//	// Compile the shader
//	shader = GPU_CompileShader(shader_type, source);
//
//	// Clean up
//	free(source);
//	SDL_RWclose(rwops);
//
//	return shader;
//}

void SDL_wrapper::onMouseButtonEvent(int x, int y, bool hold, int button)
{
	if ( button == SDL_BUTTON_LEFT)
	{
		//GPU_Log("LMB PRESS\n");
		//	BodyManager::Instance()->getDynBody("Box1")->applyForce( b2Vec2( 100.0f, 0.0f ) );
		//	BodyManager::Instance()->BodyDebug( );

	}
	//cursor->UpdateStats( x, y, hold, button );

}

//void SDL_wrapper::onKeyPress(SDL_Scancode key)
//{
//
//	//if ( key == SDL_SCANCODE_LEFT  )
//	//{
//	//	//GPU_Log("Left arrow press \n");
//	//	pl->move( b2Vec2( 0, 1 ) );		
//	//}
//	/*if ( key[ SDL_SCANCODE_LEFT ] )
//	{
//		//GPU_Log("Left arrow press \n");
//		pl->move( b2Vec2( 0, 1 ) );
//	}
//	if ( key[ SDL_SCANCODE_RIGHT ] )
//	{
//		//GPU_Log("Right arrow press \n");
//		pl->move( b2Vec2( 0, -1 ) );
//
//	}
//	if ( key[ SDL_SCANCODE_SPACE ] )
//	{
//		//GPU_Log("SPACE pressed\n");
//		pl->jump();
//	}*/
//}

//void SDL_wrapper::onKeyRelease(SDL_Scancode key)
//{
//
//	//if ( key == SDL_SCANCODE_LEFT )
//	//{
//	//	//GPU_Log("Left arrow release \n");
//	//	pl->move( b2Vec2_zero );
//	//}
//	//if ( key == SDL_SCANCODE_RIGHT )
//	//{
//	//	SDL_Log("Right arrow release \n");
//	//	pl->move( b2Vec2_zero );
//	//
//	//}
//
//}


/*
std::shared_ptr<SDL_wrapper> SDL_wrapper::Instance()
{
	if (!hInstance)
	{
		hInstance = std::make_unique< SDL_wrapper >();

	}

	return hInstance;
}
*/
//GPU_Renderer* GPU_CreateRenderer_OpenGL_3( GPU_RendererID request );
//void  GPU_FreeRenderer_OpenGL_3( GPU_Renderer* renderer );
bool SDL_wrapper::GameInit( std::string windowName, int windowWidth, int windowHeight )
{
	setvbuf(stdout, NULL, _IONBF, NULL );
	bool success = true;
	fflush(stdout);
	fflush(stderr);
	if ( !init )
	{
		TextureManager::sWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (TextureManager::sWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		TextureManager::sWindowSurf = SDL_GetWindowSurface(TextureManager::sWindow);
		//SDL_wrapper::Instance()->rendererID = GPU_MakeRendererID("OpenGL 2", GPU_RENDERER_OPENGL_2, 2, 0);
		//GPU_CreateRenderer_OpenGL_2( rendererID );
		//GPU_SetRendererOrder( 2, nullptr );
		//screen = GPU_CreateRenderer_GLES_2();
		//printf( "COUTTEST\n" );

		//SDL_wrapper::Instance()->TextureManager::gRenderer = initialize_demo( 800, 600 );
		//rendererID = GPU_MakeRendererID( windowName.c_str(), GPU_ReserveNextRendererEnum(), 1, 0 );
		//
		//
		//// Request this specific renderer
		//SDL_wrapper::Instance()->TextureManager::gRenderer = GPU_Init( 800, 600, GPU_DEFAULT_INIT_FLAGS );
		TextureManager::sRenderer = SDL_CreateRenderer(TextureManager::sWindow, -1, SDL_RENDERER_ACCELERATED);

		//setRengerer( GPU_InitRendererByID(SDL_wrapper::Instance()->rendererID, windowWidth, windowHeight, GPU_DEFAULT_INIT_FLAGS ) );
		//TextureManager::gRenderer = GPU_InitRenderer(rendererID.renderer, 800, 600, GPU_DEFAULT_INIT_FLAGS);
		fflush(stdout);
		//TextureManager::gRenderer = GPU_InitRendererByID( rendererID, 800, 600, GPU_DEFAULT_INIT_FLAGS);
		//printRenderers();
		////TextureManager::gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		//GPU_SetCurrentRenderer( SDL_wrapper::Instance()->TextureManager::gRenderer->renderer->id );
		//if (getRengerer() == nullptr)
		//{
		//	printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		//	success = false;
		//}
		//displayMode = TextureManager::sWindow;
		
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

		//GPU_SetDebugLevel( GPU_DEBUG_LEVEL_1 );
		_contactListener = std::make_shared<ContactListener>();

		TimerIns::Instance();
		//TextureManager::Instance()->loadTextures();
		TriggersManager::Instance()->Init();
		SoundManager::Instance();
		//OUT IF RANGE___________________________________
		SDL_wrapper::Instance()->cursor = std::make_shared< Mouse >();
		//OUT IF RANGE-------------------------------------
		BodyManager::Instance()->addBody("Mouse", std::static_pointer_cast<Body>(SDL_wrapper::Instance()->cursor));
		Log::Init();
		world->SetContactListener( ContactListener::Instance().get() );
		init = true;
	}

	printCurrentRenderer();

	if (!SDL_wrapper::instance->loadMedia())
	{

		printf("Failed to load media!\n");

		return 0;

	}
	//std::shared_ptr<Level1> scene = std::make_shared<Level1>();
	return success;

}

int SDL_wrapper::Run(int argc, const char* argv[])
{
	memset(EventHandle::KEYS, 322, false);
	//std::shared_ptr< Metronome /*> app */= std::make_shared< Metronome >();
	//Scene* current = SceneManager::Instance().currentScene;
	bool inited = false;
	//if (SceneManager::Instance().init())
	//{
		//Metronome::bpm = 60;

		//app->UpdateInterval();

		//std::thread beat( metr );

		//beat.detach();
	_CrtMemState sOld;
	_CrtMemState sNew;
	_CrtMemState sDiff;
	_CrtMemCheckpoint(&sOld); //take a snapshot 
	std::string windowName = "Game";

	while (!SDL_wrapper::quit)
	{
		if (!inited) {
			inited = SDL_wrapper::GameInit(windowName, 1920, 1080);
			//inited = SceneManager::Instance().init();
		}


		TimerIns::Instance()->Update();

		SDL_wrapper::Instance()->GameTick();
		//app->GameTick();

		//GameDraw();
		SDL_wrapper::Instance()->GameDraw();
		//app->GameDraw();


	}

	/*	TimerIns::Instance()->Update();


		Metronome::Instance()->GameTick();


		Metronome::Instance()->GameDraw();
	*/
	//TimerIns::Instance()->Reset();
	//long long bpm = 1;
	//auto t = UpdateManager::start( bpm );
	//using namespace std;
	////this_thread::sleep_for(10s);

	//while (!Metronome::Instance()->quit)
	//{
	//
	//
	//	TimerIns::Instance()->Update();
	//
	//
	//	Metronome::Instance()->GameTick();
	//
	//
	//	Metronome::Instance()->GameDraw();
	//
	//
	//}
	//
//}


	SceneManager::Instance().Close();
	//SDL_wrapper::Instance()->close();
	delete SDL_wrapper::Instance();
	_CrtMemCheckpoint(&sNew); //take a snapshot 
	if (_CrtMemDifference(&sDiff, &sOld, &sNew)) // if there is a difference
	{
		//OutputDebugString(L"-----------_CrtMemDumpStatistics ---------");
		_CrtMemDumpStatistics(&sDiff);
		//OutputDebugString(L"-----------_CrtMemDumpAllObjectsSince ---------");
		_CrtMemDumpAllObjectsSince(&sOld);
		//OutputDebugString(L"-----------_CrtDumpMemoryLeaks ---------");
		_CrtDumpMemoryLeaks();
	}
	return 0;
}
void SDL_wrapper::resizeWindow(int windowWidth, int windowHeight) {
	//logFileStderr("MESSAGE: Window width, height ... %d, %d\n", windowWidth, windowHeight);
	SDL_SetWindowSize(gWindow,windowWidth, windowHeight);
	//glViewport(0, 0, windowWidth, windowHeight);
}
void SDL_wrapper::InputHandler() {
	eventHandler->Update();
	//SDL_Event sdlEvent;
	//while (SDL_PollEvent(&sdlEvent)) {
	//	/* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
	//	switch (sdlEvent.type) {
	//	case SDLK_SPACE:
	//		printf("Key press detected\n");
	//		break;
	//	case SDL_KEYDOWN:
	//		printf("Key press detected\n");
	//		break;

	//	case SDL_KEYUP:
	//		printf("Key release detected\n");
	//		break; 
	//	case SDL_WINDOWEVENT:

	//			if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED) {
	//				//logFileStderr("MESSAGE:Resizing window...\n");
	//				SDL_wrapper::Instance()->resizeWindow(sdlEvent.window.data1, sdlEvent.window.data2);
	//			}
	//			break;

	//	default:
	//		break;
	//	}
	//	switch (sdlEvent.key.keysym.scancode) {
	//	case SDL_SCANCODE_SPACE:
	//		SDL_wrapper::quit = true;
	//		//printf("Key press detected\n");
	//		break;

	//	default:
	//		break;
	//	}
	//}
}

void SDL_wrapper::GameTick()
{
	InputHandler();
	doPhysicsStep(TimerIns::Instance()->DeltaTimeS());
	SceneManager::Instance().update();
	//world->Step(timeStep, velocityIterations, positionIterations);
	BodyManager::Instance()->Update();
	cursor->Update();
}
float accumulator = 0;

void SDL_wrapper::doPhysicsStep(float deltaTime) {
	// fixed time step
	// max frame time to avoid spiral of death (on slow devices)
	float frameTime = fmin(deltaTime, 0.25f);
	accumulator += frameTime;
	while (accumulator >= timeStep) {
		world->Step(timeStep, velocityIterations, positionIterations, threadPoolExecutor);
		accumulator -= timeStep*1.5;
	}
}

void SDL_wrapper::GameDraw()
{
	//GPU_Clear(TextureManager::gRenderer);
	//Clear screen
	SDL_SetRenderDrawColor(TextureManager::sRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	//SDL_RenderClear(gRenderer); 
	SDL_RenderClear(TextureManager::sRenderer);
	//SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	//SDL_SetRenderDrawColor(TextureManager::sRenderer, 0xFF, 0x00, 0x00, 0xFF);
	//SDL_RenderFillRect(TextureManager::sRenderer, &fillRect);
	//drawOutlinedQuad(50, 50, 50, 50, WHITE_COLOR);
	SceneManager::Instance().draw();
	BodyManager::Instance()->Draw();

	Log::Draw(); 
	//GPU_ResetRendererState();
	SDL_RenderPresent(TextureManager::sRenderer);
	//GPU_Flip(TextureManager::gRenderer);
}


bool SDL_wrapper::loadMedia()
{
	bool success = true;

	return success;
}

void SDL_wrapper::drawOutlinedQuad( SDL_Rect& rect, SDL_Color color, SDL_BlendFactor blend )
{
	//GPU_SetShapeBlendMode( blend );

	SDL_RenderFillRect(TextureManager::sRenderer, &rect);//;, color );
}

void SDL_wrapper::drawFilledQuad( SDL_Rect& rect, SDL_Color color, SDL_BlendFactor blend )
{
	//SDL_SetSurfaceBlendMode( blend );

	SDL_RenderFillRect(TextureManager::sRenderer, &rect);// , color );
}

void SDL_wrapper::drawFilledQuad( engRectangle& rect, SDL_Color color, SDL_BlendFactor blend )
{
	//GPU_SetShapeBlendMode( blend );

	SDL_RenderFillRect( TextureManager::sRenderer, rect.convertToSDLRect() );
}

void SDL_wrapper::drawOutlinedQuad( float x, float y, float w, float h, SDL_Color color, SDL_BlendFactor blend )
{//
	//GPU_SetShapeBlendMode( blend );

	//SDL_Rectangle( GPU_GetContextTarget(), x, y, w, h, color );
	SDL_Rect rect = { x,y,w,h };
	SDL_RenderDrawRect(TextureManager::sRenderer, &rect);
}



void SDL_wrapper::drawFilledQuad( float x, float y, float w, float h, SDL_Color color, SDL_BlendFactor blend )
{
	//GPU_SetShapeBlendMode( blend );
	SDL_Rect rect = { x,y,w,h };

	SDL_RenderFillRect(TextureManager::sRenderer, &rect);// color );
}

void SDL_wrapper::GameClose()
{
	//GPU_FreeTarget( GPU_GetContextTarget() );



	//GPU_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}



