Scene::Scene()
	: name("Default")
{

}

Scene::~Scene()
{
	removeGameObjects();
}

void Scene::load()
{
#ifdef SFGMKR_EDITOR
	MyGUI* gui = MyGUI::GetGUI();

	if (gui->selectedGameObject)
		gui->selectedGameObject->showComponents(false);

	gui->selectedGameObject = 0;
#endif

	removeGameObjects();

	tinyxml2::XMLDocument doc;

	doc.LoadFile(path.c_str());

	tinyxml2::XMLElement* gameobjects_elem = doc.FirstChildElement("GameObjects");

	tinyxml2::XMLElement* gameobject_elem = gameobjects_elem->FirstChildElement("GameObject");

	while (gameobject_elem)
	{
		GameObject* gameobject = new GameObject(false);

		tinyxml2::XMLElement* component_elem = gameobject_elem->FirstChildElement("Component");

		while (component_elem)
		{
			GameObjectComponent* component = 0;
			std::string type = component_elem->Attribute("type");

			if (type == "GameObject")
				component = new ComponentGameObject(gameobject);
			else if (type == "Transform")
				component = new ComponentTransform(gameobject);
			else if (type == "Sprite")
				component = new ComponentSprite(gameobject);
			else if (type == "Script")
				component = new ComponentScript(gameobject);
			else if (type == "Camera")
				component = new ComponentCamera(gameobject);
			else if (type == "Particle System")
				component = new ComponentParticleSystem(gameobject);
			else if (type == "TiledMap")
				component = new ComponentTiledMap(gameobject);

			if (component)
			{
				component->OnXMLLoad(component_elem);

				component->OnMembersUpdate();

				gameobject->addComponent(component);
			}

			component_elem = component_elem->NextSiblingElement("Component");
		}

#ifdef SFGMKR_EDITOR
		gameobject->showComponents(false);
#endif

		addGameObject(gameobject);

		gameobject_elem = gameobject_elem->NextSiblingElement("GameObject");
	}

#ifdef SFGMKR_EDITOR
	gui->Update_HierarchyTree();
	gui->Update_PropertyGrid();
#endif
}

void Scene::unload()
{
	removeGameObjects();
}

void Scene::save()
{
	tinyxml2::XMLDocument doc;

	tinyxml2::XMLDeclaration* declaration = doc.NewDeclaration(0);
	doc.LinkEndChild(declaration);

	tinyxml2::XMLElement* gameobjects_elem = doc.NewElement("GameObjects");
	doc.LinkEndChild(gameobjects_elem);

	for (unsigned int i = 0; i < m_GameObjects.getElementNumber(); i++)
	{
		GameObject* gameobject = m_GameObjects[i];

		tinyxml2::XMLElement* gameobject_elem = doc.NewElement("GameObject");

		gameobjects_elem->LinkEndChild(gameobject_elem);

		gmk::vector<GameObjectComponent*>& components = gameobject->getComponents();

		for (unsigned int j = 0; j < components.getElementNumber(); j++)
		{
			GameObjectComponent* component = components[j];

			tinyxml2::XMLElement* component_elem = doc.NewElement("Component");

			gameobject_elem->LinkEndChild(component_elem);

			component_elem->SetAttribute("type", component->type_name.c_str());

			component->OnXMLSave(component_elem);
		}
	}

	doc.SaveFile(path.c_str());
}

void Scene::saveTemp(std::string _path)
{
	std::string pathBckp = path;

	path = _path;
	save();
	path = pathBckp;
}

void Scene::loadTemp(std::string _path)
{
	std::string pathBckp = path;

	path = _path;
	load();
	path = pathBckp;
}

gmk::vector<GameObject*>& Scene::getGameObjects()
{
	return m_GameObjects;
}

void Scene::addGameObject(GameObject* _object)
{
	m_GameObjects.push_back(_object);
}

void Scene::removeGameObject(GameObject* _object)
{
	m_GameObjects.removeElement(_object);
}

GameObject* Scene::findGameObjectByTreeID(void* _treeID)
{
	for (unsigned int i = 0; i < m_GameObjects.getElementNumber(); i++)
		if (m_GameObjects[i]->treeID == _treeID)
			return m_GameObjects[i];

	return 0;
}

GameObject* Scene::findGameObjectByName(std::string _name)
{
	for (unsigned int i = 0; i < m_GameObjects.getElementNumber(); i++)
		if (m_GameObjects[i]->name == _name)
			return m_GameObjects[i];

	return 0;
}

void Scene::removeGameObjects()
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