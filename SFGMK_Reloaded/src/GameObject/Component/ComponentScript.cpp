ComponentScript::ComponentScript(GameObject * _parent)
	: GameObjectComponent("Script", _parent), m_LuaState(luaL_newstate()), m_LUA_OnStart(m_LuaState), m_LUA_OnUpdate(m_LuaState)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

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
		.endNamespace()

		.beginNamespace("time")
			.addVariable("deltaTime", &sfgmk::TimeManager::GetSingleton()->deltaTime)
			.addVariable("totalTime", &sfgmk::TimeManager::GetSingleton()->totalTime)
			.addVariable("timeFactor", &sfgmk::TimeManager::GetSingleton()->timeFactor)
		.endNamespace();
}

ComponentScript::~ComponentScript()
{
	lua_close(m_LuaState);
	m_LuaState = 0;
}

void ComponentScript::OnUpdate()
{
	if (!SFMLCanvas::isPlaying)
		return;

	if (m_PathChanged)
	{
		m_PathChanged = false;

		if (m_Path.find(".lua") != std::string::npos)
		{
			luaL_dofile(m_LuaState, m_Path.c_str());

			m_LUA_OnStart = luabridge::getGlobal(m_LuaState, "OnStart");
			m_LUA_OnUpdate = luabridge::getGlobal(m_LuaState, "OnUpdate");

			if (m_LUA_OnStart.isFunction())
				m_LUA_OnStart();
		}
	}

	if (m_LUA_OnUpdate.isFunction())
		m_LUA_OnUpdate();
}

void ComponentScript::OnDraw(sf::RenderWindow * _render)
{

}

#ifdef SFGMKR_EDITOR
void ComponentScript::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Path", &m_Path, &m_PathChanged);

	endRegister();
}
#endif

void ComponentScript::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("path", m_Path.c_str());
}

void ComponentScript::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_Path = _element->Attribute("path");
	m_PathChanged = true;
}