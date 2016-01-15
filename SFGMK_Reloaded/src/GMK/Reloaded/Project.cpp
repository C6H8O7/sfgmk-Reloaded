#include "stdafx.h"

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

r_void Project::addScene(Scene* _scene)
{
	m_Scenes.push_back(_scene);
}

r_void Project::removeScene(Scene* _scene)
{
	m_Scenes.removeElement(_scene);
}

Scene* Project::getCurrentScene()
{
	return m_CurrentScene;
}

r_void Project::load(r_string _path)
{
	if (m_CurrentScene)
		m_CurrentScene->unload();

	m_Scenes.deleteAndClear();

#ifdef SFGMKR_EDITOR
	MyGUI* gui = MyGUI::GetGUI();

	gui->selectedGameObject = 0;
	gui->selectedGameObjectComponent = 0;
#endif

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
	gui->GUI_ProjectPropertyName->SetValue(m_Name);
	gui->GUI_ProjectPropertyPath->SetValue(m_Path);
#endif
}

r_void Project::save(r_string _path)
{
	tinyxml2::XMLDocument doc;

	tinyxml2::XMLDeclaration* declaration = doc.NewDeclaration(0);
	doc.LinkEndChild(declaration);

	tinyxml2::XMLElement* project_elem = doc.NewElement("Project");
	doc.LinkEndChild(project_elem);

	project_elem->SetAttribute("name", m_Name.c_str());
	project_elem->SetAttribute("path", m_Path.c_str());

	for (r_uint32 i = 0; i < m_Scenes.size(); i++)
	{
		tinyxml2::XMLElement* scene_elem = doc.NewElement("Scene");
		project_elem->LinkEndChild(scene_elem);

		scene_elem->SetAttribute("name", m_Scenes[i]->name.c_str());
		scene_elem->SetAttribute("path", m_Scenes[i]->path.c_str());
	}

	doc.SaveFile(_path.c_str());
}

r_string Project::getAssetsPath()
{
	return m_Path + "\\assets";
}

r_string Project::getScenesPath()
{
	return m_Path + "\\scenes";
}

#ifdef SFGMKR_EDITOR
r_string Project::createAssetsPath(r_string _filePath)
{
	wxFileName* name = new wxFileName(wxString(_filePath));

	name->MakeRelativeTo(getAssetsPath());

	r_string relative_path = r_string((const r_int8*)name->GetFullPath().c_str());

	delete name;

	return "assets:" + relative_path;
}
#endif

r_void Project::setName(r_string _name)
{
	m_Name = _name;
}

r_string Project::getName()
{
	return m_Name;
}

r_void Project::setPath(r_string _path)
{
	m_Path = _path;
}

r_string Project::getPath()
{
	return m_Path;
}

#ifdef SFGMKR_EDITOR
r_void Project::OpenFolder(r_string _path)
{
	r_int8 command[MAX_PATH];
	sprintf_s(command, "explorer %s", _path.c_str());
	system(command);
}

r_void Project::CreateFolder(r_string _path)
{
	CreateDirectoryA(_path.c_str(), 0);
}
#endif