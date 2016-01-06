namespace gmk
{
	r_void lua_init(lua_State** _state, GameObject* _gameobject)
	{
		luaL_openlibs(*_state);

		luabridge::getGlobalNamespace(*_state)

		.beginClass<r_vector2f>("Vector2f")
			.addConstructor<r_void(*) (r_void)>()
			.addData("x", &r_vector2f::x, true)
			.addData("y", &r_vector2f::y, true)
		.endClass()

		.beginClass<Transform>("Transform")
			.addConstructor<r_void(*) (r_void)>()
			.addData("position", &Transform::positionPtr, true)
			.addData("scale", &Transform::scalePtr, true)
			.addData("rotation", &Transform::rotation, true)
		.endClass()

		.beginClass<gmk::PathfindingAgent>("PathfindingAgent")
			.addConstructor<r_void(*) (r_void)>()
			.addFunction("computePathfinding", &gmk::PathfindingAgent::computePathfinding)
		.endClass()

		.beginClass<gmk::Debug>("Debug")
			.addConstructor<r_void(*) (r_void)>()
			.addData("selected", &Debug::selected, true)
		.endClass()

		.beginClass<GameObject>("GameObject")
			.addConstructor<r_void(*) (r_void)>()
			.addData("transform", &GameObject::transformPtr, true)
			.addData("debug", &GameObject::debugPtr, true)
			.addFunction("computePathfinding", &GameObject::computePathfinding)
		.endClass()

		.beginNamespace("this")
			.addVariable("gameobject", &_gameobject->ptr)
			.addVariable("transform", &_gameobject->transformPtr)
			.addVariable("debug", &_gameobject->debugPtr, true)
		.endNamespace()

		.beginNamespace("game")
			.addFunction("getGameObjectByName", &lua_findObjectByName)
			.addFunction("removeGameObject", &lua_removeGameObject)
		.endNamespace()

		.beginNamespace("input")
			.beginNamespace("mouse")
				.addVariable("windowPosition", &SFMLCanvas::gameCanvas->getInputManager()->getMouse().windowPosition, false)
				.addVariable("worldPosition", &SFMLCanvas::gameCanvas->getInputManager()->getMouse().worldPosition, false)
				.addVariable("left", &SFMLCanvas::gameCanvas->getInputManager()->getMouse().m_KeyStates[0], false)
				.addVariable("right", &SFMLCanvas::gameCanvas->getInputManager()->getMouse().m_KeyStates[1], false)
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
			.addFunction("log", &lua_print)
		.endNamespace();
	}

	r_void lua_close(lua_State** _state)
	{
		lua_close(*_state);
		*_state = 0;
	}

	r_void lua_gmk_call(luabridge::LuaRef& _ref)
	{
		try {
			_ref();
		}
		catch (std::exception& e) {
			std::cout << "[LUA ERROR]: " << e.what() << std::endl;
		}
	}

	r_void lua_print(r_string _message)
	{
		std::cout << _message << std::endl;
	}

	GameObject* lua_findObjectByName(r_string _name)
	{
		return SFMLCanvas::project->getCurrentScene()->findGameObjectByName(_name);
	}

	r_void lua_removeGameObject(GameObject* _gameobject)
	{
		SFMLCanvas::project->getCurrentScene()->removeGameObject(_gameobject);

#ifdef SFGMKR_EDITOR
		MyGUI::GetGUI()->Update_HierarchyTree();
#endif
	}
}