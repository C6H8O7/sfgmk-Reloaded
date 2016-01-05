#ifndef SFGMKR_COMPONENTSCRIPT_HPP
#define SFGMKR_COMPONENTSCRIPT_HPP

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
#endif

	virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

	r_void OnPhysicEnter();
	r_void OnPhysicCollision(GameObject* _object);
	r_void OnPhysicExit();

protected:

	lua_State* m_LuaState;

	luabridge::LuaRef m_LUA_OnStart;
	luabridge::LuaRef m_LUA_OnUpdate;

	luabridge::LuaRef m_LUA_OnPhysicEnter;
	luabridge::LuaRef m_LUA_OnPhysicCollision;
	luabridge::LuaRef m_LUA_OnPhysicExit;

	r_string m_Path;
	r_bool m_PathChanged;
};

#endif