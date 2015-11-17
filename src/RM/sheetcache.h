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
#include <string>
#include <map>

class SpriteSheet;

//The SheetCache handles the SpriteSheets to make it easier for sprites to get a reference
class SheetCache {
	public:
		SheetCache();
		~SheetCache();

		SpriteSheet* createSheet(std::string filepath);
		SpriteSheet* getSheet(std::string filepath);

		void disposeSheet(std::string filepath);
		void clearCache(); 
	private:
		std::map<std::string, SpriteSheet*> m_Sheets;
};
