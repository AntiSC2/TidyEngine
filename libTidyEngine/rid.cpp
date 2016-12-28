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
#include "texture.hpp" 
#include "sample.hpp"
#include "renderable.hpp"
#include "sheet.hpp"
#include "shader.hpp"

RID::RID()
{
	;
}

RID::RID(Resource *res)
{
	m_Data.reset(res);
}

RID::~RID()
{
	;
}

void RID::SetResource(Texture *res)
{
	/* std::any moves the content when it is a double reference, this
	   ensures that we don't leave dangling pointers around
	*/
	m_Data.reset(new boost::any(res));
}

void RID::SetResource(Sample *res)
{
	m_Data.reset(new boost::any(res));
}

void RID::SetResource(Renderable *res)
{
	m_Data.reset(new boost::any(res));
}

void RID::SetResource(Sheet *res)
{
	m_Data.reset(new boost::any(res));
}

void RID::SetResource(Shader *res)
{
	m_Data.reset(new boost::any(res));
}

Resource *RID::Data() const
{
	return m_Data.get();
}
