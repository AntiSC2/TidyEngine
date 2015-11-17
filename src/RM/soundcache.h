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
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <map>

//The SoundCache class is handling the loading of sound effects and unloading of sound effects
class SoundCache {
	public:
		SoundCache();
		~SoundCache();

		Mix_Chunk* createSound(std::string filepath);
		Mix_Chunk* getSound(std::string filepath);
		void disposeSound(std::string filepath);
		void clearCache();
	private:
		std::map<std::string, Mix_Chunk*> m_SoundEffects;
};
