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

#include "iomanager.hpp"
#include <FreeImage.h>
#include <string>
#include <fstream>

IOManager IO;

IOManager::IOManager()
{
        ;
}

IOManager::~IOManager()
{

}

FIBITMAP *IOManager::LoadImage(std::string filepath)
{
        if (filepath.find(".png") != std::string::npos)
                return FreeImage_Load(FIF_PNG, filepath.c_str(), PNG_DEFAULT);
        else if (filepath.find(".bmp") != std::string::npos)
                return FreeImage_Load(FIF_BMP, filepath.c_str(), BMP_DEFAULT);
        else if (filepath.find(".jpeg") != std::string::npos)
                return FreeImage_Load(FIF_JPEG, filepath.c_str());
        printf("Warning: image %s has an unsupported file format!",
                       filepath.c_str());
        return nullptr;
}

std::string IOManager::ReadFile(std::string filepath)
{
        std::ifstream source(filepath);
        if (source.fail()) {
                printf("Warning: failed to open %s!\n", filepath.c_str());
                return "";
        }

        std::string source_contents = "";
        std::string line = "";

        while (std::getline(source, line))
                source_contents += line + '\n';

        source.close();
        return source_contents;
}
