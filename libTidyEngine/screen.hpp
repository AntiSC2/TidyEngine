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

struct GLFWwindow;

#include <cstdint>

class Screen {
public:
	Screen() = default;
	virtual ~Screen();

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
