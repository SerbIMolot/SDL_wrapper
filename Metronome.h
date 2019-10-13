#pragma once
#include "stdafx.h"
#include "EventHandle.h"


static auto presentTime = std::chrono::system_clock::now();
static auto prevTime = std::chrono::system_clock::now();

class Metronome {

public:
	static bool accents[4];
	static int beat;
	static std::vector< std::shared_ptr< Object > > GameObjects;
	static std::shared_ptr< EventHandle > eventHandler;
	static std::unique_ptr<SDL_wrapper> Game;
	static std::shared_ptr<Metronome> hInstance;

	static std::shared_ptr< SoundEfx > strongBeat;
	static std::shared_ptr< SoundEfx > weakBeat;
	static bool quit;

	static bool stop;
	static int64_t interval;

	static int bpm;

	std::shared_ptr< Collision > Collisions;
	Animation boom;
	std::shared_ptr< Mouse > cursor;
	std::shared_ptr< Board > board;
	std::shared_ptr< Button > button;

	bool mouseHold;

	int nextTick;
	int currentTick;



	Metronome();
	~Metronome();
	SDL_Event e;

	static void playTick();
	static void playStrongTick();
	void setBPM( int bpm );
	
	int getBPM();

	static std::shared_ptr<Metronome> Instance();

	void GameDraw();

	bool GameInit();

	static void MetronomeTick();

	void GameTick();

	void GameReset();

	void onMouseButtonEvent(int x, int y, bool isReleased, int button);
	void UpdateInterval();
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
