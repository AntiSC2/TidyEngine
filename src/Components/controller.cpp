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

#include "controller.h"
#include "../Entities/actor.h"

Controller::Controller() {
	;
}

Controller::~Controller() {
	;
}

bool Controller::initialize(std::string name, Actor* parent) {
	m_Name = name;
	m_Parent = parent;
	return (m_Parent != nullptr);
}

bool Controller::getUpdate() {
	return true; 
}

bool Controller::getDraw() {
	return false;
}

void Controller::doCommand(std::string command) {
	;
}

void Controller::update() {
	if(m_Parent != nullptr) {
			if(m_Input->getKeyPressed(SDL_SCANCODE_W)) {
			glm::vec2 temp = m_Parent->getPosition();
			temp.y -= 0.1f;
			m_Parent->moveActor(temp);
			m_Parent->doCommand("sprite", "stop");
		}

		if(m_Input->getKeyPressed(SDL_SCANCODE_S)) {
			glm::vec2 temp = m_Parent->getPosition();
			temp.y += 0.1f;
			m_Parent->moveActor(temp);
		}
	}
}

void Controller::setInputReference(Input& inputReference) {
    	m_Input = &inputReference;
}
