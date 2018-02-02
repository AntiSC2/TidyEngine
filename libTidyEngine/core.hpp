﻿/*
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
*/

#pragma once

#include "entitymanager.hpp"
#include "font.hpp"

class Core {
public:
	Core() = default;
	virtual ~Core() = default;

	virtual void Run();
	bool m_Quit = false;
protected:
	virtual bool InitSubSystems();
	virtual bool Init() = 0;
	virtual void GameLoop();
	virtual void Update(double delta) = 0;
	virtual void Quit();

	bool m_Initialized = false;		
	EntityManager m_EM;
};
