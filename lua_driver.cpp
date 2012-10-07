#include <iostream>
#include <sstream>

extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

int displayLuaFunction(lua_State*);

int main(int argc, char *argv[])
{
	std::cout<<"[C++] Starting Lua state"<<std::endl;
	lua_State *lua = luaL_newstate();

	std::cout<<"[C++] Loading Lua libraries"<<std::endl;

/*	----PASSING VALUES TO AND FROM LUA ----
	std::cout<<"[C++] Creating the arg table"<<std::endl;

	lua_createtable(lua, 2, 0);
	lua_pushnumber(lua, 1);
	lua_pushnumber(lua,49);
	lua_settable(lua, -3);
	lua_pushnumber(lua, 2);
	lua_pushstring(lua, "Life is a beach");
	lua_settable(lua, -3);
	lua_setglobal(lua, "arg");

	std::cout<<"[C++] Loading Lua script"<<std::endl;
	int status = luaL_loadfile(lua, "communication.lua");
	std::cout<<"      return: "<<status<<std::endl;

	std::cout<<"[C++] Running script..."<<std::endl;
	int result = 0;
	if (status == LUA_OK)
		result = lua_pcall(lua, 0, LUA_MULTRET, 0);
	else
		std::cout<<"      Could not load the script"<<std::endl;

	std::cout<<"[C++] Values returned from the script: "<<std::endl;
	std::stringstream str_buf;
	while (lua_gettop(lua))
	{
		str_buf.str(std::string());
		str_buf<<"      ";
		switch(lua_type(lua, lua_gettop(lua)))
		{
			case LUA_TNUMBER:
				str_buf<<"script returned the number: "<<lua_tonumber(lua, lua_gettop(lua));
				break;
			case LUA_TTABLE:
				str_buf<<"script created a table";
				break;
			case LUA_TSTRING:
				str_buf<<"script returned the string: "<<lua_tostring(lua, lua_gettop(lua));
				break;
			case LUA_TBOOLEAN:
				str_buf<<"script return the boolean: "<<lua_toboolean(lua, lua_gettop(lua));
				break;
			default:
				str_buf<<"script returned an unknown-type value";
		}
		lua_pop(lua,1);
		std::cout<<str_buf.str()<<std::endl;
	}
*/

	luaL_openlibs(lua);

	std::cout<<"[C++] Pushing C++ function"<<std::endl;
	lua_register(lua, "displayLuaFunction", displayLuaFunction);

	std::cout<<"[C++] Loading script"<<std::endl;
	int status = luaL_loadfile(lua, "functional.lua");
	std::cout<<"      return: "<<status<<std::endl;

	std::cout<<"[C++] Running..."<<std::endl;
	int result = 0;
	if (status == LUA_OK)
		result = lua_pcall(lua, 0, LUA_MULTRET, 0);
	else
		std::cout<<"      Could not load script"<<std::endl;


	std::cout<<"[C++] Closing the Lua state"<<std::endl;
	lua_close(lua);
	return 0;
}

int displayLuaFunction(lua_State *l)
{
	int argc = lua_gettop(l);
	std::cout<<"[C++] Function called from Lua with "<<argc<<" input arguments"<<std::endl;
	for (int i = 0; i < argc; i++)
	{
		std::cout<<"      input argument #"<<argc-i<<": "<<lua_tostring(l, lua_gettop(l))<<std::endl;
		lua_pop(l,1);
	}
	std::cout<<"[C++] Returning some values"<<std::endl;
	lua_pushnumber(l, 12);
	lua_pushstring(l, "Peace out");

	//num return values
	return 2;
}