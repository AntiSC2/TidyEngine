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
#include "component.h"
#include <SDL2/SDL.h>

class SpriteSheet;
//This class represents an object in form of an image, gets the image from a sprite sheet
class Sprite : public Component {
    public:
        Sprite();
        ~Sprite();

        bool initialize();
        bool initialize(std::string name);
        bool getUpdate();
        bool getDraw();

        void draw(SDL_Renderer* renderer, int x, int y);
        void renderSprite(int x, int y, SDL_Renderer* renderer = nullptr);
        void loadSpriteFromSheet(SpriteSheet* reference, SDL_Rect& region);
    private:
        SDL_Rect m_SourceRegion;
        SpriteSheet* m_SpriteReference = nullptr;      
};
