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

class Model;

class ModelRenderer : public IRenderer {
public:
	ModelRenderer();
	virtual ~ModelRenderer();

	virtual void Initialise(Shader *shader);
	virtual void Initialise(Shader *shader, Shader *color, Shader *grid = nullptr);
	virtual void Begin();
	virtual void Draw(Model *m);
	virtual void End();
	virtual void Present();
	virtual void DebugGrid();
protected:
	GLuint m_GridID = 0;
	PointLight m_Light;
	Shader *m_ColorShader = nullptr;
	Shader *m_Grid = nullptr;
	std::vector<Model*> m_Models;
};