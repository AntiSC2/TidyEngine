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

#include <glm/vec2.hpp>
#include "system.hpp"

typedef struct GLFWwindow GLFWwindow;

class Input: public ISystem {
public:
	Input(GLFWwindow *window);
	virtual ~Input() = default;

	void Initialise(GLFWwindow *window);
	virtual void Execute(bool fixed = false);
	virtual std::string GetType();
	static void MouseProcess(GLFWwindow *window, double xpos, double ypos);
	static void MousePress(GLFWwindow *window, int button, int action,
			int mods);
	bool GetKey(size_t key);
	const glm::vec2 &GetMousePos();
	bool GetMouseButton(size_t button);
protected:
	static GLFWwindow *m_Window;
	static bool m_Buttons[8];
	static glm::vec2 m_MousePos;
};