Scene::Scene()
	: name("Default")
{

}

Scene::~Scene()
{
	removeGameObjects();
}

r_void Scene::load()
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
			r_string type = component_elem->Attribute("type");

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
			else if (type == "ParticleSystem")
				component = new ComponentParticleSystem(gameobject);
			else if (type == "TiledMap")
				component = new ComponentTiledMap(gameobject);
			else if (type == "PathfindingMap")
				component = new ComponentPathfindingMap(gameobject);
			else if (type == "PathfindingAgent")
				component = new ComponentPathfindingAgent(gameobject);
			else if (type == "Collider")
				component = new ComponentCollider(gameobject);
			else if (type == "Selector")
				component = new ComponentSelector(gameobject);

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

r_void Scene::unload()
{
	removeGameObjects();
}

r_void Scene::save()
{
	tinyxml2::XMLDocument doc;

	tinyxml2::XMLDeclaration* declaration = doc.NewDeclaration(0);
	doc.LinkEndChild(declaration);

	tinyxml2::XMLElement* gameobjects_elem = doc.NewElement("GameObjects");
	doc.LinkEndChild(gameobjects_elem);

	for (r_uint32 i = 0; i < m_GameObjects.getElementNumber(); i++)
	{
		GameObject* gameobject = m_GameObjects[i];

		tinyxml2::XMLElement* gameobject_elem = doc.NewElement("GameObject");

		gameobjects_elem->LinkEndChild(gameobject_elem);

		gmk::vector<GameObjectComponent*>& components = gameobject->getComponents();

		for (r_uint32 j = 0; j < components.getElementNumber(); j++)
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

r_void Scene::saveTemp(r_string _path)
{
	r_string pathBckp = path;

	path = _path;
	save();
	path = pathBckp;
}

r_void Scene::loadTemp(r_string _path)
{
	r_string pathBckp = path;

	path = _path;
	load();
	path = pathBckp;
}

gmk::vector<GameObject*>& Scene::getGameObjects()
{
	return m_GameObjects;
}

r_void Scene::addGameObject(GameObject* _object)
{
	m_GameObjects.push_back(_object);
}

r_void Scene::removeGameObject(GameObject* _object)
{
	delete _object;

	m_GameObjects.removeElement(_object);
}

GameObject* Scene::findGameObjectByTreeID(r_void* _treeID)
{
	for (r_uint32 i = 0; i < m_GameObjects.getElementNumber(); i++)
		if (m_GameObjects[i]->treeID == _treeID)
			return m_GameObjects[i];

	return 0;
}

GameObject* Scene::findGameObjectByName(r_string _name)
{
	for (r_uint32 i = 0; i < m_GameObjects.getElementNumber(); i++)
		if (m_GameObjects[i]->name == _name)
			return m_GameObjects[i];

	return 0;
}

r_void Scene::removeGameObjects()
{
	for (r_uint32 i = 0; i < m_GameObjects.getElementNumber(); i++)
	{
#ifdef SFGMKR_EDITOR
		m_GameObjects[i]->showComponents(false);
#endif
		delete m_GameObjects[i];
	}

	m_GameObjects.clear();
}