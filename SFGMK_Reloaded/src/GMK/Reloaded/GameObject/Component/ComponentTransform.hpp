#ifndef SFGMKR_COMPONENTTRANSFORM_HPP
#define SFGMKR_COMPONENTTRANSFORM_HPP

#include "stdafx.h"

class ComponentTransform : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentTransform(GameObject* _parent);
	~ComponentTransform();

	virtual r_void OnUpdate(SFMLCanvas * _canvas);

#ifdef SFGMKR_EDITOR
	virtual r_void OnRegistration();
#endif

	virtual r_void OnMembersUpdate();

	virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

private:

	r_vector2f m_position;
	r_bool m_positionChanged;

	r_vector2f m_scale;
	r_bool m_scaleChanged;

	r_float m_rotation;
	r_bool m_rotationChanged;
};

#endif