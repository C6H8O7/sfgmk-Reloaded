#include "stdafx.h"

ComponentPathfindingMap::ComponentPathfindingMap(GameObject* _parent)
	: GameObjectComponent("PathfindingMap", _parent), m_CaseSize(32), m_MapSize(0, 0), m_MapSizeChanged(false), m_CaseNumber(0), m_WallNumber(0), 
	m_GenerationType(gmk::eMAP_GENERATION_TYPE::eClassic), m_MaxRoom(1U), m_RoomMinSize(1, 1), m_RoomMaxSize(2, 2)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif
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
r_void ComponentPathfindingMap::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Path", &m_Path, 0);
	registerProperty(ePROPERTY_TYPE::TYPE_INT, "Case Size", &m_CaseSize, &m_CaseSizeChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_INT, "Map Size X", &m_MapSize.x, &m_MapSizeChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_INT, "Map Size Y", &m_MapSize.y, &m_MapSizeChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_INT, "Map case number", &m_CaseNumber, 0, true);
	registerProperty(ePROPERTY_TYPE::TYPE_INT, "Map wall number", &m_WallNumber, 0, true);

	registerProperty(ePROPERTY_TYPE::TYPE_BUTTON, "Load Map", 0, 0, false, (wxObjectEventFunction)&ComponentPathfindingMap::LoadMapEvent);

	registerProperty(ePROPERTY_TYPE::TYPE_INT, "Max Room", &m_MaxRoom);
	registerProperty(ePROPERTY_TYPE::TYPE_INT, "Room Min Size X", &m_RoomMinSize.x);
	registerProperty(ePROPERTY_TYPE::TYPE_INT, "Room Min Size Y", &m_RoomMinSize.y);
	registerProperty(ePROPERTY_TYPE::TYPE_INT, "Room Max Size X", &m_RoomMaxSize.x);
	registerProperty(ePROPERTY_TYPE::TYPE_INT, "Room Max Size Y", &m_RoomMaxSize.y);
	GameObjectComponent::ComponentProperty* propertyType = registerProperty(ePROPERTY_TYPE::TYPE_ENUM, "Generation Type", &m_GenerationType);
	propertyType->wxChoices.Add("Classic", gmk::eMAP_GENERATION_TYPE::eClassic);

	registerProperty(ePROPERTY_TYPE::TYPE_BUTTON, "Generate Map", 0, 0, false, (wxObjectEventFunction)&ComponentPathfindingMap::Generate);
	registerProperty(ePROPERTY_TYPE::TYPE_BUTTON, "Save Map", 0, 0, false, (wxObjectEventFunction)&ComponentPathfindingMap::SaveMap);

	endRegister();
}

r_void ComponentPathfindingMap::OnEditorUpdate()
{
	r_vector2f MouseWorld = SFMLCanvas::editorCanvas->getInputManager()->getMouse().getWorldPosition();
	r_vector2i FocusedCase = m_Map.getMouseCase(MouseWorld);

	//Clic dans la grille
	if( m_Map.isInMap(FocusedCase) )
	{
		//Set wall
		if( SFMLCanvas::editorCanvas->getInputManager()->getMouse().getButtonState(sf::Mouse::Left) == KEY_DOWN )
			m_Map.setTerrainType(FocusedCase.x, FocusedCase.y, gmk::ePATHFINDING_TERRAIN_TYPE::eWALL);
		//Remove wall
		else if( SFMLCanvas::editorCanvas->getInputManager()->getMouse().getButtonState(sf::Mouse::Right) == KEY_DOWN )
			m_Map.setTerrainType(FocusedCase.x, FocusedCase.y, gmk::ePATHFINDING_TERRAIN_TYPE::eGROUND);
	}

	m_CaseNumber = m_Map.getCaseNumber();
	m_WallNumber = m_Map.getWallNumber();
}


r_void ComponentPathfindingMap::LoadMapEvent(wxEvent& _event)
{
	printf("[INFO] ComponentPathfindingMap : Loading map...\n");

	LoadMap();
}

r_void ComponentPathfindingMap::LoadMap()
{
	r_vector2i d1, d2;

	if( m_Map.loadMapFromFile(gmk::AssetsManager::GetSingleton()->getAssetPath(m_Path).c_str(), d1, d2) )
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

r_void ComponentPathfindingMap::Generate(wxEvent& _event)
{
	m_Map.generateMap(m_GenerationType, m_MaxRoom, m_RoomMinSize, m_RoomMaxSize);
}

r_void ComponentPathfindingMap::SaveMap(wxEvent& _event)
{
	printf("[INFO] ComponentPathfindingMap : Saving map...\n");

	r_vector2i d1, d2;
	if( m_Map.saveMap(gmk::AssetsManager::GetSingleton()->getAssetPath(m_Path).c_str(), d1, d2) )
		printf("[INFO] ComponentPathfindingMap : Map saved.\n");
	else
		printf("[INFO] ComponentPathfindingMap : Save failed!\n");
}
#endif

r_void ComponentPathfindingMap::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("path", m_Path.c_str());
	_element->SetAttribute("case_size", m_CaseSize);
}

r_void ComponentPathfindingMap::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_Path = _element->Attribute("path");
	if( m_Path != "" )
		LoadMap();

	m_CaseSize = _element->IntAttribute("case_size");
	m_CaseSizeChanged = true;
}

gmk::PathfindingMap * ComponentPathfindingMap::getMapPtr()
{
	return &m_Map;
}