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

#include "fontcache.h"

//The constructor does nothing special
//The destructor makes sure the textures are unloadeded.
FontCache::FontCache() {
	;
}

FontCache::~FontCache() {
	clearCache();
}

//This function creates a new font and returns it, can return nullptr if
//Error 006 is triggered. If the font already exists, the function
//simply returns it
TTF_Font* FontCache::createFont(std::string filepath, int size) {
	if(m_Fonts.find(filepath) != m_Fonts.end()) {
		return m_Fonts[filepath];
	} 
	m_Fonts[filepath] = nullptr;
	m_Fonts[filepath] = TTF_OpenFont(filepath.c_str(), size);
	if(m_Fonts[filepath] == nullptr) {
		printf("Error 006: Could not load font %s", filepath.c_str());
		return nullptr;
	}
	return m_Fonts[filepath];
}

//Returns the font if found, else it returns a NULL pointer
TTF_Font* FontCache::getFont(std::string filepath) {
	if(m_Fonts.find(filepath) != m_Fonts.end())
		return m_Fonts[filepath];
	else {
		printf("Could not find font %s!\n", filepath.c_str());
		return nullptr;
	}
	return nullptr;
}

//Removes one font
void FontCache::disposeFont(std::string filepath) {
	auto it = m_Fonts.find(filepath);
	if(it != m_Fonts.end()) {
		TTF_CloseFont(it->second);
		it->second = nullptr;
		m_Fonts.erase(it);    
	} else {
		printf("Could not find and remove %s!\n", filepath.c_str());
	}
}

//Removes all the fonts in this cache
void FontCache::clearCache() {
	for(auto& it : m_Fonts) {
		TTF_CloseFont(it.second);
		it.second = nullptr;   
	}
	m_Fonts.clear();
}
