Project::Project()
{
	m_CurrentScene = new Scene();
	m_Scenes.push_back(m_CurrentScene);
}

Project::~Project()
{

}

sfgmk::vector<Scene*>& Project::getScenes()
{
	return m_Scenes;
}

std::string Project::getPath()
{
	return m_Path;
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
		scene->path = scene_elem->Attribute("path");

		m_Scenes.push_back(scene);
	}

	if (m_Scenes.size())
		m_CurrentScene = m_Scenes[0];
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
}

#ifdef SFGMKR_EDITOR
std::string Project::getAssetsPath()
{
	std::string path_up = m_Path.substr(0, m_Path.find_last_of('\\'));

	std::string path_data = path_up + "\\assets";

	return path_data;
}

std::string Project::getRelativePath(std::string _filePath)
{
	wxFileName* name = new wxFileName(wxString(_filePath));

	name->MakeRelativeTo(wxGetCwd());

	std::string relative_path = std::string((const char*)name->GetFullPath().c_str());

	delete name;

	return relative_path;
}
#endif