#include "stdafx.h"

Scene::Scene(Project* _project)
	: name("Default"), m_project(_project)
{

}

Scene::~Scene()
{
	removeGameObjects();
}

r_void Scene::load(r_bool _tmp)
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

	r_string scenePath = m_project->getPath() + "/" + path;

	if (_tmp)
		scenePath = path;

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
		GameObject* gameobject = new GameObject();

		gameobject->OnXMLLoad(gameobject_elem);

		gameobject_elem = gameobject_elem->NextSiblingElement("GameObject");
	}

	if(SFGMKR_APP_DEBUG)
		gmk::Debug::Log(r_string("[INFO] Scene XML 100% Loaded"));

#ifdef SFGMKR_EDITOR
	gui->Update_HierarchyTree();
#endif
}

r_void Scene::unload()
{
	removeGameObjects();
}

r_void Scene::save(r_bool _tmp)
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

		if(!gameobject->getParent())
			gameobject->OnXMLSave(gameobjects_elem);
	}

	r_string scenePath = m_project->getPath() + "/" + path;

	if (_tmp)
		scenePath = path;

#ifdef SFGMKR_ANDROID
	scenePath = path;
#endif

	doc.SaveFile(scenePath.c_str());
}

r_void Scene::saveTemp(r_string _path)
{
	r_string pathBckp = path;

	path = _path;
	save(true);
	path = pathBckp;
}

r_void Scene::loadTemp(r_string _path)
{
	r_string pathBckp = path;

	path = _path;
	load(true);
	path = pathBckp;
}

gmk::vector<GameObject*>& Scene::getGameObjects()
{
	return m_GameObjects;
}

gmk::vector<GameObject*>& Scene::getRootGameObjects()
{
	return m_RootGameObjects;
}

r_void Scene::addGameObject(GameObject* _object)
{
#ifdef SFGMKR_EDITOR
	MyGUI::GetGUI()->AddTo_HierarchyTree(_object);
#endif

	m_GameObjects.push_back(_object);

	if (!_object->getParent())
		m_RootGameObjects.push_back(_object);
}

r_void Scene::removeGameObject(GameObject* _object)
{
#ifdef SFGMKR_EDITOR
	MyGUI* gui = MyGUI::GetGUI();

	if (gui->selectedGameObject == _object)
	{
		gui->selectedGameObject->showComponents(false);

		gui->selectedGameObject = 0;
		gui->selectedGameObjectComponent = 0;

		gui->Empty_PropertyGrid();
	}

	gui->RemoveFrom_HierarchyTree(_object);
#endif

	delete _object;

	m_GameObjects.removeElement(_object);
	m_RootGameObjects.removeElement(_object);
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
	m_RootGameObjects.clear();
}