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

#include "texcache.h"
#include <SDL2/SDL_image.h>

//The constructor does nothing special
//The destructor makes sure the textures are unloadeded.
TexCache::TexCache() {
    ;
}

TexCache::~TexCache() {
    clearCache();
}

//This function creates a new SDL_Texture and returns it, can return nullptr if
//Error 002 or Error 003 is triggered. If the texture already exists, the function
//simply returns it
SDL_Texture* TexCache::createTexture(std::string filepath, SDL_Renderer* renderer) {
    if(m_Textures.find(filepath) != m_Textures.end()) {
        return m_Textures[filepath];
    } 
    SDL_Texture* newTexture = nullptr;
    
    SDL_Surface* loadedSurface = IMG_Load(filepath.c_str());
    if(loadedSurface == nullptr) {
        printf("Error 002: Unable to load image %s! SDL_image Error: %s\n",
               filepath.c_str(), IMG_GetError());
        return nullptr;
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(newTexture == nullptr) {
            printf("Error 003: Unable to create texture from %s! SDL Error: %s\n",
                   filepath.c_str(), SDL_GetError());
            SDL_FreeSurface(loadedSurface);
            return nullptr;
        }
        SDL_FreeSurface(loadedSurface);
        m_Textures[filepath] = newTexture;
    }
    return newTexture;
}

//Returns the texture if found, else it returns a NULL pointer
SDL_Texture* TexCache::getTexture(std::string filepath) {
    if(m_Textures.find(filepath) != m_Textures.end())
        return m_Textures[filepath];
    else {
        printf("Could not find texture %s!\n", filepath.c_str());
    }
    return nullptr;
}

//Removes all the textures in this cache
void TexCache::clearCache() {
    for(auto& it : m_Textures) {
        SDL_DestroyTexture(it.second);
        it.second = nullptr;   
    }
    m_Textures.clear();
}
