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

#include "actor.h"

Actor::Actor() {
	m_Position.x = 640;
	m_Position.y = 360;
}

Actor::Actor(float x, float y) {
	m_Position.x = x;
	m_Position.y = y;
}

Actor::~Actor() {
	;
}

void Actor::update() {
	for(size_t i = 0; i < m_Components.size(); i++) {
		if(m_Components[i]->getUpdate()) {
			m_Components[i]->update();
		} 
	}
}

void Actor::draw(Draw& draw) {
	for(size_t i = 0; i < m_Components.size(); i++) {
		if(m_Components[i]->getDraw()) {
		m_Components[i]->draw(draw, (int)m_Position.x,
			(int)m_Position.y);
		}
	}
}

void Actor::addComponent(Component* newComponent) {
	m_Components.emplace_back(newComponent);   
}

void Actor::moveActor(float newX, float newY) {
	m_Position.x = newX;
	m_Position.y = newY;
}

void Actor::moveActor(glm::vec2& newPosition) {
	m_Position = newPosition;
}

void Actor::doCommand(std::string nameComponent, std::string command) {
	for(size_t i = 0; i < m_Components.size(); i++) {
		if(m_Components[i]->getName() == nameComponent) {
        		m_Components[i]->doCommand(command);
		}
	}
}

std::string Actor::listComponents() {
	std::string temp = "";
	for(size_t i = 0; i < m_Components.size(); i++) {
		temp += m_Components[i]->getName();
		temp += '\n';
	}
	return temp;
}

glm::vec2 Actor::getPosition() {
	return m_Position;
}
