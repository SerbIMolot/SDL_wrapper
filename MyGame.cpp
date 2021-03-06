// MyGame.cpp : Defines the entry point for the console application.
//

#include "MyGame.h"

SDL_Renderer* MyGame::gRenderer = NULL;

TTF_Font* MyGame::gFont = nullptr;


bool MyGame::Init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;

	} else 
	{

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == NULL) 
		{

			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;

		} else
		{

			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			

			int imgFlags = IMG_INIT_PNG;

			if (!(IMG_Init(imgFlags) & imgFlags)) 
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}

			if ( TTF_Init() == -1 )
			{
				printf( "SDL_ttf could not initialize! SDL_ttf error: %s\n", TTF_GetError() );
				success = false;

			}

			txtrs = TextureManager::Initialize();

			//map->Generate();

		}
		/*{
			int imgFlags = IMG_INIT_PNG;

			if ( !( IMG_Init( imgFlags ) & imgFlags ) ) 
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			} else
			{

				//Get window surface
				gScreenSurface = SDL_GetWindowSurface(gWindow);
			
			}

		}*/

	}

	return success;
}

SDL_Texture* MyGame::loadTexture( std::string path ) 
{
	//final texture
	SDL_Texture* newTexture = nullptr;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

	if (loadedSurface == NULL) 
	{
		printf("Unable to load image %s! SDL_Image error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

		if ( newTexture == NULL )
		{
			printf("Unable to create texture from %s! SDL_error: %s\n", path.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

MyGame::MyGame()
{
}

MyGame::~MyGame()
{

}

bool MyGame::loadMedia() 
{
	bool success = true;

	gFont = TTF_OpenFont("Data/lazy.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		/*
		//Render text
		SDL_Color textColor = { 0, 0, 0 };
		if (!gTextTexture.loadFromText("The quick brown fox jumps over the lazy dog", textColor))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}*/
	}
	/* Key pressing by Key States

	if (!gKeyPressDefault.loadFromFile("Data/press.bmp"))
	{
		printf("Failed to load press\n");
		success = false;
	}
	if (!gKeyPressUp.loadFromFile("Data/up.bmp"))
	{
		printf("Failed to load up\n");
		success = false;
	}
	if (!gKeyPressDown.loadFromFile("Data/down.bmp"))
	{
		printf("Failed to load down\n");
		success = false;
	}
	if (!gKeyPressLeft.loadFromFile("Data/left.bmp"))
	{
		printf("Failed to load left\n");
		success = false;
	}
	if (!gKeyPressRight.loadFromFile("Data/right.bmp"))
	{
		printf("Failed to load right\n");
		success = false;
	}
	*/


	/* Animation 
	if ( !gSpriteSheetTexture.loadFromFile("Data/foo.png")) {
		printf( "Failed to load animation texture\n" );
		success = false;
	}
	else {
		SDL_Rect tempRect;
		
		tempRect.x =   0;
		tempRect.y =   0;
		tempRect.w =  64;
		tempRect.h = 205;
		
		gSpriteClips.push_back(tempRect);

		tempRect.x =  64;
		tempRect.y =   0;
		tempRect.w =  64;
		tempRect.h = 205;
		
		gSpriteClips.push_back(tempRect);

		tempRect.x = 128;
		tempRect.y =   0;
		tempRect.w =  64;
		tempRect.h = 205;

		gSpriteClips.push_back(tempRect);
		
		tempRect.x = 196;
		tempRect.y =   0;
		tempRect.w =  64;
		tempRect.h = 205;

		gSpriteClips.push_back(tempRect);
		*/
		/*
		gSpriteClips[ 0 ].x =   0;
		gSpriteClips[ 0 ].y =   0;
		gSpriteClips[ 0 ].w =  64;
		gSpriteClips[ 0 ].h = 205;

		
		gSpriteClips[ 0 ].x =  64;
		gSpriteClips[ 0 ].y =   0;
		gSpriteClips[ 0 ].w =  64;
		gSpriteClips[ 0 ].h = 205;
		
		gSpriteClips[ 0 ].x = 128;
		gSpriteClips[ 0 ].y =   0;
		gSpriteClips[ 0 ].w =  64;
		gSpriteClips[ 0 ].h = 205;
		
		gSpriteClips[ 0 ].x = 196;
		gSpriteClips[ 0 ].y =   0;
		gSpriteClips[ 0 ].w =  64;
		gSpriteClips[ 0 ].h = 205;
	*/
	/* modulated texure 
	if ( !gModulatedTexture.loadFromFile( "Data/fadeout.png" ) )
	{
		printf( "Failed to load front texture\n" );
		success = false;
	}
	else
	{
		gModulatedTexture.setBlendMode( SDL_BLENDMODE_BLEND );
	}

	if (!gBackgroundTexture.loadFromFile("Data/fadein.png"))
	{
		printf( "Failled to load background texture\n" );
		success = false;

	}
	*/
	/* Clipping
	if ( !gFooTexture.loadFromFile("Data/dots.png") )
	{
		printf( "Failed to load foo texture image\n" );
		success = false;
	}
	else
	{
		gSpriteClips[0].x =   0;
		gSpriteClips[0].y =   0;
		gSpriteClips[0].w = 100;
		gSpriteClips[0].h = 100;

		gSpriteClips[1].x = 100;
		gSpriteClips[1].y =   0;
		gSpriteClips[1].w = 100;
		gSpriteClips[1].h = 100;

		gSpriteClips[2].x =   0;
		gSpriteClips[2].y = 100;
		gSpriteClips[2].w = 100;
		gSpriteClips[2].h = 100;

		gSpriteClips[3].x = 100;
		gSpriteClips[3].y = 100;
		gSpriteClips[3].w = 100;
		gSpriteClips[3].h = 100;
	}
	*/
	/*if ( !gBackgroundTexture.loadFromFile("Data/background.png") )
	{
		printf( "Failed to load background texture image\n" );
		success = false;
	}
	*/
	/*
	gHelloWorld = SDL_LoadBMP("Data/hello_world.bmp");

	if (gHelloWorld == NULL) 
	{
		printf("Unable to load image %s! SDL_Error: %s/n", "Data/hello_world.bmp", SDL_GetError());
		success = false;
	}

	if ((gKeyPress[KEY_PRESS_DEFAULT] = loadSurface("Data/press.bmp")) == NULL)
	{
		printf("Failed to load default image \n");
		success = false;
	}

	if ((gKeyPress[KEY_PRESS_UP] = loadSurface("Data/up.bmp")) == NULL)
	{
		printf("Failed to load up image \n");
		success = false;
	}

	if ((gKeyPress[KEY_PRESS_DOWN] = loadSurface("Data/down.bmp")) == NULL)
	{
		printf("Failed to load down image \n");
		success = false;
	}

	if ((gKeyPress[KEY_PRESS_LEFT] = loadSurface("Data/left.bmp")) == NULL)
	{
		printf("Failed to load left image \n");
		success = false;
	}

	if ((gKeyPress[KEY_PRESS_RIGHT] = loadSurface("Data/right.bmp")) == NULL)
	{
		printf("Failed to load right image \n");
		success = false;
	}
	*/
	return success;
}

void MyGame::close() 
{

	//delete &gBackgroundTexture;
	//delete &gModulatedTexture;

	//delete &gFooTexture;
	//delete &gBackgroundTexture;


	//SDL_FreeSurface(gHelloWorld);
	//gHelloWorld = NULL;
	//Free loaded images
	gTextTexture.free();

	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
/*
SDL_Surface* MyGame::loadSurface(std::string path) 
{

	SDL_Surface* optimizzedSurface = nullptr;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL) 
	{
		printf("Unable to load image %s! SDL_Error: %s/n", path.c_str(), IMG_GetError());
	} else 
	{
		optimizzedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);

		if (optimizzedSurface == NULL) 
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}

	return optimizzedSurface;
}*/
