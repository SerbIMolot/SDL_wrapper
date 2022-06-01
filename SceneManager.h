#pragma once

#include <memory>

class Scene;

class SceneManager
{
	std::shared_ptr<Scene> currentScene = nullptr;

	SceneManager() {}
	~SceneManager() {}

public:
	SceneManager(SceneManager const&) = delete;
	void operator=(SceneManager const&) = delete;

	static SceneManager& Instance();

	bool init();
	bool init(std::shared_ptr<Scene> scene);

	void update();
	void draw();

	void changeScene(std::shared_ptr<Scene> newScene );
	void Close();
};

