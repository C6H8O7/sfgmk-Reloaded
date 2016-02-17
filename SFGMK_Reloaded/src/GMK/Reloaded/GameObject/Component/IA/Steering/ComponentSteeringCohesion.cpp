#include "stdafx.h"


ComponentSteeringCohesion::ComponentSteeringCohesion(GameObject* _parent)
	: ComponentSteering("SteeringCohesion", _parent), m_fDetectionDistanceMax(0.0f), m_bDetectionDistanceMaxChanged(false)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_Steering = new gmk::SteeringCohesion(_parent);

	add();
}

ComponentSteeringCohesion::~ComponentSteeringCohesion()
{
	remove();

	delete m_Steering;
}


r_void ComponentSteeringCohesion::OnUpdate(SFMLCanvas * _canvas)
{

}

r_void ComponentSteeringCohesion::OnDraw(SFMLCanvas* _canvas)
{

}

r_void ComponentSteeringCohesion::OnMembersUpdate()
{
	ComponentSteering::OnMembersUpdate();

	if( m_bDetectionDistanceMaxChanged )
	{
		m_bDetectionDistanceMaxChanged = false;
		((gmk::SteeringCohesion*)m_Steering)->setDistanceMax(m_fDetectionDistanceMax);
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentSteeringCohesion::OnRegistration()
{
	beginRegister();

	ComponentSteering::OnRegistration();

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Cohesion Max Distance", &m_fDetectionDistanceMax, &m_bDetectionDistanceMaxChanged);

	endRegister();
}
#endif


r_void ComponentSteeringCohesion::OnXMLSave(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLSave(_element);

	_element->SetAttribute("cohesion_max_distance", m_fDetectionDistanceMax);
}

r_void ComponentSteeringCohesion::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLLoad(_element);

	m_fDetectionDistanceMax = _element->FloatAttribute("cohesion_max_distance");
	m_bDetectionDistanceMaxChanged = true;
}