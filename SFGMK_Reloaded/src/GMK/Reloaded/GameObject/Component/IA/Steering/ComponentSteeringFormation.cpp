#include "stdafx.h"

ComponentSteeringFormation::ComponentSteeringFormation(GameObject* _parent)
	: GameObjectComponent("SteeringFormation", _parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif
}

ComponentSteeringFormation::~ComponentSteeringFormation()
{

}

r_void ComponentSteeringFormation::OnUpdate(SFMLCanvas * _canvas)
{

}

r_void ComponentSteeringFormation::OnDraw(SFMLCanvas* _canvas)
{

}

r_void ComponentSteeringFormation::OnMembersUpdate()
{
	if (m_FormationNameChanged)
	{
		m_FormationNameChanged = false;
		m_Formation.setName(m_FormationName);
	}

	if (m_LeaderNameChanged)
	{
		m_LeaderNameChanged = false;
		m_Formation.setLeader(SFMLCanvas::project->getCurrentScene()->findGameObjectByName(m_LeaderName));
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentSteeringFormation::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Name", &m_FormationName, &m_FormationNameChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Leader", &m_LeaderName, &m_LeaderNameChanged);

	endRegister();
}
#endif

r_void ComponentSteeringFormation::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("name", m_FormationName.c_str());
	_element->SetAttribute("leader", m_LeaderName.c_str());
}

r_void ComponentSteeringFormation::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_FormationName = _element->Attribute("name");
	m_FormationNameChanged = true;

	m_LeaderName = _element->Attribute("leader");
	m_LeaderNameChanged = true;
}