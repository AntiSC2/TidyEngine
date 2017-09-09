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

#pragma once

#include <string>
#include <vector>
#include <lua.hpp>
#include "resource.hpp"

class LuaScript: public Resource {
public:
	LuaScript();
	LuaScript(const std::string &file);
	~LuaScript();

	virtual std::string Type();	
	bool LoadScript(const std::string &file);
	bool Lua_GetToStack(const std::string &name);
	void LoadGetKeysFunction();
	std::vector<std::string> GetTableKeys(const std::string &table);
	void CleanStack();

	template<typename T>
	T Get(const std::string &name);
	template<typename T>
	T Lua_Get(const std::string &name);
	template<typename T>
	T Lua_GetDefault();
protected:
	lua_State *m_L = nullptr;
	uint32_t m_Level = 0;
};

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
T LuaScript::Lua_GetDefault()
{
	return 0;
}
