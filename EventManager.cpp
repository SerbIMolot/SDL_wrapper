#include "EventManager.h"

EventManager::EventManager()
{
	registeredEvents = std::vector < std::shared_ptr< Event > >();
}

EventManager::~EventManager()
{

}

EventManager* EventManager::Instance()
{
	static EventManager vIntstance;

	return &vIntstance;
}

std::shared_ptr< Event > EventManager::findEventByKey( int keyID )
{
	std::vector< std::shared_ptr< Event > >::iterator eventIterator = std::find_if(registeredEvents.begin(), registeredEvents.end(),
		[&keyID]( std::shared_ptr< Event > rEvent ) {
		return keyID == rEvent->buttonID;
	});
	if ( eventIterator != registeredEvents.end() )
	{
		return registeredEvents[ std::distance( registeredEvents.begin(), eventIterator ) ];
	}

	return nullptr;
}
std::shared_ptr<GameEvent> EventManager::findEventByName( std::string eventName )
{
	std::vector< std::shared_ptr< GameEvent > >::iterator eventIterator = std::find_if(registeredGameEvents.begin(), registeredGameEvents.end(),
	[ &eventName]( std::shared_ptr< GameEvent > rEvent ) {
		return eventName == rEvent->command;
	});
	if( eventIterator != registeredGameEvents.end() )
	{
		return registeredGameEvents[ std::distance(registeredGameEvents.begin(), eventIterator ) ];
	}
	//GPU_Log("Event with name: %s. Not found.\n", eventName.c_str() );
	return nullptr;
}
//bool EventManager::registerEvent( std::string nameOfEvent, int keyID, ButtonEvent buttonState )
//{
//
//	std::shared_ptr< Event > tempEvent = std::make_shared< Event >( Event{ nameOfEvent, keyID, buttonState } );
//
//	if ( std::find( Instance()->registeredEvents.begin(), Instance()->registeredEvents.end(), tempEvent ) == registeredEvents.end() )
//	{
//		Instance()->registeredEvents.push_back( tempEvent );
//		fflush(stdout);
//		fflush(stderr);
//		////GPU_Log("Event: %s. Registered .\n", nameOfEvent.c_str() );
//		return true;
//	}
//	//GPU_Log("Event with parameters already exist.\n" );
//	return false;
//}
//bool EventManager::registerEvent( std::string nameOfEvent, GameEventType event )
//{
//
//	std::shared_ptr< Event > tempEvent = std::make_shared< Event >( Event{ nameOfEvent, SDL_SCANCODE_UNKNOWN, ButtonEvent::BUTTON_UNKNOWN } );
//
//	if ( std::find( Instance()->registeredEvents.begin(), Instance()->registeredEvents.end(), tempEvent ) == registeredEvents.end() )
//	{
//		Instance()->registeredEvents.push_back( tempEvent );
//		//GPU_Log("Event: %s. Registered .\n", nameOfEvent.c_str() );
//		return true;
//	}
//	//GPU_Log("Event with parameters already exist.\n" );
//	return false;
//}

bool EventManager::registerGameEvent(std::string nameOfEvent, int keyID, ButtonEvent buttonState, GameEventType eventType)
{

	std::shared_ptr< GameEvent > tempEvent = std::make_shared< GameEvent >();

	tempEvent->command = nameOfEvent;
	tempEvent->buttonID = keyID;
	tempEvent->button = buttonState;
	tempEvent->type = eventType;

	if (std::find(Instance()->registeredGameEvents.begin(), Instance()->registeredGameEvents.end(), tempEvent) == Instance()->registeredGameEvents.end())
	{
		Instance()->registeredGameEvents.push_back(tempEvent);
		return true;
	}
	return false;
}

//bool EventManager::registerGameEvent(std::string nameOfEvent, int keyID, ButtonEvent buttonState[], GameEventType eventType)
//{
//
//	std::shared_ptr< GameEvent > tempEvent = std::make_shared< GameEvent >();
//
//	tempEvent->command = nameOfEvent;
//	tempEvent->buttonID = keyID;
//	tempEvent->b = buttonState;
//	tempEvent->type = eventType;
//
//	if (std::find(Instance()->registeredGameEvents.begin(), Instance()->registeredGameEvents.end(), tempEvent) == Instance()->registeredGameEvents.end())
//	{
//		Instance()->registeredGameEvents.push_back(tempEvent);
//		return true;
//	}
//	return false;
//}

bool EventManager::deleteEvent(std::string nameOfEvent)
{
	
	std::vector< std::shared_ptr< Event > >::iterator eventIterator = std::find_if(registeredEvents.begin(), registeredEvents.end(),
	[ &nameOfEvent ]( std::shared_ptr< Event > rEvent ) {
		return nameOfEvent == rEvent->nameOfEvent;
	});

	if ( eventIterator != Instance()->registeredEvents.end() )
	{
		Instance()->registeredEvents.erase( eventIterator );
	
		return true;
	
	}

	//GPU_Log("Event: %s not found\n", nameOfEvent.c_str() );
	return false;
}
bool EventManager::deleteGameEvent(std::string nameOfEvent)
{
	
	std::vector< std::shared_ptr< Event > >::iterator eventIterator = std::find_if(registeredEvents.begin(), registeredEvents.end(),
	[ &nameOfEvent ]( std::shared_ptr< Event > rEvent ) {
		return nameOfEvent == rEvent->nameOfEvent;
	});

	if ( eventIterator != Instance()->registeredEvents.end() )
	{
		Instance()->registeredEvents.erase( eventIterator );
	
		return true;
	
	}

	//GPU_Log("Event: %s not found\n", nameOfEvent.c_str() );
	return false;
}
bool EventManager::deleteObserver(std::string name, std::shared_ptr< Body > observer )
{
	//observers2
	//std::vector< Body >::iterator obsIterator = std::find_if( observers.begin(), observers.end(), 
	//	[ &observer ] ( std::shared_ptr< Body > const& body )
	//{ 
	//	return ( observer->getID() == body->getID() ) == 0;
	//});
	//std::vector< Body >::iterator obsIterator = std::find_if( observers.begin(), observers.end(), 
	//	[ &observer ] ( std::shared_ptr< Body > const& body )
	//{ 
	//	return ( observer->getID() == body->getID() ) == 0;
	//});
	return Instance()->BodyObservers[name].erase(observer);//(std::remove(Instance()->registeredGameEvents.begin(), Instance()->registeredGameEvents.end(), 8), Instance()->registeredGameEvents.end());
	//return false;
}

bool EventManager::listenEvents( std::string nameOfEvent, std::shared_ptr<Body> body )
{
	if ( findEventByName( nameOfEvent ) != nullptr )
	{
		BodyObservers[ nameOfEvent ].insert( body );
		
		return true;
	}

	return false;

}
bool EventManager::listenEvents( std::string nameOfEvent, std::function<void()> func)
{
	if ( findEventByName( nameOfEvent ) != nullptr )
	{
		FunctionObservers[ nameOfEvent ] = func;
		
		return true;
	}

	return false;

}

bool EventManager::handleEvent()
{

	return false;
}

bool EventManager::notify( std::shared_ptr< GameEvent > event )
{

	for ( auto regEvent : Instance()->registeredEvents )
	{
		if ( regEvent->buttonState == event->button )
		{
			if ( regEvent->buttonID == event->buttonID )
			{
				try
				{
					for ( auto observer : Instance()->BodyObservers[ regEvent->nameOfEvent.c_str() ] )
					{
						observer->handleInput( regEvent );
					}
				}
				catch ( std::out_of_range &e )
				{
					return false;
				}
			}
		}
	}
	//auto gEventes = findItems(Instance()->registeredGameEvents, event);
	//for (auto regGEvent : Instance()->registeredGameEvents)
	//{
	////auto gEvents = [event](GameEvent gevent) { return gevent.buttonID == event->buttonID && gevent->buttonID == event->buttonID; };

	//	//std::vector<ButtonEvent>::iterator gEvents = std::find_if(Instance()->registeredGameEvents.begin(), Instance()->registeredGameEvents.end(), event);
	//	if (regGEvent->button == event->button)
	//	{
	//		//if ((*gEvents))
	//		if (regGEvent->buttonID == event->buttonID)
	//		{
	//			try
	//			{
	//				//for (auto gEvent : gEventes) {

	//					for (auto observer : Instance()->observers2.at(regGEvent->command.c_str()))
	//					{
	//						observer->handleInput(regGEvent);
	//					}
	//				//}
	//			}
	//			catch (std::out_of_range& e)
	//			{
	//				return false;
	//			}
	//		}
	//	}
	//}
	for ( auto regGEvent : Instance()->registeredGameEvents )
	{
		if (regGEvent->button == event->button )
		{
			if (regGEvent->buttonID == event->buttonID )
			{
				try
				{
					for ( auto observer : Instance()->BodyObservers.at( regGEvent->command.c_str() ) )
					{
						observer->handleInput( regGEvent );
					}
				}
				catch ( std::out_of_range &e )
				{
					return false;
				}
			}
		}
	}

	return true;
}

//std::vector<std::shared_ptr<GameEvent>> findItems(std::vector<std::shared_ptr<GameEvent>> const& events, std::shared_ptr<GameEvent> target) {
//	std::vector<std::shared_ptr<GameEvent>> indices;
//	auto it = events.begin();
//	while ((it = std::find_if(it, events.end(), [&](GameEvent const& e) { return (std::find(e.States.begin(), e.States.end(), target->button)!= e.States.end()||e.button == target->button) && e.buttonID == target->buttonID; }))
//		!= events.end())
//	{
//		indices.push_back( *it );
//		it++;
//	}
//	return indices;
//}
