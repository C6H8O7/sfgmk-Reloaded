#ifndef SFGMKR_COMPONENTSELECTOR_HPP
#define SFGMKR_COMPONENTSELECTOR_HPP

#include "stdafx.h"

class ComponentSelector : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentSelector(GameObject* _parent);
	~ComponentSelector();

	virtual r_void OnUpdate(SFMLCanvas * _canvas);
	virtual r_void OnDraw(SFMLCanvas* _canvas);

	virtual r_void OnMembersUpdate();

#ifdef SFGMKR_EDITOR
	virtual r_void OnRegistration();
#endif

	virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

private:

	gmk::Selector m_Selector;
};

#endif