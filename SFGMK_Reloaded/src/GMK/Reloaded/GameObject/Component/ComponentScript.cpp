ComponentScript::ComponentScript(GameObject * _parent)
	: GameObjectComponent("Script", _parent), m_LuaState(luaL_newstate()),
	m_LUA_OnStart(m_LuaState), m_LUA_OnUpdate(m_LuaState),
	m_LUA_OnPhysicEnter(m_LuaState), m_LUA_OnPhysicCollision(m_LuaState), m_LUA_OnPhysicExit(m_LuaState)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	gmk::lua_init(&m_LuaState, parent);
}

ComponentScript::~ComponentScript()
{
	gmk::lua_close(&m_LuaState);
}

r_void ComponentScript::OnUpdate(SFMLCanvas * _canvas)
{
	if (!SFMLCanvas::isPlaying)
		return;

	if (m_LUA_OnUpdate.isFunction())
		GMK_LUA_CALL(m_LUA_OnUpdate())
}

r_void ComponentScript::OnDraw(SFMLCanvas* _canvas)
{

}

r_void ComponentScript::OnMembersUpdate()
{
	if (m_PathChanged)
	{
		m_PathChanged = false;

		if (m_Path.find(".lua") != r_string::npos)
		{
			luaL_dofile(m_LuaState, gmk::AssetsManager::GetSingleton()->getAssetPath(m_Path).c_str());

			m_LUA_OnStart = luabridge::getGlobal(m_LuaState, "OnStart");
			m_LUA_OnUpdate = luabridge::getGlobal(m_LuaState, "OnUpdate");

			m_LUA_OnPhysicEnter = luabridge::getGlobal(m_LuaState, "OnPhysicEnter");
			m_LUA_OnPhysicCollision = luabridge::getGlobal(m_LuaState, "OnPhysicCollision");
			m_LUA_OnPhysicExit = luabridge::getGlobal(m_LuaState, "OnPhysicExit");

			if (m_LUA_OnStart.isFunction())
				gmk::lua_call(m_LUA_OnStart);
		}
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentScript::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Path", &m_Path, &m_PathChanged);

	endRegister();
}
#endif

r_void ComponentScript::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("path", m_Path.c_str());
}

r_void ComponentScript::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_Path = _element->Attribute("path");
	m_PathChanged = true;
}

r_void ComponentScript::OnPhysicEnter()
{
	if (m_LUA_OnPhysicEnter.isFunction())
		gmk::lua_call(m_LUA_OnPhysicEnter);
}

r_void ComponentScript::OnPhysicCollision(GameObject* _object)
{
	if (m_LUA_OnPhysicCollision.isFunction())
		m_LUA_OnPhysicCollision(_object);
}

r_void ComponentScript::OnPhysicExit()
{
	if (m_LUA_OnPhysicExit.isFunction())
		gmk::lua_call(m_LUA_OnPhysicExit);
}