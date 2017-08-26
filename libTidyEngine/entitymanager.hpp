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

class Entity;
class Renderer;
class Camera;

#include <memory>
#include <unordered_map>

class EntityManager {
public:
	EntityManager();
	virtual ~EntityManager();

	template<typename E>
	E &AddEntity(std::unique_ptr<E> &&e);
	Entity &GetEntity(std::string name);
	void RemoveEntity(std::string name);
protected:
	std::unordered_map<std::string, std::unique_ptr<Entity>> m_Entities;
	Camera *m_CurrentCamera = nullptr;
};

template<typename E>
E &EntityManager::AddEntity(std::unique_ptr<E> &&e)
{
	auto &ent = *e;
	std::string name = ent.GetName();
	static_assert(std::is_base_of<Entity, E>::value, "Error: tried to add non-entity object to manager!\n");

	if (m_Entities.find(name) != m_Entities.end()) {
		printf("Warning: entity %s already exists!\n", name.c_str());
		return ent;
	}

	m_Entities[name] = std::move(e);
	return ent;
}