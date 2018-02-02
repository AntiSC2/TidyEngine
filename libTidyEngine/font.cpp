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
#include <memory>
#include <string>
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
		printf("Warning: could not load font %s!\n", path.c_str());
		return false;
	}

	error = FT_Set_Pixel_Sizes(face, 0, m_Height);

	if (error) {
		printf("Warning: could not set size for font %s\n", path.c_str());
		return false;
	}

	uint32_t count = 0;
	uint32_t b_width = 0;
	uint32_t b_height = 0;
	
	std::vector<GLubyte*> temp_bitmaps;
	
	while(m_Glyphs.size() < (uint32_t)face->num_glyphs){
		error = FT_Load_Char(face, count, FT_LOAD_RENDER);
		if (error) {
			count++;
			if (count > 255)
				break;
			continue;
		}

		FT_Bitmap &bitmap= face->glyph->bitmap;
		
		if ((bitmap.width == 0 || bitmap.rows == 0) && (char)count != ' ') {
			count++;
			if (count > 255)
				break;
			continue;
		}
		
		GLubyte *temp_bitmap = new GLubyte[bitmap.width * bitmap.rows];
		
		for (uint32_t y = 0; y < bitmap.rows; y++) {
			for (uint32_t x = 0; x < bitmap.width; x++) {
				temp_bitmap[x + y * bitmap.width] =
				bitmap.buffer[x + y * bitmap.width];
			}
		}
		
		temp_bitmaps.push_back(temp_bitmap);
		m_Glyphs[count] = FontGlyph((float)b_width, 0.0f,
		                            (float)bitmap.width,
		                            (float)bitmap.rows);

		FontGlyph &temp_glyph = m_Glyphs[count];
		temp_glyph.SetPenX(face->glyph->bitmap_left);
		temp_glyph.SetPenY(face->glyph->bitmap_top);
		temp_glyph.SetAdvanceX(face->glyph->advance.x >> 6);
		temp_glyph.SetAdvanceY(face->glyph->advance.y >> 6);

		if (m_TexHeight < face->glyph->bitmap_top)
			m_TexHeight = face->glyph->bitmap_top;

		b_width += bitmap.width;
		if (bitmap.rows > b_height)
			b_height = bitmap.rows;
		count++;
	}

	uint32_t f_width = next_power(b_width);
	uint32_t f_height = next_power(b_height);
	uint32_t offset = 0;
	uint32_t index = 0;
	
	std::unique_ptr<GLubyte[]> final_bitmap = std::make_unique<GLubyte[]>(f_width * f_height * 2);
	GLubyte *final_ptr = final_bitmap.get();
	for (auto &i: m_Glyphs) {
		FontGlyph &temp = i.second;
		uint32_t width = (uint32_t)temp.GetRect().z;
		uint32_t height = (uint32_t)temp.GetRect().w;
		
		glm::vec4 uv;
		uv.x = temp.GetRect().x / (float)f_width;
		uv.y = 0.0f;
		uv.z = (float)width / (float)f_width + uv.x;
		uv.w = (float)height / (float)f_height;
		temp.SetTexUV(uv);

		for (uint32_t x = offset; x < f_width; x++) {
			for (uint32_t y = 0; y < f_height; y++) {
				final_ptr[2 * (x + y * f_width)] =
				final_ptr[2 * (x + y * f_width) + 1] =
				((x - offset) >= width || y >= height) ?
				0 : temp_bitmaps[index][(x - offset) + y * width];
			}
		}

		offset += width;
		index++;
	}

	/* Free temporary bitmaps*/
	for (auto i: temp_bitmaps)
		delete i;
	temp_bitmaps.clear();

	m_Texture.CreateTex(final_bitmap.get(), f_width, f_height, true);
	final_bitmap.reset(nullptr);

	for (auto &i : m_Glyphs)
		i.second.SetTex(m_Texture.GetTex());

	FT_Done_Face(face);

	return true;
}

std::string Font::Type()
{
	return "Font";
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
