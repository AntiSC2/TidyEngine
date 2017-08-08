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

Cache Resources;

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

Texture *Cache::CreateTexture(std::string name, std::string filepath)
{
	if (m_Textures.find(name) == m_Textures.end()) {
		FIBITMAP *bitmap = IO.LoadImage(filepath);
		bool success = m_Textures[name].CreateTex(bitmap, true, false);
		
		FreeImage_Unload(bitmap);
		
		if (success == false) {
			printf("Warning: could not create texture %s!\n",
			       filepath.c_str());
			return nullptr;
		}

		return &m_Textures[name];
	} else {
		printf("Warning: texture %s already exists!\n",
				name.c_str());
		return &m_Textures[name];
	}
}

void Cache::DestroyTexture(std::string name)
{
	m_Textures[name].DestroyTex();
	m_Textures.erase(name);
}

Texture *Cache::GetTexture(std::string name)
{
	if (m_Textures.find(name) != m_Textures.end())
		return &m_Textures[name];
	printf("Warning: could not find texture %s!\n", name.c_str());
	return nullptr;
}

Sample *Cache::CreateSample(std::string name, std::string filepath)
{
	if (m_Samples.find(name) != m_Samples.end()) {
		printf("Warning: sample %s already exists!\n",
		            name.c_str());
		return nullptr;
	}

	bool success = IO.LoadVorbis(filepath, &m_Samples[name]);
	if (success == true) {
		return &m_Samples[name];
	} else {
		printf("Warning: could not load sample %s!\n", filepath.c_str());
		return nullptr;
	}
}

void Cache::DestroySample(std::string name)
{
	m_Samples[name].DestroyBuffer();
	m_Samples.erase(name);
}

Sample *Cache::GetSample(std::string name)
{
	if (m_Samples.find(name) != m_Samples.end())
		return &m_Samples[name];
	printf("Warning: could not find sample %s!\n", name.c_str());
	return nullptr;
}

RID *Cache::CreateResource(std::string name, Resource *data)
{
	if (m_Resources.find(name) == m_Resources.end()) {
		m_Resources.emplace(name, RID(data));
		return &m_Resources[name];
	} else {
		printf("Warning: resource %s already exists!\n", name.c_str());
		return nullptr;
	}
}

void Cache::DestroyResource(std::string name)
{
	m_Resources.erase(name);
}

RID *Cache::GetResource(std::string name)
{
	if (m_Resources.find(name) != m_Resources.end()) {
		return &m_Resources[name];
	} else {
		printf("Warning: could not find %s!\n", name.c_str());
		return nullptr;
	}
}
