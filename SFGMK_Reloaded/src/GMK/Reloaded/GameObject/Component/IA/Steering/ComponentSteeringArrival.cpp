#include "stdafx.h"


ComponentSteeringArrival::ComponentSteeringArrival(GameObject* _parent)
	: ComponentSteering("SteeringArrival", _parent), m_fSlowingDistance(m_Steering.getSlowingDistance()), m_bSlowingDistanceChanged(false)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif
}

ComponentSteeringArrival::~ComponentSteeringArrival()
{
}


r_void ComponentSteeringArrival::OnUpdate(SFMLCanvas * _canvas)
{
}

r_void ComponentSteeringArrival::OnDraw(SFMLCanvas* _canvas)
{
}


r_void ComponentSteeringArrival::OnMembersUpdate()
{
	if( m_bSlowingDistanceChanged )
	{
		m_bSlowingDistanceChanged = false;
		m_Steering.setSlowingDistance(m_fSlowingDistance);
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentSteeringArrival::OnRegistration()
{
	beginRegister();

	ComponentSteering::OnMembersUpdate();

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Evasion Max Time", &m_fSlowingDistance, &m_bSlowingDistanceChanged);

	endRegister();
}
#endif


r_void ComponentSteeringArrival::OnXMLSave(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLSave(_element);

	_element->SetAttribute("pursuit_max_time", m_fSlowingDistance);
}

r_void ComponentSteeringArrival::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLLoad(_element);

	m_fSlowingDistance = _element->FloatAttribute("evasion_max_time");
	m_bSlowingDistanceChanged = true;
}