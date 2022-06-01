#pragma once
#include <unordered_map>
#include "dynBody.h"


class Scene
{
	std::unordered_map<std::string, std::shared_ptr<Body> >objects;

public:

	bool isActive = true;

	Scene();
	~Scene();

	virtual void load();
	virtual void unload() { objects.clear(); }

	virtual bool init() {
		return true;
	}

	virtual void addObject(std::string name, std::shared_ptr<Body> object)
	{

		std::pair< std::string, std::shared_ptr<Body>> objectPair(name, object);

		if (objects.find(name) != objects.end())
		{
			int objCount = 0;

			for (auto obj : objects) {
				int isContains = obj.first.compare(0, name.length(), name);

				if (isContains == 0)
					objCount++;

			}
			objectPair.first += std::to_string(objCount);
		}

		objects.insert(objectPair);
	}
	virtual void addObject(std::string name, std::shared_ptr<dynBody> object)
	{
		addObject(name, std::static_pointer_cast<Body>(object));
		
	}
	virtual void deleteObject( std::string name )
	{
		if ( objects.find(name) != objects.end() )
		{
			objects.erase( name );
		}
	}

	virtual void update()
	{
		if (!isActive)
			return;
		
		for (auto object : objects)
		{
			object.second->Update();
		}
	}
	virtual void draw()
	{
		if (!isActive)
			return;
		for (auto object : objects)
		{
			object.second->Draw();
		}
	}
	virtual void CloseScene()
	{
		objects.clear();
	}

};

