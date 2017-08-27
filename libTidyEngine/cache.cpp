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

#ifdef _WIN32
#define APIENTRY __stdcall
#endif

#include "cache.hpp"
#include <cstdio>
#include "iomanager.hpp"
#include "resource.hpp"

Cache Res;

Cache::Cache()
{
	;	
}

Cache::~Cache()
{
	Clean();	
}

bool Cache::CreateDefaultResources()
{
	GLubyte bitmap[2] = {255, 255};

	bool success = m_Textures["default"].CreateTex(bitmap, 1, 1, true);
	
	if (success == false) {
		printf("Warning: could not create default texture!\n");
		return false;
	}

	return true;
}

void Cache::Clean()
{
	for (auto it : m_Textures)
		it.second.DestroyTex();
	m_Samples.clear();
	m_Resources.clear();
}

Texture *Cache::LoadTex(std::string filepath)
{
	if (m_Textures.find(filepath) != m_Textures.end())
		return &m_Textures[filepath];
	
	FIBITMAP *bitmap = IO.LoadImage(filepath);
	bool success = m_Textures[filepath].CreateTex(bitmap, true, true);

	FreeImage_Unload(bitmap);

	if (success == false) {
		printf("Warning: could not create texture %s!\n",
		       filepath.c_str());
		return nullptr;
	}

	return &m_Textures[filepath];
}

void Cache::UnloadTex(std::string filepath)
{
	m_Textures[filepath].DestroyTex();
	m_Textures.erase(filepath);
}

Sample *Cache::LoadSample(std::string filepath)
{
	if (m_Samples.find(filepath) != m_Samples.end()) {
		return &m_Samples[filepath];
	}

	bool success = IO.LoadVorbis(filepath, &m_Samples[filepath]);
	if (success == true) {
		return &m_Samples[filepath];
	} else {
		printf("Warning: could not load sample %s!\n", filepath.c_str());
		return nullptr;
	}
}

void Cache::UnloadSample(std::string filepath)
{
	m_Samples[filepath].DestroyBuffer();
	m_Samples.erase(filepath);
}

Model *Cache::LoadModel(std::string filepath)
{
	if (m_Models.find(filepath) == m_Models.end()) {
		m_Models[filepath] = std::move(IO.LoadModel(filepath));
		return &m_Models[filepath];
	} else {
		return &m_Models[filepath];
	}
}

void Cache::UnloadModel(std::string filepath)
{
	m_Models.erase(filepath);
}

void Cache::DestroyRes(std::string name)
{
	m_Resources.erase(name);
}

Resource *Cache::GetRes(std::string name)
{
	if (m_Resources.find(name) == m_Resources.end())
		return nullptr;
	return m_Resources[name].get();
}