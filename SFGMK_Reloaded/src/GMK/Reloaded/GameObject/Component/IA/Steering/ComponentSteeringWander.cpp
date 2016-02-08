#include "stdafx.h"


ComponentSteeringWander::ComponentSteeringWander(GameObject* _parent)
	: ComponentSteering("SteeringWander", _parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_Steering = new gmk::SteeringWander(_parent);

	add();
#ifdef SFGMKR_EDITOR
	m_Circle.setFillColor(sf::Color::Transparent);
	m_Circle.setOutlineThickness(-1.0f);
	m_Circle.setOutlineColor(sf::Color::Cyan);
#endif
}

ComponentSteeringWander::~ComponentSteeringWander()
{
	remove();

	delete m_Steering;
}

r_void ComponentSteeringWander::OnUpdate(SFMLCanvas * _canvas)
{
#ifdef SFGMKR_EDITOR
	m_Circle.setPosition(((gmk::SteeringWander*)(m_Steering))->getCircleCenter());
#endif
}

r_void ComponentSteeringWander::OnDraw(SFMLCanvas* _canvas)
{
#ifdef SFGMKR_EDITOR
	if( _canvas->isEditor() )
		_canvas->draw(m_Circle);
#endif
}


r_void ComponentSteeringWander::OnMembersUpdate()
{
	ComponentSteering::OnMembersUpdate();

	if( m_bCircleDistanceChanged )
	{
		m_bCircleDistanceChanged = false;
		((gmk::SteeringWander*)(m_Steering))->setCircleDistance(m_fCircleDistance);
	}

	if( m_bCircleRadiusChanged )
	{
		m_bCircleRadiusChanged = false;
		((gmk::SteeringWander*)(m_Steering))->setCircleRadius(m_fCircleRadius);
		m_Circle.setOrigin(m_fCircleRadius * 0.5f, m_fCircleRadius * 0.5f);
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentSteeringWander::OnRegistration()
{
	beginRegister();

	ComponentSteering::OnRegistration();

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Distance", &m_fCircleDistance, &m_bCircleDistanceChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Radius", &m_fCircleRadius, &m_bCircleRadiusChanged);

	endRegister();
}
#endif


r_void ComponentSteeringWander::OnXMLSave(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLSave(_element);

	_element->SetAttribute("distance", m_fCircleDistance);
	_element->SetAttribute("radius", m_fCircleRadius);
}

r_void ComponentSteeringWander::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	ComponentSteering::OnXMLLoad(_element);

	m_fCircleDistance = _element->FloatAttribute("distance");
	m_bCircleDistanceChanged = true;
	m_fCircleRadius = _element->FloatAttribute("radius");
	m_bCircleRadiusChanged = true;
}