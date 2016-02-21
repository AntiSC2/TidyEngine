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
#include "../Graphics/draw.h"
#include <SDL2/SDL.h>
#include <string>

class Actor;

//This class represents a component that can be added to an actor
//To create a component, simply make another class inherit from this one
class Component {
	public:
		Component();
		virtual ~Component();
		virtual bool initialize(std::string name, Actor* parent = nullptr) = 0;
		virtual bool getUpdate() = 0;
		virtual bool getDraw() = 0;
		
		virtual void doCommand(std::string command);
		virtual void update();
		virtual void draw(Draw& draw, int x, int y);
		
		std::string getName() {
			return m_Name;
		}
	protected:
		std::string m_Name = "";
		Actor* m_Parent = nullptr;
};
