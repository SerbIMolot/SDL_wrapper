#pragma once

#include <string>
#include "SDL.h"
#include "SDL_mixer.h"


class SoundEfx
{
	Mix_Chunk* sound;

public:
	SoundEfx( std::string path );
	~SoundEfx();

	void play();

};

