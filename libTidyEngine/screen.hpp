﻿/*
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

struct GLFWwindow;

#include <cstdint>

class Screen {
public:
	Screen() = default;
	~Screen();

	uint16_t GetWidth();
	uint16_t GetHeight();
	const char *GetTitle();
	GLFWwindow *GetWindow();
	bool NeedUpdate();
	bool CreateWindow(uint16_t width, uint16_t height, const char* title,
	                  int gl_major, int gl_minor);
	bool InitGL();
	void CloseWindow();
	static void WindowSizeCallback(GLFWwindow *window, int width,
	                               int height);
private:
	void DestroyWindow();
	uint16_t m_Width = 0;
	uint16_t m_Height = 0;
	char *m_Title = nullptr;
	static GLFWwindow *m_NeedUpdate;
	GLFWwindow *m_Window = nullptr;
};
