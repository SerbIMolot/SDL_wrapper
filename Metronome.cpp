// Metronome.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Metronome.h"
#include "EventHandle.h"

#include "Constants.h" 
#include "SoundManager.h" 
#include "TextureManager.h" 
#include "BodyManager.h" 
#include "Animation.h" 
#include "TimerIns.h" 
#include "Rectangle.h" 
#include "Button.h" 
#include "Mouse.h" 
//#define RC_INVOKED
#include <windows.h>
#include <debugapi.h> 
#include "Log.h" 

bool Metronome::quit = false;
//std::unique_ptr<SDL_wrapper> Metronome::Game = std::make_unique<SDL_wrapper>();
//std::shared_ptr< Metronome > Metronome::hInstance(nullptr);

//int main(int argc, char* argv[])
//{
//	//std::shared_ptr< Metronome /*> app */= std::make_shared< Metronome >();
//	//Scene* current = SceneManager::Instance().currentScene;
//	bool inited = false;
//	//if (SceneManager::Instance().init())
//	//{
//		//Metronome::bpm = 60;
//
//		//app->UpdateInterval();
//
//		//std::thread beat( metr );
//
//		//beat.detach();
//	_CrtMemState sOld;
//	_CrtMemState sNew;
//	_CrtMemState sDiff;
//	_CrtMemCheckpoint(&sOld); //take a snapshot 
//	std::string windowName = "Game";
//
//		while (!SDL_wrapper::quit)
//		{
//			if (!inited) {
//				inited = SDL_wrapper::GameInit(windowName, 1920, 1080);
//				//inited = SceneManager::Instance().init();
//			}
//			
//
//			TimerIns::Instance()->Update();
//
//			SDL_wrapper::Instance()->GameTick();
//			//app->GameTick();
//			
//			//GameDraw();
//			SDL_wrapper::Instance()->GameDraw();
//			//app->GameDraw();
//
//
//		}
//
//		/*	TimerIns::Instance()->Update();
//
//
//			Metronome::Instance()->GameTick();
//
//
//			Metronome::Instance()->GameDraw();
//		*/
//		//TimerIns::Instance()->Reset();
//		//long long bpm = 1;
//		//auto t = UpdateManager::start( bpm );
//		//using namespace std;
//		////this_thread::sleep_for(10s);
//
//		//while (!Metronome::Instance()->quit)
//		//{
//		//
//		//
//		//	TimerIns::Instance()->Update();
//		//
//		//
//		//	Metronome::Instance()->GameTick();
//		//
//		//
//		//	Metronome::Instance()->GameDraw();
//		//
//		//
//		//}
//		//
//	//}
//
//
//	SceneManager::Instance().Close();
//	//SDL_wrapper::Instance()->close();
//	delete SDL_wrapper::Instance();
//	_CrtMemCheckpoint(&sNew); //take a snapshot 
//	if (_CrtMemDifference(&sDiff, &sOld, &sNew)) // if there is a difference
//	{
//		OutputDebugString(L"-----------_CrtMemDumpStatistics ---------");
//		_CrtMemDumpStatistics(&sDiff);
//		OutputDebugString(L"-----------_CrtMemDumpAllObjectsSince ---------");
//		_CrtMemDumpAllObjectsSince(&sOld);
//		OutputDebugString(L"-----------_CrtDumpMemoryLeaks ---------");
//		_CrtDumpMemoryLeaks();
//	}
//	return 0;
//}
std::shared_ptr< SoundEfx > Metronome::strongBeat = nullptr;
std::shared_ptr< SoundEfx > Metronome::weakBeat = nullptr;


void Metronome::onMouseButtonEvent(int x, int y, bool isReleased, int button)
{


	//Instance()->Game->cursor->UpdateStats(x, y, isReleased, button);


}


Metronome::Metronome()
{


}

Metronome::~Metronome()
{
}

void Metronome::playTick()
{
	weakBeat->play();
}

void Metronome::playStrongTick()
{
	strongBeat->play();
}

void Metronome::setBPM(int bpm)
{
	this->bpm = bpm;
}

int Metronome::getBPM()
{
	return bpm;
}
/*
std::shared_ptr<Metronome> Metronome::Instance()
{
	if (!hInstance)
	{
		hInstance = std::make_unique< Metronome >();
	}
	return hInstance;
}
*/
float angle = 430;
void moveInCircle( Vector2d origin, Button& object )
{
	angle += 10;
	SDL_Log("angle %f", angle);
	//object.Pos()->setX(( float ) ( origin.x + std::cos( angle / object.getRectangle()->w / 2 ) * 630 / Metronome::bpm ) );
	//object.Pos()->setY( (float) ( origin.y + std::sin( angle / object.getRectangle()->w / 2 ) * 630 / Metronome::bpm ) );

	
}
//void Metronome::GameDraw()
//{
//	GPU_Clear( TextureManager::gRenderer );
//	SDL_Rect rect{ 0, 0, 800, 600 };
//	//drawFilledQuad( rect , RED_COLOR );
//	//board->Draw();
//	//BodyManager::Instance()->Draw();
//	//engRectangle test = { 19.0f, 24.0f, 14.0f, 14.0f };
//	//drawFilledQuad(test, BLACK_COLOR);
//	//boom->drawFrame( 10, 10 ); 
//	//ball->Draw();
//	//button->Draw();
//	//GPU_Log( "x = %f, y = %f\n", button->getPos().x, button->getPos().y );
//	//GPU_Log( "x = %f, y = %f\n", MeterToPixel( button->getBody()->GetPosition().x ), MeterToPixel( button->getBody()->GetPosition().y ) );
//
//	Log::Draw();
//	GPU_Flip( TextureManager::gRenderer );
//}
void Metronome::PreDraw()
{
	//GPU_Clear( TextureManager::gRenderer );
	SDL_Rect rect{ 0, 0, 800, 600 };
}
void Metronome::PostDraw()
{

	Log::Draw();
	//GPU_Flip( TextureManager::gRenderer );
}

bool Metronome::GameInit( std::string windowName )
{
	
	//Metronome::Instance();
	fflush(stdout);
	fflush(stderr);

	//EventManager::Instance()->registerEvent( "Push", STATIC_INT( MouseButton::MOUSE_BUTTON_LEFT ), ButtonEvent::BUTTON_PRESSED );
	//if ( !SDL_wrapper::GameInit( windowName, 1920, 1080 ) )
	//{

	//	printf("Failed to initialize!\n");

	//	return 0;

	//}


	//eventHandler = std::make_shared< EventHandle >( std::static_pointer_cast< SDL_wrapper >( SDL_wrapper::) );
	
	//BodyManager::Instance()->createBody( b2Vec2( 10.0f, 10.0f ), TextureManager::Instance()->getTexture( "Puck.png"), "TEST", btBox);

	//boom = std::make_shared< Animation >();
	
	//cursor = std::make_shared< Mouse >();

	//SoundManager::Instance()->loadSounds();

	//Collisions = std::make_shared< Collision >();

	//Collisions->addObject(Game->cursor);
	//ball = std::make_shared< Button >( 400, 300, TextureManager::getTexture("Puck.png"), tPuck, sBox);
	//setBPM( 60 );

	//Metronome::strongBeat = Sound/*Manager::Instance()->getSound("StrongBeat.flac");
	//Metronome::weakBeat = SoundM*/anager::Instance()->getSound("WeakBeat.flac");

	//boom->setSpriteSheet( 48, TextureManager::Instance()->getTexture("Circle.png"), Vector2d( 140, 140 ) );
	//boom->setDevider( 48.0f / 60.0f );

	//button = std::make_shared< Button >( 50, 50, 240, 240, "Press");
	//button->setTexture( TextureManager::getTexture("ButtonReleased.png") );
	//button->setRelesedTexture( TextureManager::getTexture("ButtonPressed.png") );
	//button->setWhilePressedText( "Pressed" );
	//button->setRelesedText("Released");
	//
	//BodyManager::Instance()->addBody( "ButtonTest", std::static_pointer_cast< Body >( button ) );

	return 1;

}
//void Metronome::GamePreTick()
//{
//}
using seconds16 = std::chrono::duration<uint16_t, std::chrono::seconds::period>;





// source
/*
std::atomic<int>  UpdateManager::now_{ 0 };
std::atomic<bool> UpdateManager::stop_{ false };

UpdateManager::update_thread::~update_thread()
{
	if (joinable())
	{
		stop_ = true;
		join();
	}
}

UpdateManager::update_thread
UpdateManager::start( long long &sec )
{
	std::chrono::seconds s( sec );
	return update_thread{ [&]
						 {
							 using namespace std;
							 using namespace std::chrono;
							 
							 auto next = system_clock::now() + s;
							 
							 while ( !stop_ )
							 {
								 Metronome::playTick();
								 this_thread::sleep_until(next);
								 next += s;
							 }
						 } };
}
*/

// demo
/*
int
main()
{
	auto t = UpdateManager::start();
	using namespace std;
	this_thread::sleep_for(10s);
}
*/

void Metronome::MetronomeTick()
{
	if ( Metronome::accents[ Metronome::beat ] == true )
	{
		Metronome::playStrongTick();
	}
	else
	{
		Metronome::playTick();
	}

	
	if ( Metronome::beat < 3 )
	{
		Metronome::beat += 1;
	}
	else
	{
		Metronome::beat = 0;
	}
}
//void Metronome::GameTick()
//{
//	auto start = std::chrono::system_clock::now();
//	world->Step(timeStep, velocityIterations, positionIterations);
//	eventHandler->Update();
//	BodyManager::Instance()->Update();
//	cursor->Update();
//	GPU_Log( "State: %s\n", button->getState().c_str() );
//
//	std::chrono::seconds interval { 60 / getBPM() };
//
//	//Log::Update();
//
//	//Log::screenLog("Testing log");
//	//Log::screenLog("Meh");
//	//Log::screenLog("Is this would be okay?");
//	//GPU_Log("%f %f", test.x, test.y );
//	//moveInCircle( Vector2d( 400, 300 ), *button);
//	
//
//	//std::chrono::duration<float> elapsed_seconds = start;
//	//std::chrono::seconds next = start + interval;
//	//
//	//if ( interval >= nextTick )
//	//{
//	//	GPU_Log("Tick");
//	//	playTick();
//	//}
//	//
//	/*
//	Uint32 interval = 60000 / getBPM();
//
//	nextTick = SDL_GetTicks() + interval;
//	
//	GPU_Log(" interval : %ld", interval );
//	GPU_Log(" nextTick : %ld", nextTick );
//	GPU_Log(" next - tick : %ld ", nextTick - SDL_GetTicks());
//
//	if ( interval == nextTick - SDL_GetTicks() )
//	{
//		playTick();
//		GPU_Log("tick");
//	}
//	*/
//
//
//	//Collisions->Update();
//
//	auto end = std::chrono::system_clock::now();
//	std::chrono::duration< float > offset = end - start;
//
//	//std::cout << "Offset: " << offset.count() << std::endl;
//}
//
//void Metronome::GamePostTick()
//{
//}
//
//void Metronome::GameReset()
//{
//
//
//}
//
//void Metronome::GameClose()
//{
//	Metronome::stop = true;
//	SDL_wrapper::GameClose();
//	quit = true;
//}

using BPM = std::chrono::duration< float, std::ratio< 60 > >;
bool Metronome::stop = false;
int64_t Metronome::interval = 0;
int Metronome::bpm = 0;
int Metronome::beat = 0;
bool Metronome::accents[4] = { true, false, false, false };

void metr(  )
{
	
	auto b = std::chrono::steady_clock::now();
	auto c = std::chrono::steady_clock::now();
	int64_t offset = 0;

	while ( !Metronome::stop )
	{

		b = std::chrono::steady_clock::now();
		
		Metronome::MetronomeTick();
	
		SDL_Log( "%" PRId64 "\n", offset );
		SDL_Log("%" PRId64 "\n", std::chrono::steady_clock::is_steady );
		c = std::chrono::steady_clock::now();
		offset = std::chrono::duration_cast<std::chrono::microseconds>(c - b).count();
		std::this_thread::sleep_for(std::chrono::microseconds( Metronome::interval - offset - Metronome::bpm ) );
	}
}

void Metronome::UpdateInterval()
{
	Metronome::interval = 60000000 / Metronome::bpm;
}
void Metronome::onKeyPress( std::shared_ptr< Event > event )
{
	BodyManager::Instance()->handleInput( event );


	//if (key == SDL_SCANCODE_B)
	//{
	//}
	////if ( !KEYS[ SDL_SCANCODE_LEFT ] )
	////{
	////	SDL_wrapper::Instance()->pl->move( b2Vec2( 0, 1 ) );
	////}
	//
	if (event->buttonID == SDL_SCANCODE_SPACE)
	{
		SDL_wrapper::quit = true;
	}

}
void Metronome::onKeyRelease(std::shared_ptr< Event > event)
{
	//if (key == SDL_SCANCODE_E)
	//{
	//	button->Release();
	//}
}

//std::shared_ptr< Metronome >;



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
