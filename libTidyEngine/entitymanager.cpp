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

#include "entitymanager.hpp"
#include "entity.hpp"
#include "renderer.hpp"
#include "camera.hpp"

EntityManager::EntityManager()
{
	;
}

EntityManager::~EntityManager()
{
	m_CurrentCamera = nullptr;
}

template<typename E>
E &EntityManager::AddEntity(std::string name, std::unique_ptr<E> &&e)
{
	auto ent = *e;
	static_assert(std::is_base_of<Entity, E>::value, "Error: tried to add non-entity object to manager!\n");

	if (m_Entities.find(name) != m_Entities.end()) {
		printf("Warning: entity %s already exists!\n", name.c_str());
		return e;
	}

	m_Entities[name] = std::move(e);
	return ent;
}

Entity &EntityManager::GetEntity(std::string name)
{
	if (m_Entities.find(name) != m_Entities.end())
		return *m_Entities[name];
	else
		throw std::runtime_error("Error: could not find entity with name " + name + "!\n");
}

void EntityManager::RemoveEntity(std::string name)
{
	m_Entities.erase("name");
}