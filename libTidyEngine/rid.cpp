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

ResourcePointers::ResourcePointers()
{
	tex = nullptr;
}

ResourcePointers::~ResourcePointers()
{
	;
}

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

void RID::SetResource(Texture *res)
{
	m_ID = ID::Texture;
	m_Pointers.tex = res;
}

void RID::SetResource(Sample *res)
{
	m_ID = ID::Sample;
	m_Pointers.sample = res;
}

void RID::SetResource(Renderable *res)
{
	m_ID = ID::Renderable;
	m_Pointers.render = res;
}

void RID::SetResource(Spritesheet *res)
{
	m_ID = ID::Spritesheet;
	m_Pointers.sheet = res;
}

void RID::SetResource(Shader *res)
{
	m_ID = ID::Shader;
	m_Pointers.shader = res;
}

void *RID::Data()
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
	return nullptr;
}