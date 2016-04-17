#ifndef SFGMKR_COMPONENTLANREPLICATION_HPP
#define SFGMKR_COMPONENTLANREPLICATION_HPP

#include "stdafx.h"

class ComponentLANReplication : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentLANReplication(GameObject* _parent);
	~ComponentLANReplication();

	virtual r_void OnUpdate(SFMLCanvas * _canvas);
	virtual r_void OnDraw(SFMLCanvas* _canvas);

	virtual r_void OnMembersUpdate();

#ifdef SFGMKR_EDITOR
	virtual r_void OnRegistration();
#endif

	virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

private:

	r_float m_timer = 0.0f;
	r_float m_tick = 0.0f;

	r_bool m_registered = false;
};

#endif