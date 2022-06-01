#include "SceneManager.h"
#include "Scene.h"


SceneManager& SceneManager::Instance()
{
	static SceneManager instance;
	return instance;
}

bool SceneManager::init()
{
	if (Instance().currentScene != nullptr)
		return Instance().currentScene->init();
	return false;
}
bool SceneManager::init(std::shared_ptr<Scene> scene)
{
	bool result = false;
	if (Instance().currentScene == nullptr) {
		changeScene(scene);
		result = Instance().currentScene->init();
	}
	return result;
}

void SceneManager::update()
{
	if (Instance().currentScene != nullptr)
		Instance().currentScene->update();
}

void SceneManager::draw()
{
	if ( Instance().currentScene != nullptr )
		Instance().currentScene->draw();
}

void SceneManager::changeScene(std::shared_ptr<Scene> newScene)
{
	if (Instance().currentScene != nullptr)
	{
		Instance().currentScene->unload();
	}
	Instance().currentScene = newScene;
	Instance().currentScene->load();
}
void SceneManager::Close()
{
	if (Instance().currentScene != nullptr)
	{
		Instance().currentScene->unload();
		Instance().currentScene->CloseScene();
	}
}
