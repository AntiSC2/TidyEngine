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
#include "config.hpp"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <exception>

//This is the main engine class, this class handles the initialization of the engine
class Core {
	public:
		Core();
		virtual ~Core();
 
		virtual void run();
	protected:
		virtual bool initSubSystems();
		virtual bool init() = 0;
		virtual void gameLoop();
		virtual void update();
		virtual void drawGame() = 0;
		virtual void quit();
		bool m_Initialized = false;
};