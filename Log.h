#pragma once
#include <memory>
#include <vector>
#include <string>
#include "NFont_gpu.h"
#include "TextureManager.h"
#include "Timer.h"

#define LOG_SCREEN_TIME 10
#define LOG_INTERVAL 3

class Log
{
	std::unique_ptr< NFont > logFont;
	std::vector< std::unique_ptr< Timer > > textTimer;
	NFont::Rectf logWindow;
	std::vector< std::string > logText;

	void screenLog( std::string text );
	void Update( );
};

