#include "stdafx.h"


ComponentSteeringEvasion::ComponentSteeringEvasion(GameObject* _parent)
	: GameObjectComponent("SteeringEvasion", _parent), m_Evasion(_parent), m_fWeight(STEERING_DEFAULT_WEIGHT), m_bWeightChanged(false), m_fEvasionMaxTime(m_Evasion.getEvasionMaxTime()), m_bEvasionMaxTimeChanged(false)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_TargetNameChanged = false;

	if( parent->steeringPtr )
		parent->steeringPtr->addBehavior(&m_Evasion, STEERING_DEFAULT_WEIGHT);
}

ComponentSteeringEvasion::~ComponentSteeringEvasion()
{
	if( parent->steeringPtr )
		parent->steeringPtr->removeBehavior(&m_Evasion);
}


r_void ComponentSteeringEvasion::OnUpdate(SFMLCanvas * _canvas)
{
}

r_void ComponentSteeringEvasion::OnDraw(SFMLCanvas* _canvas)
{
}


r_void ComponentSteeringEvasion::OnMembersUpdate()
{
	if( m_TargetNameChanged )
	{
		m_TargetNameChanged = false;

		m_Evasion.setTarget(SFMLCanvas::project->getCurrentScene()->findGameObjectByName(m_TargetName));
	}

	if( m_bWeightChanged )
	{
		m_bWeightChanged = false;
		parent->steeringPtr->modifyBehaviorWeight(&m_Evasion, m_fWeight);
	}

	if( m_bEvasionMaxTimeChanged )
	{
		m_bEvasionMaxTimeChanged = false;
		m_Evasion.setEvasionMaxTime(m_fEvasionMaxTime);
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentSteeringEvasion::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Weight", &m_fWeight, &m_bWeightChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Target", &m_TargetName, &m_TargetNameChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Evasion Max Time", &m_fEvasionMaxTime, &m_bEvasionMaxTimeChanged);

	endRegister();
}
#endif


r_void ComponentSteeringEvasion::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("weight", m_fWeight);
	_element->SetAttribute("target", m_TargetName.c_str());
	_element->SetAttribute("pursuit_max_time", m_fEvasionMaxTime);
}

r_void ComponentSteeringEvasion::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_fWeight = _element->FloatAttribute("weight");
	m_bWeightChanged = true;
	m_TargetName = _element->Attribute("target");
	m_TargetNameChanged = true;
	m_fEvasionMaxTime = _element->FloatAttribute("evasion_max_time");
	m_bEvasionMaxTimeChanged = true;
}