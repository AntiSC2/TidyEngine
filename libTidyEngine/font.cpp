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

#include "font.hpp"
#include "texture.hpp"

Font::Font()
{
	;
}

Font::~Font()
{
	Clean();
}

uint32_t next_power(unsigned int u)
{
	uint32_t i = 2;

	while (i < u) {
		i *= 2;
	}

	return i;
}

bool Font::Initialize(FT_Library *lib, std::string path, uint32_t height)
{
	FT_Face face;
	m_Height = height;

	int error = FT_New_Face(*lib, path.c_str(), 0, &face);
	
	if (error) {
		printf("Error: Could not load font %s!\n", path.c_str());
		return false;
	}

	m_Size = face->num_glyphs;

	error = FT_Set_Pixel_Sizes(face, 0, m_Height);

	if (error) {
		printf("Error: Could not set size for font %s\n", path.c_str());
		return false;
	}

	for (uint8_t i = 0; i < m_Size; i++) {
		error = FT_Load_Char(face, (char)i, FT_LOAD_RENDER);
		if (error)
			continue;

		FT_Bitmap &bitmap= face->glyph->bitmap;

		uint32_t width = next_power(bitmap.width);
		uint32_t height = next_power(bitmap.rows);

		GLubyte *final_bitmap = new GLubyte[2 * width * height];

		for (uint32_t y = 0; y < height; y++) {
			for (uint32_t x = 0; x < width; x++) {
				final_bitmap[2 * (x + y * width)] =
				final_bitmap[2 * (x + y * width) + 1] =
				(x >= bitmap.width || y >= bitmap.rows) ?
				0: bitmap.buffer[x + bitmap.width * y];
			}
		}
		
		m_Textures.emplace_back(final_bitmap, width, height);

		delete []final_bitmap;
	}
	
	return true;
}

void Font::Clean()
{
	m_Textures.clear();	
}
