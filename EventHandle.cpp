#include "EventHandle.h"
#include "Constants.h"

std::shared_ptr< b2Vec2 > EventHandle::mouseCoord = std::make_shared< b2Vec2 >( 0.0f, 0.0f );

bool  EventHandle::KEYS[322] = {false};
EventHandle::EventHandle()
{
	//std::memset(KEYS.get(), false,/* */sizeof(bool) * 322);
}
EventHandle::EventHandle( std::shared_ptr< SDL_wrapper > gameCopy  )
{
	//game = std::move( gameCopy );
	//std::memset(KEYS.get(), false, sizeof(bool) * 322);
}


EventHandle::~EventHandle()
{

}

void EventHandle::Update()
{
	std::shared_ptr< GameEvent > newEvent = std::make_shared< GameEvent >();
	static ButtonEvent prevButtonState = ButtonEvent::BUTTON_UNKNOWN;
	
	while (SDL_PollEvent(&e) != 0)
	{
		//Creating empty Event
		newEvent = std::make_shared< GameEvent >();
		newEvent->button = ButtonEvent::BUTTON_UNKNOWN;
		newEvent->command = "null";
		newEvent->type = GameEventType::UNKNOWN;
		newEvent->pos = nullptr;

		//uset request quit
		if (e.type == SDL_QUIT)
		{
			//game->GameClose();
			newEvent->type = GameEventType::SYSTEM;
			//newEvent->command = "QUIT";
		}
		newEvent->eventType = static_cast< SDL_EventType >( e.type );

		if ( e.type == SDL_FINGERDOWN )
		{
				if ( prevButtonState == ButtonEvent::BUTTON_PRESSED )
				{
					newEvent->button = ButtonEvent::BUTTON_HOLD;
				}
				else
				{
					newEvent->button = ButtonEvent::BUTTON_PRESSED;
				}
				newEvent->type = GameEventType::TOUCH;
				newEvent->pos = std::make_shared<b2Vec2>(e.tfinger.x * SCREEN_WIDTH, e.tfinger.y * SCREEN_HEIGHT);
		}

		else if ( e.type == SDL_FINGERUP )
		{
					newEvent->button = ButtonEvent::BUTTON_RELEASE;
					newEvent->type = GameEventType::TOUCH;
		}
		else if ( e.type == SDL_FINGERMOTION )
		{
			newEvent->type = GameEventType::TOUCH_MOVEMENT;
			newEvent->pos = std::make_shared<b2Vec2>( e.tfinger.x * SCREEN_WIDTH, e.tfinger.y * SCREEN_HEIGHT );
		}

		if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
		{
			bool isReleased = false;
			
			if ( e.type == SDL_MOUSEMOTION )
			{
					newEvent->type = GameEventType::MOUSE_MOVEMENT;
					newEvent->pos = std::make_shared<b2Vec2>( PixelToMeter(e.motion.x), PixelToMeter(e.motion.y) );
					mouseCoord->x = PixelToMeter(e.motion.x);
					mouseCoord->y = PixelToMeter(e.motion.y);
			}
			else if ( e.type == SDL_MOUSEBUTTONDOWN )
			{
				if ( prevButtonState == ButtonEvent::BUTTON_PRESSED )
				{
					newEvent->button = ButtonEvent::BUTTON_HOLD;
				}
				else
				{
					newEvent->button = ButtonEvent::BUTTON_PRESSED;
				}
					newEvent->type = GameEventType::BUTTON;
		
			}
			else if ( e.type == SDL_MOUSEBUTTONUP )
			{
				newEvent->button = ButtonEvent::BUTTON_RELEASE;
				newEvent->type = GameEventType::BUTTON;
			}

			newEvent->buttonID = e.button.button + STATIC_INT( MouseButton::MOUSE_BUTTON_FIRST ); 

			//game->onMouseButtonEvent(e.motion.x, e.motion.y, isReleased, e.button.button);


		}

		const Uint8* currentKeyState = SDL_GetKeyboardState(NULL);
		//	SDL_Log("currentstate %d", currentKeyState);
		if (currentKeyState[SDL_SCANCODE_LEFT])
		{

		}

		if (currentKeyState[SDL_SCANCODE_RIGHT])
		{
		}

		if (e.type == SDL_KEYDOWN )
		{
			//if ( prevButtonState == ButtonEvent::BUTTON_PRESSED )
			//{
			//	newEvent->button = ButtonEvent::BUTTON_HOLD;
			//}
			//else
			//{
				newEvent->button = ButtonEvent::BUTTON_PRESSED;
			//}
				newEvent->type = GameEventType::BUTTON;
			newEvent->buttonID = e.key.keysym.scancode;
			EventHandle::KEYS[e.key.keysym.scancode] = true;

			SDL_Log(std::to_string((int)e.key.keysym.scancode).c_str());
			SDL_Log(std::to_string(EventHandle::KEYS[e.key.keysym.scancode]).c_str());
			//game->onKeyPress(e.key.keysym.scancode);

		}
		if (e.type == SDL_KEYUP )
		{

			newEvent->button = ButtonEvent::BUTTON_RELEASE;
			newEvent->type = GameEventType::BUTTON;
			newEvent->buttonID = e.key.keysym.scancode;
			EventHandle::KEYS[e.key.keysym.scancode] = false;
			SDL_Log(std::to_string((int)e.key.keysym.scancode).c_str());
			SDL_Log(std::to_string(EventHandle::KEYS[e.key.keysym.scancode]).c_str());
			//game->onKeyRelease(e.key.keysym.scancode);

		}


		EventManager::Instance()->notify( std::move( newEvent ) );
	}
	//handleInput();
	/*
		while (SDL_PollEvent(&e) != 0)
		{

			//uset request quit
			if (e.type == SDL_QUIT)
			{

				SDL_wrapper::Instance()->quit = true;

			}

			if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
			{
				bool hold = false;

				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					hold = true;

				}

				//mouseCoord->x = e.motion.x;
				//mouseCoord->y = PixelToMeter(e.motion.y);

				SDL_wrapper::Instance()->onMouseButtonEvent(e.motion.x, e.motion.y, hold, e.button.button);
			}

			const Uint8* currentKeyState = SDL_GetKeyboardState(NULL);
			//	//GPU_Log("currentstate %d", currentKeyState);
			if (currentKeyState[SDL_SCANCODE_LEFT])
			{

			}

			if (currentKeyState[SDL_SCANCODE_RIGHT])
			{
			}

			if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{

				//KEYS[e.key.keysym.scancode] = true;
				SDL_wrapper::Instance()->onKeyPress(e.key.keysym.scancode);

			}
			if (e.type == SDL_KEYUP && e.key.repeat == 0)
			{

				//KEYS[e.key.keysym.scancode] = false;
				SDL_wrapper::Instance()->onKeyRelease(e.key.keysym.scancode);
				break;

			}


		}
		//handleInput();
		*/
	}

	std::shared_ptr< b2Vec2 > const EventHandle::getMouseCoord()
	{
		return mouseCoord;
	}
	
/*	while (SDL_PollEvent(&e) != 0)
	{

		//uset request quit
		if (e.type == SDL_QUIT)
		{

			Metronome::quit = true;
			
		}
		
		if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
		{
			bool isReleased = false;

			if ( e.type == SDL_MOUSEBUTTONDOWN )
			{
				isReleased = false;
				
			}
			else if ( e.type == SDL_MOUSEBUTTONUP )
			{
				isReleased = true;
			}

			Metronome::Instance()->onMouseButtonEvent(e.motion.x, e.motion.y, isReleased, e.button.button);
		}

		const Uint8* currentKeyState = SDL_GetKeyboardState(NULL);

		if (currentKeyState[SDL_SCANCODE_LEFT])
		{

		}

		if (currentKeyState[SDL_SCANCODE_RIGHT])
		{
		}
		switch (e.type) {

		case SDLK_UP:
			Metronome::bpm += 5;
			Metronome::Instance()->UpdateInterval();
			break;

		case SDLK_DOWN:
			Metronome::bpm -= 5;
			Metronome::Instance()->UpdateInterval();
			break;

		case SDLK_LEFT:

			break;

		case SDLK_RIGHT:
			Metronome::stop = true;
			break;

		default:

			break;
		}
		

	}
*/
//}
