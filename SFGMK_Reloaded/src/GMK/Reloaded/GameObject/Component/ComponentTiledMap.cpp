#include "stdafx.h"

ComponentTiledMap::ComponentTiledMap(GameObject* _parent)
	: GameObjectComponent("TiledMap", _parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_PathChanged = false;
}

ComponentTiledMap::~ComponentTiledMap()
{

}

r_void ComponentTiledMap::OnUpdate(SFMLCanvas * _canvas)
{

}

r_void ComponentTiledMap::OnDraw(SFMLCanvas* _canvas)
{
	sf::Transform transform;
	transform.rotate(parent->transform.rotation);
	transform.scale(parent->transform.scale);
	transform.translate(parent->transform.position);

	m_Map.draw(_canvas, transform);
}

r_void ComponentTiledMap::OnMembersUpdate()
{
	if (m_PathChanged)
	{
		m_PathChanged = false;

		if (m_Path.size())
			m_Map.loadFromFile(gmk::AssetsManager::GetSingleton()->getAssetPath(m_Path));
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentTiledMap::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Path", &m_Path, &m_PathChanged);

	endRegister();
}
#endif

r_void ComponentTiledMap::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("path", m_Path.c_str());
}

r_void ComponentTiledMap::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_Path = _element->Attribute("path");
	m_PathChanged = true;
}