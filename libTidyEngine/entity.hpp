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

#include <memory>
#include <vector>
#include <string>
#include "component.hpp"
#include "renderable.hpp"

class Entity {
public:
	template<typename C>
	Entity(std::string name, std::vector<std::shared> components = {}) : m_Name(name), m_Components(components)
	{
		for (auto i: m_Components) {
			if (i.Data()->Type() == "Renderable")
				m_Graphics.push_back(static_cast<Renderable *>(i.Data()));
		}
	}
	virtual ~Entity();

	virtual void Update(double delta = 0.0f);
	virtual std::vector<Renderable *> &Draw();
	template<typename C>
	virtual void AddComponent(std::unique_ptr<C> &&component);
	template<typename C>
	virtual void RemoveComponent();
	template<typename C>
	virtual C &GetComponent();
	virtual void SetName(std::string name);
protected:
	std::string m_Name = "";
	std::vector<std::unique_ptr<Component>> m_Components = {};
	std::vector<Renderable *> m_Graphics = {};
};