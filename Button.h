#pragma once

#include <functional>

class Button
{
	std::shared_ptr< Vector2d > pos;
	std::shared_ptr< engRectangle > rect;

	bool pressed;
	bool released;

	std::shared_ptr< Texture > defaultTexture;
	std::shared_ptr< Texture > whilePressedTexture;
	std::shared_ptr< Texture > releasedTexture;

	std::string textDefault;
	std::string textWhilePressed;
	std::string textReleased;

	std::function< void() > onClick;

	NFont::Color boxColor;

	static std::unique_ptr< NFont > buttonFont;
	std::unique_ptr< NFont > buttonFont1;
public:
	Button();
	//Button();
	Button( std::shared_ptr<Vector2d> vec, float w, float h, std::string text, std::function< void() > funcOnClick = nullptr );
	Button( Vector2d vec, float w, float h, std::string text, std::function< void() > funcOnClick = nullptr );
	Button( int x, int y, int w, int h, std::string text, std::function< void() > funcOnClick = nullptr );
	Button( float x, float y, float w, float h, std::string text, std::function< void() > funcOnClick = nullptr );
	~Button();


public:

	std::shared_ptr< engRectangle > getRectangle();
	std::shared_ptr< Vector2d > Pos();

	//Setters
	void setText( std::string text );

	void setPos(Vector2d vec);
	void setPos(std::shared_ptr<Vector2d> vec);

	void setTexture( std::shared_ptr< Texture > texture );
	void setRelesedTexture( std::shared_ptr< Texture > texture );
	void setWhilePressedTexture( std::shared_ptr< Texture > texture );

	void setWhilePressedText( std::string text );
	void setRelesedText( std::string text );
	
	void setTextColor( SDL_Color color );

	void setOnClickFunction( std::function< void() > func );

	void handleInput( SDL_Scancode key );

	void Draw();

	bool isPressed();

	bool isReleased();

	bool Press();
	bool Release();
	bool Click();
};

