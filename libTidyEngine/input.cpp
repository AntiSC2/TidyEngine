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

#include "input.hpp"
#include <cstdint>
#include <cstdio>
#include <GLFW/glfw3.h>

GLFWwindow *Input::m_Window = nullptr;
bool Input::m_Buttons[8];
glm::vec2 Input::m_MousePos = glm::vec2(0.0f, 0.0f);

Input::Input(GLFWwindow *window)
{
	for (uint8_t i = 0; i < 8; i++)
		m_Buttons[i] = false;
	Initialise(window);
}

void Input::Initialise(GLFWwindow *window)
{
	m_Window = window;
	glfwSetCursorPosCallback(window, MouseProcess);
	glfwSetMouseButtonCallback(window, MousePress);
}

void Input::Execute(bool fixed)
{
	glfwPollEvents();
}

std::string Input::GetType()
{
	return "Input";
}

void Input::MouseProcess(GLFWwindow *window, double xpos, double ypos)
{
	m_MousePos = glm::vec2(xpos, ypos);
}

void Input::MousePress(GLFWwindow *window, int button, int action, int mods)
{
	if (button < 0 || button > 7)
		return;

	if (action == GLFW_PRESS)
		m_Buttons[button] = true;
	else if (action == GLFW_RELEASE)
		m_Buttons[button] = false;
}

bool Input::GetKey(size_t key)
{
	return glfwGetKey(m_Window, key);
}

const glm::vec2 &Input::GetMousePos()
{
	return m_MousePos;
}

bool Input::GetMouseButton(size_t button)
{
	if (button >= 8) {
		printf("Warning: mouse button unknown!\n");
		return false;
	}
	return m_Buttons[button];
}
