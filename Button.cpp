#include "stdafx.h"
#include "Button.h"

Button::Button()
{

}

Button::Button( std::shared_ptr< Vector2d > vec, float w, float h , std::string text, std::function< void() > funcOnClick )
{
	pos = std::move( vec );
	buttonFont1 = std::make_unique< NFont >( "Data/FreeSans.ttf", 60, NFont::Color( 0, 0, 0, 255) );

	rect = std::make_shared< engRectangle >( pos, w, h );

	this->textDefault = std::move( text );

	defaultTexture = nullptr;
	whilePressedTexture = nullptr;
	releasedTexture = nullptr;

	textWhilePressed = "";
	textReleased = "";

	pressed = false;
	released = false;

	if ( funcOnClick )
	{
		std::swap( onClick, funcOnClick );
	} 
}

Button::Button( Vector2d vec, float w, float h, std::string text, std::function< void() > funcOnClick )
{
	pos = std::make_shared< Vector2d >( vec );
	buttonFont1 = std::make_unique< NFont >( "Data/FreeSans.ttf", 60, NFont::Color( 0, 0, 0, 255) );

	rect = std::make_shared< engRectangle >( pos, w, h );

	this->textDefault = std::move( text );

	defaultTexture = nullptr;
	whilePressedTexture = nullptr;
	releasedTexture = nullptr;
	
	textWhilePressed = "";
	textReleased = "";

	pressed = false;
	released = false;

	if ( funcOnClick )
	{
		std::swap( onClick, funcOnClick );
	}
}

Button::Button( int x, int y, int w, int h , std::string text, std::function< void() > funcOnClick )
{
	pos = std::make_shared< Vector2d >( x, y );
	buttonFont1 = std::make_unique< NFont >( "Data/FreeSans.ttf", 60, NFont::Color(0, 0, 0, 255) );
	rect = std::make_shared< engRectangle >( pos, w, h );

	this->textDefault = std::move( text );
	
	defaultTexture = nullptr;
	whilePressedTexture = nullptr;
	releasedTexture = nullptr;

	textWhilePressed = "";
	textReleased = "";

	pressed = false;
	released = false;

	if ( funcOnClick )
	{
		std::swap( onClick, funcOnClick );
	}
}

Button::Button( float x, float y, float w, float h , std::string text, std::function< void() > funcOnClick )
{
	pos = std::make_shared< Vector2d >( x, y );
	buttonFont1 = std::make_unique< NFont >( "Data/FreeSans.ttf", 60, NFont::Color(0, 0, 0, 255) );
	rect = std::make_shared< engRectangle >( pos, w, h );

	this->textDefault = std::move( text );

	defaultTexture = nullptr;
	whilePressedTexture = nullptr;
	releasedTexture = nullptr;

	textWhilePressed = "";
	textReleased = "";

	pressed = false;
	released = false;

	if ( funcOnClick )
	{
		std::swap( onClick, funcOnClick );
	}
	
}


Button::~Button()
{
}

//GETTERS
std::shared_ptr<engRectangle> Button::getRectangle()
{
	return rect;
}

std::shared_ptr<Vector2d> Button::Pos()
{
	return pos;
}
//END OF GETTERS


//SETTERS
void Button::setText( std::string text )
{
	this->textDefault = std::move( text );
}

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

void Button::setOnClickFunction( std::function< void() > func )
{
	std::swap( onClick, func );
}
// END OF SETTERS

void Button::Draw()
{
	
	if ( pressed == false && released == false )
	{
		if ( defaultTexture != nullptr && !textDefault.empty() )
		{ 
			defaultTexture->render( pos );

			buttonFont1->draw( SDL_wrapper::gRenderer, pos->x, pos->y, textDefault.c_str()  );;

		}
		else
		{
			if ( textDefault.empty() )
				buttonFont1->drawBox( SDL_wrapper::gRenderer, rect->convertToNFontRect(), boxColor, "defautTextError"  );
			else
				buttonFont1->drawBox( SDL_wrapper::gRenderer, rect->convertToNFontRect(), boxColor, textDefault.c_str()  );
			
		}
#ifdef DEBUG
			GPU_Log(" FALSE button: %s", textDefault.c_str() );
#endif

	}
	else if( pressed == true && released == false || released == true  )
	{

		if ( whilePressedTexture != nullptr && !textWhilePressed.empty() )
		{ 
			whilePressedTexture->render( pos );

			if ( textWhilePressed.empty() )
				buttonFont1->draw( SDL_wrapper::gRenderer, pos->x, pos->y, textDefault.c_str()  );
			else
				buttonFont1->draw( SDL_wrapper::gRenderer, pos->x, pos->y, textWhilePressed.c_str());

		}
		else
		{
			if ( textWhilePressed.empty() )
				buttonFont1->drawBox( SDL_wrapper::gRenderer, rect->convertToNFontRect(), boxColor, textDefault.c_str()  );
			else
				buttonFont1->drawBox( SDL_wrapper::gRenderer, rect->convertToNFontRect(), boxColor, textWhilePressed.c_str()  );

			SDL_wrapper::Instance()->drawFilledQuad( *rect, SDL_Color{ 0, 0, 0, 100 }, GPU_BLEND_NORMAL );

		}
#ifdef DEBUG
		GPU_Log("P - TRUE, R - FALSE button: %s", textWhilePressed.c_str());
#endif
	}
	else if ( pressed == false && released == true )
	{

		if ( releasedTexture != nullptr )
		{ 
			releasedTexture->render( pos );

			if ( textReleased.empty() )
				buttonFont1->drawBox( SDL_wrapper::gRenderer, rect->convertToNFontRect(), BLUE_COLOR, textDefault.c_str()  );
			else
				buttonFont1->drawBox( SDL_wrapper::gRenderer, rect->convertToNFontRect(), BLUE_COLOR, textReleased.c_str()  );

		}
		else
		{
			if ( textReleased.empty() )
				buttonFont1->drawBox( SDL_wrapper::gRenderer, rect->convertToNFontRect(), BLUE_COLOR, textDefault.c_str()  );
			else
				buttonFont1->drawBox( SDL_wrapper::gRenderer, rect->convertToNFontRect(), BLUE_COLOR, textReleased.c_str()  );

		}
#ifdef DEBUG
		GPU_Log(" P - FALSE, R - TRUE button: %s", textReleased.c_str());
#endif
	}
	
}

void Button::handleInput( SDL_Scancode key )
{
	
}

bool Button::isPressed()
{
	return pressed;
}

bool Button::isReleased()
{
	return released;
}


bool Button::Press()
{
	if ( pressed == false )
	{
		pressed = true;
	}
	else
	{
		Release();
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