#include "stdafx.h"

ComponentSteering::ComponentSteering(const r_string& _typeName, GameObject* _parent)
	: GameObjectComponent(_typeName, _parent), m_fSteeringWeight(STEERING_DEFAULT_WEIGHT), m_bSteeringWeightChanged(false), m_sTargetName(""), m_bTargetNameChanged(false)
{

}

ComponentSteering::~ComponentSteering()
{

}

r_void ComponentSteering::add()
{
	if (parent->steeringPtr)
		parent->steeringPtr->addBehavior(type_name, m_Steering, STEERING_DEFAULT_WEIGHT);
}

r_void ComponentSteering::remove()
{
	if (parent->steeringPtr)
		parent->steeringPtr->removeBehavior(m_Steering);
}

r_void ComponentSteering::OnMembersUpdate()
{
	if (m_bSteeringWeightChanged)
	{
		m_bSteeringWeightChanged = false;
		parent->steeringPtr->modifyBehaviorWeight(m_Steering, m_fSteeringWeight);
	}

	if (m_bTargetNameChanged)
	{
		m_bTargetNameChanged = false;
		m_Steering->setTarget(SFMLCanvas::project->getCurrentScene()->findGameObjectByName(m_sTargetName));
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentSteering::OnRegistration()
{
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Weight", &m_fSteeringWeight, &m_bSteeringWeightChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Target", &m_sTargetName, &m_bTargetNameChanged);
}
#endif

r_void ComponentSteering::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("weight", m_fSteeringWeight);
	_element->SetAttribute("target", m_sTargetName.c_str());
}

r_void ComponentSteering::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_fSteeringWeight = _element->FloatAttribute("weight");
	m_bSteeringWeightChanged = true;
	m_sTargetName = _element->Attribute("target");
	m_bTargetNameChanged = true;
}