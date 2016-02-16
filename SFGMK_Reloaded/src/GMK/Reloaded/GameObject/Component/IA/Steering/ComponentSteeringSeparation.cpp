#include "stdafx.h"


ComponentSteeringSeparation::ComponentSteeringSeparation(GameObject* _parent)
	: ComponentSteering("SteeringSeparation", _parent), m_fDetectionDistanceMax(0.0f), m_bDetectionDistanceMaxChanged(false)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_Steering = new gmk::SteeringSeparation(_parent);

	add();
}

ComponentSteeringSeparation::~ComponentSteeringSeparation()
{
	remove();

	delete m_Steering;
}


r_void ComponentSteeringSeparation::OnUpdate(SFMLCanvas * _canvas)
{

}

r_void ComponentSteeringSeparation::OnDraw(SFMLCanvas* _canvas)
{

}

r_void ComponentSteeringSeparation::OnMembersUpdate()
{
	ComponentSteering::OnMembersUpdate();

	if( m_bDetectionDistanceMaxChanged )
	{
		m_bDetectionDistanceMaxChanged = false;
		((gmk::SteeringSeparation*)m_Steering)->setDistanceMax(m_fDetectionDistanceMax);
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentSteeringSeparation::OnRegistration()
{
	beginRegister();

	ComponentSteering::OnRegistration();

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Separation Max Distance", &m_fDetectionDistanceMax, &m_bDetectionDistanceMaxChanged);

	endRegister();
}
#endif


r_void ComponentSteeringSeparation::OnXMLSave(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLSave(_element);

	_element->SetAttribute("separation_max_distance", m_fDetectionDistanceMax);
}

r_void ComponentSteeringSeparation::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLLoad(_element);

	m_fDetectionDistanceMax = _element->FloatAttribute("separation_max_distance");
	m_bDetectionDistanceMaxChanged = true;
}