#include "stdafx.h"

ComponentPlanner::ComponentPlanner(GameObject* _parent)
	: GameObjectComponent("Planner", _parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	parent->plannerPtr = &m_planner;
}

ComponentPlanner::~ComponentPlanner()
{
	parent->plannerPtr = 0;
}

r_void ComponentPlanner::OnUpdate(SFMLCanvas * _canvas)
{
	if (_canvas->isPlaying)
		m_planner.update();
}

r_void ComponentPlanner::OnDraw(SFMLCanvas* _canvas)
{

}

r_void ComponentPlanner::OnMembersUpdate()
{

}

#ifdef SFGMKR_EDITOR
r_void ComponentPlanner::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Goal", m_planner.getGoalPtr());

	endRegister();
}
#endif

r_void ComponentPlanner::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("goal", m_planner.getGoal().c_str());
}

r_void ComponentPlanner::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_planner.setGoal(_element->Attribute("goal"));
}