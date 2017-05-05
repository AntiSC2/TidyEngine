/*
TidyEngine
Copyright (C) 2016 Jakob Sinclair

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
Contact the author at: jakob.sinclair99@gmail.com
*/

#include "luascript.hpp"
#include "entitymanager.hpp"

LuaScript::LuaScript()
{
	;
}

LuaScript::LuaScript(const std::string &file)
{
	m_L = luaL_newstate();
	if (LoadScript(file) == false)
		m_L = nullptr;
}

LuaScript::~LuaScript()
{
	if (m_L != nullptr) {
		lua_close(m_L);
		m_L = nullptr;
	}
}

std::string LuaScript::Type()
{
	return "LuaScript";
}

bool LuaScript::LoadScript(const std::string &file)
{
	if (m_L == nullptr)
		m_L = luaL_newstate();

	if (luaL_loadfile(m_L, file.c_str()) || lua_pcall(m_L, 0, 0, 0)) {
		printf("Warning: could not load script %s!\n", file.c_str());
		return false;
	}

	return true;
}

bool LuaScript::Lua_GetToStack(const std::string &name)
{
	m_Level = 0;
	std::string var = "";

	for (uint32_t i = 0; i < name.size(); i++) {
		if(name[i] == '.') {
			if (m_Level == 0)
				lua_getglobal(m_L, var.c_str());
			else
				lua_getfield(m_L, -1, var.c_str());
		
			if (lua_isnil(m_L, -1)) {
				printf("Warning: %s is not in stack!\n", name.c_str());
				return false;
			} else {
				var = "";
				m_Level++;
			}
		} else {
			var += name[i];
		}
	}

	if (m_Level == 0)
		lua_getglobal(m_L, var.c_str());
	else
		lua_getfield(m_L, -1, var.c_str());

	if (lua_isnil(m_L, -1)) {
		printf("Warning: %s is not in stack!\n", name.c_str());
		return false;
	}

	return true;
}

void LuaScript::CleanStack()
{
	int n = lua_gettop(m_L);
	lua_pop(m_L, n);
}

template<typename T>
T LuaScript::Get(const std::string &name)
{
	if (!m_L) {
		printf("Warning: script is not loaded!\n");
		return Lua_GetDefault<T>();
	}

	T result;
	if (Lua_GetToStack(name)) {
		result = Lua_Get<T>(name);
	} else {
		result = Lua_GetDefault<T>();
	}

	lua_pop(m_L, m_Level + 1);
	return result;
}

template<typename T>
T LuaScript::Lua_Get(const std::string &name)
{
	return 0;
}

template<>
bool LuaScript::Lua_Get(const std::string &name)
{
	return (bool)lua_toboolean(m_L, -1);
}

template<>
float LuaScript::Lua_Get(const std::string &name)
{
	if (lua_isnumber(m_L, -1) == false)
		printf("Warning: Lua var %s is not a number!\n", name.c_str());
	return (float)lua_tonumber(m_L, -1);
}

template<>
int LuaScript::Lua_Get(const std::string &name)
{
	if (lua_isnumber(m_L, -1) == false)
		printf("Warning: Lua var %s is not a number!\n", name.c_str());
	return (int)lua_tonumber(m_L, -1);
}

template<>
std::string LuaScript::Lua_Get(const std::string &name)
{
	if (lua_isstring(m_L, -1)) {
		return std::string(lua_tostring(m_L, -1));
	} else {
		printf("Warning: Lua var %s is not a string!\n", name.c_str());
		return "null";
	}
}

template<typename T>
T LuaScript::Lua_GetDefault()
{
	return 0;
}

template<>
std::string LuaScript::Lua_GetDefault()
{
	return "null";
}
