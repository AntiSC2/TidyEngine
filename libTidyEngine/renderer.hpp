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

class Shader;
class Batch;
class Renderable;

#include <GL/glew.h>
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

class Renderer {
public:
	Renderer();
	virtual ~Renderer();

	virtual void Initialise(Shader *shader, Batch *batch) = 0;
	virtual void Begin();
	virtual void Draw(const Renderable *object);
	virtual void DrawText(std::string text, glm::vec2 pos,
	                      glm::vec4 color);
	virtual void End();
	virtual void Present();
protected:
	Shader *m_Shader = nullptr;
	Batch *m_Batch = nullptr;
	GLuint m_VAOID = 0;
	GLuint m_VBOID = 0;
};
