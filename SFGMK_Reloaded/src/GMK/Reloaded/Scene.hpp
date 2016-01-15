#ifndef SFGMKR_SCENE_HPP
#define SFGMKR_SCENE_HPP

#include "stdafx.h"

class Scene
{
public:

	Scene();
	~Scene();

	r_void load();
	r_void unload();
	r_void save();

	r_void saveTemp(r_string _path);
	r_void loadTemp(r_string _path);

	r_string name;
	r_string path;

	gmk::vector<GameObject*>& getGameObjects();

	r_void addGameObject(GameObject* _object);
	r_void removeGameObject(GameObject* _object);

	GameObject* findGameObjectByTreeID(r_void* _treeID);
	GameObject* findGameObjectByName(r_string _name);

	r_void removeGameObjects();

protected:

	gmk::vector<GameObject*> m_GameObjects;
};

#endif