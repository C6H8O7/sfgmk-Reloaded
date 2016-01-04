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
	m_Map.setPosition(parent->transform.position);
}

r_void ComponentPathfindingMap::OnDraw(SFMLCanvas* _canvas)
{
#ifdef SFGMKR_EDITOR
	if (!_canvas->isEditor())
		return;

	if (MyGUI::GetGUI()->selectedGameObject != parent)
		return;

	sf::Transform transform;
	transform.translate(m_Map.getPosition());

	m_Map.draw(_canvas, transform);
#endif
}

r_void ComponentPathfindingMap::OnMembersUpdate()
{
	if (m_PathChanged)
	{
		m_PathChanged = false;

		sf::Vector2i d1, d2;

		m_Map.loadMapFromFile(gmk::AssetsManager::GetSingleton()->getAssetPath(m_Path).c_str(), d1, d2);
	}

	if (m_CaseSizeChanged)
	{
		m_CaseSizeChanged = false;

		m_Map.setCaseSize(m_CaseSize);
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentPathfindingMap::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Path", &m_Path, &m_PathChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_INT, "Case Size", &m_CaseSize, &m_CaseSizeChanged);

	endRegister();
}
#endif

r_void ComponentPathfindingMap::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("path", m_Path.c_str());
	_element->SetAttribute("case", m_CaseSize);
}

r_void ComponentPathfindingMap::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_Path = _element->Attribute("path");
	m_PathChanged = true;

	m_CaseSize = _element->IntAttribute("case");
	m_CaseSizeChanged = true;
}

gmk::PathfindingMap * ComponentPathfindingMap::getMapPtr()
{
	return &m_Map;
}