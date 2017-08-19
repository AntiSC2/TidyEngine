/*
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
#include "core.hpp"
#include "model.hpp"

class Game : public Core {
public:
	Game();
	~Game();
private:
	bool Init();
	void Update(double delta);
	void DrawGame();
	Model m_Model;
	glm::vec3 m_Pos = glm::vec3(0.0f, 15.0f, 10.0f);
};