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

#include "font.hpp"
#include <memory>
#include <string>
#include <glad/glad.h>
#include <freetype2/ft2build.h>
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

	error = FT_Select_Charmap(face, FT_ENCODING_UNICODE);

	if (error) {
		printf("Warning: could not find Unicode support for font %s\n", path.c_str());
		return false;
	}

	uint32_t b_width = 0;
	uint32_t b_height = 0;
	
	std::vector<GLubyte*> temp_bitmaps;

	/*
	 * Load all UTF-8 characters
	 */

	uint8_t charcode = 0x20;
	
	while(charcode < 0xFF) {
		error = FT_Load_Char(face, charcode, FT_LOAD_RENDER);
		if (error) {
			charcode++;
			continue;
		}

		FT_Bitmap &bitmap= face->glyph->bitmap;
		
		if (bitmap.width == 0 || bitmap.rows == 0) {
			charcode++;
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
		m_Glyphs[charcode] = FontGlyph((float)b_width, 0.0f,
		                            (float)bitmap.width,
		                            (float)bitmap.rows);

		FontGlyph &temp_glyph = m_Glyphs[charcode];
		temp_glyph.SetPenX(face->glyph->bitmap_left);
		temp_glyph.SetPenY(face->glyph->bitmap_top);
		temp_glyph.SetAdvanceX(face->glyph->advance.x >> 6);
		temp_glyph.SetAdvanceY(face->glyph->advance.y >> 6);

		if (m_TexHeight < face->glyph->bitmap_top)
			m_TexHeight = face->glyph->bitmap_top;

		b_width += bitmap.width;
		if (bitmap.rows > b_height)
			b_height = bitmap.rows;
	
		charcode++;
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

		for (uint32_t x = offset; x < width + offset; x++) {
			for (uint32_t y = 0; y < height; y++) {
				final_ptr[2 * (x + y * f_width)] =
				final_ptr[2 * (x + y * f_width) + 1] = temp_bitmaps[index][(x - offset) + y * width];
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
