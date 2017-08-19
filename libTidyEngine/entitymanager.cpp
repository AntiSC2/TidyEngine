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

void EntityManager::AddEntity(Entity *entity)
{
	m_Entities.emplace_back(entity);
}

void EntityManager::Update()
{
	for (size_t i = 0; i < m_Entities.size(); i++)
		m_Entities[i]->Update();
}

void EntityManager::Draw(Renderer *renderer)
{
	for (size_t i = 0; i < m_Entities.size(); i++) {
		std::vector<Renderable *> temp = m_Entities[i]->Draw();
		if (temp.size() != 0) {
			for (auto i: temp) {
				i->Render();
				renderer->Draw(i);
			}
		}
	}
}

void EntityManager::SetCamera(Camera *camera)
{
	m_CurrentCamera = camera;

	if (camera == nullptr)
		return;

	this->AddEntity(camera);
}

Camera *EntityManager::GetCamera()
{
	return m_CurrentCamera;
}
