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
#include <type_traits>

Entity::~Entity()
{
	;
}

const std::string &Entity::GetName()
{
	return m_Name;
}

void Entity::SetName(std::string name)
{
	m_Name = name;
}

bool Entity::HasComponent(std::type_index index)
{
	if (m_Components.find(index) != m_Components.end())
		return true;
	else
		return false;
}