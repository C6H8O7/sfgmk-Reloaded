#include "stdafx.h"


ComponentSteeringAgent::ComponentSteeringAgent(GameObject* _parent)
	: GameObjectComponent("SteeringAgent", _parent), m_Steering(_parent), m_SteeringVectors(sf::Lines, 4)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	parent->steeringPtr = &m_Steering;

	m_SteeringVectors[0].color = m_SteeringVectors[1].color = sf::Color::White;
	m_SteeringVectors[2].color = m_SteeringVectors[3].color = sf::Color::Blue;
}

ComponentSteeringAgent::~ComponentSteeringAgent()
{
	parent->steeringPtr = 0;
}

r_void ComponentSteeringAgent::OnUpdate(SFMLCanvas * _canvas)
{
#ifdef SFGMKR_EDITOR
	//Speed
	m_SteeringVectors[0].position = sf::Vector2f(parent->transform.position);
	m_SteeringVectors[1].position = m_SteeringVectors[0].position + ((ComponentRigidbody*)(parent->getComponent("Rigidbody")))->getRigidBody()->getSpeed();

	//Steering
	m_SteeringVectors[2].position = m_SteeringVectors[0].position;
	m_SteeringVectors[3].position = m_SteeringVectors[2].position + ((ComponentRigidbody*)(parent->getComponent("Rigidbody")))->getRigidBody()->getForce();

#endif
}

r_void ComponentSteeringAgent::OnDraw(SFMLCanvas* _canvas)
{
#ifdef SFGMKR_EDITOR
	if( _canvas->isEditor() )
		_canvas->draw(m_SteeringVectors);
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