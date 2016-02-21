/*
Copyright (C) 2015 Jakob Sinclair

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

#include "screen.hpp"
#include <stdio.h>

Screen::Screen()
{
        ;
}

Screen::~Screen()
{
        DestroyWindow();
}

bool Screen::CreateWindow(int width, int height, const char* title)
{
        bool success = true;
        m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (m_Window == nullptr) {
                success = false;
        } else {
                m_Width = width;
                m_Height = height;
                m_Title = (char*)title;
        }
        return success;
}

void Screen::DestroyWindow()
{
        if (m_Window != nullptr) {
                glfwDestroyWindow(m_Window);
        }
}
