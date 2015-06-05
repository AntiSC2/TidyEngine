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

#include "cache.h"

//This is a static class so the constructor and destructor doesn't need to do everything
Cache::Cache() {
    ;
}

Cache::~Cache() {

}

//This is the texture cache
TexCache Cache::texCache;
SheetCache Cache::sheetCache;

//This function clears all caches
void Cache::clearAllCaches() {
    texCache.clearCache();
    sheetCache.clearCache();
}

//This function loads a block with textures
//A block is a part of a file that's marked out with a # in the start and a # in the end
//Between two # there should be filepaths to, in this case, textures
