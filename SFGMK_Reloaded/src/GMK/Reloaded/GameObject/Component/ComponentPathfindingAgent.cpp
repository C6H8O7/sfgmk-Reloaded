ComponentPathfindingAgent::ComponentPathfindingAgent(GameObject* _parent)
	: GameObjectComponent("PathfindingAgent", _parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_MapNameChanged = false;
	m_MapName = "null";

	m_Speed = 0.0f;
}

ComponentPathfindingAgent::~ComponentPathfindingAgent()
{

}

r_void ComponentPathfindingAgent::OnUpdate(SFMLCanvas * _canvas)
{

}

r_void ComponentPathfindingAgent::OnDraw(SFMLCanvas* _canvas)
{

}

r_void ComponentPathfindingAgent::OnMembersUpdate()
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
		}
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentPathfindingAgent::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Map", &m_MapName, &m_MapNameChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Speed", &m_Speed, 0);

	endRegister();
}
#endif

r_void ComponentPathfindingAgent::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("map", m_MapName.c_str());
	_element->SetAttribute("speed", m_Speed);
}

r_void ComponentPathfindingAgent::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_MapName = _element->Attribute("map");
	m_MapNameChanged = true;

	m_Speed = _element->FloatAttribute("speed");
}