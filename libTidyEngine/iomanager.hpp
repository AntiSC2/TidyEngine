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

#include <memory>
#include <string>
#include <FreeImage.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "model.hpp"
#include "sample.hpp"

class Texture;

class IOManager {
public:
	IOManager();
	~IOManager();

	FIBITMAP *LoadImage(std::string filepath);
	std::string ReadFile(std::string filepath);
	Model LoadModel(std::string filepath);
	bool LoadVorbis(std::string filepath, Sample *out);
protected:
	void ProcessTree(Model &m, aiNode *node, const aiScene *scene, std::string dir);
	void ProcessNode(Model &m, aiNode *node, const aiScene *scene, std::string dir);
	std::shared_ptr<Mesh> ProcessMesh(aiMesh *mesh, const aiScene *scene, std::string dir);
	std::vector<Texture*> LoadMatTextures(aiMaterial *mat, aiTextureType type, std::string dir);
} extern IO;
