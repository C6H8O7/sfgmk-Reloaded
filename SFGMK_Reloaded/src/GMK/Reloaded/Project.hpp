#ifndef SFGMKR_PROJECT_HPP
#define SFGMKR_PROJECT_HPP

class Project
{
public:

	Project();
	~Project();

	sfgmk::vector<Scene*>& getScenes();

	void addScene(Scene* _scene);
	void removeScene(Scene* _scene);

	Scene* getCurrentScene();

	void load(std::string _path);
	void save(std::string _path);

#ifdef SFGMKR_EDITOR
	std::string getAssetsPath();
	std::string createAssetsPath(std::string _filePath);
#endif

	void setName(std::string _name);
	std::string getName();

	void setPath(std::string _path);
	std::string getPath();

protected:

	Scene* m_CurrentScene;

	sfgmk::vector<Scene*> m_Scenes;

	std::string m_Name;
	std::string m_Path;
};

#endif