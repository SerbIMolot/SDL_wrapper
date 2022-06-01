#pragma once
#include <vector>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <string>
#include "EventData.h"
#include "Body.h"


class SDL_wrapper;
class Body;

class EventManager
{
	// static std::shared_ptr< EventManager > vIntstance;


	//std::vector < std::shared_ptr< Body > > observers;
	std::unordered_map < std::string, std::unordered_set< std::shared_ptr< Body > > > BodyObservers;
	//std::unordered_map < std::string, std::shared_ptr< Body > > observers3;
	std::unordered_map < std::string, std::function<void()> > FunctionObservers;
	std::vector < std::shared_ptr< Event > > registeredEvents;
	std::vector < std::shared_ptr< GameEvent > > registeredGameEvents;
	std::shared_ptr< SDL_wrapper > game;
	SDL_Event e;
	EventManager();
public:
	~EventManager();

	static EventManager* Instance();

	std::shared_ptr< Event > findEventByKey( int keyID );
	std::shared_ptr< GameEvent > findEventByName( std::string eventName );

	bool registerGameEvent(std::string nameOfEvent, int keyID, ButtonEvent buttonState, GameEventType eventType);
	//bool registerGameEvent(std::string nameOfEvent, int keyID, ButtonEvent buttonState[], GameEventType eventType);
	bool deleteEvent( std::string nameOfEvent );

	bool deleteGameEvent(std::string nameOfEvent);

	bool deleteObserver(std::string name, std::shared_ptr<Body> observer);

	bool listenEvents( std::string nameOfEvent, std::shared_ptr< Body > body );

	bool listenEvents(std::string nameOfEvent, std::function<void()> func);

	bool handleEvent();

	bool notify( std::shared_ptr < GameEvent > event );

};

