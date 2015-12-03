Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::Load(std::string _path)
{
	GameObjectManager* manager = GameObjectManager::GetSingleton();

#ifdef SFGMKR_EDITOR
	MyGUI* gui = MyGUI::GetGUI();

	if (gui->selectedGameObject)
		gui->selectedGameObject->showComponents(false);

	gui->selectedGameObject = 0;
#endif

	manager->removeGameObjects();

	tinyxml2::XMLDocument doc;

	doc.LoadFile(_path.c_str());

	tinyxml2::XMLElement* gameobjects_elem = doc.FirstChildElement("GameObjects");

	tinyxml2::XMLElement* gameobject_elem = gameobjects_elem->FirstChildElement("GameObject");

	while (gameobject_elem)
	{
		GameObject* gameobject = new GameObject();

		gameobject->name = gameobject_elem->Attribute("name");
		gameobject->transform.position.x = gameobject_elem->FloatAttribute("position_x");
		gameobject->transform.position.y = gameobject_elem->FloatAttribute("position_y");
		gameobject->transform.scale.x = gameobject_elem->FloatAttribute("scale_x");
		gameobject->transform.scale.y = gameobject_elem->FloatAttribute("scale_y");
		gameobject->transform.rotation = gameobject_elem->FloatAttribute("rotation");

		tinyxml2::XMLElement* component_elem = gameobject_elem->FirstChildElement("Component");

		while (component_elem)
		{
			GameObjectComponent* component = 0;
			std::string type = component_elem->Attribute("type");

			if (type == "Sprite")
				component = new ComponentSprite(gameobject);
			else if (type == "Script")
				component = new ComponentScript(gameobject);
			else if (type == "Camera")
				component = new ComponentCamera(gameobject);
			else if (type == "Particle System")
				component = new ComponentParticleSystem(gameobject);

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

		manager->addGameObject(gameobject);

		gameobject_elem = gameobject_elem->NextSiblingElement("GameObject");
	}

#ifdef SFGMKR_EDITOR
	gui->Update_HierarchyTree();
	gui->Update_PropertyGrid();
#endif
}

void Scene::Save(std::string _path)
{
	GameObjectManager* manager = GameObjectManager::GetSingleton();

	tinyxml2::XMLDocument doc;

	tinyxml2::XMLDeclaration* declaration = doc.NewDeclaration(0);
	doc.LinkEndChild(declaration);

	tinyxml2::XMLElement* gameobjects_elem = doc.NewElement("GameObjects");
	doc.LinkEndChild(gameobjects_elem);

	sfgmk::vector<GameObject*>& gameobjects = manager->getGameObjects();

	for (unsigned int i = 0; i < gameobjects.getElementNumber(); i++)
	{
		GameObject* gameobject = gameobjects[i];

		tinyxml2::XMLElement* gameobject_elem = doc.NewElement("GameObject");

		gameobjects_elem->LinkEndChild(gameobject_elem);

		gameobject_elem->SetAttribute("name", gameobject->name.c_str());
		gameobject_elem->SetAttribute("position_x", gameobject->transform.position.x);
		gameobject_elem->SetAttribute("position_y", gameobject->transform.position.y);
		gameobject_elem->SetAttribute("scale_x", gameobject->transform.scale.x);
		gameobject_elem->SetAttribute("scale_y", gameobject->transform.scale.y);
		gameobject_elem->SetAttribute("rotation", gameobject->transform.rotation);

		sfgmk::vector<GameObjectComponent*>& components = gameobject->getComponents();

		for (unsigned int j = 0; j < components.getElementNumber(); j++)
		{
			GameObjectComponent* component = components[j];

			tinyxml2::XMLElement* component_elem = doc.NewElement("Component");

			gameobject_elem->LinkEndChild(component_elem);

			component_elem->SetAttribute("type", component->type_name.c_str());

			component->OnXMLSave(component_elem);
		}
	}

	doc.SaveFile(_path.c_str());
}

#ifdef SFGMKR_EDITOR
std::string Scene::GetDataPath()
{
	std::string path = std::string(wxGetCwd().c_str());

	std::string path_up = path.substr(0, path.find_last_of('\\'));

	std::string path_data = path_up + "\\data";

	return path_data;
}

std::string Scene::GetRelativePath(std::string _filePath)
{
	wxFileName* name = new wxFileName(wxString(_filePath));

	name->MakeRelativeTo(wxGetCwd());

	std::string relative_path = std::string((const char*)name->GetFullPath().c_str());

	delete name;

	return relative_path;
}
#endif