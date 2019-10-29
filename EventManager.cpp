#include "EventManager.h"
#include "Metronome.h"

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
std::shared_ptr<Event> EventManager::findEventByName( std::string eventName )
{
	std::vector< std::shared_ptr< Event > >::iterator eventIterator = std::find_if(registeredEvents.begin(), registeredEvents.end(),
	[ &eventName]( std::shared_ptr< Event > rEvent ) {
		return eventName == rEvent->nameOfEvent;
	});
	if( eventIterator != registeredEvents.end() )
	{
		return registeredEvents[ std::distance( registeredEvents.begin(), eventIterator ) ];
	}
	GPU_Log("Event with name: %s. Not found.\n", eventName.c_str() );
	return nullptr;
}
bool EventManager::registerEvent( std::string nameOfEvent, int keyID, ButtonEvent buttonState )
{

	std::shared_ptr< Event > tempEvent = std::make_shared< Event >( Event{ nameOfEvent, keyID, buttonState } );

	if ( std::find( Instance()->registeredEvents.begin(), Instance()->registeredEvents.end(), tempEvent ) == registeredEvents.end() )
	{
		Instance()->registeredEvents.push_back( tempEvent );
		return true;
	}
	GPU_Log("Event with parameters already exist.\n" );
	return false;
}

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

	GPU_Log("Event: %s not found\n", nameOfEvent );
	return false;
}
bool EventManager::deleteObserver( std::shared_ptr< Body > observer )
{
	//std::vector< Body >::iterator obsIterator = std::find_if( observers.begin(), observers.end(), 
	//	[ &observer ] ( std::shared_ptr< Body > const& body )
	//{ 
	//	return ( observer->getID() == body->getID() ) == 0;
	//});
	return false;
}

bool EventManager::listenEvents( std::string nameOfEvent, std::shared_ptr<Body> body )
{
	if ( findEventByName( nameOfEvent ) != nullptr )
	{
		observers2[ nameOfEvent ];
		observers2[ nameOfEvent ].push_back( std::move( body ) );
		
		return true;
	}

	GPU_Log("No event with that name to listen\n");
	return false;

}

bool EventManager::handleEvent()
{

	return false;
}

bool EventManager::notify( std::shared_ptr< GameEvent > event )
{

	for ( auto regEvent : registeredEvents )
	{
		if ( regEvent->buttonState == event->button )
		{
			if ( regEvent->buttonID == event->buttonID )
			{
				try
				{
					for ( auto observer : observers2.at( regEvent->nameOfEvent.c_str() ) )
					{
						observer->handleInput( regEvent );
					}
				}
				catch ( std::out_of_range &e )
				{
					GPU_Log( "Event with that name is not registered! :ERROR %s\n", e.what() );
				}
			}
		}
	}

	return true;
}
