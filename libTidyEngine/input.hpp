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

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

class Input {
public:
	Input();
	~Input();

	void Initialise(GLFWwindow *window);
	void Update();
	static void Process(GLFWwindow *window, int key, int scancode,
			int action, int mode);
	static void MouseProcess(GLFWwindow *window, double xpos, double ypos);
	static void MousePress(GLFWwindow *window, int button, int action,
			int mods);
	bool GetKey(int key);
	const glm::vec2 &GetMousePos();
	bool GetMouseButton(int button);
private:
	static bool m_Keys[350];
	static bool m_Buttons[8];
	static glm::vec2 m_MousePos;
};