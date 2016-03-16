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

bool Input::m_Keys[350];

Input::Input()
{
        for (uint16_t i = 0; i < 350; i++)
                m_Keys[i] = false;
}

Input::~Input()
{
        ;
}

void Input::Initialise(GLFWwindow *window)
{
        glfwSetKeyCallback(window, Process);
}

void Input::Update()
{
        glfwPollEvents();
}

void Input::Process(GLFWwindow *window, int key, int scancode, int action,
        int mode)
{
        if (key == GLFW_KEY_UNKNOWN) {
                std::printf("Warning: key unknown!\n");
                return;
        }
        
        if (action == GLFW_PRESS)
                m_Keys[key] = true;
        else if (action == GLFW_RELEASE)
                m_Keys[key] = false;
}

bool Input::GetKey(int key)
{
        if (key < 0 || key >= 350) {
                std::printf("Warning: key unknown!\n");
                return false;
        }
        return m_Keys[key];
}