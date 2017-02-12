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

#include "font.hpp"
#include <glad/glad.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>

Font::Font()
{
	;
}

Font::~Font()
{
	Clean();
}

uint32_t next_power(uint32_t u)
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

	uint32_t count = 0;
	uint32_t b_width = 0;
	uint32_t b_height = 0;
	
	std::vector<GLubyte *> temp_bitmaps;
	
	while(m_Glyphs.size() < (uint32_t)face->num_glyphs){
		error = FT_Load_Char(face, count, FT_LOAD_RENDER);
		if (error) {
			count++;
			/* Big risk of infinite loop otherwise,
			 * 100 is just an arbitary number
			 */
			if (count > m_Glyphs.size() + 100)
				break;
			continue;
		}

		FT_Bitmap &bitmap= face->glyph->bitmap;
		
		if ((bitmap.width == 0 || bitmap.rows == 0) &&
		    (char)count != ' ') {
			count++;
			if (count > m_Glyphs.size() + 100)
				break;
			continue;
		}
		
		b_width += bitmap.width;
		if (bitmap.rows > b_height)
			b_height = bitmap.rows;
		
		GLubyte *temp_bitmap = new GLubyte[bitmap.width * bitmap.rows
		                                   * 2];
		
		for (uint32_t y = 0; y < bitmap.rows; y++) {
			for (uint32_t x = 0; x < bitmap.width; x++) {
				temp_bitmap[2 * (x + y * bitmap.width)] =
				temp_bitmap[2 * (x + y * bitmap.width) + 1] =
				bitmap.buffer[x + bitmap.width * y];
			}
		}
		
		temp_bitmaps.push_back(temp_bitmap);
		m_Glyphs[count] = FontGlyph(0.0f, 0.0f, next_power(bitmap.width),
		                           next_power(bitmap.rows), 1);
		
		FontGlyph &temp_glyph = m_Glyphs[m_Glyphs.size() - 1];
		temp_glyph.SetPenX(face->glyph->bitmap_left);
		temp_glyph.SetPenY(face->glyph->bitmap_top);
		temp_glyph.SetAdvanceX(face->glyph->advance.x >> 6);
		temp_glyph.SetAdvanceY(face->glyph->advance.y >> 6);
		
		if (m_TexHeight < face->glyph->bitmap_top)
			m_TexHeight = face->glyph->bitmap_top;
	
		count++;
	}

	uint32_t f_width = next_power(b_width);
	uint32_t f_height = next_power(b_height);
	uint32_t index = 0;
	uint32_t offset = 0;
	GLubyte *final_bitmap = new GLubyte[f_width * f_height * 2];
	
	for (uint32_t x = 0; x < f_width; x++) {
		for (uint32_t y = 0; y < f_height; y++) {
			if (x >= b_width || y >= (uint32_t)m_Glyphs[index].GetRect().w) {
				final_bitmap[2 * (x + y * f_width)] = 
				final_bitmap[2 * (x + y * f_width) + 1] = 0;
			} else if (x >= (uint32_t)m_Glyphs[index].GetRect().z + offset) {
				offset += (uint32_t)m_Glyphs[index].GetRect().z;
				index++;

				final_bitmap[2 * (x + y * f_width)] = 
				final_bitmap[2 * (x + y * f_width) + 1] =
				temp_bitmaps[index][2 * ((x - offset) + y * (uint32_t)m_Glyphs[index].GetRect().z)];
			} else {
				final_bitmap[2 * (x + y * f_width)] = 
				final_bitmap[2 * (x + y * f_width) + 1] =
				temp_bitmaps[index][2 * ((x - offset) + y * (uint32_t)m_Glyphs[index].GetRect().z)];
			}
		}
	}
		
	for (auto i: temp_bitmaps) {
		delete[] i;
	}
	
	temp_bitmaps.clear();
	m_Texture.CreateTex(final_bitmap, f_width, f_height, true);
	delete []final_bitmap;

	for (size_t i = 0; i < m_Glyphs.size(); i++) {
		glm::vec4 coords;
		coords.x = m_Glyphs[i].GetRect().x / f_width;
		coords.y = m_Glyphs[i].GetRect().y / f_height;
		coords.z = coords.x + (m_Glyphs[i].GetRect().z / f_width);
		coords.w = coords.y + (m_Glyphs[i].GetRect().w / f_height);
		m_Glyphs[i].SetTexCoords(coords);
		//m_Glyphs[i].SetTex(m_Texture.GetTex());
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
	m_Texture.DestroyTex();
	m_Glyphs.clear();	
}

FontGlyph &Font::GetChar(char c)
{
	if (m_Glyphs.find((uint32_t)c) != m_Glyphs.end())
		return m_Glyphs[(uint32_t)c];
	else
		return m_Glyphs[(uint32_t)' '];
}
