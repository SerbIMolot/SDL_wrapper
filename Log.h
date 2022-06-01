#pragma once
#include <memory>
#include <vector>
#include <map>
#include <string>
#include "NFont_gpu.h"
//#include "TextureManager.h"
#include "Timer.h"

#define LOG_SCREEN_TIME 10
#define LOG_INTERVAL 3

#define TEXTBOX_MAX_Y 500
#define TEXTBOX_MAX_X 700

class Log
{
	static std::unique_ptr< NFont > logFont;
	static std::vector< std::unique_ptr< Timer > > textTimer;
	static std::map < std::string, float > TextLog;
	NFont::Rectf logWindow;
	static std::vector< std::string > logText;
public:
	static void Init();

	static void screenLog( std::string text );
	static void Update( );
	static void Draw();
};

