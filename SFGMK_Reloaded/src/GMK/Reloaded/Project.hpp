#ifndef SFGMKR_PROJECT_HPP
#define SFGMKR_PROJECT_HPP

class Project
{
public:

	Project();
	~Project();

	gmk::vector<Scene*>& getScenes();

	void addScene(Scene* _scene);
	void removeScene(Scene* _scene);

	Scene* getCurrentScene();

	void load(std::string _path);
	void save(std::string _path);

	std::string getAssetsPath();
	std::string getScenesPath();

#ifdef SFGMKR_EDITOR
	std::string createAssetsPath(std::string _filePath);
#endif

	void setName(std::string _name);
	std::string getName();

	void setPath(std::string _path);
	std::string getPath();

	static void OpenFolder(std::string _path);
	static void CreateFolder(std::string _path);

protected:

	Scene* m_CurrentScene;

	gmk::vector<Scene*> m_Scenes;

	std::string m_Name;
	std::string m_Path;
};

#endif