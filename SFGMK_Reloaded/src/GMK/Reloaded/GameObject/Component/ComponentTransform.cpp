#include "stdafx.h"

ComponentTransform::ComponentTransform(GameObject * _parent)
	: GameObjectComponent("Transform", _parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_positionChanged = m_scaleChanged = m_rotationChanged = false;
}

ComponentTransform::~ComponentTransform()
{

}

r_void ComponentTransform::OnUpdate(SFMLCanvas * _canvas)
{
#ifdef SFGMKR_EDITOR
	m_position = parent->transform.getPosition();
	m_scale = parent->transform.getScale();
	m_rotation = parent->transform.getRotation();
#endif
}

#ifdef SFGMKR_EDITOR
r_void ComponentTransform::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Pos X", &m_position.x, &m_positionChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Pos Y", &m_position.y, &m_positionChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Scale X", &m_scale.x, &m_scaleChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Scale Y", &m_scale.y, &m_scaleChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Rotation", &m_rotation, &m_rotationChanged);
}
#endif

r_void ComponentTransform::OnMembersUpdate()
{
	if (m_positionChanged)
	{
		m_positionChanged = false;
		parent->transform.setPosition(m_position);
	}

	if (m_scaleChanged)
	{
		m_scaleChanged = false;
		parent->transform.setScale(m_scale);
	}

	if (m_rotationChanged)
	{
		m_rotationChanged = false;
		parent->transform.setRotation(m_rotation);
	}
}

r_void ComponentTransform::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("position_x", m_position.x);
	_element->SetAttribute("position_y", m_position.y);

	_element->SetAttribute("scale_x", m_scale.x);
	_element->SetAttribute("scale_y", m_scale.y);

	_element->SetAttribute("rotation", m_rotation);
}

r_void ComponentTransform::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_position.x = _element->FloatAttribute("position_x");
	m_position.y = _element->FloatAttribute("position_y");

	m_scale.x = _element->FloatAttribute("scale_x");
	m_scale.y = _element->FloatAttribute("scale_y");

	m_rotation = _element->FloatAttribute("rotation");

	m_positionChanged = m_scaleChanged = m_rotationChanged = true;
}