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
#include "texcache.h"
#include "sheetcache.h"

//The cache class is the root of the resource manager system
//This class will handle loading, and unload, textures, sounds, fonts, music
//This is a static class

class Cache {
    public:
        Cache();
        ~Cache();
       
        static TexCache texCache;
        static SheetCache sheetCache;
        
        static bool loadTexturesFromBlock(std::string filepath, int start, SDL_Renderer* renderer);
        static void clearAllCaches();
    private:
        
}; 
