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

#include "sheetcache.h"
#include "spritesheet.h"
#include <stdio.h>

//The constructor does nothing special,
//The destructor makes sure that the cache is emptied
SheetCache::SheetCache() {
    ;
}

SheetCache::~SheetCache() {
    clearCache();
}

SpriteSheet* SheetCache::createSheet(std::string filepath) {
    auto it = m_Sheets.find(filepath);
    if(it != m_Sheets.end()) {
        printf("ŚpriteSheet %s already existed!\n", filepath.c_str());
        return nullptr;
    } else {
        SpriteSheet* temp = new SpriteSheet;
        temp->loadSpriteSheet(filepath);
        m_Sheets[filepath] = temp;
        return temp;        
    }
    
    return nullptr;
}

SpriteSheet* SheetCache::getSheet(std::string filepath) {
    auto it = m_Sheets.find(filepath);
    if(it == m_Sheets.end()) {
        printf("Could not find SpriteSheet %s!\n", filepath.c_str());
        return nullptr; 
    }
    return m_Sheets[filepath];
}

void SheetCache::disposeSheet(std::string filepath) {
    auto it = m_Sheets.find(filepath);
    if(it != m_Sheets.end()) {
        delete it->second;
        m_Sheets.erase(it);
    } else {
        printf("SpriteSheet %s was not found so could not be deleted\n", filepath.c_str());
    }
}

void SheetCache::clearCache() {
    for(auto& it : m_Sheets) {
        delete it.second;
        it.second = nullptr;
    }
    m_Sheets.clear();
}









































