#include "stdafx.h"

ComponentRigidbody::ComponentRigidbody(GameObject* _parent)
	: GameObjectComponent("Rigidbody", _parent), m_Rigidbody(_parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	parent->rigidbodyPtr = &m_Rigidbody;
}

ComponentRigidbody::~ComponentRigidbody()
{

}

r_void ComponentRigidbody::OnUpdate(SFMLCanvas * _canvas)
{
#ifdef SFGMKR_EDITOR
	if (_canvas->isEditor())
		return;
#endif
	if (!_canvas->isPlaying)
		return;

	m_Rigidbody.update(gmk::TimeManager::GetSingleton()->getDeltaTime());
}

r_void ComponentRigidbody::OnDraw(SFMLCanvas* _canvas)
{

}

r_void ComponentRigidbody::OnMembersUpdate()
{

}

#ifdef SFGMKR_EDITOR
r_void ComponentRigidbody::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_BOOL, "Gravity Applied", m_Rigidbody.getGravityAppliedPtr());
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Gravity Force X", &m_Rigidbody.getGravityForcePtr()->x);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Gravity Force Y", &m_Rigidbody.getGravityForcePtr()->y);

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Max Speed", m_Rigidbody.getMaxSpeedPtr());
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Max Force", m_Rigidbody.getMaxAccelerationPtr());

	endRegister();
}
#endif

r_void ComponentRigidbody::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("gravity_applied", m_Rigidbody.getGravityApplied());
	_element->SetAttribute("gravity_x", m_Rigidbody.getGravityForce().x);
	_element->SetAttribute("gravity_y", m_Rigidbody.getGravityForce().y);

	_element->SetAttribute("max_speed", m_Rigidbody.getMaxSpeed());
	_element->SetAttribute("max_force", m_Rigidbody.getMaxAcceleration());
}

r_void ComponentRigidbody::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_Rigidbody.setGravityApplied(_element->BoolAttribute("gravity_applied"));
	m_Rigidbody.setGravityForce(r_vector2f(_element->FloatAttribute("gravity_x"), _element->FloatAttribute("gravity_y")));

	m_Rigidbody.setMaxSpeed(_element->FloatAttribute("max_speed"));
	m_Rigidbody.setMaxAcceleration(_element->FloatAttribute("max_force"));
}