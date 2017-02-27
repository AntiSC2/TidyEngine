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
#include "objectmanager.hpp"

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

template<>
std::string LuaScript::lua_getdefault()
{
	return "null";
}

template<typename T>
T LuaScript::Get(const std::string &name)
{
	if (m_L == nullptr) {
		Error();
		return lua_getdefault<T>();
	}

	/*T result;
	if (lua_gettostack(name)) {
		result = lua_get<T>(name)
	} else {
		result = lua_getdefault<T>();
	}

	lua_pop(m_L, m_Level + 1);*/
}

void LuaScript::Error(const std::string &name)
{
	printf("Error: could not get variable %s from script!\n" name.c_str());
}
