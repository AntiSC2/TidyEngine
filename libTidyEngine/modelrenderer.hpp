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

class Camera;

#include "renderer.hpp"

class ModelRenderer : public Renderer {
public:
	ModelRenderer();
	virtual ~ModelRenderer();

	virtual void Initialise(Shader *shader);
	virtual void Present(const Camera *camera);
protected:
	virtual void CreateBatches();
	float m_Ambient = 0.1f;
	glm::vec3 m_Light = glm::vec3(0.0f, 10.0f, 5.0f);
	glm::vec3 m_LightC = glm::vec3(1.0f, 1.0f, 1.0f);
	GLuint m_EBOID = 0;
	std::vector<MeshBatch> m_RenderBatches;
};