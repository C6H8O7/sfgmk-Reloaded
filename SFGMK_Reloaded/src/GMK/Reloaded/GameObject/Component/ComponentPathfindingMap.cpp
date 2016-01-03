#include "ComponentPathfindingMap.hpp"
ComponentPathfindingMap::ComponentPathfindingMap(GameObject* _parent)
	: GameObjectComponent("PathfindingMap", _parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_PathChanged = false;
}

ComponentPathfindingMap::~ComponentPathfindingMap()
{

}

r_void ComponentPathfindingMap::OnUpdate(SFMLCanvas * _canvas)
{

}

r_void ComponentPathfindingMap::OnDraw(SFMLCanvas* _canvas)
{
	if (!_canvas->isEditor())
		return;

#ifdef SFGMKR_EDITOR
	if (MyGUI::GetGUI()->selectedGameObject != parent)
		return;
#endif

	sf::Transform transform;
	transform.rotate(parent->transform.rotation);
	transform.scale(parent->transform.scale);
	transform.translate(parent->transform.position);

	m_Map.draw(_canvas, transform);
}

r_void ComponentPathfindingMap::OnMembersUpdate()
{
	if (m_PathChanged)
	{
		m_PathChanged = false;

		sf::Vector2i d1, d2;

		m_Map.loadMapFromFile(gmk::AssetsManager::GetSingleton()->getAssetPath(m_Path).c_str(), d1, d2);
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentPathfindingMap::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Path", &m_Path, &m_PathChanged);

	endRegister();
}
#endif

r_void ComponentPathfindingMap::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("path", m_Path.c_str());
}

r_void ComponentPathfindingMap::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_Path = _element->Attribute("path");
	m_PathChanged = true;
}

gmk::PathfindingMap * ComponentPathfindingMap::getMapPtr()
{
	return &m_Map;
}