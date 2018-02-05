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

#include <memory>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "bitmap.hpp"
#include "model.hpp"
#include "sample.hpp"

class Texture;

class IOManager {
public:
	IOManager();
	~IOManager();

	TE::Bitmap *LoadImage(std::string filepath);
	std::string ReadFile(std::string filepath);
	Model LoadModel(std::string filepath);
	bool LoadVorbis(std::string filepath, Sample *out);
protected:
	void ProcessTree(Model &m, aiNode *node, const aiScene *scene, std::string dir);
	void ProcessNode(Model &m, aiNode *node, const aiScene *scene, std::string dir);
	std::shared_ptr<Mesh> ProcessMesh(aiMesh *mesh, const aiScene *scene, std::string dir);
	std::vector<Texture*> LoadMatTextures(aiMaterial *mat, aiTextureType type, std::string dir);
} extern IO;
