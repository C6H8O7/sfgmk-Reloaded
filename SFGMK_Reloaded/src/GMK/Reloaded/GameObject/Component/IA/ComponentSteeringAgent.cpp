#include "stdafx.h"

ComponentSteeringAgent::ComponentSteeringAgent(GameObject* _parent)
	: GameObjectComponent("SteeringAgent", _parent), m_Steering(_parent), m_SteeringVector(sf::Lines, 2)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	parent->steeringPtr = &m_Steering;

	m_SteeringVector[0].color = sf::Color::White;
	m_SteeringVector[1].color = sf::Color::White;
}

ComponentSteeringAgent::~ComponentSteeringAgent()
{
	parent->steeringPtr = 0;
}

r_void ComponentSteeringAgent::OnUpdate(SFMLCanvas * _canvas)
{
#ifdef SFGMKR_EDITOR
	r_vector2f Steering = gmk::math::Calc_UnitVector(m_Steering.getSteeringVector());
	Steering *= 100.0f;

	m_SteeringVector[0].position = sf::Vector2f(parent->transform.position);
	m_SteeringVector[1].position = m_SteeringVector[0].position + Steering;
#endif
}

r_void ComponentSteeringAgent::OnDraw(SFMLCanvas* _canvas)
{
#ifdef SFGMKR_EDITOR
	if( _canvas->isEditor() )
		_canvas->draw(m_SteeringVector);
#endif
}

r_void ComponentSteeringAgent::OnMembersUpdate()
{

}

#ifdef SFGMKR_EDITOR
r_void ComponentSteeringAgent::OnRegistration()
{
	beginRegister();


	endRegister();
}
#endif

r_void ComponentSteeringAgent::OnXMLSave(tinyxml2::XMLElement* _element)
{

}

r_void ComponentSteeringAgent::OnXMLLoad(tinyxml2::XMLElement* _element)
{

}