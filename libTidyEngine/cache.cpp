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

#include "cache.hpp"
#include <cstdio>
#include "error.hpp"
#include "iomanager.hpp"

Cache Resources;

Cache::Cache()
{
	FIBITMAP *bitmap = FreeImage_Allocate(2, 2, 32, FI_RGBA_RED_MASK,
			FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);

	uint16_t byte_space = (uint16_t)(FreeImage_GetLine(bitmap) /
	                      FreeImage_GetHeight(bitmap));

	for (uint8_t y = 0; y < 2; y++) {
		BYTE *bits = FreeImage_GetScanLine(bitmap, y);
		
		for (uint8_t x = 0; x < 2; x++) {
			bits[FI_RGBA_RED] = 255;
			bits[FI_RGBA_GREEN] = 255;
			bits[FI_RGBA_BLUE] = 255;
			bits[FI_RGBA_ALPHA] = 255;

			bits += byte_space;
		}
	}

	bool success = m_Textures["default"].CreateTex(bitmap);

	FreeImage_Unload(bitmap);

	if (success == false) {
		Error e("Exception: could not create default texture!");
		throw e;
	}
}

Cache::~Cache()
{
	for (auto it : m_Textures)
		it.second.DestroyTex();
}

const Texture &Cache::CreateTexture(std::string name, std::string filepath)
{
	if (m_Textures.find(name) == m_Textures.end()) {
		FIBITMAP *bitmap = IO.LoadImage(filepath);
		bool success = m_Textures[name].CreateTex(bitmap, true, false);
		
		FreeImage_Unload(bitmap);
		
		if (success == false) {
			Error e("Exception: could not create texture " +
					filepath);
			throw e;
		}

		return m_Textures[name];
	} else {
		std::printf("Warning: texture %s already exists!\n",
				name.c_str());
		return m_Textures[name];
	}
}

void Cache::DestroyTexture(std::string name)
{
	m_Textures[name].DestroyTex();
	m_Textures.erase(name);
}

const Texture &Cache::GetTexture(std::string name)
{
	if (m_Textures.find(name) != m_Textures.end())
		return m_Textures[name];
	std::printf("Warning: could not find texture %s!", name.c_str());
	return m_Textures["default"];
}

const Sample &Cache::CreateSample(std::string name, std::string filepath)
{
	try {
		IO.LoadVorbis(filepath, &m_Samples[name]);
		return m_Samples[name];
	}
	catch (std::exception &e) {
		printf("%s\n", e.what());
	}
	return m_Samples["default"];
}

void Cache::DestroySample(std::string name)
{
	m_Samples[name].DestroyBuffer();
	m_Samples.erase(name);
}

const Sample &Cache::GetSample(std::string name)
{
	if (m_Samples.find(name) != m_Samples.end())
		return m_Samples[name];
	std::printf("Warning: could not find sample %s!", name.c_str());
	return Sample();
}