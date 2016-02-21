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
#include "renderable.h"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

class Draw {
	public:
		Draw();
		~Draw();

		void begin();
		void draw(Renderable sprite);
		void drawText(std::string text, std::string font,
			glm::vec2 position,SDL_Color color,
			SDL_Renderer* renderer = nullptr, float depth = 0.0f);
		void end();
		void render(SDL_Renderer* renderer);

	private:
		void sortGlyphs();
		std::vector<Renderable> m_Glyphs;
		std::vector<SDL_Texture*> m_TextTextures;
};
