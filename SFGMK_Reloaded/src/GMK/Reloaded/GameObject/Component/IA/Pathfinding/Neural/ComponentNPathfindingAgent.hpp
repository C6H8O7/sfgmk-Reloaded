#ifndef SFGMKR_COMPONENTNPATHFINDINGAGENT_HPP
#define SFGMKR_COMPONENTNPATHFINDINGAGENT_HPP

#include "stdafx.h"

class ComponentNPathfindingAgent : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentNPathfindingAgent(GameObject* _parent);
	~ComponentNPathfindingAgent();

	virtual r_void OnUpdate(SFMLCanvas * _canvas);
	virtual r_void OnDraw(SFMLCanvas* _canvas);

	virtual r_void OnMembersUpdate();

#ifdef SFGMKR_EDITOR
	virtual r_void OnRegistration();
#endif

	virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

private:

	r_bool m_MapNameChanged;
	r_string m_MapName;

	r_float m_Speed;

	gmk::PathfindingMap* m_Map = 0;
	gmk::Pathfinding* m_Pathfinding = 0;
	GameObject* m_MapObject;
};

#endif