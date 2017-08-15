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

#include "iomanager.hpp"
#include <fstream>
#include <vorbis/vorbisfile.h>
#include <vector>
#include "cache.hpp"
#include "error.hpp"

IOManager IO;

IOManager::IOManager()
{
	;
}

IOManager::~IOManager()
{

}

FIBITMAP *IOManager::LoadImage(std::string filepath)
{
	if (filepath.find(".png") != std::string::npos)
		return FreeImage_Load(FIF_PNG, filepath.c_str(), PNG_DEFAULT);
	else if (filepath.find(".bmp") != std::string::npos)
		return FreeImage_Load(FIF_BMP, filepath.c_str(), BMP_DEFAULT);
	else if (filepath.find(".jpeg") != std::string::npos)
		return FreeImage_Load(FIF_JPEG, filepath.c_str());

	printf("Warning: image %s has an unsupported file format!\n",
		       filepath.c_str());
	return nullptr;
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
	const aiScene *scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

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
		Mesh temp = ProcessMesh(mesh, scene, dir);
		m.AddMesh(temp);
	}
}

Mesh IOManager::ProcessMesh(aiMesh *mesh, const aiScene *scene, std::string dir)
{
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
    std::vector<GLuint> textures;

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
		textures = LoadMatTextures(mat, aiTextureType_DIFFUSE, dir);
    }

    return Mesh(vertices, indices, textures);
}

std::vector<GLuint> IOManager::LoadMatTextures(aiMaterial *mat, aiTextureType type, std::string dir)
{
	std::vector<GLuint> textures;
	for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		Texture *temp = Resources.CreateTexture(dir + str.C_Str(), dir + str.C_Str());
		if (temp != nullptr)
			textures.push_back(temp->GetTex());
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
