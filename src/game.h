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
#include "Core/core.h"
#include "Entities/actor.h"
#include "Graphics/screen.h"
#include "Graphics/draw.h"

//This class is not part of the engine! It's just for testing
//The game class is the actual game, it makes sure that everything gets initialized and that
//everything gets updated and rendered

class Game : public Core {
	public:
		Game();
		~Game();

	private:
		bool init();
		void update();
		void drawGame();

		Actor m_Player;
		Screen m_Screen;
		Draw draw;
};
