#ifndef SFGMKR_LUA_HPP
#define SFGMKR_LUA_HPP

namespace gmk
{
	enum eLUA_VARIABLE_TYPE
	{
		LUA_INT,
		LUA_FLOAT,
		LUA_STRING
	};

	class Lua
	{
	public:

		struct sLUA_VARIABLE
		{
			r_string name;
			eLUA_VARIABLE_TYPE type;
		};

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
		r_void onPhysicCollision(GameObject* _gameobject);
		r_void onPhysicExit();

		static r_void print(r_string _message);

		static GameObject* findObjectByName(r_string _name);
		static r_void removeGameObject(GameObject* _gameobject);

	protected:

		r_void openlibs();

		std::vector<r_string> parseFile(r_string _path);

		luabridge::LuaRef* m_onStart = 0;
		luabridge::LuaRef* m_onUpdate = 0;

		luabridge::LuaRef* m_onPhysicEnter = 0;
		luabridge::LuaRef* m_onPhysicCollision = 0;
		luabridge::LuaRef* m_onPhysicExit = 0;

		lua_State* m_state;
	};
}

#endif