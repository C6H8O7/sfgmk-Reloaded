#ifndef SFGMKR_COMPONENTGAMEOBJECT_HPP
#define SFGMKR_COMPONENTGAMEOBJECT_HPP

#include "stdafx.h"

class ComponentGameObject : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentGameObject(GameObject* _parent);
	~ComponentGameObject();

	virtual r_void OnMembersUpdate();

#ifdef SFGMKR_EDITOR
	virtual r_void OnRegistration();
#endif

	virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);
};

#endif