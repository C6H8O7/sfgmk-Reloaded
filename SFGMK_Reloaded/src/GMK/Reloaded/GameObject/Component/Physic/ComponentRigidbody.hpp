#ifndef SFGMKR_COMPONENTRIGIDBODY_HPP
#define SFGMKR_COMPONENTRIGIDBODY_HPP

#include "stdafx.h"

class ComponentRigidbody : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentRigidbody(GameObject* _parent);
	~ComponentRigidbody();

	virtual r_void OnUpdate(SFMLCanvas * _canvas);
	virtual r_void OnDraw(SFMLCanvas* _canvas);

	virtual r_void OnMembersUpdate();

#ifdef SFGMKR_EDITOR
	virtual r_void OnRegistration();
#endif

	virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

	gmk::Rigidbody* getRigidBody();

protected:

	gmk::Rigidbody m_Rigidbody;
};

#endif