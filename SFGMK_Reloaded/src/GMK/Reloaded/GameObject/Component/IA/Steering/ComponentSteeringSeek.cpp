#include "stdafx.h"


ComponentSteeringSeek::ComponentSteeringSeek(GameObject* _parent)
	: ComponentSteering("SteeringSeek", _parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_Steering = new gmk::SteeringSeek(_parent);

	add();
}

ComponentSteeringSeek::~ComponentSteeringSeek()
{
	remove();

	delete m_Steering;
}

r_void ComponentSteeringSeek::OnUpdate(SFMLCanvas * _canvas)
{

}

r_void ComponentSteeringSeek::OnDraw(SFMLCanvas* _canvas)
{

}

r_void ComponentSteeringSeek::OnMembersUpdate()
{
	ComponentSteering::OnMembersUpdate();
}

#ifdef SFGMKR_EDITOR
r_void ComponentSteeringSeek::OnRegistration()
{
	beginRegister();

	ComponentSteering::OnRegistration();

	endRegister();
}
#endif

r_void ComponentSteeringSeek::OnXMLSave(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLSave(_element);
}

r_void ComponentSteeringSeek::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLLoad(_element);
}