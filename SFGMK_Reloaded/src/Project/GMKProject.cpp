GMKProject::GMKProject()
{

}

GMKProject::~GMKProject()
{

}

sfgmk::vector<Scene*>& GMKProject::getScenes()
{
	return m_Scenes;
}

std::string GMKProject::getPath()
{
	return m_Path;
}

void GMKProject::addScene(Scene* _scene)
{
	m_Scenes.push_back(_scene);
}

void GMKProject::removeScene(Scene* _scene)
{
	m_Scenes.removeElement(_scene);
}