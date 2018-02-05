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

#include "entitymanager.hpp"
#include "system.hpp"
#include "entity.hpp"
#include "renderer.hpp"

EntityManager::EntityManager()
{
	;
}

EntityManager::~EntityManager()
{
	;
}

void EntityManager::Update()
{
	for (auto &e: m_Entities) {
		if (e.second->Changed() == true) {
			for (auto &i: m_Systems) {
				if (i.second->CheckComponents(e.second.get()) == false) {
					i.second->RemoveEntity(e.second->GetName());
				} else {
					i.second->AddEntity(e.second.get());
				}
			}
		}	
	}
	for (auto &i: m_Systems)
		i.second->Execute();
}

Entity &EntityManager::GetEntity(std::string name)
{
	if (m_Entities.find(name) != m_Entities.end())
		return *m_Entities[name];
	else
		throw std::runtime_error("Error: could not find entity with name: \"" + name + "\"\n");
}

void EntityManager::RemoveEntity(std::string name)
{
	m_Entities.erase(name);
	for (auto &i: m_Systems) {
		i.second->RemoveEntity(name);
	}
}

void EntityManager::AddSystem(std::unique_ptr<ISystem> &&system, std::type_index i)
{
	system->SetManager(this);
	m_Systems[i] = std::move(system);
}