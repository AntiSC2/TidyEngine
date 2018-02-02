﻿/*
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