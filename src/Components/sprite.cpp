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
#include "../Graphics/spritesheet.h"
#include "../Entities/actor.h"

Sprite::Sprite() {
    ;
}

Sprite::~Sprite() {
    m_SpriteReference = nullptr;
}

bool Sprite::initialize(std::string name, Actor* parent) {
    m_Name = name;
    m_Parent = parent;
    return (m_Parent != nullptr);
}

bool Sprite::getUpdate() {
    return true;
}

bool Sprite::getDraw() {
    return true;
}

void Sprite::doCommand(std::string command) {
    if(command == "play") {
        m_Play = true;
    } else if(command == "pause") {
        m_Play = false;
    } else if(command == "stop") {
        m_Play = false;
        m_CurrentFrame = 0;
    }
}

void Sprite::update() {
    if(m_Play == true) {
        m_CurrentFrame++;
    }
    if (m_CurrentFrame >= m_Frames) {
        m_CurrentFrame = 0;
    }
}

void Sprite::draw(SDL_Renderer* renderer, int x, int y) {
    renderSprite(x, y, renderer);
}

//This function renders the sprite
void Sprite::renderSprite(int x, int y, SDL_Renderer* renderer) {
    if(m_SpriteReference != nullptr) {

        SDL_Rect currentSourceRegion = m_SourceRegion;
        for(int i = 0; i < m_CurrentFrame; i++) {
            currentSourceRegion.x += currentSourceRegion.w;
        }

        m_SpriteReference->renderSprite(x, y, &currentSourceRegion, renderer);
    }
}

//Set the reference to the correct sprite sheet
void Sprite::loadSpriteFromSheet(SpriteSheet* reference, SDL_Rect& region, int frames) {
    m_SpriteReference = reference;
    m_SourceRegion = region;
    m_Frames = frames;
}
