#include "stdafx.h"


ComponentSteeringFlee::ComponentSteeringFlee(GameObject* _parent)
	: GameObjectComponent("SteeringFlee", _parent), m_Flee(_parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_TargetNameChanged = false;

	if( parent->steeringPtr )
		parent->steeringPtr->addBehavior(&m_Flee, 1.0f);
}

ComponentSteeringFlee::~ComponentSteeringFlee()
{
	if( parent->steeringPtr )
		parent->steeringPtr->removeBehavior(&m_Flee);
}

r_void ComponentSteeringFlee::OnUpdate(SFMLCanvas * _canvas)
{

}

r_void ComponentSteeringFlee::OnDraw(SFMLCanvas* _canvas)
{

}

r_void ComponentSteeringFlee::OnMembersUpdate()
{
	if( m_TargetNameChanged )
	{
		m_TargetNameChanged = false;

		m_Flee.setTarget(SFMLCanvas::project->getCurrentScene()->findGameObjectByName(m_TargetName));
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentSteeringFlee::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Target", &m_TargetName, &m_TargetNameChanged);

	endRegister();
}
#endif

r_void ComponentSteeringFlee::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("target", m_TargetName.c_str());
}

r_void ComponentSteeringFlee::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_TargetName = _element->Attribute("target");
	m_TargetNameChanged = true;
}