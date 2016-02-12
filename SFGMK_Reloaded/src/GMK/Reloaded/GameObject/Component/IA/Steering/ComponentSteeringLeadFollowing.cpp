#include "stdafx.h"


ComponentSteeringLeadFollowing::ComponentSteeringLeadFollowing(GameObject* _parent)
	: ComponentSteering("SteeringLeadFollowing", _parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_Steering = new gmk::SteeringLeadFollowing(_parent);

	add();
}

ComponentSteeringLeadFollowing::~ComponentSteeringLeadFollowing()
{
	remove();

	delete m_Steering;
}

r_void ComponentSteeringLeadFollowing::OnUpdate(SFMLCanvas * _canvas)
{

}

r_void ComponentSteeringLeadFollowing::OnDraw(SFMLCanvas* _canvas)
{

}

r_void ComponentSteeringLeadFollowing::OnMembersUpdate()
{
	ComponentSteering::OnMembersUpdate();
}

#ifdef SFGMKR_EDITOR
r_void ComponentSteeringLeadFollowing::OnRegistration()
{
	beginRegister();

	ComponentSteering::OnRegistration();

	endRegister();
}
#endif

r_void ComponentSteeringLeadFollowing::OnXMLSave(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLSave(_element);
}

r_void ComponentSteeringLeadFollowing::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLLoad(_element);
}