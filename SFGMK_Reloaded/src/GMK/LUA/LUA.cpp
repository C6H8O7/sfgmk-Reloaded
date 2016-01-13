#define GMK_LUA_CALL(F)			{																					\
									try {																			\
										F;																			\
									} catch (std::exception& e) {													\
										std::cout << "[LUA ERROR]: " << e.what() << std::endl;						\
									}																				\
								}																					\

namespace gmk
{
	Lua::Lua(GameObject* _gameobject)
	{
		init(_gameobject);
	}

	Lua::~Lua()
	{
		resetRefs();
		close();
	}

	r_void Lua::init(GameObject* _gameobject)
	{
		m_state = luaL_newstate();
		openlibs();

		luabridge::getGlobalNamespace(m_state)

		.beginNamespace("gmk")
			.beginClass<r_vector2f>("Vector2f")
				.addConstructor<r_void(*) (r_void)>()
				.addConstructor<r_void(*) (r_float, r_float)>()
				.addData("x", &r_vector2f::x)
				.addData("y", &r_vector2f::y)
			.endClass()

			.beginClass<Transform>("Transform")
				.addConstructor<r_void(*) (r_void)>()
				.addData("position", &Transform::positionPtr)
				.addData("scale", &Transform::scalePtr)
				.addData("rotation", &Transform::rotation)
			.endClass()

			.beginClass<gmk::PathfindingAgent>("PathfindingAgent")
				.addConstructor<r_void(*) (r_void)>()
				.addFunction("computePathfinding", &gmk::PathfindingAgent::computePathfinding)
			.endClass()

			.beginClass<gmk::Debug>("Debug")
				.addConstructor<r_void(*) (r_void)>()
				.addData("selected", &Debug::selected)
			.endClass()

			.beginClass<gmk::Rigidbody>("Rigidbody")
				.addConstructor<r_void(*) (GameObject*)>()
				.addFunction("addForce", &gmk::Rigidbody::addForce)
				.addFunction("setPosition", &gmk::Rigidbody::setPosition)
				.addFunction("setForce", &gmk::Rigidbody::setAcceleration)
				.addFunction("setSpeed", &gmk::Rigidbody::setSpeed)
				.addFunction("cleanForces", &gmk::Rigidbody::cleanForces)
				.addFunction("cleanSpeed", &gmk::Rigidbody::cleanSpeed)
				.addFunction("getMaxSpeed", &gmk::Rigidbody::getMaxSpeed)
				.addFunction("getMaxForce", &gmk::Rigidbody::getMaxAcceleration)
				.addFunction("getSpeed", &gmk::Rigidbody::getSpeed)
			.endClass()

			.beginClass<GameObject>("GameObject")
				.addConstructor<r_void(*) (r_void)>()
				.addData("transform", &GameObject::transformPtr)
				.addData("debug", &GameObject::debugPtr)
				.addData("rigidbody", &GameObject::rigidbodyPtr)
				.addFunction("computePathfinding", &GameObject::computePathfinding)
			.endClass()
		.endNamespace()

		.beginNamespace("this")
			.addVariable("gameobject", &_gameobject->ptr)
			.addVariable("transform", &_gameobject->transformPtr)
			.addVariable("debug", &_gameobject->debugPtr)
			.addVariable("rigidbody", &_gameobject->rigidbodyPtr)
		.endNamespace()

		.beginNamespace("game")
			.addFunction("getGameObjectByName", &Lua::findObjectByName)
			.addFunction("removeGameObject", &Lua::removeGameObject)
			.addFunction("log", &Lua::print)
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
	}

	r_void Lua::close()
	{
		lua_close(m_state);
		m_state = 0;
	}

	r_void Lua::loadFile(r_string _path)
	{
		resetRefs();

		luaL_dofile(m_state, _path.c_str());

		m_onStart				= initRef("OnStart");
		m_onUpdate				= initRef("OnUpdate");

		m_onPhysicEnter			= initRef("OnPhysicEnter");
		m_onPhysicCollision		= initRef("OnPhysicCollision");
		m_onPhysicExit			= initRef("OnPhysicExit");

		parseFile(_path);
	}

	luabridge::LuaRef* Lua::initRef(r_string _func)
	{
		luabridge::LuaRef ref = luabridge::getGlobal(m_state, _func.c_str());

		if (ref.isFunction())
			return new luabridge::LuaRef(ref);
		
		return 0;
	}

	r_void Lua::resetRefs()
	{
		SAFE_DELETE(m_onStart);
		SAFE_DELETE(m_onUpdate);

		SAFE_DELETE(m_onPhysicEnter);
		SAFE_DELETE(m_onPhysicCollision);
		SAFE_DELETE(m_onPhysicExit);
	}

	r_void Lua::openlibs()
	{
		const r_int32 gmk_lualibs_count = 8;

		const luaL_Reg gmk_lualibs[gmk_lualibs_count] = {
			{ "_G", luaopen_base },
			{ LUA_LOADLIBNAME, luaopen_package },
			{ LUA_TABLIBNAME, luaopen_table },
			{ LUA_IOLIBNAME, luaopen_io },
			{ LUA_OSLIBNAME, luaopen_os },
			{ LUA_STRLIBNAME, luaopen_string },
			{ LUA_MATHLIBNAME, luaopen_math },
			{ LUA_DBLIBNAME, luaopen_debug }
		};

		for (r_int32 i = 0; i < gmk_lualibs_count; i++) {
			lua_pushcfunction(m_state, gmk_lualibs[i].func);
			lua_pushstring(m_state, gmk_lualibs[i].name);
			lua_call(m_state, 1, 0);
		}
	}

	r_void Lua::onStart()
	{
		if(m_onStart)
			GMK_LUA_CALL((*m_onStart)())
	}

	r_void Lua::onUpdate()
	{
		if (m_onUpdate)
			GMK_LUA_CALL((*m_onUpdate)())
	}

	r_void Lua::onPhysicEnter()
	{
		if (m_onPhysicEnter)
			GMK_LUA_CALL((*m_onPhysicEnter)())
	}

	r_void Lua::onPhysicCollision(GameObject* _gameobject)
	{
		if(m_onPhysicCollision)
			GMK_LUA_CALL((*m_onPhysicCollision)(_gameobject))
	}

	r_void Lua::onPhysicExit()
	{
		if (m_onPhysicExit)
			GMK_LUA_CALL((*m_onPhysicExit)())
	}

	r_void Lua::print(r_string _message)
	{
		std::cout << _message << std::endl;
	}

	GameObject* Lua::findObjectByName(r_string _name)
	{
		return SFMLCanvas::project->getCurrentScene()->findGameObjectByName(_name);
	}

	r_void Lua::removeGameObject(GameObject* _gameobject)
	{
		SFMLCanvas::project->getCurrentScene()->removeGameObject(_gameobject);

	#ifdef SFGMKR_EDITOR
		MyGUI::GetGUI()->Update_HierarchyTree();
	#endif
	}

	std::vector<r_string> Lua::parseFile(r_string _path)
	{
		std::vector<r_string> lines = gmk::getFileLines(_path);

		return lines;
	}
}