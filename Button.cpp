
#include "Button.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "Log.h"

Button::Button()
{

}

Button::Button( std::shared_ptr< b2Vec2 > vec, float w, float h , std::string text, std::function< void() > funcOnClick )
	: Body( btButton, *vec, TextureManager::getTexture("ButtonReleased.png") )
{
	states = std::make_shared< ButtonStateMachine >();
	

	if ( funcOnClick )
	{
		std::swap( onClick, funcOnClick );
	} 
}

Button::Button( b2Vec2 vec, float w, float h, std::string text, std::function< void() > funcOnClick )
	: Body( btButton, vec, TextureManager::getTexture("ButtonReleased.png") )
{
	states = std::make_shared< ButtonStateMachine >();
	//EventManager::registerEvent( "Mouse move" );

	if ( funcOnClick )
	{
		std::swap( onClick, funcOnClick );
	}
}

Button::Button( int x, int y, int w, int h , std::string text, std::function< void() > funcOnClick )
	: Body( btButton, static_cast< float >( x ), static_cast< float >( y ), TextureManager::getTexture("ButtonReleased.png") )
{
	states = std::make_shared< ButtonStateMachine >();
	pos = std::make_shared< Vector2d >( x, y );
	

	if ( funcOnClick )
	{
		std::swap( onClick, funcOnClick );
	}
}

Button::Button( float x, float y, float w, float h , std::string text, std::function< void() > funcOnClick )
	: Body( btButton, x, y, TextureManager::getTexture("ButtonReleased.png") )
{
	states = std::make_shared< ButtonStateMachine >();
	pos = std::make_shared< Vector2d >( x, y );

	if ( funcOnClick )
	{
		std::swap( onClick, funcOnClick );
	}
	
}


Button::~Button()
{
	//buttonFont.reset();
	buttonFont1.reset();
}

void Button::Init()
{
	states->Init();
	states->setHolder( this->shared_from_this() );
	//EventManager::Instance()->registerEvent( "Up", SDL_SCANCODE_UP, ButtonEvent::BUTTON_PRESSED );
	EventManager::Instance()->registerGameEvent( "Up", SDL_SCANCODE_UP, ButtonEvent::BUTTON_PRESSED, GameEventType::KEY );
	EventManager::Instance()->registerGameEvent( "MouseMove", 0, ButtonEvent::BUTTON_UNKNOWN, GameEventType::MOUSE_MOVEMENT );
	EventManager::Instance()->registerGameEvent( "MouseLMB", static_cast<int>(MouseButton::MOUSE_BUTTON_LEFT), ButtonEvent::BUTTON_PRESSED, GameEventType::KEY );
	EventManager::Instance()->registerGameEvent( "Down", SDL_SCANCODE_DOWN, ButtonEvent::BUTTON_PRESSED, GameEventType::KEY  );
	EventManager::Instance()->registerGameEvent( "Left", SDL_SCANCODE_LEFT, ButtonEvent::BUTTON_PRESSED, GameEventType::KEY  );
	EventManager::Instance()->registerGameEvent( "Right", SDL_SCANCODE_RIGHT, ButtonEvent::BUTTON_PRESSED, GameEventType::KEY  );
	//EventManager::Instance()->registerGameEvent( "Push", static_cast< int >( MouseButton::MOUSE_BUTTON_LEFT ), ButtonEvent::BUTTON_PRESSED, GameEventType::KEY  );
	EventManager::Instance()->listenEvents( "Up", this->shared_from_this() );
	EventManager::Instance()->listenEvents( "Down", this->shared_from_this() );
	EventManager::Instance()->listenEvents( "Left", this->shared_from_this() );
	EventManager::Instance()->listenEvents( "Right", this->shared_from_this() );
	//EventManager::Instance()->listenEvents( "Push", this->shared_from_this() );
	EventManager::Instance()->listenEvents( "MouseLMB", this->shared_from_this() );
}

//GETTERS
std::shared_ptr<engRectangle> Button::getRectangle()
{
	return rect;
}

//std::shared_ptr<Vector2d> Button::Pos()
//{
//	return pos;
//}
////END OF GETTERS


//SETTERS
void Button::setText( std::string text )
{
	this->textDefault = std::move( text );
}
/*
void Button::setPos( Vector2d vec )
{
	pos = std::make_shared< Vector2d >( vec );
}
void Button::setPos( std::shared_ptr< Vector2d > vec )
{
	pos = std::move( pos );
}

void Button::setTexture(std::shared_ptr<Texture> texture)
{
	defaultTexture = std::move( texture );
}

void Button::setRelesedTexture( std::shared_ptr<Texture> texture )
{
	releasedTexture = std::move( texture );
}

void Button::setWhilePressedTexture( std::shared_ptr<Texture> texture )
{
	whilePressedTexture = std::move( texture );
}

void Button::setWhilePressedText( std::string text )
{
	textWhilePressed = std::move( text );
}

void Button::setRelesedText( std::string text )
{
	textReleased = std::move( text );
}

void Button::setTextColor( SDL_Color color )
{
	buttonFont1->setDefaultColor( color );
}
*/
void Button::setOnClickFunction( std::function< void() > func )
{
	std::swap( onClick, func );
}
// END OF SETTERS

void Button::Draw()
{
	Body::Draw();
	
	//getSkin()->render( &getPos() );
	/*
	if ( pressed == false && released == false )
	{
		if ( defaultTexture != nullptr && !textDefault.empty() )
		{ 
			defaultTexture->render( pos );

			buttonFont1->draw( TextureManager::gRenderer, pos->x, pos->y, textDefault.c_str()  );;

		}
		else
		{
			if ( textDefault.empty() )
				buttonFont1->drawBox( TextureManager::gRenderer, rect->convertToNFontRect(), boxColor, "defautTextError"  );
			else
				buttonFont1->drawBox( TextureManager::gRenderer, rect->convertToNFontRect(), boxColor, textDefault.c_str()  );
			
		}
#ifdef DEBUG
			//GPU_Log(" FALSE button: %s", textDefault.c_str() );
#endif

	}
	else if( pressed == true && released == false || released == true  )
	{

		if ( whilePressedTexture != nullptr && !textWhilePressed.empty() )
		{ 
			whilePressedTexture->render( pos );

			if ( textWhilePressed.empty() )
				buttonFont1->draw( TextureManager::gRenderer, pos->x, pos->y, textDefault.c_str()  );
			else
				buttonFont1->draw( TextureManager::gRenderer, pos->x, pos->y, textWhilePressed.c_str());

		}
		else
		{
			if ( textWhilePressed.empty() )
				buttonFont1->drawBox( TextureManager::gRenderer, rect->convertToNFontRect(), boxColor, textDefault.c_str()  );
			else
				buttonFont1->drawBox( TextureManager::gRenderer, rect->convertToNFontRect(), boxColor, textWhilePressed.c_str()  );

			SDL_wrapper::Instance()->drawFilledQuad( *rect, SDL_Color{ 0, 0, 0, 100 }, GPU_BLEND_NORMAL );

		}
#ifdef DEBUG
		//GPU_Log("P - TRUE, R - FALSE button: %s", textWhilePressed.c_str());
#endif
	}
	else if ( pressed == false && released == true )
	{

		if ( releasedTexture != nullptr )
		{ 
			releasedTexture->render( pos );

			if ( textReleased.empty() )
				buttonFont1->drawBox( TextureManager::gRenderer, rect->convertToNFontRect(), BLUE_COLOR, textDefault.c_str()  );
			else
				buttonFont1->drawBox( TextureManager::gRenderer, rect->convertToNFontRect(), BLUE_COLOR, textReleased.c_str()  );

		}
		else
		{
			if ( textReleased.empty() )
				buttonFont1->drawBox( TextureManager::gRenderer, rect->convertToNFontRect(), BLUE_COLOR, textDefault.c_str()  );
			else
				buttonFont1->drawBox( TextureManager::gRenderer, rect->convertToNFontRect(), BLUE_COLOR, textReleased.c_str()  );

		}
#ifdef DEBUG
		//GPU_Log(" P - FALSE, R - TRUE button: %s", textReleased.c_str());
#endif
	}
	*/
}

std::string Button::getState()
{
	return states->getCurrentState()->getName();
}

void Button::handleInput( std::shared_ptr< GameEvent > newEvent )
{
	//std::shared_ptr< Body > tempCopy = std::make_shared < Body >( *this );
	states->handleInput( this->shared_from_this(), newEvent );
	if (newEvent->command == "MouseMove")
	{
		
	}
	if ( newEvent->command == "Left" )
	{
		setPos( getPos().x - 1.0f, getPos().y );
		//Metronome::bpm += 5;
		//UpdateInterval();
	}
	if (newEvent->command == "Up")
	{
		setPos( getPos().x, getPos().y - 1.0f);
		//Metronome::bpm += 5;
		//UpdateInterval();
	}
	if (newEvent->command == "Down")
	{
		setPos(getPos().x, getPos().y + 1.0f);
		//Metronome::bpm += 5;
		//UpdateInterval();
	}
	if (newEvent->command == "Right")
	{
		setPos(getPos().x + 1.0f, getPos().y);
		//Metronome::bpm += 5;
		//UpdateInterval();
	}
}
void Button::handleInput( std::shared_ptr< Event > newEvent )
{
	//std::shared_ptr< Body > tempCopy = std::make_shared < Body >( *this );
	states->handleInput( this->shared_from_this(), newEvent );
	/*
	if ( newEvent->command == "Left" )
	{
		setPos( getPos().x - 1.0f, getPos().y );
		//Metronome::bpm += 5;
		//UpdateInterval();
	}
	if (newEvent->command == "Up")
	{
		setPos( getPos().x, getPos().y - 1.0f);
		//Metronome::bpm += 5;
		//UpdateInterval();
	}
	if (newEvent->command == "Down")
	{
		setPos(getPos().x, getPos().y + 1.0f);
		//Metronome::bpm += 5;
		//UpdateInterval();
	}
	if (newEvent->command == "Right")
	{
		setPos(getPos().x + 1.0f, getPos().y);
		//Metronome::bpm += 5;
		//UpdateInterval();
	}*/
}

void Button::update()
{
	std::shared_ptr< Body > tempCopy = std::make_shared < Body >( *this );
	states->update( std::move( tempCopy ) );
}

bool Button::isPressed()
{
	return true ? false : strncmp(states->getCurrentState()->getName().c_str() , "PressedState", 12 ) == 0;
	//return pressed;
}

bool Button::isReleased()
{
	return true ? false : strncmp(states->getCurrentState()->getName().c_str() , "ReleasedState", 13 ) == 0;
	//return released;
}


bool Button::Press()
{
	if ( pressed == false )
	{
		pressed = true;
	}
	else
	{
		pressed = false;
	}

	return pressed;

}

bool Button::Release()
{
	if ( released == false )
	{
		released = true;
	}
	else
	{
		released = false;
	}

	return released;

}
bool Button::Click()
{
	if ( onClick )
	{
		onClick();
		return true;
	}
	else
	{
		return false;
	}
}