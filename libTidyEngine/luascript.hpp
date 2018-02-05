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
