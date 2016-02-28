﻿/*
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
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <FreeImage.h>
#include <stdio.h>
#include "config.hpp"
#include "screen.hpp"
#include "render2d.hpp"
#include "error.hpp"

class Core {
	public:
		Core();
		virtual ~Core();

                virtual void Run();
	protected:
		virtual bool InitSubSystems();
		virtual bool Init() = 0;
		virtual void GameLoop();
		virtual void Update() = 0;
		virtual void DrawGame() = 0;
		virtual void Quit();
		bool m_Initialized = false;
                Screen m_Screen;
                Render2D m_2DRenderer;
};
