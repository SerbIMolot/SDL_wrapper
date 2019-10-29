#include "stdafx.h"
#include "SDL_wrapper.h"


SDL_Renderer* TextureManager::gRenderer = nullptr;

SDL_DisplayMode SDL_wrapper::displayMode;

std::shared_ptr< EventHandle > SDL_wrapper::eventHandler = std::make_shared< EventHandle >();

b2World* SDL_wrapper::world = new b2World( b2Vec2( 0.0f, 10.0f ) );

//std::unique_ptr< BodyManager > SDL_wrapper::bodyManager = std::make_unique< BodyManager >();


SDL_wrapper::SDL_wrapper()
{

}


bool SDL_wrapper::quit = false;
//std::unique_ptr<SDL_wrapper> SDL_wrapper::Game = std::make_unique<SDL_wrapper>();
std::shared_ptr< SDL_wrapper > SDL_wrapper::hInstance(nullptr);
std::vector< std::shared_ptr< Body > > SDL_wrapper::GameBodys;
//std::shared_ptr< EventHandle > SDL_wrapper::eventHandler = std::make_shared< EventHandle >();



void SDL_wrapper::onMouseButtonEvent(int x, int y, bool isReleased, int button)
{

	if ( isReleased == false && button == SDL_BUTTON_LEFT )
	{
		SDL_Log("LMB PRESS\n");
	//	BodyManager::Instance()->getDynBody("Box1")->applyForce( b2Vec2( 100.0f, 0.0f ) );
	//	BodyManager::Instance()->BodyDebug( );
	
	}

}

void SDL_wrapper::onKeyPress( SDL_Scancode key )
{
	if (key == SDL_SCANCODE_LEFT)
	{
		BodyManager::Instance()->getPlayer()->move(b2Vec2(0, -1));
	}

	if ( key == SDL_SCANCODE_B )
	{
		BodyManager::Instance()->BodyDebug();
	}
	//if ( !KEYS[ SDL_SCANCODE_LEFT ] )
	//{
	//	SDL_wrapper::Instance()->pl->move( b2Vec2( 0, 1 ) );
	//}
	if ( key == SDL_SCANCODE_RIGHT )
	{
		BodyManager::Instance()->getPlayer()->move(b2Vec2(0, 1));
	}
	if (key == SDL_SCANCODE_SPACE )
	{
		BodyManager::Instance()->getPlayer()->jump();
	}
	//if ( key == SDL_SCANCODE_LEFT  )
	//{
	//	SDL_Log("Left arrow press \n");
	//	pl->move( b2Vec2( 0, 1 ) );		
	//}
	/*if ( key[ SDL_SCANCODE_LEFT ] )
	{
		SDL_Log("Left arrow press \n");
		pl->move( b2Vec2( 0, 1 ) );
	}
	if ( key[ SDL_SCANCODE_RIGHT ] )
	{
		SDL_Log("Right arrow press \n");
		pl->move( b2Vec2( 0, -1 ) );

	}
	if ( key[ SDL_SCANCODE_SPACE ] )
	{
		SDL_Log("SPACE pressed\n");
		pl->jump();
	}*/
}

void SDL_wrapper::onKeyRelease( SDL_Scancode key )
{
	//if ( key == SDL_SCANCODE_LEFT )
	//{
	//	SDL_Log("Left arrow release \n");
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
	}
	return hInstance;
}

void SDL_wrapper::GameDraw()
{
	SDL_SetRenderDrawColor(TextureManager::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(TextureManager::gRenderer);

	BodyManager::Instance()->Draw();
//	botbox->Draw();
	//leftbox->Draw();
	//topbox->Draw();
	//rightbox->Draw();
	//dybox->Draw();
	//printf("BOXVEL = %f : %f\n", dybox->getVelocity().x, dybox->getVelocity().y );
	//dybox2->Draw();
	//pl->Draw();



	SDL_RenderPresent(TextureManager::gRenderer);
}

bool SDL_wrapper::GameInit()
{

	SDL_wrapper::Instance();


	if (!Instance()->Init())
	{

		printf("Failed to initialize!\n");

		return 0;

	}

	if (!Instance()->loadMedia())
	{

		printf("Failed to load media!\n");

		return 0;

	}

	//b2Vec2 gravity( 0.0f, -10.0f );
	//
	//world = new b2World( gravity );


	TriggersManager::Instance();

	SoundManager::Instance();
	SoundManager::Instance()->loadSounds();

	BodyManager::Instance()->createBody( PixelToMeter( SCREEN_WIDTH / 2 ), PixelToMeter( SCREEN_HEIGHT ), TextureManager::getTexture( "HorizontalWall.png" ), "botWall", btWall );
	BodyManager::Instance()->createBody( PixelToMeter( 10.0f ), PixelToMeter( SCREEN_HEIGHT / 2 ), TextureManager::getTexture( "VerticalWall.png" ), "leftWall", btWall );
	BodyManager::Instance()->createBody( PixelToMeter( SCREEN_WIDTH / 2 ), PixelToMeter( 10.0f ), TextureManager::getTexture("HorizontalWall.png"), "topWall", btWall );
	BodyManager::Instance()->createBody( PixelToMeter( SCREEN_WIDTH ), PixelToMeter( SCREEN_HEIGHT / 2 ), TextureManager::getTexture("VerticalWall.png"), "rightWall", btWall );
	//botbox = std::make_shared< Body >( PixelToMeter( SCREEN_WIDTH / 2 ), PixelToMeter( SCREEN_HEIGHT - 10.0f ), TextureManager::getTexture( "HorizontalWall.png" ) );
	//leftbox= std::make_shared< Body >( PixelToMeter( 10.0f ), PixelToMeter( SCREEN_HEIGHT / 2 ), TextureManager::getTexture( "VerticalWall.png" ) );
	//topbox= std::make_shared< Body >( PixelToMeter( SCREEN_WIDTH / 2 ), PixelToMeter( 10.0f ), TextureManager::getTexture("HorizontalWall.png") );
	//rightbox= std::make_shared< Body >( PixelToMeter( SCREEN_WIDTH ), PixelToMeter( SCREEN_HEIGHT / 2 ), TextureManager::getTexture("VerticalWall.png") );
	
	BodyManager::Instance()->createBody( 3.0f, 4.0f, TextureManager::getTexture("box.jpg"), "Box1", btBox );
	BodyManager::Instance()->createBody( 5.0f, 7.0f, TextureManager::getTexture("box.jpg"), "Box2", btBox );

	BodyManager::Instance()->createBody( "player", btPlayer ); 

	
	BodyManager::Instance()->createBody( BodyManager::Instance()->getPlayer()->getPos() - b2Vec2( 10, 10 ),
											TextureManager::getTexture( "gun.png" ), "PlayerGun", btGun );
	//
	std::shared_ptr< Gun > gun = BodyManager::Instance()->getGun("PlayerGun"); 
	//if ( gun != nullptr )
		gun->setParent( BodyManager::Instance()->getPlayer() );
	//else
	//	SDL_Log("Gun returbed nullptr");
	world->SetContactListener( ContactListener::Instance().get() );

	//dybox = std::make_shared< dynBody >( 3.0f, 4.0f, TextureManager::getTexture("box.jpg"), 0.65f, 0.3f );
	//dybox2 = std::make_shared< dynBody >( 2.0f, 6.0f, TextureManager::getTexture("box.jpg"), 0.65f, 0.3f );
	
	//pl = std::make_shared< Player >();
	//phObj = std::make_shared< phBody >( 10, 20, std::make_shared< b2Vec2 >( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 ), TextureManager::getTexture("Puck.png") );
	//phObj1 = std::make_shared< phBody >( 10, 20, std::make_shared< b2Vec2 >( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 ), TextureManager::getTexture("Puck.png"));

	return 1;

}

void SDL_wrapper::GameTick()
{
	eventHandler->Update();
	world->Step( timeStep, velocityIterations, positionIterations );
	BodyManager::Instance()->Update();

	for ( auto b : BodyManager::Instance()->getBoxes() )
	{
		//b->rotateTo( 180 );
	}

}

void SDL_wrapper::GameReset()
{

}




SDL_wrapper::~SDL_wrapper()
{
	delete world;
}


bool SDL_wrapper::Init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;

	}
	else
	{
		if ( SDL_GetDesktopDisplayMode( 0, &displayMode ) != 0)
		{
			success = false;
		}

		//Create window
		gWindow = SDL_CreateWindow("Air Hockey", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		

		if (gWindow == NULL)
		{

			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;

		}
		else
		{

			TextureManager::gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (TextureManager::gRenderer == NULL)
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

			TimerIns::Instance();
			TextureManager::Instance();

		}


	}

	return success;
}


bool SDL_wrapper::loadMedia()
{
	bool success = true;

	return success;
}

void SDL_wrapper::drawRect(std::shared_ptr<b2AABB> rect, const SDL_Color & color)
{

		//SDL_Rect r = rect->convertToSDLRect();
		SDL_SetRenderDrawBlendMode( TextureManager::gRenderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor( TextureManager::gRenderer, color.r, color.g, color.b, color.a);
		//SDL_RenderDrawRect(TextureManager::gRenderer, &r);
		SDL_SetRenderDrawBlendMode(TextureManager::gRenderer, SDL_BLENDMODE_NONE);
		SDL_SetRenderDrawColor(TextureManager::gRenderer, 255, 255, 255, 255);

}

void SDL_wrapper::close()
{

	delete TextureManager::Instance();
	delete TriggersManager::Instance();

	SDL_DestroyRenderer(TextureManager::gRenderer);
	SDL_DestroyWindow(gWindow);
	TextureManager::gRenderer = NULL;
	gWindow = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}



