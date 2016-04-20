#include "stdafx.h"

ComponentNPathfindingAgent::ComponentNPathfindingAgent(GameObject* _parent)
	: GameObjectComponent("NPathfindingAgent", _parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_Map = 0;

	m_MapNameChanged = false;
	m_MapName = "null";

	m_Speed = 0.0f;
}

ComponentNPathfindingAgent::~ComponentNPathfindingAgent()
{

}

r_void ComponentNPathfindingAgent::OnUpdate(SFMLCanvas * _canvas)
{
	if (!_canvas->isPlaying || !m_Pathfinding)
		return;

	gmk::Mouse& mouse = _canvas->getInputManager()->getMouse();

	if (mouse.getButtonState(sf::Mouse::Left) == KEY_DOWN)
	{
		r_vector2f mouse_pos = mouse.getWorldPosition();

		r_vector2f currentPos = parent->transform.getPosition();

		r_vector2f mapSize = (r_vector2f)m_Map->getSize();
		r_float mapCaseSize = (r_float)m_Map->getCaseSize();

		r_float currx = (currentPos.x - m_Map->getPosition().x) / (mapCaseSize * mapSize.x);
		r_float curry = (currentPos.y - m_Map->getPosition().y) / (mapCaseSize * mapSize.y);

		r_float mousex = (mouse_pos.x - m_Map->getPosition().x) / (mapCaseSize * mapSize.x);
		r_float mousey = (mouse_pos.y - m_Map->getPosition().y) / (mapCaseSize * mapSize.y);

		r_vector2f dir = m_Pathfinding->getNeuronPrecomputedDirection(currx, curry, mousex, mousey);
		dir = gmk::math::Calc_UnitVector(dir);

		currentPos += m_Speed * dir * gmk::TimeManager::GetSingleton()->getDeltaTime();

		parent->transform.setPosition(currentPos);
	}
}

r_void ComponentNPathfindingAgent::OnDraw(SFMLCanvas* _canvas)
{

}

r_void ComponentNPathfindingAgent::OnMembersUpdate()
{
	if (m_MapNameChanged)
	{
		if (!m_MapName.size() || m_MapName.find("null") != std::string::npos)
		{
			m_MapObject = 0;
		}
		else
		{
			m_MapObject = SFMLCanvas::project->getCurrentScene()->findGameObjectByName(m_MapName);

			if (m_MapObject)
			{
				GameObjectComponent* mapComponent = m_MapObject->getComponent("NPathfindingMap");

				if (mapComponent)
				{
					m_Map = ((ComponentNPathfindingMap*)mapComponent)->getMapPtr();
					m_Pathfinding = ((ComponentNPathfindingMap*)mapComponent)->getPathfindingPtr();
				}
			}
		}
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentNPathfindingAgent::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Map", &m_MapName, &m_MapNameChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Speed", &m_Speed, 0);

	endRegister();
}
#endif

r_void ComponentNPathfindingAgent::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("map", m_MapName.c_str());
	_element->SetAttribute("speed", m_Speed);
}

r_void ComponentNPathfindingAgent::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_MapName = _element->Attribute("map");
	m_MapNameChanged = true;

	m_Speed = _element->FloatAttribute("speed");
}