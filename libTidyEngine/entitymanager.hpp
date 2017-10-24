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

#pragma once

class Entity;
class IRenderer;
class ISystem;
class Camera;

#include <memory>
#include <unordered_map>
#include <typeindex>

class EntityManager {
public:
	EntityManager();
	virtual ~EntityManager();

	virtual void Update();
	template<typename E>
	E &AddEntity(std::shared_ptr<E> &&e);
	Entity &GetEntity(std::string name);
	void RemoveEntity(std::string name);

	template<typename S, typename ...Args>
	S &CreateSystem(Args &&...args);
	void AddSystem(std::unique_ptr<ISystem> &&system, std::type_index i);
	template<typename S>
	S &GetSystem();
	template<typename S>
	void RemoveSystem();
protected:
	std::unordered_map<std::type_index, std::unique_ptr<ISystem>> m_Systems;
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

template<typename S, typename ...Args>
S &EntityManager::CreateSystem(Args &&...args)
{
	static_assert(std::is_base_of<ISystem, S>::value, "Error: tried to create a non-system object with manager!\n");	
	S *sys_p = new S(std::forward<Args>(args)...);	
	S &sys = *sys_p;
	AddSystem(std::unique_ptr<ISystem>(static_cast<ISystem*>(sys_p)), std::type_index(typeid(S)));
	return sys;
}

template<typename S>
S &EntityManager::GetSystem()
{
	static_assert(std::is_base_of<ISystem, S>::value, "Error: tried to retrieve non-system object from manager!\n");
	if (m_Systems.find(std::type_index(typeid(S))) == m_Systems.end())
		throw std::runtime_error("Error: could not find system of that type in manager!\n");
	auto &sys = static_cast<S&>(*m_Systems[std::type_index(typeid(S))].get());
	return sys;
}

template<typename S>
void EntityManager::RemoveSystem()
{
	static_assert(std::is_base_of<ISystem, S>::value, "Error: tried to remove non-system object from manager!\n");
	m_Systems.erase(std::type_index(typeid(S)));
}