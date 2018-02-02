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

#include <algorithm>
#include "system.hpp"
#include "entity.hpp"
#include "entitymanager.hpp"

void ISystem::Execute()
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