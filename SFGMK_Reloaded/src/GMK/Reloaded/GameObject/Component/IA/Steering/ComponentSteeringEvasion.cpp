#include "stdafx.h"


ComponentSteeringEvasion::ComponentSteeringEvasion(GameObject* _parent)
	: ComponentSteering("SteeringEvasion", _parent), m_fEvasionMaxTime(m_Steering.getEvasionMaxTime()), m_bEvasionMaxTimeChanged(false)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif
}

ComponentSteeringEvasion::~ComponentSteeringEvasion()
{
}


r_void ComponentSteeringEvasion::OnUpdate(SFMLCanvas * _canvas)
{
}

r_void ComponentSteeringEvasion::OnDraw(SFMLCanvas* _canvas)
{
}


r_void ComponentSteeringEvasion::OnMembersUpdate()
{
	ComponentSteering::OnMembersUpdate();

	if( m_bEvasionMaxTimeChanged )
	{
		m_bEvasionMaxTimeChanged = false;
		m_Steering.setEvasionMaxTime(m_fEvasionMaxTime);
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentSteeringEvasion::OnRegistration()
{
	beginRegister();

	ComponentSteering::OnRegistration();

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Evasion Max Time", &m_fEvasionMaxTime, &m_bEvasionMaxTimeChanged);

	endRegister();
}
#endif


r_void ComponentSteeringEvasion::OnXMLSave(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLSave(_element);

	_element->SetAttribute("evasion_max_time", m_fEvasionMaxTime);
}

r_void ComponentSteeringEvasion::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLLoad(_element);

	m_fEvasionMaxTime = _element->FloatAttribute("evasion_max_time");
	m_bEvasionMaxTimeChanged = true;
}