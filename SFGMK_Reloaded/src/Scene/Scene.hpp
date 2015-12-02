#ifndef SFGMKR_SCENE_HPP
#define SFGMKR_SCENE_HPP

#define DEFAULT_SCENE_FILE "../data/scene.gmkscene"
#define DEFAULT_TEMP_SCENE_FILE "../data/editor/temp.gmkscene"

class Scene
{
public:

	Scene();
	~Scene();

	static void Load(std::string _path);
	static void Save(std::string _path);

#ifdef SFGMKR_EDITOR
	static std::string GetDataPath();
	static std::string GetRelativePath(std::string _filePath);
#endif

	std::string name;
};

#endif