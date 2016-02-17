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

#pragma once
#include <GLFW\glfw3.h>

//The screen class handles the SDL window & the SDL renderer. It also stores the width, height and the title of the window
class Screen {
	public:
		Screen();
		~Screen();

		int getWidth() {
			return m_Width;
		}
		int getHeight() {
			return m_Height;
		}
		const char* getTitle() {
			return m_Title;
		}
		bool createNewWindow(int width, int height, const char* title);
	private:
		int m_Width = 0;
		int m_Height = 0;
		char* m_Title = 0;
};
