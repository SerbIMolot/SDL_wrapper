#include "PressedState.h"
#include "Button.h"

PressedState::PressedState( std::string name )
	:	ButtonState( name, PRESSED_NEIGHBORS )
{
	buttonFont = std::make_unique< NFont >( "Data/FreeSans.ttf", 60, NFont::Color( 0, 0, 0, 255) );
	setText( "Pressed" );
}

PressedState::~PressedState()
{
}

void PressedState::atStart(std::shared_ptr<Body> body)
{
	body->setSkin( TextureManager::getTexture( IMAGE_PRESSED ) );
}

void PressedState::update( Body* body )
{
	buttonFont->draw( TextureManager::gRenderer, body->getPos().x, body->getPos().y, text.c_str() );
}

void PressedState::update(std::shared_ptr<Body> body)
{
	buttonFont->draw( TextureManager::gRenderer, body->getPos().x, body->getPos().y, text.c_str() );
}

bool PressedState::handleInput( std::shared_ptr< Body > body, std::shared_ptr< Event > newEvent )
{
	bool handled = false;
	
	std::shared_ptr< Button > button = std::static_pointer_cast< Button >( body );
	
	if( newEvent->nameOfEvent == "Press" )
	{ 
		button->Press();
		getMachine()->changeState("ReleasedState");
		handled = true;
	}

	return handled;
}
void PressedState::handleInput( Body* body, SDL_Scancode key )
{
	if( key == SDL_SCANCODE_P )
	{ 
		 static_cast< Button* >( body )->Press();
		 body->setSkin( TextureManager::getTexture( IMAGE_PRESSED ) );
		 getMachine()->changeState( "ReleasedState" );
	}
}
