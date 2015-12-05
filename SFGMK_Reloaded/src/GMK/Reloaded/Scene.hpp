#ifndef SFGMKR_SCENE_HPP
#define SFGMKR_SCENE_HPP

#define DEFAULT_SCENE_FILE "../assets/scene.gmkscene"
#define DEFAULT_TEMP_SCENE_FILE "../assets/editor/temp.gmkscene"

class Scene
{
public:

	Scene();
	~Scene();

	void load();
	void unload();
	void save();

	std::string name;
	std::string path;

	sfgmk::vector<GameObject*>& getGameObjects();

	void addGameObject(GameObject* _object);
	void removeGameObject(GameObject* _object);

	GameObject* findGameObjectByTreeID(void* _treeID);
	GameObject* findGameObjectByName(std::string _name);

	void removeGameObjects();

protected:

	sfgmk::vector<GameObject*> m_GameObjects;
};

#endif