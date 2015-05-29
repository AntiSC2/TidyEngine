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

#include "sprite.h"
#include "spritesheet.h"

Sprite::Sprite() {
    ;
}

Sprite::~Sprite() {
    m_SpriteReference = nullptr;
}
//This function renders the sprite
void Sprite::renderSprite(int x, int y, SDL_Renderer* renderer) {
    if(m_SpriteReference != nullptr) {
        m_SpriteReference->renderSprite(x, y, &m_SourceRegion, renderer);
    }
}
//Set the reference to the correct sprite sheet
void Sprite::loadSpriteFromSheet(SpriteSheet* reference, SDL_Rect& region) {
    m_SpriteReference = reference;
    m_SourceRegion = region;
}
