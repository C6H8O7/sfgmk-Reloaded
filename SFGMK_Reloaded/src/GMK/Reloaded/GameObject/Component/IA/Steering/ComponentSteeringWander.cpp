#include "stdafx.h"


ComponentSteeringWander::ComponentSteeringWander(GameObject* _parent)
	: ComponentSteering("SteeringWander", _parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_Steering = new gmk::SteeringWander(_parent);

	add();
}

ComponentSteeringWander::~ComponentSteeringWander()
{
	remove();

	delete m_Steering;
}

r_void ComponentSteeringWander::OnUpdate(SFMLCanvas * _canvas)
{
/*#ifdef SFGMKR_EDITOR
	m_AheadVector[0].position = sf::Vector2f(parent->transform.getPosition());
	m_AheadVector[1].position = m_Steering.getAhead();
#endif*/
}

r_void ComponentSteeringWander::OnDraw(SFMLCanvas* _canvas)
{
/*#ifdef SFGMKR_EDITOR
	if( _canvas->isEditor() )
		_canvas->draw(m_AheadVector);
#endif*/
}


r_void ComponentSteeringWander::OnMembersUpdate()
{
	ComponentSteering::OnMembersUpdate();
}

#ifdef SFGMKR_EDITOR
r_void ComponentSteeringWander::OnRegistration()
{
	beginRegister();

	ComponentSteering::OnRegistration();

	endRegister();
}
#endif


r_void ComponentSteeringWander::OnXMLSave(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLSave(_element);
}

r_void ComponentSteeringWander::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLLoad(_element);
}