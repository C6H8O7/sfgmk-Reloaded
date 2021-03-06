#include "stdafx.h"

#define GMK_LUA_CALL(F)			{																					\
									try {																			\
										F;																			\
									} catch (std::exception& e) {													\
										gmk::Debug::Log(r_string("[LUA ERROR]: ") + e.what() + "\n");				\
									}																				\
								}																					\

static char* KeyboardKeys[sf::Keyboard::KeyCount] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
													"Num0", "Num1", "Num2", "Num3", "Num4", "Num5", "Num6", "Num7", "Num8", "Num9",
													"Escape", "LControl", "LShift", "LAlt", "LSystem", "RControl", "RShift", "RAlt", "RSystem", "Menu",
													"LBracket", "RBracket", "SemiColon", "Comma", "Period", "Quote", "Slash", "BackSlash", "Tilde", "Equal", "Dash",
													"Space", "Return", "BackSpace", "Tab", "PageUp", "PageDown", "End", "Home", "Insert", "Delete",
													"Add", "Subtract", "Multiply", "Divide", "Left", "Right", "Up", "Down",
													"Numpad0", "Numpad1", "Numpad2", "Numpad3", "Numpad4", "Numpad5", "Numpad6", "Numpad7", "Numpad8", "Numpad9",
													"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15", "Pause" };

static int KeyboardKeysValues[sf::Keyboard::KeyCount] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
														20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
														40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
														60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
														80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
														100 };

static int StatesValues[] = { gmk::eKEY_UP, gmk::eKEY_PRESSED, gmk::eKEY_DOWN, gmk::eKEY_RELEASED };

namespace gmk
{
	Lua::Lua(GameObject* _gameobject)
		: m_gameobject(_gameobject), m_this(this)
	{
		init(_gameobject);
	}

	Lua::~Lua()
	{
		resetRefs();
		close();

		emptyVariables();
	}

	r_void Lua::initKeyboardInputs(lua_State* _state)
	{
		for (r_int32 i = 0; i < sf::Keyboard::KeyCount; i++)
		{
			luabridge::getGlobalNamespace(_state)

			.beginNamespace("input")
				.beginNamespace("key")
					.addVariable(KeyboardKeys[i], &KeyboardKeysValues[i])
				.endNamespace()
			.endNamespace();
		}
	}

	r_void Lua::init(GameObject* _gameobject)
	{
		m_state = luaL_newstate();
		openlibs();

		r_void (r_transform::*setPositionPtr)(const r_vector2f&) = &r_transform::setPosition;
		r_void (r_transform::*setScalePtr)(const r_vector2f&) = &r_transform::setScale;
		r_vector2f (r_transform::*getPositionPtr)() = &r_transform::getPositionCopy;
		r_vector2f (r_transform::*getScalePtr)() = &r_transform::getScaleCopy;

		luabridge::getGlobalNamespace(m_state)

		.beginClass<r_vector2f>("r_vector2f")
			.addConstructor<r_void(*) ()>()
			.addConstructor<r_void(*) (r_float, r_float)>()
			.addData("x", &r_vector2f::x)
			.addData("y", &r_vector2f::y)
		.endClass()

		.beginClass<r_vector2i>("r_vector2i")
			.addConstructor<r_void(*) ()>()
			.addConstructor<r_void(*) (r_int32, r_int32)>()
			.addData("x", &r_vector2i::x)
			.addData("y", &r_vector2i::y)
		.endClass()

		.beginClass<r_transform>("r_transform")
			.addConstructor<r_void(*) ()>()
			.addFunction("setPosition", setPositionPtr)
			.addFunction("setScale", setScalePtr)
			.addFunction("setRotation", &r_transform::setRotation)
			.addFunction("getPosition", getPositionPtr)
			.addFunction("getScale", getScalePtr)
			.addFunction("getRotation", &r_transform::getRotation)
		.endClass()

		.beginClass<gmk::PathfindingAgent>("PathfindingAgent")
			.addConstructor<r_void(*) ()>()
			.addFunction("computePathfinding", &gmk::PathfindingAgent::computePathfinding)
		.endClass()

		.beginClass<gmk::Debug>("Debug")
			.addConstructor<r_void(*) ()>()
			.addData("selected", &Debug::selected)
		.endClass()

		.beginClass<gmk::Rigidbody>("Rigidbody")
			.addConstructor<r_void(*) (GameObject*)>()
			.addFunction("addForce", &gmk::Rigidbody::addForce)
			.addFunction("setForce", &gmk::Rigidbody::setForce)
			.addFunction("setSpeed", &gmk::Rigidbody::setSpeed)
			.addFunction("cleanForces", &gmk::Rigidbody::cleanForces)
			.addFunction("cleanSpeed", &gmk::Rigidbody::cleanSpeed)
			.addFunction("getMaxSpeed", &gmk::Rigidbody::getMaxSpeed)
			.addFunction("getMaxForce", &gmk::Rigidbody::getMaxForce)
			.addFunction("getSpeed", &gmk::Rigidbody::getSpeed)
		.endClass()

		.beginClass<ComponentSoundBuffer>("SoundBuffer")
			.addFunction("playSound", &ComponentSoundBuffer::playSound)
			.addFunction("playMusic", &ComponentSoundBuffer::playMusic)
			.addFunction("stopMusic", &ComponentSoundBuffer::stopMusic)
		.endClass()

		.beginClass<gmk::Lua>("Lua")
			.addConstructor<r_void(*) (GameObject*)>()
		.endClass()

		.beginClass<gmk::LuaScript>("LuaScript")
			.addFunction("setFloat", &LuaScript::setFloat)
			.addFunction("getFloat", &LuaScript::getFloat)
			.addFunction("setInt", &LuaScript::setInt)
			.addFunction("getInt", &LuaScript::getInt)
			.addFunction("setString", &LuaScript::setString)
			.addFunction("getString", &LuaScript::getString)
			.addFunction("callFunction", &LuaScript::callFunction)
		.endClass()

		.beginClass<gmk::Steering>("Steering")
			.addFunction("setTarget", &gmk::Steering::setSteeringTarget)
			.addFunction("setWeight", &gmk::Steering::setSteeringWeight)
		.endClass()

		.beginClass<gmk::Planner>("Planner")
			.addConstructor<r_void(*) ()>()
			.addFunction("addAction", &gmk::Planner::addAction)
			.addFunction("createAction", &gmk::Planner::createAction)
			.addFunction("setGoal", &gmk::Planner::setGoal)
		.endClass()

		.beginClass<gmk::PlannerAction>("PlannerAction")
			.addConstructor<r_void(*) (gmk::Planner*, gmk::Lua*)>()
			.addFunction("addCondition", &gmk::PlannerAction::addCondition)
			.addFunction("addEffect", &gmk::PlannerAction::addEffect)
			.addFunction("setDone", &gmk::PlannerAction::setDone)
		.endClass()

		.beginClass<GameObject>("GameObject")
			.addConstructor<r_void(*) ()>()
			.addData("gameobject", &GameObject::ptr)
			.addData("transform", &GameObject::transformPtr)
			.addData("debug", &GameObject::debugPtr)
			.addData("rigidbody", &GameObject::rigidbodyPtr)
			.addData("name", &GameObject::name)
			.addData("tag", &GameObject::tag)
			.addData("text", &GameObject::text)
			.addData("soundBuffer", &GameObject::soundBufferPtr)
			.addData("steering", &GameObject::steeringPtr)
			.addData("planner", &GameObject::plannerPtr)
			.addFunction("computePathfinding", &GameObject::computePathfinding)
			.addFunction("destroy", &GameObject::destroy)
			.addFunction("hardDestroy", &GameObject::hardDestroy)
			.addFunction("getScript", &GameObject::getScriptByName)
		.endClass()

		.beginNamespace("this")
			.addVariable("gameobject", &_gameobject->ptr)
			.addVariable("transform", &_gameobject->transformPtr)
			.addVariable("debug", &_gameobject->debugPtr)
			.addVariable("rigidbody", &_gameobject->rigidbodyPtr)
			.addVariable("name", &_gameobject->name)
			.addVariable("soundBuffer", &_gameobject->soundBufferPtr)
			.addVariable("steering", &_gameobject->steeringPtr)
			.addVariable("planner", &_gameobject->plannerPtr)
			.addVariable("lua", &m_this)
		.endNamespace()

		.beginNamespace("game")
			.addFunction("getGameObjectByName", &Lua::findObjectByName)
			.addFunction("removeGameObject", &Lua::removeGameObject)
			.addFunction("instantiate", &Lua::instantiate)
			.addFunction("loadScene", &Project::LoadSceneByName)
		.endNamespace()

		.beginNamespace("input")
			.beginNamespace("mouse")
				.addVariable("windowPosition", &SFMLCanvas::gameCanvas->getInputManager()->getMouse().windowPosition)
				.addVariable("worldPosition", &SFMLCanvas::gameCanvas->getInputManager()->getMouse().worldPosition)
				.addVariable("unscaledWindowPosition", &SFMLCanvas::gameCanvas->getInputManager()->getMouse().unscaledWindowPosition)
				.addVariable("left", &SFMLCanvas::gameCanvas->getInputManager()->getMouse().m_KeyStates[0])
				.addVariable("right", &SFMLCanvas::gameCanvas->getInputManager()->getMouse().m_KeyStates[1])
			.endNamespace()
			.beginNamespace("keyboard")
				.addFunction("getKeyState", &Lua::getKeyState)
			.endNamespace()
			.addVariable("up", &StatesValues[0])
			.addVariable("pressed", &StatesValues[1])
			.addVariable("down", &StatesValues[2])
			.addVariable("released", &StatesValues[3])
		.endNamespace()

		.beginNamespace("time")
			.addVariable("deltaTime", &gmk::TimeManager::GetSingleton()->deltaTime)
			.addVariable("totalTime", &gmk::TimeManager::GetSingleton()->totalTime)
			.addVariable("timeFactor", &gmk::TimeManager::GetSingleton()->timeFactor)
		.endNamespace()

		.beginNamespace("debug")
			.addFunction("log", &Lua::print)
		.endNamespace()

		.beginNamespace("math")
			.addFunction("distance", &math::Calc_DistanceHard)
			.addFunction("unitVectorFromPoints", &math::Calc_UnitVectorHard)
		.endNamespace()

		.beginNamespace("net")
			.addFunction("setHost", &gmk::net::NetworkManager::SetHost)
			.addFunction("setClient", &gmk::net::NetworkManager::SetClient)
			.addFunction("isHost", &gmk::net::NetworkManager::IsHost)
			.addFunction("hasValidHost", &gmk::net::NetworkManager::HasValidHost)
			.addFunction("sendGameObjectCall", &gmk::net::NetworkManager::SendGameObjectCall)
			.addFunction("clean", &gmk::net::NetworkManager::Clean)
		.endNamespace();

		initKeyboardInputs(m_state);
	}

	r_void Lua::close()
	{
		if (m_state)
		{
			lua_close(m_state);
			m_state = 0;
		}
	}

	r_void Lua::loadFile(r_string _path)
	{
		resetRefs();

		r_int8* lua_string = gmk::loadFile(_path);
		luaL_dostring(m_state, lua_string);
		delete lua_string;

		m_onStart					= initRef("OnStart");
		m_onUpdate					= initRef("OnUpdate");
		
		m_onPhysicEnter				= initRef("OnPhysicEnter");
		m_onPhysicCollisionEnter	= initRef("OnPhysicCollisionEnter");
		m_onPhysicCollision			= initRef("OnPhysicCollision");
		m_onPhysicExit				= initRef("OnPhysicExit");

		m_onPlannerActionStart		= initRef("OnPlannerActionStart");
		m_onPlannerActionPerform	= initRef("OnPlannerActionPerform");
	}

	r_void Lua::loadString(r_int8* _string)
	{
		resetRefs();

		luaL_dostring(m_state, _string);

		m_onStart					= initRef("OnStart");
		m_onUpdate					= initRef("OnUpdate");

		m_onPhysicEnter				= initRef("OnPhysicEnter");
		m_onPhysicCollisionEnter	= initRef("OnPhysicCollisionEnter");
		m_onPhysicCollision			= initRef("OnPhysicCollision");
		m_onPhysicExit				= initRef("OnPhysicExit");

		m_onPlannerActionStart		= initRef("OnPlannerActionStart");
		m_onPlannerActionPerform	= initRef("OnPlannerActionPerform");
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
		SAFE_DELETE(m_onPhysicCollisionEnter);
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

	r_void Lua::onPhysicCollisionEnter(GameObject* _gameobject)
	{
		if (m_onPhysicCollisionEnter)
			GMK_LUA_CALL((*m_onPhysicCollisionEnter)(_gameobject))
	}

	r_void Lua::onPhysicCollision(GameObject* _gameobject)
	{
		if (m_onPhysicCollision)
			GMK_LUA_CALL((*m_onPhysicCollision)(_gameobject))
	}

	r_void Lua::onPhysicExit()
	{
		if (m_onPhysicExit)
			GMK_LUA_CALL((*m_onPhysicExit)())
	}

	r_void Lua::onPlannerActionStart(gmk::PlannerAction* _action)
	{
		if (m_onPlannerActionStart)
			GMK_LUA_CALL((*m_onPlannerActionStart)(_action))
	}

	r_void Lua::onPlannerActionPerform(gmk::PlannerAction* _action)
	{
		if (m_onPlannerActionPerform)
			GMK_LUA_CALL((*m_onPlannerActionPerform)(_action))
	}

	r_void Lua::onVariablesRefresh()
	{
		for (r_uint32 i = 0; i < m_Variables.size(); i++)
			m_Variables[i]->function(m_state, m_Variables[i]->data, m_Variables[i]->name);
	}

	r_void Lua::print(r_string _message)
	{
		gmk::Debug::Log("[LUA_DEBUG] " + _message + "\n");
	}

	GameObject* Lua::findObjectByName(r_string _name)
	{
		return SFMLCanvas::project->getCurrentScene()->findGameObjectByName(_name);
	}

	r_void Lua::removeGameObject(GameObject* _gameobject)
	{
		SFMLCanvas::project->getCurrentScene()->removeGameObject(_gameobject);
	}

	GameObject* Lua::instantiate(r_string _prefabName)
	{
		GameObject* object = gmk::Factory::getSingleton()->instantiate(_prefabName);

		return object;
	}

	r_int32 Lua::getKeyState(r_int32 _key)
	{
		return SFMLCanvas::gameCanvas->getInputManager()->getKeyboard().getKeyState((sf::Keyboard::Key)_key);
	}

	lua_State* Lua::getStatePtr()
	{
		return m_state;
	}

	gmk::vector<sLUA_VARIABLE*>* Lua::getVariables()
	{
		return &m_Variables;
	}

	r_void Lua::emptyVariables()
	{
		for (r_uint32 i = 0; i < m_Variables.size(); i++)
			delete m_Variables[i]->data;

		m_Variables.deleteAndClear();
	}

	r_void Lua::parseVariables(r_string _string)
	{
		std::vector<r_string> lines = gmk::stringSplit(_string, '\n');

		std::string token = "--";

		for (r_uint32 i = 0; i < lines.size(); i++)
		{
			size_t index = lines[i].find(token);

			if (index != r_string::npos)
			{
				r_string params = lines[i].substr(index + token.length());

				r_bool isPublic = params.find("-public") != r_string::npos;
				r_bool isString = params.find("-string") != r_string::npos;
				r_bool isInt = params.find("-int") != r_string::npos;
				r_bool isFloat = params.find("-float") != r_string::npos;

				if (isPublic)
				{
					size_t firstLetter = lines[i].find_first_not_of(" ");
					size_t lastLetter = lines[i].find_first_of(" ", firstLetter);

					if (firstLetter != r_string::npos && lastLetter != r_string::npos && lastLetter > firstLetter)
					{
						r_string name = lines[i].substr(firstLetter, lastLetter - firstLetter);

						sLUA_VARIABLE* variablePtr = new sLUA_VARIABLE();
						variablePtr->name = name;

						if (isString)
						{
							variablePtr->type = eLUA_VARIABLE_TYPE::LUA_STRING;
							variablePtr->data = new r_string(luabridge::getGlobal(m_state, name.c_str()).cast<r_string>());
							variablePtr->function = &SetGlobal<r_string>;
							variablePtr->getFunction = &GetGlobal<r_string>;
						}
						else if (isInt)
						{
							variablePtr->type = eLUA_VARIABLE_TYPE::LUA_INT;
							variablePtr->data = new r_int32(luabridge::getGlobal(m_state, name.c_str()).cast<r_int32>());
							variablePtr->function = &SetGlobal<r_int32>;
							variablePtr->getFunction = &GetGlobal<r_int32>;
						}
						else if (isFloat)
						{
							variablePtr->type = eLUA_VARIABLE_TYPE::LUA_FLOAT;
							variablePtr->data = new r_float(luabridge::getGlobal(m_state, name.c_str()).cast<r_float>());
							variablePtr->function = &SetGlobal<r_float>;
							variablePtr->getFunction = &GetGlobal<r_float>;
						}
						else
						{
							delete variablePtr;
							variablePtr = 0;
						}

						if (variablePtr)
							m_Variables.push_back(variablePtr);
					}
				}
			}
		}
	}

	r_void Lua::updateVariables()
	{
		for (r_int32 i = 0; i < (r_int32)m_Variables.size(); i++)
			m_Variables[i]->getFunction(m_state, m_Variables[i]->data, m_Variables[i]->name.c_str());
	}

	////////////////////////////////////////////////////////////////////////// LuaScript

	LuaScript::LuaScript(Lua* _script)
		: m_script(_script)
	{

	}

	r_void LuaScript::setFloat(r_string _name, r_float _value)
	{
		if (m_script)
		{
			auto variables = m_script->getVariables();
			for (r_int32 i = 0; i < (r_int32)variables->size(); i++)
				if ((*variables)[i]->name == _name)
					(*variables)[i]->function(m_script->getStatePtr(), (r_void*)&_value, _name);
		}
	}

	r_float LuaScript::getFloat(r_string _name)
	{
		if (m_script)
			return luabridge::getGlobal(m_script->getStatePtr(), _name.c_str()).cast<r_float>();

		return 0.0f;
	}

	r_void LuaScript::setInt(r_string _name, r_int32 _value)
	{
		if (m_script)
		{
			auto variables = m_script->getVariables();
			for (r_int32 i = 0; i < (r_int32)variables->size(); i++)
				if ((*variables)[i]->name == _name)
					(*variables)[i]->function(m_script->getStatePtr(), (r_void*)&_value, _name);
		}
	}

	r_int32 LuaScript::getInt(r_string _name)
	{
		if (m_script)
			return luabridge::getGlobal(m_script->getStatePtr(), _name.c_str()).cast<r_int32>();

		return 0;
	}

	r_void LuaScript::setString(r_string _name, r_string _value)
	{
		if (m_script)
		{
			auto variables = m_script->getVariables();
			for (r_int32 i = 0; i < (r_int32)variables->size(); i++)
				if ((*variables)[i]->name == _name)
					(*variables)[i]->function(m_script->getStatePtr(), (r_void*)_value.c_str(), _name);
		}
	}

	r_string LuaScript::getString(r_string _name)
	{
		if (m_script)
			return luabridge::getGlobal(m_script->getStatePtr(), _name.c_str()).cast<r_string>();

		return "";
	}

	r_void LuaScript::callFunction(r_string _name)
	{
		luabridge::LuaRef* function = m_script->initRef(_name.c_str());

		if (function)
		{
			GMK_LUA_CALL((*function)())
			delete function;
		}
	}
}