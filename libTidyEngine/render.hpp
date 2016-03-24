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

struct GLFWwindow;
class Shader;

#include <vector>
#include <map>
#include <memory>
#include <string>
#include "batch.hpp"

class Render {
public:
	Render();
	~Render();

	void LoadShaders(std::string name, std::string v, std::string f,
			std::vector<std::string> attributes = {});
        Shader *GetShader(std::string name);
        Batch &GetBatch();
	void Clear();
	void Present(GLFWwindow *window);
private:
	std::map<std::string, std::unique_ptr<Shader>> m_Shaders;
	Batch m_Batch;
};
