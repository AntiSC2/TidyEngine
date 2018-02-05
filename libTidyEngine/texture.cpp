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

#include "texture.hpp"
#include <glad/glad.h>
#include <cstdio>

Texture::Texture()
{
	;
}

Texture::Texture(const Texture &tex)
{
	m_TexID = tex.m_TexID;
	m_Width = tex.m_Width;
	m_Height = tex.m_Height;
}

Texture::Texture(Texture &&tex) noexcept
{
	m_TexID = tex.m_TexID;
	m_Width = tex.m_Width;
	m_Height = tex.m_Height;

	tex.m_TexID = 0;
	tex.m_Width = 0;
	tex.m_Height = 0;
}

Texture::Texture(GLubyte *bitmap, uint32_t w, uint32_t h, bool dual,
                 bool mipmap, bool linear)
{
	CreateTex(bitmap, w, h, dual, mipmap, linear);
}

Texture::~Texture()
{
	DestroyTex();
}

std::string Texture::Type() {
	return "Texture";
}

bool Texture::CreateTex(GLubyte *bitmap, uint32_t w, uint32_t h, bool dual,
                        bool mipmap, bool linear)
{
	if (bitmap == nullptr)
		return false;

	DestroyTex();

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

	m_Width = w;
	m_Height = h;
	
	if (dual == true) {
		GLint swizzle_mask[4] = {GL_RED, GL_RED, GL_RED, GL_GREEN};
		glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, 
		                 swizzle_mask);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, 
		             GL_RG, GL_UNSIGNED_BYTE, bitmap);
	} else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0,
		             GL_RGBA, GL_UNSIGNED_BYTE, bitmap);
	}

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

void Texture::DestroyTex()
{
	if (m_TexID != 0) {
		glDeleteTextures(1, &m_TexID);
		m_TexID = 0;
	}
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
