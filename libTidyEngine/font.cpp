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
#include <glad/glad.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>

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
	Clean();
	FT_Face face;
	m_Height = height;

	int error = FT_New_Face(*lib, path.c_str(), 0, &face);
	
	if (error) {
		printf("Error: Could not load font %s!\n", path.c_str());
		return false;
	}

	error = FT_Set_Pixel_Sizes(face, 0, m_Height);

	if (error) {
		printf("Error: Could not set size for font %s\n", path.c_str());
		return false;
	}

	uint32_t index = 0;
	uint32_t count = 0;

	while(index < (uint32_t)face->num_glyphs) {
		error = FT_Load_Char(face, count, FT_LOAD_RENDER);
		if (error) {
			count++;
			/* Big risk of infinite loop otherwise,
			 * 100 is just an arbitary number
			 */
			if (count > index + 100)
				break;
			continue;
		}

		FT_Bitmap &bitmap= face->glyph->bitmap;

		if (bitmap.width == 0 && (char)count != ' ') {
			count++;

			if (count > index + 100)
				break;

			continue;
		}

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
		
		m_Textures.emplace_back(final_bitmap, width, height, true);
		Texture &temp = m_Textures[index];

		m_Glyphs.emplace(std::piecewise_construct,
		                 std::forward_as_tuple(count), 
		                 std::forward_as_tuple(0.0f, 0.0f,
		                 temp.GetWidth(), 
		                 temp.GetHeight(), 
		                 temp.GetTex()));
		FontGlyph &temp_glyph = m_Glyphs[count];
		temp_glyph.SetPenX(face->glyph->bitmap_left);
		temp_glyph.SetPenY(face->glyph->bitmap_top);
		temp_glyph.SetAdvanceX(face->glyph->advance.x >> 6);
		temp_glyph.SetAdvanceY(face->glyph->advance.y >> 6);
		
		if (m_TexHeight < face->glyph->bitmap_top)
			m_TexHeight = face->glyph->bitmap_top;

		index++;
		count++;

		delete []final_bitmap;
	}

	FT_Done_Face(face);

	return true;
}

uint32_t Font::GetHeight()
{
	return m_Height;
}

int32_t Font::GetTexHeight()
{
	return m_TexHeight;
}

void Font::Clean()
{
	m_Textures.clear();
	m_Glyphs.clear();	
}

FontGlyph &Font::GetChar(char c)
{
	if (m_Glyphs.find((uint32_t)c) != m_Glyphs.end())
		return m_Glyphs[(uint32_t)c];
	else
		return m_Glyphs[(uint32_t)' '];
}
