ComponentScript::ComponentScript(GameObject * _parent)
	: GameObjectComponent("Script", _parent), m_LuaState(luaL_newstate()), m_LUA_OnStart(m_LuaState), m_LUA_OnUpdate(m_LuaState)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	luaL_openlibs(m_LuaState);

	m_TransformPtr = &parent->transform;

	luabridge::getGlobalNamespace(m_LuaState)

		.beginClass<sf::Vector2f>("Vector2")
			.addConstructor<void (*) (void)>()
			.addData("x", &sf::Vector2f::x, true)
			.addData("y", &sf::Vector2f::y, true)
		.endClass()

		.beginClass<Transform>("Transform")
			.addConstructor<void(*) (void)>()
			.addData("position", &Transform::positionPtr, true)
			.addData("scale", &Transform::scalePtr, true)
			.addData("rotation", &Transform::rotation, true)
		.endClass()

		.beginNamespace("this")
			.addVariable("transform", &m_TransformPtr)
		.endNamespace()

		.beginNamespace("time")
			.addVariable("deltaTime", &sfgmk::TimeManager::GetSingleton()->deltaTime)
			.addVariable("totalTime", &sfgmk::TimeManager::GetSingleton()->totalTime)
			.addVariable("timeFactor", &sfgmk::TimeManager::GetSingleton()->timeFactor)
		.endNamespace()

		.beginNamespace("math")
			.addFunction("cos", &std::cosf)
			.addFunction("sin", &std::sinf)
			.addFunction("acos", &std::acosf)
			.addFunction("asin", &std::asinf)
		.endNamespace()

		.beginNamespace("debug")
			.addFunction("log", &ComponentScript::LUA_Print)
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

void ComponentScript::LUA_Print(std::string _message)
{
	std::cout << _message << std::endl;
}