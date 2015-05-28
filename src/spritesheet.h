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
#include <SDL2/SDL.h>

class SpriteSheet {
    public:
        friend class Sprite;
        SpriteSheet();
        ~SpriteSheet();

        void loadSpriteSheet(const char* filepath);

        int getWidth() {
            return m_Width;
        }
        int getHeight() {
            return m_Height;
        }
        void renderSprite(int x, int y, SDL_Rect* clip = nullptr, SDL_Renderer* renderer = nullptr);
    private:
        SDL_Texture* m_Texture = nullptr;
        int m_Width;
        int m_Height;
};
