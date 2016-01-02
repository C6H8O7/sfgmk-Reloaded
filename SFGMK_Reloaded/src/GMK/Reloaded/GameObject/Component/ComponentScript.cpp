ComponentScript::ComponentScript(GameObject * _parent)
	: GameObjectComponent("Script", _parent), m_LuaState(luaL_newstate()), m_LUA_OnStart(m_LuaState), m_LUA_OnUpdate(m_LuaState)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	luaL_openlibs(m_LuaState);

	luabridge::getGlobalNamespace(m_LuaState)

		.beginClass<r_vector2f>("Vector2")
			.addConstructor<r_void (*) (r_void)>()
			.addData("x", &r_vector2f::x, true)
			.addData("y", &r_vector2f::y, true)
		.endClass()

		.beginClass<Transform>("Transform")
			.addConstructor<r_void(*) (r_void)>()
			.addData("position", &Transform::positionPtr, true)
			.addData("scale", &Transform::scalePtr, true)
			.addData("rotation", &Transform::rotation, true)
		.endClass()

		.beginClass<GameObject>("GameObject")
			.addConstructor<r_void(*) (r_void)>()
			.addData("transform", &GameObject::transformPtr, true)
		.endClass()

		.beginNamespace("this")
			.addVariable("gameobject", &parent)
			.addVariable("transform", &parent->transformPtr)
		.endNamespace()
		
		.beginNamespace("game")
			.addFunction("getGameObjectByName", &ComponentScript::LUA_GetGameObjectByName)
			.addFunction("removeGameObject", &ComponentScript::LUA_RemoveGameObject)
		.endNamespace()

		.beginNamespace("input")
			.beginNamespace("mouse")
				.addVariable("windowPosition", &SFMLCanvas::gameCanvas->getInputManager()->getMouse().windowPosition, false)
				.addVariable("worldPosition", &SFMLCanvas::gameCanvas->getInputManager()->getMouse().worldPosition, false)
			.endNamespace()
		.endNamespace()

		.beginNamespace("time")
			.addVariable("deltaTime", &gmk::TimeManager::GetSingleton()->deltaTime)
			.addVariable("totalTime", &gmk::TimeManager::GetSingleton()->totalTime)
			.addVariable("timeFactor", &gmk::TimeManager::GetSingleton()->timeFactor)
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

r_void ComponentScript::OnUpdate(SFMLCanvas * _canvas)
{
	if (!SFMLCanvas::isPlaying)
		return;

	if (m_LUA_OnUpdate.isFunction())
		CallLUA(m_LUA_OnUpdate);
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

			if (m_LUA_OnStart.isFunction())
				CallLUA(m_LUA_OnStart);
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

r_void ComponentScript::LUA_Print(r_string _message)
{
	std::cout << _message << std::endl;
}

GameObject* ComponentScript::LUA_GetGameObjectByName(r_string _name)
{
	return SFMLCanvas::project->getCurrentScene()->findGameObjectByName(_name);
}

r_void ComponentScript::LUA_RemoveGameObject(GameObject* _gameobject)
{
	SFMLCanvas::project->getCurrentScene()->removeGameObject(_gameobject);

#ifdef SFGMKR_EDITOR
	MyGUI::GetGUI()->Update_HierarchyTree();
#endif
}

r_void ComponentScript::CallLUA(luabridge::LuaRef& _ref)
{
	try {
		_ref();
	} catch (std::exception& e) {
		std::cout << "[LUA ERROR]: " << e.what() << std::endl;
	}
}