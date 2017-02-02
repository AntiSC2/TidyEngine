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

#include "fontglyph.hpp"

FontGlyph::FontGlyph()
{
	;
}

FontGlyph::FontGlyph(float x, float y, float w, float h, GLuint tex)
{
	SetRect(x, y, w, h);
	m_Tex = tex;
}

FontGlyph::~FontGlyph()
{
	;
}

void FontGlyph::SetPenX(int32_t pen_x)
{
	m_Left = pen_x;
}

void FontGlyph::SetPenY(int32_t pen_y)
{
	m_Top = pen_y;
}

int32_t FontGlyph::GetPenX()
{
	return m_Left;
}

int32_t FontGlyph::GetPenY()
{
	return m_Top;
}

void FontGlyph::SetAdvanceX(int32_t pen_x)
{
	m_AdvanceX = pen_x;
}

void FontGlyph::SetAdvanceY(int32_t pen_y)
{
	m_AdvanceY = pen_y;
}

int32_t FontGlyph::GetAdvanceX()
{
	return m_AdvanceX;
}

int32_t FontGlyph::GetAdvanceY()
{
	return m_AdvanceY;
}
