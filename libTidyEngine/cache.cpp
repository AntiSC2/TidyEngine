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

#include "cache.hpp"

Cache Resources;

Cache::Cache()
{
        ;
}

Cache::~Cache()
{
        for (auto it : m_Textures)
                it.second.DeleteTex();
}

const Texture &Cache::CreateTexture(std::string name,std::string filepath)
{
        if (m_Textures.find(name) == m_Textures.end()) {
                FIBITMAP *bitmap = IO.LoadImage(filepath);
                bool success = m_Textures[name].CreateTex(bitmap, true, true);
                if (success == false) {
                        Error e("Exception: could not create texture " +
                                        filepath);
                        throw e;
                }
                FreeImage_Unload(bitmap);
                return m_Textures[name];
        } else {
                printf("Warning: a texture with the name %s already exists!\n",
                                name.c_str());
                return m_Textures[name];
        }
}

void Cache::DeleteTexture(std::string name)
{
        m_Textures[name].DeleteTex();
        m_Textures.erase(name);
}

const Texture &Cache::GetTexture(std::string name)
{
        if (m_Textures.find(name) != m_Textures.end())
                return m_Textures[name];
        Error e("Exception: could not find texture with the name " + name);
        throw e;
}