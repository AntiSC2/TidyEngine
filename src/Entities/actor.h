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
#include "../Components/component.h"
#include <string>
#include <vector>
#include <memory>

//This class represents a physical object that can be placed in the world
//This is a base class
class Actor {
    public:
        Actor();
        virtual ~Actor();

        std::string listComponents();
    protected:
         std::vector<std::unique_ptr<Component>> m_Components; 
};
