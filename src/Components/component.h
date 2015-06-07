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
#include <string>

//This class represents a component that can be added to an actor
//To create a component, simply make another class inherit from this one
class Component {
    public:
        Component();
        virtual ~Component();
        virtual bool initialize() = 0;
        virtual bool getUpdate() = 0;
        virtual bool getDraw() = 0;

        virtual void update();
        virtual void draw(SDL_Renderer* renderer);
  
        std::string getName() {
            return m_Name;
        }
    protected:
        std::string m_Name;       
};
