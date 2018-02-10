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

#ifdef _WIN32
#define APIENTRY __stdcall
#endif

#include "cache.hpp"
#include <cstdio>
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
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
	m_Textures.clear();
	m_Samples.clear();
	m_Models.clear();
	m_Fonts.clear();
	m_Resources.clear();
}

Texture *Cache::LoadTex(std::string filepath)
{
	if (m_Textures.find(filepath) != m_Textures.end())
		return &m_Textures[filepath];
	
	TE::Bitmap *bitmap = IO.LoadImage(filepath);
	bool success = m_Textures[filepath].CreateTex(bitmap->Data, (uint32_t)bitmap->Width, (uint32_t)bitmap->Height, false, true, true);

	if (bitmap != nullptr)
		delete bitmap;

	if (success == false) {
		printf("Warning: could not create texture %s!\n",
		       filepath.c_str());
		return nullptr;
	}
	printf("Loaded texture %s\n", filepath.c_str());
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

Font *Cache::LoadFont(std::string filepath)
{
	if (m_Fonts.find(filepath) == m_Fonts.end()) {
		m_Fonts[filepath].Initialize(&m_FontLib, filepath, 128);
		return &m_Fonts[filepath];
	} else {
		return &m_Fonts[filepath];
	}
}

void Cache::UnloadFont(std::string filepath)
{
	m_Fonts.erase(filepath);
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