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

RID::RID(ID id, void *data)
{
	m_ID = id;
	m_Data.reset(data);
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
	m_Data.reset(res);
}

void RID::SetResource(Sample *res)
{
	m_ID = ID::Sample;
	m_Data.reset(res);
}

void RID::SetResource(Renderable *res)
{
	m_ID = ID::Renderable;
	m_Data.reset(res);
}

void RID::SetResource(Sheet *res)
{
	m_ID = ID::Sheet;
	m_Data.reset(res);
}

void RID::SetResource(Shader *res)
{
	m_ID = ID::Shader;
	m_Data.reset(res);
}

void *RID::Data()
{
	if (m_ID == ID::None)
		return nullptr;
	else
		return m_Data.get();
}