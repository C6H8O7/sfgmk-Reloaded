ComponentPathfindingAgent::ComponentPathfindingAgent(GameObject* _parent)
	: GameObjectComponent("PathfindingAgent", _parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_Map = 0;

	m_MapNameChanged = false;
	m_MapName = "null";

	m_Speed = 0.0f;

	parent->pathfindingPtr = &m_Agent;
}

ComponentPathfindingAgent::~ComponentPathfindingAgent()
{
	parent->pathfindingPtr = 0;
}

r_void ComponentPathfindingAgent::OnUpdate(SFMLCanvas * _canvas)
{
	if (!SFMLCanvas::isPlaying)
		return;

	r_vector2f dir = m_Agent.getDirection(parent->transform.position);

	if (dir.x || dir.y)
		parent->transform.position += dir * m_Speed * gmk::TimeManager::GetSingleton()->getDeltaTime();
}

r_void ComponentPathfindingAgent::OnDraw(SFMLCanvas* _canvas)
{
#ifdef SFGMKR_EDITOR
	if (!_canvas->isEditor())
		return;

	if (!m_Map)
		return;

	sf::Transform transform;
	transform.translate(m_Map->getPosition());

	m_Agent.drawPath(_canvas, transform);
#endif
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

			if (m_MapObject)
			{
				GameObjectComponent* mapComponent = m_MapObject->getComponent("PathfindingMap");

				if (mapComponent)
				{
					m_Map = ((ComponentPathfindingMap*)mapComponent)->getMapPtr();
					m_Agent.setMap(m_Map);
				}
			}
		}
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentPathfindingAgent::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Map", &m_MapName, &m_MapNameChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Speed", &m_Speed, 0);

	GameObjectComponent::ComponentProperty* propertyAlgo = registerProperty(ePROPERTY_TYPE::TYPE_ENUM, "Algo", &m_Algo, &m_AlgoChanged);
	propertyAlgo->wxChoices.Add("Z-Path", gmk::ePATHFINDING_ALGOS::eZpath);
	propertyAlgo->wxChoices.Add("Dijkstra", gmk::ePATHFINDING_ALGOS::eDijkstra);
	propertyAlgo->wxChoices.Add("A*", gmk::ePATHFINDING_ALGOS::eAStar);

	endRegister();
}
#endif

r_void ComponentPathfindingAgent::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("map", m_MapName.c_str());
	_element->SetAttribute("speed", m_Speed);
	_element->SetAttribute("algo", m_Algo);
}

r_void ComponentPathfindingAgent::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_MapName = _element->Attribute("map");
	m_MapNameChanged = true;

	m_Speed = _element->FloatAttribute("speed");

	m_Algo = _element->IntAttribute("algo");
}