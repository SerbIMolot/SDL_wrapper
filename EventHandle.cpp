#include "stdafx.h"
#include "Metronome.h"

EventHandle::EventHandle()
{
}


EventHandle::~EventHandle()
{
}

void EventHandle::Update()
{

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
			//	GPU_Log("currentstate %d", currentKeyState);
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
