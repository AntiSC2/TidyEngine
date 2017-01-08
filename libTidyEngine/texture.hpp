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

struct FIBITMAP;

#include <cstdint>
#include <string>
#include <GL/glew.h>
#include "resource.hpp"

class Texture: public Resource {
public:
	Texture();
	Texture(FIBITMAP *bitmap, bool mipmap = false, bool linear = false);
	Texture(GLubyte *bitmap, uint32_t w, uint32_t h, bool mipmap = false,
	        bool linear = false);
	~Texture();

	virtual std::string Type();

	bool CreateTex(FIBITMAP *bitmap, bool mipmap = false,
	               bool linear = false);
	bool CreateTex(GLubyte *bitmap, uint32_t w, uint32_t h,
	               bool mipmap = false, bool linear = false);
	void DestroyTex();
	const GLuint &GetTex() const;
	const uint32_t &GetWidth() const;
	const uint32_t &GetHeight() const;
private:
	GLuint m_TexID = 0;
	uint32_t m_Width = 0;
	uint32_t m_Height = 0;
};
