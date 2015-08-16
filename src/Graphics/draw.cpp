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
#include <algorithm>

Draw::Draw() {
    ;
}

Draw::~Draw() {
    ;
}

void Draw::begin() {
    m_Glyphs.clear();
}

void Draw::draw(Renderable sprite) {
    m_Glyphs.push_back(sprite);
}

void Draw::end() {
    sortGlyphs();
}

void Draw::render(SDL_Renderer* renderer) {
    //printf("%d\n %d\n %d\n %d\n", m_Glyphs[0].clip->x, m_Glyphs[0].clip->y,
                                  //m_Glyphs[0].clip->w, m_Glyphs[0].clip->h);
    for(size_t i = 0; i < m_Glyphs.size(); i++) {
        SDL_RenderCopy(renderer, Cache::texCache.getTexture(m_Glyphs[i].texName),
	               &m_Glyphs[i].clip, &m_Glyphs[i].glyph);
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
