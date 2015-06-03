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

#include "spritesheet.h"
#include "cache.h"

// The constructor does nothing special here
SpriteSheet::SpriteSheet() {
    ;
}
//The texture is destroyed in the resource manager
SpriteSheet::~SpriteSheet() {
    m_Texture = nullptr;
}
//Loads in a texture
void SpriteSheet::loadSpriteSheet(std::string filepath) {
    m_Texture = nullptr; //Makes sure that the previous sprite sheet is not linked anymore
    m_Texture = Cache::texCache.getTexture(filepath);
    SDL_QueryTexture(m_Texture, nullptr, nullptr, &m_Width, &m_Height);
    if(m_Texture == nullptr) {
        printf("Error: Could not get texture %s!\n", filepath.c_str());
    } 
}
//Renders the entire, or part of, spritesheet
void SpriteSheet::renderSprite(int x, int y, SDL_Rect* clip, SDL_Renderer* renderer) {
    SDL_Rect renderQuad = {x, y, m_Width, m_Height}; 
    if(clip != nullptr) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(renderer, m_Texture, clip, &renderQuad);
}
