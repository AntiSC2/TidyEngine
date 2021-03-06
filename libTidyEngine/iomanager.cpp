﻿/*
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

#include "iomanager.hpp"
#include <fstream>
#include <al.h>
#include <vorbis/vorbisfile.h>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "cache.hpp"

IOManager IO;

IOManager::IOManager()
{
	;
}

IOManager::~IOManager()
{

}

TE::Bitmap *IOManager::LoadImage(std::string filepath)
{
	TE::Bitmap *bitmap = new TE::Bitmap;
	bitmap->Data = stbi_load(filepath.c_str(), &bitmap->Width, &bitmap->Height, &bitmap->NrChannels, 0);

	if (bitmap->Data == nullptr) {
		printf("Warning: image %s has an unsupported file format!\n", filepath.c_str());
		return nullptr;
	}

	return bitmap;
}

std::string IOManager::ReadFile(std::string filepath)
{
	std::ifstream source(filepath);
	if (source.fail()) {
		printf("Warning: failed to open %s!\n", filepath.c_str());
		return "";
	}

	std::string source_contents = "";
	std::string line = "";

	while (std::getline(source, line))
		source_contents += line + '\n';

	source.close();
	return source_contents;
}

Model IOManager::LoadModel(std::string filepath)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_CalcTangentSpace | aiProcess_RemoveRedundantMaterials | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		printf("Warning: could not load mesh %s\n", filepath.c_str());
		printf("ASSIMP WARNING: %s\n", importer.GetErrorString());
	}

	Model m;
	std::string dir = filepath.substr(0, filepath.find_last_of('/')) + '/';
	ProcessNode(m, scene->mRootNode, scene, dir);
	ProcessTree(m, scene->mRootNode, scene, dir);
	return m;
}

void IOManager::ProcessTree(Model &m, aiNode *node, const aiScene *scene, std::string dir)
{
	for (uint32_t i = 0; i < node->mNumChildren; i++) {
		ProcessNode(m, node->mChildren[i], scene, dir);
	}

	for (uint32_t i = 0; i < node->mNumChildren; i++) {
		ProcessTree(m, node->mChildren[i], scene, dir);
	}
}

void IOManager::ProcessNode(Model &m, aiNode *node, const aiScene *scene, std::string dir)
{
	for (size_t i = 0; i < node->mNumMeshes; i++) {
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		std::shared_ptr<Mesh> temp = ProcessMesh(mesh, scene, dir);
		m.AddMesh(temp);
	}
}

std::shared_ptr<Mesh> IOManager::ProcessMesh(aiMesh *mesh, const aiScene *scene, std::string dir)
{
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 spec;
    std::vector<Texture*> diffuse_textures;
	std::vector<Texture*> spec_textures;
	Material *material = nullptr;

    for (uint64_t i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
		vertex.Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec3 vector;

        vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;

		if (mesh->mTextureCoords[0])
		{
		    glm::vec2 vec;
		    vec.x = mesh->mTextureCoords[0][i].x; 
		    vec.y = mesh->mTextureCoords[0][i].y;
		    vertex.TexUV = vec;
		}
		else {
			vertex.TexUV = glm::vec2(0.0f, 0.0f);
		}
        vertices.push_back(vertex);
	}

	for(uint64_t i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for(uint64_t j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
 
    if(mesh->mMaterialIndex >= 0) {	
		aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];
		aiColor4D a;
		aiColor4D d;
		aiColor4D s;
		aiGetMaterialColor(mat, AI_MATKEY_COLOR_AMBIENT, &a);
		aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d); 
		aiGetMaterialColor(mat, AI_MATKEY_COLOR_SPECULAR, &s);

		ambient.r = a.r;
		ambient.g = a.g;
		ambient.b = a.b;
		ambient.a = a.a;

		diffuse.r = d.r;
		diffuse.g = d.g;
		diffuse.b = d.b;
		diffuse.a = d.a;

		spec.r = s.r;
		spec.g = s.g;
		spec.b = s.b;
		spec.a = s.a;

		diffuse_textures = LoadMatTextures(mat, aiTextureType_DIFFUSE, dir);
		spec_textures = LoadMatTextures(mat, aiTextureType_SPECULAR, dir);
		float shine = 32.0f;

		if (aiGetMaterialFloat(mat, AI_MATKEY_SHININESS, &shine) != AI_SUCCESS) {
			printf("Warning: could not get shininess from material!\n");
			shine = 32.0f;
		}

		material = new Material(ambient, diffuse, spec, diffuse_textures, spec_textures, shine * 2.0f);
    }
	std::shared_ptr<Mesh> temp;
    temp.reset(new Mesh(vertices, indices, material));
	return temp;
}

std::vector<Texture*> IOManager::LoadMatTextures(aiMaterial *mat, aiTextureType type, std::string dir)
{
	std::vector<Texture*> textures;
	for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		Texture *temp = Res.LoadTex(dir + str.C_Str());
		if (temp != nullptr)
			textures.push_back(temp);
	}
	return textures;
}

size_t IfsRead(void *out, size_t size, size_t bytesize, void *in)
{
	auto& stream = *static_cast<std::ifstream *> (in);
	stream.read(static_cast<char *> (out), size * bytesize);

	return stream.gcount();
}

int IfsClose(void *in)
{
	auto& stream = *static_cast<std::ifstream *> (in);
	stream.close();

	return 0;
}

bool IOManager::LoadVorbis(std::string filepath, Sample *out)
{
	std::ifstream source(filepath, std::ifstream::binary);
	
	if (source.is_open() == false) {
		printf("Warning: failed to open %s!\n", filepath.c_str());
		return false;
	}

	ov_callbacks cbs {IfsRead, nullptr, IfsClose, nullptr};
	OggVorbis_File vorbis;

	if (ov_open_callbacks(&source, &vorbis, nullptr,
	    0, cbs) < 0) {
		ov_clear(&vorbis);
		return false;
	}

	vorbis_info *info = ov_info(&vorbis, -1);	
	char buffer[4096];
	int current_section;
	std::vector<char> pcm;

	while (true) {
		long ret = ov_read(&vorbis, buffer, sizeof(char) * 4096, 
		                   0, 2, 1, &current_section);
		if (ret == 0) {
			break;
		} else if (ret < 0) {
			ov_clear(&vorbis);
			printf("Warning: error in stream %s!\n",
			       filepath.c_str());
			return false;
		} else {
			for (int i = 0; i < ret; i++)
				pcm.push_back(buffer[i]);
		}
	}
	
	ALenum format = (info->channels > 1) ? AL_FORMAT_STEREO16 :
	                                       AL_FORMAT_MONO16;

	out->CreateBuffer(format, pcm.data(), pcm.size(), info->rate);
	ov_clear(&vorbis);
	return true;
}
