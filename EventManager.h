#pragma once
#include <vector>
#include <memory>
#include <map>
#include <string>
#include "EventData.h"
#include "Body.h"


class SDL_wrapper;
class Body;

class EventManager
{
	// static std::shared_ptr< EventManager > vIntstance;


	std::vector < std::shared_ptr< Body > > observers;
	std::map < std::string, std::vector< std::shared_ptr< Body > > > observers2;
	std::vector < std::shared_ptr< Event > > registeredEvents;
	std::shared_ptr< SDL_wrapper > game;
	SDL_Event e;
	EventManager();
public:
	~EventManager();

	static EventManager* Instance();

	std::shared_ptr< Event > findEventByKey( int keyID );
	std::shared_ptr< Event > findEventByName( std::string eventName );

	bool registerEvent( std::string nameOfEvent, int keyID, ButtonEvent buttonState = ButtonEvent::BUTTON_UNKNOWN );
	bool deleteEvent( std::string nameOfEvent );

	bool deleteObserver( std::shared_ptr< Body > observer );

	bool listenEvents( std::string nameOfEvent, std::shared_ptr< Body > body );

	bool handleEvent();

	bool notify( std::shared_ptr < GameEvent > event );

};

