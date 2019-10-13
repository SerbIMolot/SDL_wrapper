#include "stdafx.h"
#include "Mouse.h"


Mouse::Mouse()
	: Object()
{

	setSkin(TextureManager::getTexture("Scope.png"), tMouse );
	
	getColShape()->addShape( -10, -10 );

	setMass( 0 );
	grabbedObj = nullptr;
	LMBHold = false;
	
}


Mouse::~Mouse()
{
}

void Mouse::grabObj(std::shared_ptr<Object> obj)
{
	grabbedObj = std::move( obj );
}

void Mouse::releaseObj()
{
	grabbedObj.reset();
}


void Mouse::UpdateStats( int x, int y, bool isReleased, int button )
{
	updatePosition( static_cast< float >( x ) , static_cast< float >( y ) );

	if ( isReleased == false && button == SDL_BUTTON_LEFT )
	{
		LMBHold = true;
		
	}
	else if ( isReleased == true && button == SDL_BUTTON_LEFT )
	{
		LMBHold = false;

		releaseObj();
	}
	if ( isReleased == false && button == SDL_BUTTON_RIGHT )
	{
		RMBHold = true;
	}
	else if ( isReleased == true && button == SDL_BUTTON_RIGHT )
	{
		RMBHold = false;
	}

	getColShape()->Update( Pos() );
	
}

void Mouse::Update()
{

	if (grabbedObj != nullptr && LMBHold == true)
	{
		grabbedObj->updatePosition( Pos()->getX(), Pos()->getY() );
	}


	getColShape()->Update( Pos() );


}

void Mouse::Draw()
{
		getSkin()->render( Pos() );

}

void Mouse::collisionDetected( std::shared_ptr < Object > obj )
{

	if( obj->getType() == tButton && LMBHold == true )
	{
		
	}
}

bool Mouse::isLMBHold()
{
	return LMBHold;
}
bool Mouse::isRMBHold()
{
	return RMBHold;
}



