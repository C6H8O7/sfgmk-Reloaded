#ifndef SFGMKR_COMPONENTSCRIPT_HPP
#define SFGMKR_COMPONENTSCRIPT_HPP

class ComponentScript : public GameObjectComponent
{
public:

	ComponentScript(GameObject* _parent);
	~ComponentScript();

	virtual void OnUpdate();
	virtual void OnDraw(sf::RenderWindow* _render);

	virtual void OnRegistration();

	virtual void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual void OnXMLLoad(tinyxml2::XMLElement* _element);

protected:

	lua_State* m_LuaState;

	luabridge::LuaRef m_LUA_OnUpdate;

	std::string m_Path;
	bool m_PathChanged;

	bool m_Opened;
};

#endif