#include "stdafx.h"


ComponentSteeringObstacleAvoidance::ComponentSteeringObstacleAvoidance(GameObject* _parent)
	: ComponentSteering("SteeringObstacleAvoidance", _parent), m_bAheadFactor(false)
#ifdef SFGMKR_EDITOR
	, m_AheadVector(sf::Lines, 2)
#endif
{
#ifdef SFGMKR_EDITOR
	OnRegistration();

	m_AheadVector[0].color = m_AheadVector[1].color = sf::Color::Green;
#endif

	m_Steering = new gmk::SteeringObstacleAvoidance(_parent);

	add();

	m_fAheadFactor = ((gmk::SteeringObstacleAvoidance*)(m_Steering))->getAheadFactor();
}

ComponentSteeringObstacleAvoidance::~ComponentSteeringObstacleAvoidance()
{
	remove();

	delete m_Steering;
}

r_void ComponentSteeringObstacleAvoidance::OnUpdate(SFMLCanvas * _canvas)
{
#ifdef SFGMKR_EDITOR
	m_AheadVector[0].position = sf::Vector2f(parent->transform.getPosition());
	m_AheadVector[1].position = ((gmk::SteeringObstacleAvoidance*)m_Steering)->getAhead();
#endif
}

r_void ComponentSteeringObstacleAvoidance::OnDraw(SFMLCanvas* _canvas)
{
#ifdef SFGMKR_EDITOR
	if( _canvas->isEditor() )
		_canvas->draw(m_AheadVector);
#endif
}

r_void ComponentSteeringObstacleAvoidance::OnMembersUpdate()
{
	ComponentSteering::OnMembersUpdate();

	if( m_bAheadFactor )
	{
		m_bAheadFactor = false;
		((gmk::SteeringObstacleAvoidance*)m_Steering)->setAheadFactor(m_fAheadFactor);
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentSteeringObstacleAvoidance::OnRegistration()
{
	beginRegister();

	ComponentSteering::OnRegistration();

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Ahead Factor", &m_fAheadFactor, &m_bAheadFactor);

	endRegister();
}
#endif

r_void ComponentSteeringObstacleAvoidance::OnXMLSave(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLSave(_element);

	_element->SetAttribute("ahead_factor", m_fAheadFactor);
}

r_void ComponentSteeringObstacleAvoidance::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLLoad(_element);

	m_fAheadFactor = _element->FloatAttribute("ahead_factor");
	m_bAheadFactor = true;
}