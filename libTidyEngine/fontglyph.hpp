/*
 * TidyEngine
 * Copyright (c) 2018 Jakob Sinclair <sinclair.jakob@mailbox.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#pragma once

#include "renderable.hpp"

class FontGlyph: public Renderable {
public:
	FontGlyph();
	FontGlyph(float x, float y, float w, float h);
	~FontGlyph();

	virtual void SetPos(float x, float y);
	virtual void SetColor(glm::vec4 color);
	virtual void SetTexUV(glm::vec4 coords);
	virtual void SetPenX(int32_t pen_x);
	virtual void SetPenY(int32_t pen_y);
	virtual int32_t GetPenX();
	virtual int32_t GetPenY();
	virtual void SetAdvanceX(int32_t pen_x);
	virtual void SetAdvanceY(int32_t pen_y);
	virtual int32_t GetAdvanceX();
	virtual int32_t GetAdvanceY();
	virtual glm::vec4 GetRect();
protected:
	glm::vec4 m_Rect = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	glm::vec4 m_Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 m_TexCoords = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	int32_t m_Left = 0; /* Distance in pixels from the left side */
	int32_t m_Top = 0; /* Distance in pixels from the top side */
	int32_t m_AdvanceX = 0;
	int32_t m_AdvanceY = 0;
	int32_t m_OffsetBaseline = 0;
};
