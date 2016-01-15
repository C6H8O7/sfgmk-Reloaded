#ifndef SFGMKR_PROJECT_HPP
#define SFGMKR_PROJECT_HPP

#include "stdafx.h"

class Project
{
public:

	Project();
	~Project();

	gmk::vector<Scene*>& getScenes();

	r_void addScene(Scene* _scene);
	r_void removeScene(Scene* _scene);

	Scene* getCurrentScene();

	r_void load(r_string _path);
	r_void save(r_string _path);

	r_string getAssetsPath();
	r_string getScenesPath();

#ifdef SFGMKR_EDITOR
	r_string createAssetsPath(r_string _filePath);
#endif

	r_void setName(r_string _name);
	r_string getName();

	r_void setPath(r_string _path);
	r_string getPath();

#ifdef SFGMKR_EDITOR
	static r_void OpenFolder(r_string _path);
	static r_void CreateFolder(r_string _path);
#endif

protected:

	Scene* m_CurrentScene;

	gmk::vector<Scene*> m_Scenes;

	r_string m_Name;
	r_string m_Path;
};

#endif