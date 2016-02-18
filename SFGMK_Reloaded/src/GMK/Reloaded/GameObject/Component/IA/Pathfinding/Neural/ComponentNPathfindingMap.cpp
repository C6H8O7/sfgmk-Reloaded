#include "stdafx.h"

ComponentNPathfindingMap::ComponentNPathfindingMap(GameObject* _parent)
	: GameObjectComponent("NPathfindingMap", _parent), m_CaseSize(32), m_MapSize(0, 0), m_MapSizeChanged(false), m_CaseNumber(0), m_WallNumber(0)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif
}

ComponentNPathfindingMap::~ComponentNPathfindingMap()
{

}

r_void ComponentNPathfindingMap::OnUpdate(SFMLCanvas * _canvas)
{
	m_Map.setPosition(parent->transform.getPosition());
}

r_void ComponentNPathfindingMap::OnDraw(SFMLCanvas* _canvas)
{
	if (MyGUI::GetGUI()->selectedGameObject != parent)
		return;

	m_Map.draw(_canvas, parent->transform.getTransform());
}

r_void ComponentNPathfindingMap::OnMembersUpdate()
{
	if (m_CaseSizeChanged)
	{
		m_CaseSizeChanged = false;

		m_Map.setCaseSize(m_CaseSize);
	}

	if( m_MapSizeChanged )
	{
		m_MapSizeChanged = false;

		m_Map.resize(m_MapSize.x, m_MapSize.y);
		m_CaseNumber = m_Map.getCaseNumber();
		m_WallNumber = m_Map.getWallNumber();
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentNPathfindingMap::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Path", &m_Path, 0);
	registerProperty(ePROPERTY_TYPE::TYPE_INT, "Case Size", &m_CaseSize, &m_CaseSizeChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_INT, "Map Size X", &m_MapSize.x, &m_MapSizeChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_INT, "Map Size Y", &m_MapSize.y, &m_MapSizeChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_INT, "Map case number", &m_CaseNumber, 0, true);
	registerProperty(ePROPERTY_TYPE::TYPE_INT, "Map wall number", &m_WallNumber, 0, true);

	registerProperty(ePROPERTY_TYPE::TYPE_BUTTON, "Load Map", 0, 0, false, (wxObjectEventFunction)&ComponentNPathfindingMap::LoadMapEvent);
	registerProperty(ePROPERTY_TYPE::TYPE_BUTTON, "Precompute Paths", 0, 0, false, (wxObjectEventFunction)&ComponentNPathfindingMap::PrecomputePaths);
	registerProperty(ePROPERTY_TYPE::TYPE_BUTTON, "Precompute Network", 0, 0, false, (wxObjectEventFunction)&ComponentNPathfindingMap::PrecomputeNetwork);

	endRegister();
}

r_void ComponentNPathfindingMap::OnEditorUpdate()
{

}

r_void ComponentNPathfindingMap::LoadMapEvent(wxEvent& _event)
{
	printf("[INFO] ComponentNPathfindingMap : Loading map ...\n");

	LoadMap();
}

r_void ComponentNPathfindingMap::PrecomputePaths(wxEvent& _event)
{
	printf("[INFO] ComponentNPathfindingMap : Precomputing paths ... ");

	m_Pathfinding.precomputePaths(gmk::ePATHFINDING_ALGOS::eZpath, &m_Map);
}

r_void ComponentNPathfindingMap::PrecomputeNetwork(wxEvent& _event)
{
	printf("[INFO] ComponentNPathfindingMap : Precomputing network ...\n");

	m_Pathfinding.precomputeNeuronNetwork(500000, {4, 16, 2});
}
#endif

r_void ComponentNPathfindingMap::LoadMap()
{
	r_vector2i d1, d2;

	if (m_Map.loadMapFromFile(gmk::AssetsManager::GetSingleton()->getAssetPath(m_Path).c_str(), d1, d2))
		printf("[INFO] ComponentPathfindingMap : Map loaded.\n");
	else
	{
		printf("[INFO] ComponentPathfindingMap : Loading failed!\n");
		return;
	}

	m_MapSize = m_Map.getSize();

	m_CaseNumber = m_Map.getCaseNumber();
	m_WallNumber = m_Map.getWallNumber();
}

r_void ComponentNPathfindingMap::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("path", m_Path.c_str());
	_element->SetAttribute("case_size", m_CaseSize);
}

r_void ComponentNPathfindingMap::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_Path = _element->Attribute("path");

	if( m_Path != "" )
		LoadMap();

	m_CaseSize = _element->IntAttribute("case_size");
	m_CaseSizeChanged = true;
}

gmk::PathfindingMap* ComponentNPathfindingMap::getMapPtr()
{
	return &m_Map;
}

gmk::Pathfinding* ComponentNPathfindingMap::getPathfindingPtr()
{
	return &m_Pathfinding;
}