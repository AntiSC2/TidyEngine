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

void Input::Execute()
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
