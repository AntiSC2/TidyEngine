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
#include <SDL2/SDL_ttf.h>
#include <string>
#include <map>

//The FontCache class is handling the loading of fonts and the unloading of fonts
class FontCache {
   public:
       FontCache();
       ~FontCache();
       
       TTF_Font* createFont(std::string filepath, int size);
       TTF_Font* getFont(std::string filepath);
       void disposeFont(std::string filepath);
       void clearCache();
   private:
       std::map<std::string, TTF_Font*> m_Fonts;
};
