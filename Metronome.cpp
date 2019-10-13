// Metronome.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Metronome.h"
#include <chrono>
#include <ctime>    

bool Metronome::quit = false;
std::unique_ptr<SDL_wrapper> Metronome::Game = std::make_unique<SDL_wrapper>();
std::shared_ptr< Metronome > Metronome::hInstance(nullptr);
std::vector< std::shared_ptr< Object > > Metronome::GameObjects;
std::shared_ptr< EventHandle > Metronome::eventHandler = std::make_shared< EventHandle >();
std::shared_ptr< SoundEfx > Metronome::strongBeat = nullptr;
std::shared_ptr< SoundEfx > Metronome::weakBeat = nullptr;


void Metronome::onMouseButtonEvent(int x, int y, bool isReleased, int button)
{


	//Instance()->cursor->UpdateStats(x, y, isReleased, button);


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

std::shared_ptr<Metronome> Metronome::Instance()
{
	if (!hInstance)
	{
		hInstance = std::make_unique< Metronome >();
	}
	return hInstance;
}

void Metronome::GameDraw()
{
	GPU_Clear( SDL_wrapper::gRenderer );

	//board->Draw();

	boom.drawFrame( 0, 0 );

	button->Draw();

	GPU_Flip( SDL_wrapper::gRenderer );
}

bool Metronome::GameInit()
{

	Metronome::Instance();


	if (!Game->Init())
	{

		printf("Failed to initialize!\n");

		return 0;

	}

	if (!Game->loadMedia())
	{

		printf("Failed to load media!\n");

		return 0;

	}

	eventHandler = std::make_shared< EventHandle >();
	board = std::make_shared< Board >();


	TriggersManager::Instance();
	
	cursor = std::make_shared< Mouse >();

	SoundManager::Instance();
	SoundManager::Instance()->loadSounds();

	Collisions = std::make_shared< Collision >();

	Collisions->addObject(cursor);

	setBPM( 60 );

	Metronome::strongBeat = SoundManager::Instance()->getSound("StrongBeat.flac");
	Metronome::weakBeat = SoundManager::Instance()->getSound("WeakBeat.flac");

	boom.setSpriteSheet( 48, TextureManager::Initialize()->getTexture("Circle.png"), Vector2d( 140, 140 ) );
	boom.setDevider( 48.0f / 60.0f );

	button = std::make_shared< Button >( 50, 50, 240, 240, "Press");
	button->setTexture( TextureManager::getTexture("ButtonReleased.png") );
	button->setRelesedTexture( TextureManager::getTexture("ButtonPressed.png") );
	button->setWhilePressedText( "Pressed" );
	button->setRelesedText("Released");

	return 1;

}
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
void Metronome::GameTick()
{
	auto start = std::chrono::system_clock::now();

	eventHandler->Update();

	cursor->Update();

	std::chrono::seconds interval { 60 / getBPM() };

	button->Draw();

	

	//std::chrono::duration<float> elapsed_seconds = start;
	//std::chrono::seconds next = start + interval;
	//
	//if ( interval >= nextTick )
	//{
	//	GPU_Log("Tick");
	//	playTick();
	//}
	//
	/*
	Uint32 interval = 60000 / getBPM();

	nextTick = SDL_GetTicks() + interval;
	
	GPU_Log(" interval : %ld", interval );
	GPU_Log(" nextTick : %ld", nextTick );
	GPU_Log(" next - tick : %ld ", nextTick - SDL_GetTicks());

	if ( interval == nextTick - SDL_GetTicks() )
	{
		playTick();
		GPU_Log("tick");
	}
	*/


	Collisions->Update();

	auto end = std::chrono::system_clock::now();
	std::chrono::duration< float > offset = end - start;

	//std::cout << "Offset: " << offset.count() << std::endl;
}

void Metronome::GameReset()
{


}

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
	
		std::cout << offset << std::endl;
		std::cout << std::chrono::steady_clock::is_steady << std::endl;
		c = std::chrono::steady_clock::now();
		offset = std::chrono::duration_cast<std::chrono::microseconds>(c - b).count();
		std::this_thread::sleep_for(std::chrono::microseconds( Metronome::interval - offset - Metronome::bpm ) );
	}
}

void Metronome::UpdateInterval()
{
	Metronome::interval = 60000000 / Metronome::bpm;
}
int main(int argc, char *argv[])
{

	if (Metronome::Instance()->GameInit())
	{
		Metronome::bpm = 60;
		
		Metronome::Instance()->UpdateInterval();

		std::thread beat( metr );

		beat.detach();


		while (!Metronome::Instance()->quit)
		{
		
		
			TimerIns::Instance()->Update();
		
		
			Metronome::Instance()->GameTick();
		
		
			Metronome::Instance()->GameDraw();
		
		
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
	}



	Metronome::Instance()->Game->close();

	return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
