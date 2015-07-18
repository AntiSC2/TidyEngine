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
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

//This class represents a physical object that can be placed in the world
//This is a base class
class Actor {
    public:
        Actor();
        Actor(float x, float y);
        virtual ~Actor();

        virtual void update();
        virtual void draw(SDL_Renderer* renderer);
        virtual void addComponent(Component* newComponent);
	virtual void moveActor(float newX, float newY);
	virtual void moveActor(glm::vec2& newPosition);
	void doCommand(std::string nameComponent, std::string command);
        std::string listComponents();
	glm::vec2 getPosition();
    protected:
        std::vector<std::unique_ptr<Component>> m_Components;
        glm::vec2 m_Position;
};
