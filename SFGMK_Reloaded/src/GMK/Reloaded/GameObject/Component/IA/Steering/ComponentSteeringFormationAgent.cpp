#include "stdafx.h"

ComponentSteeringFormationAgent::ComponentSteeringFormationAgent(GameObject* _parent)
	: ComponentSteering("SteeringFormationAgent", _parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_Steering = new gmk::SteeringFormationAgent(_parent);

	add();
}

ComponentSteeringFormationAgent::~ComponentSteeringFormationAgent()
{
	remove();

	delete m_Steering;
}

r_void ComponentSteeringFormationAgent::OnUpdate(SFMLCanvas * _canvas)
{

}

r_void ComponentSteeringFormationAgent::OnDraw(SFMLCanvas* _canvas)
{

}

r_void ComponentSteeringFormationAgent::OnMembersUpdate()
{
	ComponentSteering::OnMembersUpdate();

	if (m_FormationNameChanged)
	{
		m_FormationNameChanged = false;

		((gmk::SteeringFormationAgent*)(m_Steering))->setSteeringFormation(m_FormationName);
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentSteeringFormationAgent::OnRegistration()
{
	beginRegister();

	ComponentSteering::OnRegistration();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Formation", &m_FormationName, &m_FormationNameChanged);

	endRegister();
}
#endif

r_void ComponentSteeringFormationAgent::OnXMLSave(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLSave(_element);

	_element->SetAttribute("formation", m_FormationName.c_str());
}

r_void ComponentSteeringFormationAgent::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLLoad(_element);

	m_FormationName = _element->Attribute("formation");
	m_FormationNameChanged = true;
}