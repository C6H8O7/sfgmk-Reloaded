#include "stdafx.h"


ComponentSteeringPathFollowing::ComponentSteeringPathFollowing(GameObject* _parent)
	: ComponentSteering("SteeringPathFollowing", _parent), m_fDetectionDistanceMax(0.0f), m_bDetectionDistanceMaxChanged(false)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_Steering = new gmk::SteeringPathFollowing(_parent);

	add();
}

ComponentSteeringPathFollowing::~ComponentSteeringPathFollowing()
{
	remove();

	delete m_Steering;
}


r_void ComponentSteeringPathFollowing::OnUpdate(SFMLCanvas * _canvas)
{

}

r_void ComponentSteeringPathFollowing::OnDraw(SFMLCanvas* _canvas)
{

}

r_void ComponentSteeringPathFollowing::OnMembersUpdate()
{
	ComponentSteering::OnMembersUpdate();
}

#ifdef SFGMKR_EDITOR
r_void ComponentSteeringPathFollowing::OnRegistration()
{
	beginRegister();

	ComponentSteering::OnRegistration();

	endRegister();
}
#endif


r_void ComponentSteeringPathFollowing::OnXMLSave(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLSave(_element);
}

r_void ComponentSteeringPathFollowing::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLLoad(_element);
}