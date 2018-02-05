/*
 * TidyEngine
 * Copyright (c) 2018 Jakob Sinclair <sinclair.jakob@mailbox.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
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

void LuaScript::LoadGetKeysFunction()
{
	std::string code =
		R"(function getKeys(t)
		s = {}
		for k, v in pairs(t) do
			table.insert(s, k)
			end 
		return s 
		end)";
	luaL_dostring(m_L, code.c_str());
}

std::vector<std::string> LuaScript::GetTableKeys(const std::string &table)
{
	lua_getglobal(m_L, "GetKeys");
	if (lua_isnil(m_L, -1)) {
		printf("Lua Warning: Get keys function is not loaded. Loading...\n");
		LoadGetKeysFunction();
		lua_getglobal(m_L, "getKeys");
	}

	std::vector<std::string> keys;
	Lua_GetToStack(table);
	lua_pcall(m_L, 1, 1, 0);

	while (lua_next(m_L, -2)) {
		if (lua_type(m_L, -1) == LUA_TSTRING) {
			keys.push_back(lua_tostring(m_L, -1));
		}
		lua_pop(m_L, 1);
	}
	
	lua_settop(m_L, 0);
	return keys;
}

void LuaScript::CleanStack()
{
	int n = lua_gettop(m_L);
	lua_pop(m_L, n);
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

template<>
std::string LuaScript::Lua_GetDefault()
{
	return "null";
}
