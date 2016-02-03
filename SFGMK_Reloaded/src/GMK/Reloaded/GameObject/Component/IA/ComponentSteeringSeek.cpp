#include "stdafx.h"

ComponentSteeringSeek::ComponentSteeringSeek(GameObject* _parent)
	: GameObjectComponent("SteeringSeek", _parent), m_Seek(_parent), m_fWeight(STEERING_DEFAULT_WEIGHT), m_bWeightChanged(false)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_TargetNameChanged = false;

	if (parent->steeringPtr)
		parent->steeringPtr->addBehavior(&m_Seek, STEERING_DEFAULT_WEIGHT);
}

ComponentSteeringSeek::~ComponentSteeringSeek()
{
	if (parent->steeringPtr)
		parent->steeringPtr->removeBehavior(&m_Seek);
}

r_void ComponentSteeringSeek::OnUpdate(SFMLCanvas * _canvas)
{
}

r_void ComponentSteeringSeek::OnDraw(SFMLCanvas* _canvas)
{
}

r_void ComponentSteeringSeek::OnMembersUpdate()
{
	if (m_TargetNameChanged)
	{
		m_TargetNameChanged = false;

		m_Seek.setTarget(SFMLCanvas::project->getCurrentScene()->findGameObjectByName(m_TargetName));
	}

	if( m_bWeightChanged )
	{
		m_bWeightChanged = false;
		parent->steeringPtr->modifyBehaviorWeight(&m_Seek, m_fWeight);
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentSteeringSeek::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Weight", &m_fWeight, &m_bWeightChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Target", &m_TargetName, &m_TargetNameChanged);

	endRegister();
}
#endif

r_void ComponentSteeringSeek::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("weight", m_fWeight);
	_element->SetAttribute("target", m_TargetName.c_str());
}

r_void ComponentSteeringSeek::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_fWeight = _element->FloatAttribute("weight");
	m_bWeightChanged = true;
	m_TargetName = _element->Attribute("target");
	m_TargetNameChanged = true;
}