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
#include "lua.hpp"

class LuaScript {
public:
	LuaScript();
	LuaScript(const std::string &file);
	~LuaScript();
	
	bool LoadScript(const std::string &file);
	bool Lua_GetToStack(const std::string &name);

	template<typename T>
	T Get(const std::string &name);
	template<typename T>
	T Lua_Get(const std::string &name);
	template<typename T>
	T Lua_GetDefault();
protected:
	void Error(const std::string &name);
	lua_State *m_L = nullptr;
	uint32_t m_Level = 0;
};
