#ifndef SFGMKR_LUA_HPP
#define SFGMKR_LUA_HPP

#include "stdafx.h"

namespace gmk
{
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

		sLUA_VARIABLE()
			: name("NULL"), type(eLUA_VARIABLE_TYPE::LUA_ERROR), data(0), function(0)
		{

		}
	};

	class Lua
	{
	public:

		Lua(GameObject* _gameobject);
		~Lua();

		r_void init(GameObject* _gameobject);
		r_void close();

		r_void loadFile(r_string _path);

		luabridge::LuaRef* initRef(r_string _func);
		r_void resetRefs();

		r_void onStart();
		r_void onUpdate();

		r_void onPhysicEnter();
		r_void onPhysicCollisionEnter(GameObject* _gameobject);
		r_void onPhysicCollision(GameObject* _gameobject);
		r_void onPhysicCollisionExit(GameObject* _gameobject);
		r_void onPhysicExit();

		r_void onVariablesRefresh();

		lua_State* getStatePtr();

		gmk::vector<sLUA_VARIABLE*>* getVariables();

		r_void emptyVariables();
		r_void parseVariables(r_string _path);

		static r_void print(r_string _message);

		static GameObject* findObjectByName(r_string _name);
		static r_void removeGameObject(GameObject* _gameobject);

		template <class T>
		friend r_void SetGlobal(lua_State* _state, r_void* _valuePtr, r_string _name)
		{
			luabridge::setGlobal<T>(_state, *(T*)_valuePtr, _name.c_str());
		}

	protected:

		gmk::vector<sLUA_VARIABLE*> m_Variables;

		r_void openlibs();

		luabridge::LuaRef* m_onStart = 0;
		luabridge::LuaRef* m_onUpdate = 0;

		luabridge::LuaRef* m_onPhysicEnter = 0;
		luabridge::LuaRef* m_onPhysicCollisionEnter = 0;
		luabridge::LuaRef* m_onPhysicCollision = 0;
		luabridge::LuaRef* m_onPhysicExit = 0;

		lua_State* m_state;
	};
}

#endif