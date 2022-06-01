#pragma once

#include <ctime>
#include <atomic>
#include <string>
#include <thread>
#include <inttypes.h>
#include "SDL_wrapper.h"
#include "SceneManager.h"
#define USE_REAL_BOOL

static auto presentTime = std::chrono::system_clock::now();
static auto prevTime = std::chrono::system_clock::now();

union SDL_Event;
class Button;
class SoundEfx;
class Animation;
struct Event;

class Metronome 
	: public SDL_wrapper, public std::enable_shared_from_this< Metronome >
{


public:
	static bool accents[4];
	static int beat;
	

	static std::unique_ptr<SDL_wrapper> Game;
	//static std::shared_ptr<Metronome> hInstance;

	static std::shared_ptr< SoundEfx > strongBeat;
	static std::shared_ptr< SoundEfx > weakBeat;
	static bool quit;

	static bool stop;
	static int64_t interval;

	static int bpm;

	//std::shared_ptr< Collision > Collisions;
	std::shared_ptr< Animation > boom;
	
	
	std::shared_ptr< Button > button;
	//std::shared_ptr< Button > ball;

	bool mouseHold;

	int nextTick;
	int currentTick;


	Metronome();
	~Metronome();
	SDL_Event* e;

	static void playTick();
	static void playStrongTick();
	void setBPM( int bpm );
	
	int getBPM();

	//static std::shared_ptr<Metronome> Instance();


	static bool GameInit( std::string windowName = "Demo" );
	/*void GamePreTick() override;
	void GameTick() override;
	void GamePostTick() override;
	void GameDraw() override;*/
	void PreDraw();
	void PostDraw();
	//void GameClose() override;

	static void MetronomeTick();


	void GameReset();

	void onMouseButtonEvent(int x, int y, bool isReleased, int button);
	void UpdateInterval();

	void onKeyPress( std::shared_ptr< Event > event ) ;
	void onKeyRelease( std::shared_ptr< Event > event );
};

class UpdateManager
{
public:
	explicit UpdateManager() = default;

private:
	static std::atomic<int> now_;
	static std::atomic<bool> stop_;

	struct update_thread
		: private std::thread
	{
		~update_thread();
		update_thread(update_thread&&) = default;

		using std::thread::thread;
	};

public:
	static update_thread start( long long &sec );
};
