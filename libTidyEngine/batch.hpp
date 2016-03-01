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
#include <GL/glew.h>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include "renderable.hpp"

class Batch {
public:
	Batch();
	virtual ~Batch();

	void Initialise();

	void Begin();
	void End();
	void Draw(const Renderable &object);
	void Present();
private:
	void SortGlyphs();
	void CreateBatches();
	static bool CompareTex(Renderable *a, Renderable *b);

	GLuint m_VBOID = 0;
	GLuint m_VAOID = 0;
	std::vector<Renderable> m_Glyphs;
	std::vector<Renderable*> m_SortedGlyphs;
	std::vector<RenderBatch> m_RenderBatches;
};
