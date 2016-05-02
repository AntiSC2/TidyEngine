﻿/*
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

#include "vm.hpp"

LuaVM::LuaVM()
{
	m_State = luaL_newstate();
	luaL_openlibs(m_State);
}

LuaVM::~LuaVM()
{
	lua_close(m_State);
}

int LuaVM::LoadScript(const std::string &file)
{
	return luaL_loadfile(m_State, file.c_str());
}
