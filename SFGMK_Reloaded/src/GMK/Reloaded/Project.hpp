#ifndef SFGMKR_PROJECT_HPP
#define SFGMKR_PROJECT_HPP

class Project
{
public:

	Project();
	~Project();

	sfgmk::vector<Scene*>& getScenes();

	std::string getPath();

	void addScene(Scene* _scene);
	void removeScene(Scene* _scene);

	Scene* getCurrentScene();

	void load(std::string _path);
	void save(std::string _path);

#ifdef SFGMKR_EDITOR
	std::string getAssetsPath();
	std::string getRelativePath(std::string _filePath);
#endif

protected:

	Scene* m_CurrentScene;

	sfgmk::vector<Scene*> m_Scenes;

	std::string m_Name;
	std::string m_Path;
};

#endif