#ifndef SFGMKR_SCENE_HPP
#define SFGMKR_SCENE_HPP

class Scene
{
public:

	Scene();
	~Scene();

	void load();
	void unload();
	void save();

	void saveTemp(std::string _path);
	void loadTemp(std::string _path);

	std::string name;
	std::string path;

	gmk::vector<GameObject*>& getGameObjects();

	void addGameObject(GameObject* _object);
	void removeGameObject(GameObject* _object);

	GameObject* findGameObjectByTreeID(void* _treeID);
	GameObject* findGameObjectByName(std::string _name);

	void removeGameObjects();

protected:

	gmk::vector<GameObject*> m_GameObjects;
};

#endif