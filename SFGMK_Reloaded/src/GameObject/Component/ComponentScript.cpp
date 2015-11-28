ComponentScript::ComponentScript(GameObject * _parent)
	: GameObjectComponent("Script", _parent), m_LuaState(luaL_newstate()), m_LUA_OnUpdate(m_LuaState)
{
	OnRegistration();

	m_Opened = false;

	luaL_openlibs(m_LuaState);

	luabridge::getGlobalNamespace(m_LuaState)
		.beginNamespace("transform")
			.beginNamespace("position")
				.addVariable("x", &parent->transform.position.x)
				.addVariable("y", &parent->transform.position.y)
			.endNamespace()
			.beginNamespace("scale")
				.addVariable("x", &parent->transform.scale.x)
				.addVariable("y", &parent->transform.scale.y)
			.endNamespace()
			.addVariable("rotation", &parent->transform.rotation)
		.endNamespace();
}

ComponentScript::~ComponentScript()
{
	lua_close(m_LuaState);
	m_LuaState = 0;
}

void ComponentScript::OnUpdate()
{
	if (m_PathChanged)
	{
		m_PathChanged = false;

		if (m_Path.find(".lua") != std::string::npos)
		{
			luaL_dofile(m_LuaState, m_Path.c_str());

			m_LUA_OnUpdate = luabridge::getGlobal(m_LuaState, "OnUpdate");

			m_Opened = true;
		}
	}

	if (m_Opened)
		m_LUA_OnUpdate();
}

void ComponentScript::OnDraw(sf::RenderWindow * _render)
{

}

void ComponentScript::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Path", &m_Path, &m_PathChanged);

	endRegister();
}