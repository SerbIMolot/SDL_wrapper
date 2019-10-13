#pragma once

#include <map>

struct Text
{
	Vector2d pos;
	std::string data;
};

class TextureManager {
	static TextureManager* tmInstance;

	static std::map<std::string, std::shared_ptr<Texture>> Textures;

	TextureManager();

public:

	~TextureManager();

	static void addTexture(const char* path);

	static void addText();

	static TextureManager* Initialize();

	static void Close(std::string fileName);

	static std::shared_ptr<Texture> getTexture(const char * fileName);
	void loadTextures();
};


