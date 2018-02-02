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

#pragma once

#include <vector>
#include <map>
#include "fontglyph.hpp"
#include "resource.hpp"
#include "texture.hpp"

typedef struct FT_LibraryRec_ *FT_Library;

class Font: public Resource {
public:
	Font();
	virtual ~Font();

	bool Initialize(FT_Library *lib, std::string path, uint32_t height);
	void Clean();
	virtual std::string Type();
	uint32_t GetHeight();
	int32_t GetTexHeight();
	FontGlyph &GetChar(char c);
private:
	uint32_t m_Height = 0;
	int32_t m_TexHeight = 0;
	Texture m_Texture;
	std::map<uint32_t, FontGlyph> m_Glyphs;
};
