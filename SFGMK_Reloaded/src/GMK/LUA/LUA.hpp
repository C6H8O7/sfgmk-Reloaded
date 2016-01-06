#ifndef SFGMKR_LUA_HPP
#define SFGMKR_LUA_HPP

#define GMK_LUA_CALL(F)			{																					\
									try {																			\
										F;																			\
									} catch (std::exception& e) {													\
										std::cout << "[LUA ERROR]: " << e.what() << std::endl;						\
									}																				\
								}																					\

namespace gmk
{
	lua_State* lua_gmk_init(GameObject* _gameobject);
	r_void lua_gmk_close(lua_State** _state);

	r_void lua_gmk_call(luabridge::LuaRef& _ref);

	r_void lua_print(r_string _message);
	GameObject* lua_findObjectByName(r_string _name);
	r_void lua_removeGameObject(GameObject* _gameobject);
}

#endif