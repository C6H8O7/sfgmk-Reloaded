namespace gmk
{
	static const r_int32 gmk_lualibs_count = 8;

	static const luaL_Reg gmk_lualibs[gmk_lualibs_count] = {
		{ "_G", luaopen_base },
		{ LUA_LOADLIBNAME, luaopen_package },
		{ LUA_TABLIBNAME, luaopen_table },
		{ LUA_IOLIBNAME, luaopen_io },
		{ LUA_OSLIBNAME, luaopen_os },
		{ LUA_STRLIBNAME, luaopen_string },
		{ LUA_MATHLIBNAME, luaopen_math },
		{ LUA_DBLIBNAME, luaopen_debug }
	};

	void gmk_luaL_openlibs(lua_State *L) {
		for (r_int32 i = 0; i < gmk_lualibs_count; i++) {
			lua_pushcfunction(L, gmk_lualibs[i].func);
			lua_pushstring(L, gmk_lualibs[i].name);
			lua_call(L, 1, 0);
		}
	}

	lua_State* lua_gmk_init(GameObject* _gameobject)
	{
		lua_State* state = luaL_newstate();
		gmk_luaL_openlibs(state);

		luabridge::getGlobalNamespace(state)

		.beginNamespace("gmk")

			.beginClass<r_vector2f>("Vector2f")
				.addConstructor<r_void(*) (r_void)>()
				.addData("x", &r_vector2f::x)
				.addData("y", &r_vector2f::y)
			.endClass()

			.beginClass<Transform>("Transform")
				.addConstructor<r_void(*) (r_void)>()
				.addData("position", &Transform::positionPtr)
				.addData("scale", &Transform::scalePtr)
				.addData("rotation", &Transform::rotation)
			.endClass()

			/*.beginClass<gmk::PathfindingAgent>("PathfindingAgent")
				.addConstructor<r_void(*) (r_void)>()
				.addFunction("computePathfinding", &gmk::PathfindingAgent::computePathfinding)
			.endClass()*/

			.beginClass<gmk::Debug>("Debug")
				.addConstructor<r_void(*) (r_void)>()
				.addData("selected", &Debug::selected)
			.endClass()

			.beginClass<GameObject>("GameObject")
				.addConstructor<r_void(*) (r_void)>()
				.addData("transform", &GameObject::transformPtr)
				.addData("debug", &GameObject::debugPtr)
				.addFunction("computePathfinding", &GameObject::computePathfinding)
			.endClass()

		.endNamespace()

		.beginNamespace("this")
			.addVariable("gameobject", &_gameobject->ptr)
			.addVariable("transform", &_gameobject->transformPtr)
			.addVariable("debug", &_gameobject->debugPtr)
		.endNamespace()

		.beginNamespace("game")
			.addFunction("getGameObjectByName", &lua_findObjectByName)
			.addFunction("removeGameObject", &lua_removeGameObject)
			.addFunction("log", &lua_print)
		.endNamespace()

		.beginNamespace("input")
			.beginNamespace("mouse")
				.addVariable("windowPosition", &SFMLCanvas::gameCanvas->getInputManager()->getMouse().windowPosition)
				.addVariable("worldPosition", &SFMLCanvas::gameCanvas->getInputManager()->getMouse().worldPosition)
				.addVariable("left", &SFMLCanvas::gameCanvas->getInputManager()->getMouse().m_KeyStates[0])
				.addVariable("right", &SFMLCanvas::gameCanvas->getInputManager()->getMouse().m_KeyStates[1])
			.endNamespace()
		.endNamespace()

		.beginNamespace("time")
			.addVariable("deltaTime", &gmk::TimeManager::GetSingleton()->deltaTime)
			.addVariable("totalTime", &gmk::TimeManager::GetSingleton()->totalTime)
			.addVariable("timeFactor", &gmk::TimeManager::GetSingleton()->timeFactor)
		.endNamespace();

		return state;
	}

	r_void lua_gmk_close(lua_State** _state)
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