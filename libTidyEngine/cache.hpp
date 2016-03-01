/*
TidyEngine
Copyright (C) 2016 Jakob Sinclair

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
Contact the author at: jakob.sinclair99@gmail.com
*/

#pragma once
#include <map>
#include <string>
#include "error.hpp"
#include "texture.hpp"
#include "iomanager.hpp"

class Cache {
public:
        Cache();
        ~Cache();

        const Texture &CreateTexture(std::string name, std::string filepath);
        void DeleteTexture(std::string name);
        const Texture &GetTexture(std::string name);
private:
        std::map<std::string, Texture> m_Textures;
} extern Resources;