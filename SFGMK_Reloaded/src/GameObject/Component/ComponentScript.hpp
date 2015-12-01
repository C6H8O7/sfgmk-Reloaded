#ifndef SFGMKR_COMPONENTSCRIPT_HPP
#define SFGMKR_COMPONENTSCRIPT_HPP

class ComponentScript : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentScript(GameObject* _parent);
	~ComponentScript();

	virtual void OnUpdate(SFMLCanvas * _canvas);
	virtual void OnDraw(SFMLCanvas* _canvas);

#ifdef SFGMKR_EDITOR
	virtual void OnRegistration();
#endif

	virtual void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual void OnXMLLoad(tinyxml2::XMLElement* _element);

	static void LUA_Print(std::string _message);

	static GameObject* LUA_GetGameObjectByName(std::string _name);
	static void LUA_RemoveGameObjectByName(GameObject* _gameobject);

	static void CallLUA(luabridge::LuaRef& _ref);

protected:

	lua_State* m_LuaState;

	luabridge::LuaRef m_LUA_OnStart;
	luabridge::LuaRef m_LUA_OnUpdate;

	std::string m_Path;
	bool m_PathChanged;
};

#endif