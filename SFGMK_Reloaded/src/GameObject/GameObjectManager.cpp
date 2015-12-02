GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{

}

GameObjectManager * GameObjectManager::GetSingleton()
{
	static GameObjectManager singleton;

	return &singleton;
}

sfgmk::vector<GameObject*>& GameObjectManager::getGameObjects()
{
	return m_GameObjects;
}

void GameObjectManager::addGameObject(GameObject* _object)
{
	m_GameObjects.push_back(_object);
}

void GameObjectManager::removeGameObject(GameObject* _object)
{
	m_GameObjects.removeElement(_object);
}

GameObject* GameObjectManager::findGameObjectByTreeID(void* _treeID)
{
	for (unsigned int i = 0; i < m_GameObjects.getElementNumber(); i++)
		if (m_GameObjects[i]->treeID == _treeID)
			return m_GameObjects[i];

	return 0;
}

GameObject* GameObjectManager::findGameObjectByName(std::string _name)
{
	for (unsigned int i = 0; i < m_GameObjects.getElementNumber(); i++)
		if (m_GameObjects[i]->name == _name)
			return m_GameObjects[i];

	return 0;
}

void GameObjectManager::removeGameObjects()
{
	for (unsigned int i = 0; i < m_GameObjects.getElementNumber(); i++)
	{
#ifdef SFGMKR_EDITOR
		m_GameObjects[i]->showComponents(false);
#endif
		delete m_GameObjects[i];
	}

	m_GameObjects.clear();
}