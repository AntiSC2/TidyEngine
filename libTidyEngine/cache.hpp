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

/* TODO:
- Implement default resources in code. DONE FOR TEXTURES
*/

#pragma once

#include <unordered_map>
#include <string>
#include "texture.hpp"
#include "sample.hpp"
#include "model.hpp"
#include "font.hpp"
#include "resource.hpp"

typedef struct FT_LibraryRec_ * FT_Library;

class Cache {
public:
	Cache();
	~Cache();

	bool CreateDefaultResources();
	void Clean();

	Texture *LoadTex(std::string filepath);
	void UnloadTex(std::string filepath);

	Sample *LoadSample(std::string filepath);
	void UnloadSample(std::string filepath);

	Model *LoadModel(std::string filepath);
	void UnloadModel(std::string filepath);

	Font *LoadFont(std::string filepath);
	void UnloadFont(std::string filepath);

	template<typename R>
	R &CreateRes(std::string name, std::unique_ptr<R> &&res);
	void DestroyRes(std::string name);
	Resource *GetRes(std::string name);

	FT_Library m_FontLib;
private:
	std::unordered_map<std::string, Texture> m_Textures;
	std::unordered_map<std::string, Sample> m_Samples;
	std::unordered_map<std::string, Model> m_Models;
	std::unordered_map<std::string, Font> m_Fonts;
	std::unordered_map<std::string, std::shared_ptr<Resource>> m_Resources;	
} extern Res;

template<typename R>
R &Cache::CreateRes(std::string name, std::unique_ptr<R> &&r)
{
	auto &res = *r;

	static_assert(std::is_base_of<Resource, R>::value, "Error: tried creating resource with non-resource type!\n");
	m_Resources[name] = std::move(r);

	return res;
}