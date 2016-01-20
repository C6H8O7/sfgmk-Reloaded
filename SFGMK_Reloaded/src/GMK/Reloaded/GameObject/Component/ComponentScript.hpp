#ifndef SFGMKR_COMPONENTSCRIPT_HPP
#define SFGMKR_COMPONENTSCRIPT_HPP

#include "stdafx.h"

class ComponentScript : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentScript(GameObject* _parent);
	~ComponentScript();

	virtual r_void OnUpdate(SFMLCanvas * _canvas);
	virtual r_void OnDraw(SFMLCanvas* _canvas);

	virtual r_void OnMembersUpdate();

#ifdef SFGMKR_EDITOR
	virtual r_void OnRegistration();

	r_void RefreshScript();
	r_void ReloadScript(wxEvent& _event);
#endif

	virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

	r_void OnPhysicEnter();
	r_void OnPhysicCollisionEnter(GameObject* _object);
	r_void OnPhysicCollision(GameObject* _object);
	r_void OnPhysicExit();

	r_void onScriptLoad();

protected:

	gmk::Lua m_Lua;

	r_string m_Path;
	r_bool m_PathChanged;

	r_bool m_VariablesChanged;

	r_bool m_Init;
};

#endif