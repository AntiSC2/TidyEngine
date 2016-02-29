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
#include <GLFW/glfw3.h>
#include <map>
#include <memory>
#include <vector>
#include "shader.hpp"
#include "error.hpp"
#include "vertex.hpp"
#include "batch.hpp"

class Render2D {
public:
	Render2D();
	~Render2D();

	void LoadShaders(std::string name, std::string v, std::string f,
			std::vector<std::string> attributes = {});
	void UseShader(std::string name);
	void StopShaders();
	Batch& GetBatch();
	void Begin();
	void End();
	void Present(GLFWwindow *window);
private:
	std::map<std::string, std::unique_ptr<Shader>> m_Shaders;
	std::string m_CurrentShader = "";
	Batch SpriteBatch;
};
