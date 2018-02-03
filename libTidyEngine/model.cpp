/*
TidyEngine
Copyright (C) 2017 Jakob Sinclair

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

#include "model.hpp"
#include "modelrenderer.hpp"
#include "shader.hpp"

Model::Model()
{
    ;
}

Model::~Model()
{
    ;
}

std::string Model::Type()
{
    return "Model";
}

void Model::AddMesh(std::shared_ptr<Mesh> m)
{
    m_Meshes.push_back(m);
}

void Model::Draw(Shader *shader, bool textured)
{
    for (auto i: m_Meshes) {
        if (i.get()->Textured() == textured) {
            i.get()->Render(shader);
        }
    }
}