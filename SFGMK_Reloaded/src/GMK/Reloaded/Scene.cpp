#include "stdafx.h"

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
	gui->selectedGameObjectComponent = 0;
#endif

	removeGameObjects();

	tinyxml2::XMLDocument doc;

	r_string scenePath = SFMLCanvas::project->getPath() + "/" + path;

#ifdef SFGMKR_ANDROID
	scenePath = path;
#endif

	doc.LoadFile(scenePath.c_str());

	if(SFGMKR_APP_DEBUG)
		gmk::Debug::Log(r_string("[INFO] Scene XML 0% Loaded"));

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

			component = ComponentsBank::GetSingleton()->createComponent(type, gameobject);

			if (component)
			{
				component->OnXMLLoad(component_elem);

				component->OnMembersUpdate();

				gameobject->addComponent(component);
			}

			component_elem = component_elem->NextSiblingElement("Component");
		}

		addGameObject(gameobject);

		gameobject_elem = gameobject_elem->NextSiblingElement("GameObject");
	}

	if(SFGMKR_APP_DEBUG)
		gmk::Debug::Log(r_string("[INFO] Scene XML 100% Loaded"));

#ifdef SFGMKR_EDITOR
	gui->Update_HierarchyTree();
	gui->Empty_PropertyGrid();
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

	tinyxml2::XMLElement* scene_elem = doc.NewElement("Scene");
	doc.LinkEndChild(scene_elem);

	scene_elem->SetAttribute("name", name.c_str());

	tinyxml2::XMLElement* gameobjects_elem = doc.NewElement("GameObjects");
	doc.LinkEndChild(gameobjects_elem);

	for (r_uint32 i = 0; i < m_GameObjects.size(); i++)
	{
		GameObject* gameobject = m_GameObjects[i];

		tinyxml2::XMLElement* gameobject_elem = doc.NewElement("GameObject");

		gameobjects_elem->LinkEndChild(gameobject_elem);

		gmk::vector<GameObjectComponent*>& components = gameobject->getComponents();

		for (r_uint32 j = 0; j < components.size(); j++)
		{
			GameObjectComponent* component = components[j];

			tinyxml2::XMLElement* component_elem = doc.NewElement("Component");

			gameobject_elem->LinkEndChild(component_elem);

			component_elem->SetAttribute("type", component->type_name.c_str());

			component->OnXMLSave(component_elem);
		}
	}

	r_string scenePath = SFMLCanvas::project->getPath() + "/" + path;

#ifdef SFGMKR_ANDROID
	scenePath = path;
#endif

	doc.SaveFile(scenePath.c_str());
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
#ifdef SFGMKR_EDITOR
	MyGUI* gui = MyGUI::GetGUI();

	if (gui->selectedGameObject == _object)
	{
		std::cout << "lel" << std::endl;

		gui->selectedGameObject->showComponents(false);

		gui->selectedGameObject = 0;
		gui->selectedGameObjectComponent = 0;

		gui->Empty_PropertyGrid();
	}

	gui->RemoveFrom_HierarchyTree(_object);
#endif

	delete _object;

	m_GameObjects.removeElement(_object);
}

GameObject* Scene::findGameObjectByTreeID(r_void* _treeID)
{
	for (r_uint32 i = 0; i < m_GameObjects.size(); i++)
		if (m_GameObjects[i]->treeID == _treeID)
			return m_GameObjects[i];

	return 0;
}

GameObject* Scene::findGameObjectByName(r_string _name)
{
	for (r_uint32 i = 0; i < m_GameObjects.size(); i++)
		if (m_GameObjects[i]->name == _name)
			return m_GameObjects[i];

	return 0;
}

r_bool Scene::isGameObjectInScene(GameObject* _gameobject)
{
	for (r_uint32 i = 0; i < m_GameObjects.size(); i++)
		if (m_GameObjects[i] == _gameobject)
			return true;

	return false;
}

r_void Scene::removeGameObjects()
{
#ifdef SFGMKR_EDITOR
	MyGUI::GetGUI()->Empty_PropertyGrid();
#endif

	for (r_uint32 i = 0; i < m_GameObjects.size(); i++)
		delete m_GameObjects[i];

	m_GameObjects.clear();
}