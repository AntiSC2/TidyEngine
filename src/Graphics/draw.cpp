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

#include "draw.h"
#include "screen.h"
#include "../RM/cache.h"
#include <SDL2/SDL_ttf.h>
#include <algorithm>

Draw::Draw() {
    ;
}

Draw::~Draw() {
    for(auto &it : m_TextTextures) {
        SDL_DestroyTexture(it);
    }
    m_TextTextures.clear();
}

void Draw::begin() {
    m_Glyphs.clear();
    for(auto &it : m_TextTextures) {
        SDL_DestroyTexture(it);
    }
    m_TextTextures.clear();
}

void Draw::draw(Renderable sprite) {
    m_Glyphs.push_back(sprite);
}

void Draw::drawText(std::string text, std::string font, glm::vec2 position,
                    SDL_Color color, SDL_Renderer* renderer, float depth) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(Cache::fontCache.getFont(font), text.c_str(),  color);
    if(textSurface == nullptr) {
        printf("Unable to render text to surface! SDL_ttf Error: %s\n", TTF_GetError());
    } else {
        SDL_Texture* textTexture = nullptr;
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(textTexture == nullptr) {
            printf("Unable to create texture from surface text!\n");
	} else {
            m_TextTextures.emplace_back(textTexture);
            Renderable newText;
	    newText.tex = m_TextTextures[m_TextTextures.size() - 1];
	    newText.texName = "TextPLZ";
	    newText.glyph.x = (int)position.x;
	    newText.glyph.y = (int)position.y;
	    SDL_QueryTexture(m_TextTextures[m_TextTextures.size() - 1], nullptr, nullptr, &newText.glyph.w, &newText.glyph.h);
	    m_Glyphs.push_back(newText);
	}
    }
    SDL_FreeSurface(textSurface);
}

void Draw::end() {
    sortGlyphs();
}

void Draw::render(SDL_Renderer* renderer) {
    for(size_t i = 0; i < m_Glyphs.size(); i++) {
        SDL_RenderCopy(renderer, m_Glyphs[i].tex, &m_Glyphs[i].clip,
	               &m_Glyphs[i].glyph);
    }
}

bool sortTexture(Renderable a, Renderable b) {
    return a.texName.compare(b.texName) < 0;   
}

bool sortDepth(Renderable a, Renderable b) {
    return a.depth < b.depth;
}

void Draw::sortGlyphs() {
    std::stable_sort(m_Glyphs.begin(), m_Glyphs.end(), sortTexture);
    std::stable_sort(m_Glyphs.begin(), m_Glyphs.end(), sortDepth);
}
