#include "stdafx.h"

ComponentSteeringFormation::ComponentSteeringFormation(GameObject* _parent)
	: GameObjectComponent("SteeringFormation", _parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif
}

ComponentSteeringFormation::~ComponentSteeringFormation()
{

}

r_void ComponentSteeringFormation::OnUpdate(SFMLCanvas * _canvas)
{

}

r_void ComponentSteeringFormation::OnDraw(SFMLCanvas* _canvas)
{

}

r_void ComponentSteeringFormation::OnMembersUpdate()
{

}

#ifdef SFGMKR_EDITOR
r_void ComponentSteeringFormation::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Name", m_Formation.getNamePtr(), 0);
	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Leader", m_Formation.getLeaderNamePtr(), 0);

	GameObjectComponent::ComponentProperty* propertyType = registerProperty(ePROPERTY_TYPE::TYPE_ENUM, "Type", m_Formation.getFormationFuncPtr(), 0);
	propertyType->wxChoices.Add("Circle", gmk::FORMATION_CIRCLE);
	propertyType->wxChoices.Add("V", gmk::FORMATION_V);
	propertyType->wxChoices.Add("Line", gmk::FORMATION_LINE);

	endRegister();
}
#endif

r_void ComponentSteeringFormation::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("name", m_Formation.getName().c_str());
	_element->SetAttribute("leader", m_Formation.getLeaderName().c_str());
	_element->SetAttribute("formation_type", (r_int32)m_Formation.getFormationFunc());
}

r_void ComponentSteeringFormation::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_Formation.setName(_element->Attribute("name"));
	m_Formation.setLeaderName(_element->Attribute("leader"));
	m_Formation.setFormationFunc((gmk::eSTEERING_FORMATION_FUNC)_element->IntAttribute("formation_type"));
}