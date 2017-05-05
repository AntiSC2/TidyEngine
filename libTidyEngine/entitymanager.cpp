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

#include "entitymanager.hpp"
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

void EntityManager::AddEntity(Entity *entity)
{
	m_Entities.emplace_back(entity);
}

void EntityManager::Update()
{
	for (size_t i = 0; i < m_Objects.size(); i++)
		m_Entities[i]->Update();
}

void EntityManager::Draw(Renderer *renderer)
{
	for (size_t i = 0; i < m_Objects.size(); i++) {
		if (m_Entities[i]->Draw() != nullptr) {
			m_Entities[i]->Draw()->Update(true);
			renderer->Draw(m_Entities[i]->Draw());
		}
	}
}

void EntityManager::SetCamera(Camera2D *camera)
{
	m_CurrentCamera = camera;
}

const Camera2D *EntityManager::GetCamera()
{
	return m_CurrentCamera;
}