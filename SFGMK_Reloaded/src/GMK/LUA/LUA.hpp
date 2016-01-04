#ifndef SFGMKR_LUA_HPP
#define SFGMKR_LUA_HPP

namespace gmk
{
	r_void lua_init(lua_State** _state, GameObject* _gameobject);
	r_void lua_close(lua_State** _state);

	r_void lua_call(luabridge::LuaRef& _ref);

	r_void lua_print(r_string _message);
	GameObject* lua_findObjectByName(r_string _name);
	r_void lua_removeGameObject(GameObject* _gameobject);
}

#endif