#ifndef SFGMKR_COMPONENTPLANNER_HPP
#define SFGMKR_COMPONENTPLANNER_HPP

#include "stdafx.h"

class ComponentPlanner : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentPlanner(GameObject* _parent);
	~ComponentPlanner();

	virtual r_void OnUpdate(SFMLCanvas * _canvas);
	virtual r_void OnDraw(SFMLCanvas* _canvas);

	virtual r_void OnMembersUpdate();

#ifdef SFGMKR_EDITOR
	virtual r_void OnRegistration();
#endif

	virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

private:

	gmk::Planner m_planner;
};

#endif