#include "stdafx.h"


ComponentSteeringSwarming::ComponentSteeringSwarming(GameObject* _parent)
	: ComponentSteering("SteeringSwarming", _parent), m_fAreaRadius(0.0f), m_bAreaRadiusChanged(false)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_Steering = new gmk::SteeringSwarming(_parent);

	add();

	parent->rigidbodyPtr->setDirection(r_vector2f(1.0f, 0.0f));
	parent->rigidbodyPtr->setSpeed(r_vector2f(100.0f, 0.0f));
}

ComponentSteeringSwarming::~ComponentSteeringSwarming()
{
	remove();

	delete m_Steering;
}

r_void ComponentSteeringSwarming::OnUpdate(SFMLCanvas * _canvas)
{

}

r_void ComponentSteeringSwarming::OnDraw(SFMLCanvas* _canvas)
{

}

r_void ComponentSteeringSwarming::OnMembersUpdate()
{
	ComponentSteering::OnMembersUpdate();

	if( m_bAreaRadiusChanged )
	{
		m_bAreaRadiusChanged = false;
		((gmk::SteeringSwarming*)m_Steering)->setAreaRadius(m_fAreaRadius);
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentSteeringSwarming::OnRegistration()
{
	beginRegister();

	ComponentSteering::OnRegistration();

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Area Radius", &m_fAreaRadius, &m_bAreaRadiusChanged);

	endRegister();
}
#endif

r_void ComponentSteeringSwarming::OnXMLSave(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLSave(_element);

	_element->SetAttribute("area_radius", m_fAreaRadius);
}

r_void ComponentSteeringSwarming::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLLoad(_element);

	m_fAreaRadius = _element->FloatAttribute("area_radius");
	m_bAreaRadiusChanged = true;
}