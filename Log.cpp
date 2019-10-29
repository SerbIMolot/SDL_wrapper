#include "Log.h"

void Log::screenLog(std::string text)
{
	logText.push_back( text );
	if ( logText.size() < textTimer.size() )
	{
		textTimer[ logText.size() ]->start();
	}
	else
	{
		textTimer.push_back = std::make_unique< Timer >();
		textTimer.end()->get()->start();
	}
	
}

void Log::Update()
{
	float x, y = 0.0f;

	for ( int i = 0; i < logText.size(); i++ )
	{
		if ( textTimer[ i ]->getSeconds() > LOG_SCREEN_TIME )
		{
			textTimer[ i ]->stop();
			logText.erase( logText.begin() + i );
		} 
		else
		{
			y += logFont->getHeight();
			logFont->draw( TextureManager::gRenderer, x, y, logText[ i ].c_str() );

		}
	}
}
