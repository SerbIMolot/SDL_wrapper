#include "TextureManager.h"
#include "Texture.h"
#include "SDL.h"

std::map<std::string, std::shared_ptr<Texture>> TextureManager::Textures;
SDL_Window* TextureManager::sWindow = nullptr;
SDL_Renderer* TextureManager::sRenderer = nullptr;
SDL_Surface* TextureManager::sWindowSurf = nullptr;


TextureManager::TextureManager() {

}


TextureManager::~TextureManager() {
	Close("all");
}

void TextureManager::addTexture(const char * path) {
	std::string temp = path;

	std::string fileName;

	if ( temp.find_last_of("/") == -1 ) 
	{
		fileName = temp;
	}

	fileName = temp.substr(temp.find_last_of("/") + 1, temp.size());

	int i = 0;
	for (auto k : Textures)
	{
		if (k.first == fileName)
		{
			i++;
			if (i > 0) {
				break;
			}
		}
	}
	if (i != 0) {
		return;
		//fileName += std::to_string(i);
	}
	fflush( stdout );
	fflush( stderr );
	
	SDL_Log( "Texture : %s\n", fileName.c_str() );
	Textures[fileName] = std::make_shared<Texture>();
 	Textures[fileName]->loadFromFile(path);
}



TextureManager* TextureManager::Instance() {
	static TextureManager* tmInstance;

	return tmInstance;
}

void TextureManager::Close(std::string fileName) {

	if (fileName == "all") {

		Textures.clear();
	}

	for (auto t : Textures) {
		if (t.first == fileName) {


			Textures.erase(fileName);

			break;
		}
	}

}

std::shared_ptr<Texture> TextureManager::getTexture(const char* fileName) {
	try
	{
		return Textures.at(fileName);
	}
	catch (std::out_of_range& e)
	{
		return nullptr;
	}
}


