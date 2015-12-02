#ifndef SFGMKR_GMKPROJECT_HPP
#define SFGMKR_GMKPROJECT_HPP

class GMKProject
{
public:

	GMKProject();
	~GMKProject();

	sfgmk::vector<Scene*>& getScenes();

	std::string getPath();

	void addScene(Scene* _scene);
	void removeScene(Scene* _scene);

protected:

	sfgmk::vector<Scene*> m_Scenes;

	std::string m_Path;
};

#endif