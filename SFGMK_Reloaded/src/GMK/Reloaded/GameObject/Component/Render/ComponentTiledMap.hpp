#ifndef SFGMKR_COMPONENTTILEDMAP_HPP
#define SFGMKR_COMPONENTTILEDMAP_HPP

#include "stdafx.h"

class ComponentTiledMap : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentTiledMap(GameObject* _parent);
	~ComponentTiledMap();

	virtual r_void OnUpdate(SFMLCanvas * _canvas);
	virtual r_void OnDraw(SFMLCanvas* _canvas);

	virtual r_void OnMembersUpdate();

#ifdef SFGMKR_EDITOR
	virtual r_void OnRegistration();
#endif

	virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

private:

	gmk::TiledMap m_Map;

	r_string m_Path;
	r_bool m_PathChanged;
};

#endif