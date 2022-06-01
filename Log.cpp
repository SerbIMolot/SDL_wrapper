#include "Log.h"
#include "TimerIns.h"
#include "TextureManager.h"

std::unique_ptr< NFont > Log::logFont = nullptr;
std::vector< std::unique_ptr< Timer > > Log::textTimer;
std::vector< std::string > Log::logText ;
std::map< std::string, float > Log::TextLog;
void Log::Init()
{
	//logFont = std::make_unique< NFont >("Data/FreeSans.ttf", 60, NFont::Color(0, 0, 0, 255));
}
void Log::screenLog(std::string text)
{
	if( TextLog.find( text ) == TextLog.end() )
	{
		TextLog[ text ] = 0.0f;
	}


	/*
	if ( logText.empty() || std::find( logText.begin(), logText.end(), text ) == logText.end() )
	{
		logText.push_back(text);
		if (logText.size() < textTimer.size())
		{
			textTimer[logText.size()]->start();
		}
		else
		{
			textTimer.push_back( std::make_unique< Timer >() );
			textTimer.end().start();
		}
	}
	*/
}

void Log::Update()
{

	/*
	float x = 0.0f;
	float y = 0.0f;

	for( auto log : TextLog )
	{
		log.second += TimerIns::Instance()->DeltaTimeS();

		if( log.second >= LOG_SCREEN_TIME )
		{
			TextLog.erase( log.first );
		}
		else
		{
			y += logFont->getHeight();
			logFont->draw( GPU_GetContextTarget(), x, y, log.first.c_str() );
		}
	}
	*/
	/*
	for ( int i = 0; i < logText.size(); i++ )
	{
		if ( textTimer[ i ]->getSeconds() > LOG_SCREEN_TIME )
		{
			textTimer[ i ]->stop();
			logText.erase( logText.begin() + i );
			//GPU_Log("delete log: %s", logText[i].c_str() );
		} 
		else
		{
			//GPU_Log("LOG: %s", logText[i].c_str() );
			y += logFont->getHeight();
			logFont->draw( GPU_GetContextTarget(), x, y, logText[ i ].c_str() );

		}
	}
	*/
}

void Log::Draw()
{
	float x = 0.0f;
	float y = 0.0f;

	std::map< std::string, float >::iterator it;
	for (it = TextLog.begin(); it != TextLog.end(); )
	{
		it->second += TimerIns::Instance()->DeltaTimeS();


		if (it->second >= LOG_SCREEN_TIME)
		{
			if (it == TextLog.begin())
			{
				TextLog.erase(it->first);
				break;
			}
		}
		else
		{
			y += logFont->getHeight();

			//logFont->draw(TextureManager::sRenderer, x, y, it->first.c_str() );

			
			if (y + logFont->getHeight() > TEXTBOX_MAX_Y)
			{
				TextLog.erase(TextLog.begin());
			}
		}

		it = std::next(it);
	}
	/*
	for( auto& log : TextLog )
	{
		log.second += TimerIns::Instance()->DeltaTimeS();

		if (log.second >= LOG_SCREEN_TIME )
		{
			TextLog.erase(log.first );
		}
		else
		{
			y += logFont->getHeight();
			logFont->draw( GPU_GetContextTarget(), x, y, log.first.c_str() );
		}
	}
	*/
	

	
}