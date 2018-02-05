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

#pragma once

#include <cstdint>
#include <string>
#include "resource.hpp"

typedef unsigned char GLubyte;
typedef unsigned int GLuint;

class Texture: public Resource {
public:
	Texture();
	Texture(const Texture &tex);
	Texture(Texture &&tex) noexcept;
	Texture(GLubyte *bitmap, uint32_t w, uint32_t h, bool dual = false, 
	        bool mipmap = false, bool linear = false);
	~Texture();

	virtual std::string Type();

	bool CreateTex(GLubyte *bitmap, uint32_t w, uint32_t h, 
	               bool dual = false, bool mipmap = false,
	               bool linear = false);
	void DestroyTex();
	const GLuint &GetTex() const;
	const uint32_t &GetWidth() const;
	const uint32_t &GetHeight() const;
private:
	GLuint m_TexID = 0;
	uint32_t m_Width = 0;
	uint32_t m_Height = 0;
};
