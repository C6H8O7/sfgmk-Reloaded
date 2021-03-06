#include "stdafx.h"


ComponentSteeringArrival::ComponentSteeringArrival(GameObject* _parent)
	: ComponentSteering("SteeringArrival", _parent), m_bSlowingDistanceChanged(false)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_Steering = new gmk::SteeringArrival(_parent);
	m_fSlowingDistance = ((gmk::SteeringArrival*)m_Steering)->getSlowingDistance();

	add();
}

ComponentSteeringArrival::~ComponentSteeringArrival()
{
	remove();

	delete m_Steering;
}

r_void ComponentSteeringArrival::OnDraw(SFMLCanvas* _canvas)
{

}

r_void ComponentSteeringArrival::OnMembersUpdate()
{
	ComponentSteering::OnMembersUpdate();

	if( m_bSlowingDistanceChanged )
	{
		m_bSlowingDistanceChanged = false;
		((gmk::SteeringArrival*)m_Steering)->setSlowingDistance(m_fSlowingDistance);
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentSteeringArrival::OnRegistration()
{
	beginRegister();

	ComponentSteering::OnRegistration();

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Slowing Distance", &m_fSlowingDistance, &m_bSlowingDistanceChanged);

	endRegister();
}
#endif

r_void ComponentSteeringArrival::OnXMLSave(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLSave(_element);

	_element->SetAttribute("slowing_distance", m_fSlowingDistance);
}

r_void ComponentSteeringArrival::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLLoad(_element);

	m_fSlowingDistance = _element->FloatAttribute("slowing_distance");
	m_bSlowingDistanceChanged = true;
}