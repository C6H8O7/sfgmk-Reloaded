#include "stdafx.h"


ComponentSteeringUnalignedCollisionAvoidance::ComponentSteeringUnalignedCollisionAvoidance(GameObject* _parent)
	: ComponentSteering("SteeringUnalignedCollisionAvoidance", _parent), m_fDetectionDistanceMax(0.0f), m_bDetectionDistanceMaxChanged(false)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_Steering = new gmk::SteeringUnalignedCollisionAvoidance(_parent);

	add();
}

ComponentSteeringUnalignedCollisionAvoidance::~ComponentSteeringUnalignedCollisionAvoidance()
{
	remove();

	delete m_Steering;
}


r_void ComponentSteeringUnalignedCollisionAvoidance::OnUpdate(SFMLCanvas * _canvas)
{

}

r_void ComponentSteeringUnalignedCollisionAvoidance::OnDraw(SFMLCanvas* _canvas)
{

}

r_void ComponentSteeringUnalignedCollisionAvoidance::OnMembersUpdate()
{
	ComponentSteering::OnMembersUpdate();

	if( m_bDetectionDistanceMaxChanged )
	{
		m_bDetectionDistanceMaxChanged = false;
		((gmk::SteeringAlignment*)m_Steering)->setDistanceMax(m_fDetectionDistanceMax);
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentSteeringUnalignedCollisionAvoidance::OnRegistration()
{
	beginRegister();

	ComponentSteering::OnRegistration();

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Avoidance Max Distance", &m_fDetectionDistanceMax, &m_bDetectionDistanceMaxChanged);

	endRegister();
}
#endif


r_void ComponentSteeringUnalignedCollisionAvoidance::OnXMLSave(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLSave(_element);

	_element->SetAttribute("avoidance_max_distance", m_fDetectionDistanceMax);
}

r_void ComponentSteeringUnalignedCollisionAvoidance::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLLoad(_element);

	m_fDetectionDistanceMax = _element->FloatAttribute("avoidance_max_distance");
	m_bDetectionDistanceMaxChanged = true;
}