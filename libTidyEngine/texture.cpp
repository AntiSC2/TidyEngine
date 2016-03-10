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

#include "texture.hpp"
#include <cstdio>
#include <FreeImage.h>

Texture::Texture()
{
	;
}

Texture::Texture(FIBITMAP *bitmap, bool mipmap, bool linear)
{
	CreateTex(bitmap, mipmap, linear);
}

Texture::~Texture()
{
	if (m_TexID != 0) {
		DeleteTex();
	}
}

bool Texture::CreateTex(FIBITMAP *bitmap, bool mipmap, bool linear)
{
        if (bitmap == nullptr)
                return false;
	glGenTextures(1, &m_TexID);
	glBindTexture(GL_TEXTURE_2D, m_TexID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	if (linear == true && mipmap == false) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
				GL_LINEAR);
	} else if (mipmap == false) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
				GL_NEAREST);
	}

	FIBITMAP *temp = FreeImage_ConvertTo32Bits(bitmap);
	if (temp == nullptr) {
		DeleteTex();
		FreeImage_Unload(temp);
		std::printf("Error: could not convert texture to 32 bits!\n");
		return false;
	}
	m_Width = FreeImage_GetWidth(temp);
	m_Height = FreeImage_GetHeight(temp);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, 
			GL_BGRA, GL_UNSIGNED_BYTE,
			(void*)FreeImage_GetBits(temp));

	FreeImage_Unload(temp);
	
	if (linear == true && mipmap == true) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
				GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else if (mipmap == true) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
				GL_NEAREST_MIPMAP_NEAREST);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	return true;
}

void Texture::DeleteTex()
{
	if (m_TexID != 0)
		glDeleteTextures(1, &m_TexID);
}

const GLuint &Texture::GetTex() const
{
        return m_TexID;
}

const uint32_t &Texture::GetWidth() const
{
	return m_Width;
}

const uint32_t &Texture::GetHeight() const
{
	return m_Height;
}
