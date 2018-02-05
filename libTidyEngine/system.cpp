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

#include <algorithm>
#include "system.hpp"
#include "entity.hpp"
#include "entitymanager.hpp"

void ISystem::Execute(bool fixed)
{
	;
}

void ISystem::SetManager(EntityManager *manager)
{
	m_EM = manager;
}

void ISystem::RegisterComponent(std::type_index index)
{
	if (std::find(m_Index.begin(), m_Index.end(), index) == m_Index.end())
		m_Index.push_back(index);
}

void ISystem::RemoveComponent(std::type_index index)
{
	auto it = std::find(m_Index.begin(), m_Index.end(), index);
	if (it != m_Index.end())
		m_Index.erase(it);
}

bool ISystem::CheckComponents(Entity *e)
{
	for (auto &i: m_Index) {
		if (e->HasComponent(i) == false)
			return false;
	}

	return true;
}

void ISystem::AddEntity(Entity *e)
{
	if (e == nullptr)
		return;

	m_Entities[e->GetName()] = e;
}

bool ISystem::HasEntity(std::string name)
{
	if (m_Entities.find(name) != m_Entities.end())
		return true;
	else
		return false;
}

void ISystem::RemoveEntity(std::string name)
{
	m_Entities.erase(name);
}

size_t ISystem::GetFrameRate()
{
	return 60;
}