#include "Constants.h"
#include "SDL_wrapper.h"
#include "TextureManager.h"

b2World* getWBox2DWorld()
{
	return SDL_wrapper::world;
}

void setRengerer(SDL_Renderer* renderer)
{
	TextureManager::sRenderer = renderer;
}

SDL_Renderer* getRengerer()
{
	return TextureManager::sRenderer;
}
