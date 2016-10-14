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

#include "rid.hpp"

RID::RID()
{
	;
}

RID::~RID()
{
	;
}

ID RID::State()
{
	return m_ID;
}

std::shared_ptr<void> RID::Data()
{
	if (m_ID == ID::None)
		return nullptr;
	else if (m_ID == ID::Texture)
		return m_Pointers.tex;
	else if (m_ID == ID::Sample)
		return m_Pointers.sample;
	else if (m_ID == ID::Renderable)
		return m_Pointers.render;
	else if (m_ID == ID::Spritesheet)
		return m_Pointers.sheet;
	else if (m_ID == ID::Shader)
		return m_Pointers.shader;
}