#include "stdafx.h"


ComponentSteeringPursuit::ComponentSteeringPursuit(GameObject* _parent)
	: GameObjectComponent("SteeringPursuit", _parent), m_Pursuit(_parent), m_fWeight(STEERING_DEFAULT_WEIGHT), m_bWeightChanged(false), m_fPursuitMaxTime(m_Pursuit.getPursuitMaxTime()), m_bPursuitMaxTimeChanged(false)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_TargetNameChanged = false;

	if( parent->steeringPtr )
		parent->steeringPtr->addBehavior(&m_Pursuit, STEERING_DEFAULT_WEIGHT);
}

ComponentSteeringPursuit::~ComponentSteeringPursuit()
{
	if( parent->steeringPtr )
		parent->steeringPtr->removeBehavior(&m_Pursuit);
}


r_void ComponentSteeringPursuit::OnUpdate(SFMLCanvas * _canvas)
{
}

r_void ComponentSteeringPursuit::OnDraw(SFMLCanvas* _canvas)
{
}


r_void ComponentSteeringPursuit::OnMembersUpdate()
{
	if( m_TargetNameChanged )
	{
		m_TargetNameChanged = false;

		m_Pursuit.setTarget(SFMLCanvas::project->getCurrentScene()->findGameObjectByName(m_TargetName));
	}

	if( m_bWeightChanged )
	{
		m_bWeightChanged = false;
		parent->steeringPtr->modifyBehaviorWeight(&m_Pursuit, m_fWeight);
	}

	if( m_bPursuitMaxTimeChanged )
	{
		m_bPursuitMaxTimeChanged = false;
		m_Pursuit.setPursuitMaxTime(m_fPursuitMaxTime);
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentSteeringPursuit::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Weight", &m_fWeight, &m_bWeightChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Target", &m_TargetName, &m_TargetNameChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Pursuit Max Time", &m_fPursuitMaxTime, &m_bPursuitMaxTimeChanged);

	endRegister();
}
#endif


r_void ComponentSteeringPursuit::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("weight", m_fWeight);
	_element->SetAttribute("target", m_TargetName.c_str());
	_element->SetAttribute("pursuit_max_time", m_fPursuitMaxTime);
}

r_void ComponentSteeringPursuit::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_fWeight = _element->FloatAttribute("weight");
	m_bWeightChanged = true;
	m_TargetName = _element->Attribute("target");
	m_TargetNameChanged = true;
	m_fPursuitMaxTime = _element->FloatAttribute("pursuit_max_time");
	m_bPursuitMaxTimeChanged = true;
}