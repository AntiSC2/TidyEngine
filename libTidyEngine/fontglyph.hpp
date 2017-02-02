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

#pragma once

#include "rect2d.hpp"

class FontGlyph: public Rect2D {
public:
	FontGlyph();
	FontGlyph(float x, float y, float w, float h, GLuint tex);
	~FontGlyph();

	virtual void SetPenX(int32_t pen_x);
	virtual void SetPenY(int32_t pen_y);
	virtual int32_t GetPenX();
	virtual int32_t GetPenY();
	virtual void SetAdvanceX(int32_t pen_x);
	virtual void SetAdvanceY(int32_t pen_y);
	virtual int32_t GetAdvanceX();
	virtual int32_t GetAdvanceY();
protected:
	int32_t m_Left = 0; /* Distance in pixels from the left side */
	int32_t m_Top = 0; /* Distance in pixels from the top side */
	int32_t m_AdvanceX = 0;
	int32_t m_AdvanceY = 0;
	int32_t m_OffsetBaseline = 0;
};
