#include "stdafx.h"


ComponentSteeringPursuit::ComponentSteeringPursuit(GameObject* _parent)
	: ComponentSteering("SteeringPursuit", _parent), m_fPursuitMaxTime(m_Steering.getPursuitMaxTime()), m_bPursuitMaxTimeChanged(false)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif
}

ComponentSteeringPursuit::~ComponentSteeringPursuit()
{
}


r_void ComponentSteeringPursuit::OnUpdate(SFMLCanvas * _canvas)
{
}

r_void ComponentSteeringPursuit::OnDraw(SFMLCanvas* _canvas)
{
}


r_void ComponentSteeringPursuit::OnMembersUpdate()
{
	ComponentSteering::OnMembersUpdate();

	if( m_bPursuitMaxTimeChanged )
	{
		m_bPursuitMaxTimeChanged = false;
		m_Steering.setPursuitMaxTime(m_fPursuitMaxTime);
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentSteeringPursuit::OnRegistration()
{
	beginRegister();

	ComponentSteering::OnRegistration();

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Pursuit Max Time", &m_fPursuitMaxTime, &m_bPursuitMaxTimeChanged);

	endRegister();
}
#endif


r_void ComponentSteeringPursuit::OnXMLSave(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLSave(_element);
	
	_element->SetAttribute("pursuit_max_time", m_fPursuitMaxTime);
}

r_void ComponentSteeringPursuit::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLLoad(_element);

	m_fPursuitMaxTime = _element->FloatAttribute("pursuit_max_time");
	m_bPursuitMaxTimeChanged = true;
}