#ifndef SFGMKR_GAMEOBJECTMANAGER_HPP
#define SFGMKR_GAMEOBJECTMANAGER_HPP

class GameObjectManager
{
private:

	GameObjectManager();
	~GameObjectManager();

	sfgmk::vector<GameObject*> m_GameObjects;

public:

	static GameObjectManager* GetSingleton();

	sfgmk::vector<GameObject*>& getGameObjects();

	void addGameObject(GameObject* _object);
	void removeGameObject(GameObject* _object);

	GameObject* findGameObjectByTreeID(void* _treeID);
	GameObject* findGameObjectByName(std::string _name);

	void removeGameObjects();
};

#endif