#include "stdafx.h"


ComponentSteeringAlignment::ComponentSteeringAlignment(GameObject* _parent)
	: ComponentSteering("SteeringAlignment", _parent), m_fDetectionDistanceMax(0.0f), m_bDetectionDistanceMaxChanged(false)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_Steering = new gmk::SteeringAlignment(_parent);

	add();
}

ComponentSteeringAlignment::~ComponentSteeringAlignment()
{
	remove();

	delete m_Steering;
}


r_void ComponentSteeringAlignment::OnUpdate(SFMLCanvas * _canvas)
{

}

r_void ComponentSteeringAlignment::OnDraw(SFMLCanvas* _canvas)
{

}

r_void ComponentSteeringAlignment::OnMembersUpdate()
{
	ComponentSteering::OnMembersUpdate();

	if( m_bDetectionDistanceMaxChanged )
	{
		m_bDetectionDistanceMaxChanged = false;
		((gmk::SteeringAlignment*)m_Steering)->setDistanceMax(m_fDetectionDistanceMax);
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentSteeringAlignment::OnRegistration()
{
	beginRegister();

	ComponentSteering::OnRegistration();

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Alignment Max Distance", &m_fDetectionDistanceMax, &m_bDetectionDistanceMaxChanged);

	endRegister();
}
#endif


r_void ComponentSteeringAlignment::OnXMLSave(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLSave(_element);

	_element->SetAttribute("alignment_max_distance", m_fDetectionDistanceMax);
}

r_void ComponentSteeringAlignment::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLLoad(_element);

	m_fDetectionDistanceMax = _element->FloatAttribute("alignment_max_distance");
	m_bDetectionDistanceMaxChanged = true;
}