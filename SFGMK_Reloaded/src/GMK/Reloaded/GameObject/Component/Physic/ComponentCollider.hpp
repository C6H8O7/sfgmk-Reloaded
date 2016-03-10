#ifndef SFGMKR_COMPONENTCOLLIDER_HPP
#define SFGMKR_COMPONENTCOLLIDER_HPP

#include "stdafx.h"

class ComponentCollider : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentCollider(GameObject* _parent);
	~ComponentCollider();

	virtual r_void OnUpdate(SFMLCanvas * _canvas);
	virtual r_void OnDraw(SFMLCanvas* _canvas);

	virtual r_void OnMembersUpdate();

#ifdef SFGMKR_EDITOR
	virtual r_void OnRegistration();
#endif

	virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

	r_void setType(gmk::eCOLLIDER_TYPE _type);
	r_void initType(gmk::eCOLLIDER_TYPE _type);

	gmk::Collider* getCollider();

private:
	gmk::Collider m_Collider;

	r_bool m_TypeChanged = false;
	gmk::eCOLLIDER_TYPE m_Type;

	r_bool m_SizeChanged = false;
	r_float m_SizeX = 0.0f, m_SizeY = 0.0f;

	r_vector2f m_Offset = r_vector2f(0.0f, 0.0f);
	r_bool m_bOffsetChanged = false;
};

#endif