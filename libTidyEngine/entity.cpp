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

#include "entity.hpp"

Entity::~Entity()
{
	;
}

void Entity::Update(float delta)
{
	for (auto i : m_Resources) {
		if (i.Data()->Type() == "Renderable") {
			Renderable *temp = static_cast<Renderable *>(i.Data());
			temp->Update(false);
		}
	}
}

Renderable *Entity::Draw()
{
	for (auto i : m_Resources) {
		if (i.Data()->Type() == "Renderable") {
			Renderable *temp = static_cast<Renderable *>(i.Data());
			return temp;
		}
	}
	return nullptr;
}

void Entity::SetName(std::string name)
{
	m_Name = name;
}

void Entity::SetScript(std::string script)
{
	m_Script = script;
}