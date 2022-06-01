#include "ReleasedState.h"
#include "Button.h"
#include "NFont.h"
#include "TextureManager.h"

ReleasedState::ReleasedState(std::string name)
	: ButtonState ( name, RELEASED_NEIGHBORS )
{
	//buttonFont = std::make_unique< NFont >(TextureManager::sRenderer, "Data/FreeSans.ttf", 60, NFont::Color( 0, 0, 0, 255) );
	setText( "Released" );
}

ReleasedState::~ReleasedState()
{
}
void ReleasedState::atStart( std::shared_ptr<Body> body )
{
	body->setSkin( TextureManager::getTexture( IMAGE_RELEASED ) );
}
void ReleasedState::update( std::shared_ptr<Body> body )
{
	//buttonFont->draw(TextureManager::sRenderer, body->getPos().x, body->getPos().y, text.c_str());
}
void ReleasedState::update( Body* body )
{
	//buttonFont->draw(TextureManager::sRenderer, body->getPos().x, body->getPos().y, text.c_str());
}

bool ReleasedState::handleInput( std::shared_ptr<Body> body, std::shared_ptr< Event > event )
{
	bool handled = false;

	std::shared_ptr< Button > button = std::static_pointer_cast<Button>(body);

	if( event->nameOfEvent == "MouseLMB" )
	{ 
		button->Press();
		getMachine()->changeState( "PressedState" );

		handled = true;
	}

	return handled;
}
bool ReleasedState::handleInput( std::shared_ptr<Body> body, std::shared_ptr< GameEvent > event )
{
	bool handled = false;

	std::shared_ptr< Button > button = std::static_pointer_cast<Button>(body);

	if( event->command == "MouseLMB" )
	{ 
		button->Press();
		getMachine()->changeState( "PressedState" );

		handled = true;
	}

	return handled;
}
void ReleasedState::handleInput( Body* body, SDL_Scancode key )
{

}
