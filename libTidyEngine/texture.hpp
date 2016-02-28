/*
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
*/

#pragma once
#ifdef _WIN32
#include <cstdint>
#endif
#include <GL/glew.h>
#include <FreeImage.h>

class Texture {
public:
	Texture();
	Texture(FIBITMAP *bitmap, bool mipmap = false, bool linear = false);
	~Texture();

	bool CreateTex(FIBITMAP *bitmap, bool mipmap = false,
			bool linear = false);
	void DeleteTex();
	uint32_t GetWidth();
	uint32_t GetHeight();
private:
	GLuint m_TexID = 0;
	uint32_t m_Width = 0;
	uint32_t m_Height = 0;
};
