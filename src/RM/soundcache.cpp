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

#include "soundcache.h"

SoundCache::SoundCache() {
    ;
}

SoundCache::~SoundCache() {
    clearCache();
}

//This function creates a new SDL_Texture and returns it, can return nullptr if
//Error 002 or Error 003 is triggered. If the texture already exists, the function
//simply returns it
Mix_Chunk* SoundCache::createSound(std::string filepath) {
    if(m_SoundEffects.find(filepath) != m_SoundEffects.end()) {
        return m_SoundEffects[filepath];
    } 
    Mix_Chunk* newSound = nullptr;
    
    newSound = Mix_LoadWAV(filepath.c_str());
    if(newSound == nullptr) {
        printf("Error 005: Unable to load sound file %s! SDL_mixer Error: %s\n",
               filepath.c_str(), Mix_GetError());
        return nullptr;
    } else {
        m_SoundEffects[filepath] = newSound;
    }
    printf("Created new sound %s\n", filepath.c_str());
    return newSound;
}

//Returns the texture if found, else it returns a NULL pointer
Mix_Chunk* SoundCache::getSound(std::string filepath) {
    if(m_SoundEffects.find(filepath) != m_SoundEffects.end())
        return m_SoundEffects[filepath];
    else {
        printf("Could not find sound %s!\n", filepath.c_str());
    }
    return nullptr;
}

//Removes one texture
void SoundCache::disposeSound(std::string filepath) {
    auto it = m_SoundEffects.find(filepath);
    if(it != m_SoundEffects.end()) {
        Mix_FreeChunk(it->second);
        it->second = nullptr;
        m_SoundEffects.erase(it);    
    } else {
        printf("Could not find and remove %s!\n", filepath.c_str());
    }
}

//Removes all the textures in this cache
void SoundCache::clearCache() {
    for(auto& it : m_SoundEffects) {
        Mix_FreeChunk(it.second);
        it.second = nullptr;   
    }
    m_SoundEffects.clear();
}
