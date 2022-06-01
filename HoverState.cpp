#include "HoverState.h"
#include "TextureManager.h"
#include "Button.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"

HoverState::HoverState( std::string name )
	: ButtonState(name, HOVER_NEIGHBORS )
{
	buttonFont = std::make_unique< NFont >(TextureManager::sRenderer, "Data/FreeSans.ttf", 60, NFont::Color(0, 0, 0, 255));
	setText("Hover");
}

HoverState::~HoverState()
{
}

void HoverState::atStart(std::shared_ptr<Body> body)
{
	body->setSkin(TextureManager::getTexture(IMAGE_HOVER));
}

void HoverState::update(std::shared_ptr<Body> body)
{
	buttonFont->draw(TextureManager::sRenderer, body->getPos().x, body->getPos().y, text.c_str());
}
bool HoverState::handleInput(std::shared_ptr< Body > body, std::shared_ptr< GameEvent > newEvent)
{
	bool handled = false;

	std::shared_ptr< Button > button = std::static_pointer_cast<Button>(body);



	return handled;
}
bool HoverState::handleInput(std::shared_ptr< Body > body, std::shared_ptr< Event > newEvent)
{
	bool handled = false;

	std::shared_ptr< Button > button = std::static_pointer_cast<Button>(body);

	if (newEvent->nameOfEvent == "MouseLMB")
	{
		button->Press();
		getMachine()->changeState("ReleasedState");
		handled = true;
	}

	return handled;
}
