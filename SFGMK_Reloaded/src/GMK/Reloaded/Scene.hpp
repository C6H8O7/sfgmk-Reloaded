#ifndef SFGMKR_SCENE_HPP
#define SFGMKR_SCENE_HPP

#include "stdafx.h"

class Project;

class Scene
{
public:

	Scene(Project* _project);
	~Scene();

	r_void load(r_bool _tmp = false);
	r_void unload();
	r_void save(r_bool _tmp = false);

	r_void saveTemp(r_string _path);
	r_void loadTemp(r_string _path);

	r_string name;
	r_string path;

	gmk::vector<GameObject*>& getGameObjects();
	gmk::vector<GameObject*>& getRootGameObjects();

	r_void addGameObject(GameObject* _object);
	r_void removeGameObject(GameObject* _object);

	GameObject* findGameObjectByTreeID(r_void* _treeID);
	GameObject* findGameObjectByName(r_string _name);
	r_bool isGameObjectInScene(GameObject* _gameobject);

	r_void removeGameObjects();

protected:

	gmk::vector<GameObject*> m_GameObjects;
	gmk::vector<GameObject*> m_RootGameObjects;

	Project* m_project;
};

#endif