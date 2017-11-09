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

#include "renderer.hpp"
#include "pointlight.hpp"

class ModelRenderer : public IRenderer {
public:
	ModelRenderer();
	virtual ~ModelRenderer();

	virtual void Initialise(Shader *shader);
	virtual void Present();
protected:
	PointLight m_Light;
	virtual void CreateBatches();
	GLuint m_EBOID = 0;
	std::vector<MeshBatch> m_RenderBatches;
};