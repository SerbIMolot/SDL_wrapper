#pragma once
#include <stdexcept>
#include <map>
#include <string>
#include <mutex>
#include "Box2D/Common/b2Math.h"
#include "Texture.h"


class TextureManager {
	std::once_flag initFlag;
	static std::map<std::string, std::shared_ptr<Texture>> Textures;

	TextureManager();

public:
	static SDL_Renderer* sRenderer;
	static SDL_Window* sWindow;
	static SDL_Surface* sWindowSurf;

	~TextureManager();

	static void addTexture(const char* path);


	static TextureManager* Instance();

	static void Close(std::string fileName);

	static std::shared_ptr<Texture> getTexture(const char * fileName);
};


