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

#include <typeindex>
#include <string>
#include <map>
#include <vector>

class Entity;
class EntityManager;

class ISystem {
public:
	ISystem() = default;
	virtual ~ISystem() = default;

	virtual void Execute();
	virtual void SetManager(EntityManager *manager);
	virtual void RegisterComponent(std::type_index index);
	virtual void RemoveComponent(std::type_index index);
	virtual bool CheckComponents(Entity *e);
	virtual void AddEntity(Entity *e);
	virtual bool HasEntity(std::string name);
	virtual void RemoveEntity(std::string name);
	virtual size_t GetFrameRate();
	virtual std::string GetType() = 0;
protected:
	EntityManager *m_EM = nullptr;
	std::map<std::string, Entity*> m_Entities;
	std::vector<std::type_index> m_Index;
};