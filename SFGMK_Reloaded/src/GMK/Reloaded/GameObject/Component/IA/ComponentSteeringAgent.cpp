#include "stdafx.h"

ComponentSteeringAgent::ComponentSteeringAgent(GameObject* _parent)
	: GameObjectComponent("SteeringAgent", _parent), m_Steering(_parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	parent->steeringPtr = &m_Steering;
}

ComponentSteeringAgent::~ComponentSteeringAgent()
{
	parent->steeringPtr = 0;
}

r_void ComponentSteeringAgent::OnUpdate(SFMLCanvas * _canvas)
{

}

r_void ComponentSteeringAgent::OnDraw(SFMLCanvas* _canvas)
{

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