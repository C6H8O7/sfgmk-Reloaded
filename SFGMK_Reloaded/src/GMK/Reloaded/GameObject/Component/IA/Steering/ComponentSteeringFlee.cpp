#include "stdafx.h"


ComponentSteeringFlee::ComponentSteeringFlee(GameObject* _parent)
	: ComponentSteering("SteeringFlee", _parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_Steering = new gmk::SteeringFlee(_parent);

	add();
}

ComponentSteeringFlee::~ComponentSteeringFlee()
{
	remove();

	delete m_Steering;
}

r_void ComponentSteeringFlee::OnUpdate(SFMLCanvas * _canvas)
{

}

r_void ComponentSteeringFlee::OnDraw(SFMLCanvas* _canvas)
{

}

r_void ComponentSteeringFlee::OnMembersUpdate()
{
	ComponentSteering::OnMembersUpdate();
}

#ifdef SFGMKR_EDITOR
r_void ComponentSteeringFlee::OnRegistration()
{
	beginRegister();

	ComponentSteering::OnRegistration();

	endRegister();
}
#endif

r_void ComponentSteeringFlee::OnXMLSave(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLSave(_element);
}

r_void ComponentSteeringFlee::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLLoad(_element);
}