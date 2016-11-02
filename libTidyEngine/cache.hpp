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

/* TODO:
- Implement default resources in code. DONE FOR TEXTURES
*/

#pragma once

#include <unordered_map>
#include <string>
#include "texture.hpp"
#include "sample.hpp"
#include "rid.hpp"

class Cache {
public:
	Cache();
	~Cache();

	const Texture *CreateTexture(std::string name, std::string filepath);
	void DestroyTexture(std::string name);
	const Texture *GetTexture(std::string name);

	const Sample *CreateSample(std::string name, std::string filepath);
	void DestroySample(std::string name);
	const Sample *GetSample(std::string name);

	RID *CreateResource(std::string name, ID type, void *data);
	void DestroyResource(std::string name);
	RID *GetResource(std::string name);
private:
	std::unordered_map<std::string, Texture> m_Textures;
	std::unordered_map<std::string, Sample> m_Samples;
	std::unordered_map<std::string, RID> m_Resources;
} extern Resources;