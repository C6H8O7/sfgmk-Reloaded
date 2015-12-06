Project::Project()
{
	m_CurrentScene = new Scene();
	m_Scenes.push_back(m_CurrentScene);
}

Project::~Project()
{

}

gmk::vector<Scene*>& Project::getScenes()
{
	return m_Scenes;
}

void Project::addScene(Scene* _scene)
{
	m_Scenes.push_back(_scene);
}

void Project::removeScene(Scene* _scene)
{
	m_Scenes.removeElement(_scene);
}

Scene* Project::getCurrentScene()
{
	return m_CurrentScene;
}

void Project::load(std::string _path)
{
	m_Scenes.deleteAndClear();

	tinyxml2::XMLDocument doc;

	doc.LoadFile(_path.c_str());

	tinyxml2::XMLElement* project_elem = doc.FirstChildElement("Project");

	m_Name = project_elem->Attribute("name");
	m_Path = project_elem->Attribute("path");

	tinyxml2::XMLElement* scene_elem = project_elem->FirstChildElement("Scene");

	while (scene_elem)
	{
		Scene* scene = new Scene();

		scene->name = scene_elem->Attribute("name");
		scene->path = getScenesPath() + '\\' + scene->name + ".gmkscene";

		scene_elem = scene_elem->NextSiblingElement("Scene");

		m_Scenes.push_back(scene);
	}

	if (m_Scenes.size())
	{
		m_CurrentScene = m_Scenes[0];
		m_CurrentScene->load();
	}

#ifdef SFGMKR_EDITOR
	MyGUI* gui = MyGUI::GetGUI();

	gui->GUI_ProjectPropertyName->SetValue(m_Name);
	gui->GUI_ProjectPropertyPath->SetValue(m_Path);
#endif
}

void Project::save(std::string _path)
{
	tinyxml2::XMLDocument doc;

	tinyxml2::XMLDeclaration* declaration = doc.NewDeclaration(0);
	doc.LinkEndChild(declaration);

	tinyxml2::XMLElement* project_elem = doc.NewElement("Project");
	doc.LinkEndChild(project_elem);

	project_elem->SetAttribute("name", m_Name.c_str());
	project_elem->SetAttribute("path", m_Path.c_str());

	for (unsigned int i = 0; i < m_Scenes.size(); i++)
	{
		tinyxml2::XMLElement* scene_elem = doc.NewElement("Scene");
		project_elem->LinkEndChild(scene_elem);

		scene_elem->SetAttribute("name", m_Scenes[i]->name.c_str());
		scene_elem->SetAttribute("path", m_Scenes[i]->path.c_str());
	}

	doc.SaveFile(_path.c_str());
}

std::string Project::getAssetsPath()
{
	return m_Path + "\\assets";
}

std::string Project::getScenesPath()
{
	return m_Path + "\\scenes";
}

#ifdef SFGMKR_EDITOR
std::string Project::createAssetsPath(std::string _filePath)
{
	wxFileName* name = new wxFileName(wxString(_filePath));

	name->MakeRelativeTo(getAssetsPath());

	std::string relative_path = std::string((const char*)name->GetFullPath().c_str());

	delete name;

	return "assets:" + relative_path;
}
#endif

void Project::setName(std::string _name)
{
	m_Name = _name;
}

std::string Project::getName()
{
	return m_Name;
}

void Project::setPath(std::string _path)
{
	m_Path = _path;
}

std::string Project::getPath()
{
	return m_Path;
}

void Project::OpenFolder(std::string _path)
{
	char command[MAX_PATH];
	sprintf_s(command, "explorer %s", _path.c_str());
	system(command);
}

void Project::CreateFolder(std::string _path)
{
	CreateDirectoryA(_path.c_str(), 0);
}