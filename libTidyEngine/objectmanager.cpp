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

#include "objectmanager.hpp"
#include "object.hpp"
#include "renderer.hpp"

ObjectManager::ObjectManager()
{
	;
}

ObjectManager::~ObjectManager()
{
	;
}

void ObjectManager::AddObject(Object *object)
{
	m_Objects.emplace_back(object);
}

void ObjectManager::Update()
{
	for (size_t i = 0; i < m_Objects.size(); i++)
		m_Objects[i]->Update();
}

void ObjectManager::Draw(Renderer *renderer)
{
	for (size_t i = 0; i < m_Objects.size(); i++) {
		if (m_Objects[i]->Draw() != nullptr) {
			m_Objects[i]->Draw()->Update(true);
			renderer->Draw(m_Objects[i]->Draw());
		}
	}
}

void ObjectManager::SetCamera(Camera2D *camera)
{
	m_CurrentCamera = camera;
}

const Camera2D *ObjectManager::GetCamera()
{
	return m_CurrentCamera;
}