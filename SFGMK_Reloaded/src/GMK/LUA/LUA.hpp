#ifndef SFGMKR_LUA_HPP
#define SFGMKR_LUA_HPP

#include "stdafx.h"

namespace gmk
{
	class Lua;

	enum eLUA_VARIABLE_TYPE
	{
		LUA_ERROR = 0,
		LUA_STRING = 1,
		LUA_INT = 2,
		LUA_FLOAT = 3
	};

	struct sLUA_VARIABLE
	{
		r_string name;
		eLUA_VARIABLE_TYPE type;
		r_void* data;
		r_void (*function)(lua_State*, r_void*, r_string);
		r_void(*getFunction)(lua_State*, r_void*, r_string);

		sLUA_VARIABLE()
			: name("NULL"), type(eLUA_VARIABLE_TYPE::LUA_ERROR), data(0), function(0)
		{

		}
	};

	class LuaScript
	{
	public:

		LuaScript(Lua* _script);

		r_void setFloat(r_string _name, r_float _value);
		r_float getFloat(r_string _name);

		r_void setInt(r_string _name, r_int32 _value);
		r_int32 getInt(r_string _name);

	protected:

		Lua* m_script;
	};

	class Lua
	{
	public:

		Lua(GameObject* _gameobject);
		~Lua();

		r_void init(GameObject* _gameobject);
		r_void close();

		r_void loadFile(r_string _path);
		r_void loadString(r_int8* _string);

		luabridge::LuaRef* initRef(r_string _func);
		r_void resetRefs();

		r_void onStart();
		r_void onUpdate();

		r_void onPhysicEnter();
		r_void onPhysicCollisionEnter(GameObject* _gameobject);
		r_void onPhysicCollision(GameObject* _gameobject);
		r_void onPhysicExit();

		r_void onPlannerActionStart(gmk::PlannerAction* _action);
		r_void onPlannerActionPerform(gmk::PlannerAction* _action);

		r_void onVariablesRefresh();

		lua_State* getStatePtr();

		gmk::vector<sLUA_VARIABLE*>* getVariables();

		r_void emptyVariables();
		r_void parseVariables(r_string _string);

		static r_void print(r_string _message);

		static GameObject* findObjectByName(r_string _name);
		static r_void removeGameObject(GameObject* _gameobject);
		static GameObject* instantiate(r_string _prefabName);

		r_void updateVariables();

		template <class T>
		friend r_void SetGlobal(lua_State* _state, r_void* _valuePtr, r_string _name)
		{
			luabridge::setGlobal<T>(_state, *(T*)_valuePtr, _name.c_str());
		}

		template <class T>
		friend r_void GetGlobal(lua_State* _state, r_void* _valuePtr, r_string _name)
		{
			*(T*)(_valuePtr) = luabridge::getGlobal(_state, _name.c_str()).cast<T>();
		}

	protected:

		gmk::Lua* m_this;

		GameObject* m_gameobject;

		gmk::vector<sLUA_VARIABLE*> m_Variables;

		r_void openlibs();

		luabridge::LuaRef* m_onStart = 0;
		luabridge::LuaRef* m_onUpdate = 0;

		luabridge::LuaRef* m_onPhysicEnter = 0;
		luabridge::LuaRef* m_onPhysicCollisionEnter = 0;
		luabridge::LuaRef* m_onPhysicCollision = 0;
		luabridge::LuaRef* m_onPhysicExit = 0;

		luabridge::LuaRef* m_onPlannerActionStart = 0;
		luabridge::LuaRef* m_onPlannerActionPerform = 0;

		lua_State* m_state;
	};
}

#endif